#include"block.h"
#include"DBFile.h"
#include"basichead.h"

// --------------------------------- block info function -------------------------------
int block::getRecordNum()
{
	int temp;
	temp = ((int *)space)[0];
	return temp;
}

void block::setRecordNum(int num)
{
	((int*)space)[0] = num;
}

int block::getFreeSpaceEnd()
{
	return ((int *)space)[1];
}

void block::setFreeSpaceEnd(int end)
{
	((int*)space)[1] = end;
}

void block::setDataSize(int index, int size)
{
	((int*)space)[2+2*index] = size;
}

int block::getDataSize(int index)
{
	return ((int*)space)[2+2*index];
}

void block::setDataPoint(int index, int position)
{
	((int*)space)[2+2*index+1] = position;
}

int block::getDataPoint(int index)
{
	return ((int*)space)[2+2*index+1];
}



// ------------------------------- block basic function -----------------------------------

block::block()
{
	block_position = -1;
	last_use = CTime::GetCurrentTime();
	valid = 0;
	modified = 0;
	setRecordNum(0);
	setFreeSpaceEnd(BLOCKSIZE - 1);
	file = NULL;
}

block::~block()
{
}

bool block::canHoldTheSize(int data_size)
{
	int left = getFreeSpaceEnd();
	int num = getRecordNum();
	left = left + 1 - 2*4 - 2*num*4;
	return left >= data_size + 4*2;
}

int block::addData(char* data, int data_size)
{
	if(canHoldTheSize(data_size) == 0)
		return -1;

	int total = getRecordNum();
	for(int i = 0; i < total; i++)
		if(getDataSize(i) == 0)
			break;
	if(i != total)
	{
		int index = i;
		setDataSize(i,data_size);
		int FreeSpaceEnd = getFreeSpaceEnd();
		FreeSpaceEnd = FreeSpaceEnd - data_size;
		setFreeSpaceEnd(FreeSpaceEnd);
		setDataPoint(i,FreeSpaceEnd + 1);
		for(i = 0; i < data_size; i++)
			space[FreeSpaceEnd + 1 + i] = data[i];
		last_use = CTime::GetCurrentTime();
		modified = 1;
		return index;
	}
	else
	{
		setRecordNum(total+1);
		setDataSize(total,data_size);
		int FreeSpaceEnd = getFreeSpaceEnd();
		FreeSpaceEnd = FreeSpaceEnd - data_size;
		setFreeSpaceEnd(FreeSpaceEnd);
		setDataPoint(total,FreeSpaceEnd + 1);
		for(i = 0; i < data_size; i++)
			space[FreeSpaceEnd + 1 + i] = data[i];
		last_use = CTime::GetCurrentTime();
		modified = 1;
		return total;
	}
}

void block::getData(int index, char* container)
{
	int size = getDataSize(index);

	int length = 0;
	int p = getDataPoint(index);
	int end = p + getDataSize(index) - 1;
	for(; p <= end; p++, length++)
		container[length] = space[p];
	last_use = CTime::GetCurrentTime();
}

int compare(const void*, const void*);
void block::rmData(int index)
{
	int total = getRecordNum();
	if(index >= total)
		return;
	
	if(getDataSize(index) == 0)
		return;

	int oldSize = getDataSize(index);
	setDataSize(index,0);
	int current = getDataPoint(index);

	int size = 0;
	item* array = new item[total];
	for(int i =0; i < total; i++)
	{
		int p = getDataPoint(i);
		int s = getDataSize(i);
		if(s != 0 && p < current)
		{
			array[size].index = i;
			array[size].size = s;
			array[size].point = p;
			size++;
		}
	}	
	
	int temp;
	if(size != 0)
	{
		qsort((void *)array,size,sizeof(item), compare);
#ifdef DEBUG
	for(int i = 0; i < size; i++)
		cout << "[" << array[i].index << "," << array[i].point << "]" << endl;
#endif	
		for(i = size - 1; i >= 0; i--)
		{
			if(i == size - 1)
			{
				temp = current + oldSize - array[i].size;
				for(int j = 1; j <= array[i].size; j++)
					space[current+oldSize-j] = space[array[i].point+array[i].size-j]; 
				setDataPoint(array[i].index,temp);
			}
			else
			{
				for(int j = 1; j <= array[i].size; j++)
					space[temp - j] = space[array[i].point + array[i].size - j];
				temp = temp - array[i].size;
				setDataPoint(array[i].index,temp);
			}
		}
	}
	delete array;
	if(size != 0)
		setFreeSpaceEnd(temp-1);
	else
		setFreeSpaceEnd(current+oldSize-1);
	if(index == total - 1)
		setRecordNum(total - 1);
	last_use = CTime::GetCurrentTime();
	modified = 1;
}

int compare(const void * a, const void * b)
{
	return ((item *)a)->point > ((item *)b)->point;
}

void block::saveToDisk()
{
	if(file == NULL)
		return;
	if(valid && modified)
	{
		if(block_position != -1)
		{
			file->Seek(BLOCKSIZE*block_position,CFile::begin);
			file->Write((void*)space,BLOCKSIZE);
		}
	}
}

void block::getFromDisk(int block_position, CFile* file)
{
	if((unsigned int)block_position >= file->GetLength()/BLOCKSIZE)
	{
		this->block_position = -1;
		return;
	}
	this->file = file;
	file->Seek(block_position*BLOCKSIZE,CFile::begin);
	file->Read(space,BLOCKSIZE);
	this->block_position = block_position;
	last_use = CTime::GetCurrentTime();
	valid = 1;
	modified = 0;
}

// ----------------------------- data link function -------------------------------------

void block::setNextLink(int index, address next)
{
	int p, size;
	p = getDataPoint(index);
	size = getDataSize(index);
	p = p + size - 8;
	((int *)(space + p))[0] = next.block_position;
	((int *)(space + p))[1] = next.index_position;
	last_use = CTime::GetCurrentTime();
	modified = 1;
}

void block::getNextLink(int index, address& next)
{	
	int p, size;
	p = getDataPoint(index);
	size = getDataSize(index);
	p = p + size - 8;
	next.block_position = ((int *)(space + p))[0];
	next.index_position = ((int *)(space + p))[1];
	last_use = CTime::GetCurrentTime();
}

void block::setRecordNextLink(int index, address next)
{
	int p, size;
	p = getDataPoint(index);
	size = getDataSize(index);
	p = p + size - 16;
	((int *)(space + p))[0] = next.block_position;
	((int *)(space + p))[1] = next.index_position;
	last_use = CTime::GetCurrentTime();
	modified = 1;
}

void block::getRecordNextLink(int index, address& next)
{
	int p, size;
	p = getDataPoint(index);
	size = getDataSize(index);
	p = p + size - 16;
	next.block_position = ((int *)(space + p))[0];
	next.index_position = ((int *)(space + p))[1];
	last_use = CTime::GetCurrentTime();
}

void block::setRecordFrontLink(int index, address front)
{
	int p, size;
	p = getDataPoint(index);
	size = getDataSize(index);
	p = p + size - 24;
	((int *)(space + p))[0] = front.block_position;
	((int *)(space + p))[1] = front.index_position;
	last_use = CTime::GetCurrentTime();
	modified = 1;
}

void block::getRecordFrontLink(int index, address& front)
{
	int p, size;
	p = getDataPoint(index);
	size = getDataSize(index);
	p = p + size - 24;
	front.block_position = ((int *)(space + p))[0];
	front.index_position = ((int *)(space + p))[1];
	last_use = CTime::GetCurrentTime();
}

void block::setIndexNext(int index, address next)
{
	setRecordNextLink(index, next);
}

void block::getIndexNext(int index, address next)
{
	getRecordNextLink(index, next);
}