#include"basichead.h"
#include"bufferManager.h"

// --------------------------- basic buffer function --------------------------

bufferManager::bufferManager()
{
	bufferContainer.clear();
}

bufferManager::~bufferManager()
{
	for(int i = 0; i < 100; i++)
		buffer[i].saveToDisk();
}

int bufferManager::findReplaceBlock()
{	
	int replace_position = 0;
	CTime earliest_time = buffer[0].getUseTime();
	for(int i = 0; i < 100; i++)
	{
		if(!buffer[i].IsValid())
			break;
		if(earliest_time > buffer[i].getUseTime())
		{
			replace_position = i;
			earliest_time = buffer[i].getUseTime();
		}
	}
	if(i != 100)
		return i;
	else
		return replace_position;
}

int bufferManager::readBlockFromDisk(int block_position)
{
	std::set<int>::const_iterator cit;
	cit = bufferContainer.find(block_position);
	if(cit != bufferContainer.end())
	{
		for(int i = 0; i < 100; i++)
			if(buffer[i].getBlockPosition() == block_position)
				return i;
	}

	int i = findReplaceBlock();

	buffer[i].saveToDisk();
	if(buffer[i].IsValid())
		bufferContainer.erase(buffer[i].getBlockPosition());
	buffer[i].getFromDisk(block_position, &file.m_file);
	bufferContainer.insert(block_position);
	return i;
}

// ----------------------------- user interface function -------------------------------

int bufferManager::storeData(char* head, int size, address& return_value)
{
	int replace_position = 0;
	CTime earliest_time = buffer[0].getUseTime();
	for(int i = 0; i < 100; i++)
	{
		if(!buffer[i].IsValid() || 
			(buffer[i].canHoldTheSize(size) && buffer[i].getBlockPosition() != 0))
			break;
		if(earliest_time > buffer[i].getUseTime())
		{
			replace_position = i;
			earliest_time = buffer[i].getUseTime();
		}
	}
	if(i != 100)
	{
		if(buffer[i].IsValid())
		{
			return_value.block_position = buffer[i].getBlockPosition();
			return_value.index_position = buffer[i].addData(head,size);
		}
		else
		{
			int free_block = 0;
			std::set<int>::const_iterator cit;
			while(1)
			{
				free_block = file.findEnoughSpace(free_block + 1, size);
				cit = bufferContainer.find(free_block);
				if(cit == bufferContainer.end())
					break;
			}
			buffer[i].getFromDisk(free_block, &file.m_file);
			bufferContainer.insert(free_block);
			return_value.block_position = free_block;
			return_value.index_position = buffer[i].addData(head, size);
		}
		return i;
	}
	else
	{
		int free_block = 0;
		std::set<int>::const_iterator cit;
		while(1)
		{
			free_block = file.findEnoughSpace(free_block + 1, size);
			cit = bufferContainer.find(free_block);
			if(cit == bufferContainer.end())
				break;
		}		
		buffer[replace_position].saveToDisk();
		bufferContainer.erase(buffer[replace_position].getBlockPosition());
		buffer[replace_position].getFromDisk(free_block, &file.m_file);
		bufferContainer.insert(free_block);
		return_value.block_position = free_block;
		return_value.index_position = buffer[replace_position].addData(head, size);
		return replace_position;
	}
}


char* bufferManager::readData(address position, int& size)
{
	int i = readBlockFromDisk(position.block_position);
	char* head;
	size = buffer[i].getDataSize(position.index_position);
	head = new char[size];
	buffer[i].getData(position.index_position, head);
	return head;
}

void bufferManager::rmData(address position)
{
	int i = readBlockFromDisk(position.block_position);
	buffer[i].rmData(position.index_position);
}

int bufferManager::addTableEntry(CString table_name, address &return_value)
{
	int size = 0;
	size = table_name.GetLength() + 1 + 6*sizeof(int);
	char* tableEntryHead = new char[size];
	for(int i = 0; i < table_name.GetLength(); i++)
		tableEntryHead[i] = table_name.GetAt(i);
	tableEntryHead[i++] = '\0';
	((int *)(tableEntryHead + i))[0] = ((int *)(tableEntryHead + i))[1]
		= ((int *)(tableEntryHead + i))[2] = ((int *)(tableEntryHead + i))[3]
		= ((int *)(tableEntryHead + i))[4] = ((int *)(tableEntryHead + i))[5]
		= -1;

	int j = storeData(tableEntryHead, size, return_value);
	i = readBlockFromDisk(0);
	address head_add;
	buffer[i].getData(0,(char *)&head_add);
	buffer[j].setNextLink(return_value.index_position, head_add);
	buffer[i].setNextLink(0,return_value);
	delete [] tableEntryHead;
	return j;
}


// --------------------------- advanced interface function -------------------------------

// ***********************  tableInfo functions *****************************
void bufferManager::addInfo(char* head, int size)
{
	address store_add;
	int j = storeData(head,size,store_add);
	int i = readBlockFromDisk(0);
	address head_add;
	buffer[i].getData(1,(char *)&head_add);
	buffer[j].setNextLink(store_add.index_position, head_add);
	buffer[i].setNextLink(1,store_add);
}

char* bufferManager::readInfo(CString table_name, int& size)
{	
	int num;
	CString a;
	address addr;
	char* info;

    addr.block_position = 0;
	addr.index_position = 1;
	num = readBlockFromDisk(addr.block_position);
    buffer[num].getNextLink(addr.index_position,addr);
	
    while (addr.index_position != -1)
	{
	   num = readBlockFromDisk(addr.block_position);
	   size = buffer[num].getDataSize(addr.index_position);
       info = new char[size];
       buffer[num].getData(addr.index_position, info);
	   a = info;
       if (a == table_name)
		   break;
	   else
		   delete [] info;
       buffer[num].getNextLink(addr.index_position,addr);
	}

	if (addr.index_position == -1)
	{
	    size = -1;
     	info = NULL;
	}
	return info;
}

void bufferManager::rmInfo(CString table_name)
{
	int i = readBlockFromDisk(0);
	address add;
	buffer[i].getNextLink(1,add);

	address oldAdd, nextAdd;
	CString name;
	int size;
	oldAdd.block_position = 0;
	oldAdd.index_position = 1;
	int j;
	while(add.block_position != -1 && add.index_position != -1)
	{
		j = readBlockFromDisk(add.block_position);
		size = buffer[j].getDataSize(add.index_position);
		char* TableInfo = new char[size];
		buffer[j].getData(add.index_position,TableInfo);
		buffer[j].getNextLink(add.index_position,nextAdd);
		name = TableInfo;
		if(name == table_name)
		{
			int front = readBlockFromDisk(oldAdd.block_position);
			buffer[front].setNextLink(oldAdd.index_position, nextAdd);
			rmData(add);
			delete [] TableInfo;
			break;
		}
		delete [] TableInfo;
		oldAdd.block_position = add.block_position;
		oldAdd.index_position = add.index_position;
		add.block_position = nextAdd.block_position;
		add.index_position = nextAdd.index_position;
	}
}


//  ****************************** record functions **********************************

void bufferManager::findTableEntry(CString table_name, address& return_value)
{
	int i = readBlockFromDisk(0);
	address add;
	buffer[i].getData(0, (char *)&add);

	CString table;
	int size;
	char* tableEntry;
	while(add.block_position != -1 && add.index_position != -1)
	{
		tableEntry = readData(add, size);	
		table = tableEntry;
		if(table == table_name)
			break;
		add.block_position = ((int *)(tableEntry + size - 8))[0];
		add.index_position = ((int *)(tableEntry + size - 8))[1];
		delete [] tableEntry;
	}
	return_value.block_position = add.block_position;
	return_value.index_position = add.index_position;
}

void bufferManager::rmTableEntry(CString table_name)
{
	address add, oldAdd, nextAdd;
	oldAdd.block_position = 0;
	oldAdd.index_position = 0;
	int i = readBlockFromDisk(0);
	buffer[i].getNextLink(0,add);
	CString name;
	while(add.block_position != -1 && add.index_position != -1)
	{
		char* content;
		int size;
		content = readData(add, size);
		name = content;
		nextAdd.block_position = ((int *)(content + size - 8))[0];
		nextAdd.index_position = ((int *)(content + size - 8))[1];
		if(name == table_name)
		{
			int j = readBlockFromDisk(oldAdd.block_position);
			buffer[j].setNextLink(oldAdd.index_position, nextAdd);
			int m = readBlockFromDisk(add.block_position);
			buffer[m].rmData(add.index_position);
			break;
		}
		delete [] content;
		oldAdd = add;
		add = nextAdd;
	}
}

void bufferManager::addRecord(CString table_name, char* head, int size)
{
	address add, dataAdd, nextAdd;
	findTableEntry(table_name, add);
	if(add.block_position == -1 && add.index_position == -1)
	{
		int i = addTableEntry(table_name,add);
		int j = storeData(head,size,dataAdd);
		buffer[i].setRecordFrontLink(add.index_position, dataAdd);
		buffer[i].setRecordNextLink(add.index_position, dataAdd);
		buffer[j].setRecordFrontLink(dataAdd.index_position, add);
		buffer[j].setRecordNextLink(dataAdd.index_position, add);
	}
	else
	{
		int i = readBlockFromDisk(add.block_position);
		buffer[i].getRecordNextLink(add.index_position, nextAdd);
		if(nextAdd.block_position != -1 && nextAdd.index_position != -1)
		{
			int j = storeData(head, size, dataAdd);
			buffer[i].getRecordNextLink(add.index_position, nextAdd);
			int m = readBlockFromDisk(nextAdd.block_position);

			buffer[j].setRecordFrontLink(dataAdd.index_position, add);
			buffer[j].setRecordNextLink(dataAdd.index_position, nextAdd);
			buffer[i].setRecordNextLink(add.index_position, dataAdd);
			buffer[m].setRecordFrontLink(nextAdd.index_position, dataAdd);
		}
		else
		{
			int j = storeData(head, size, dataAdd);
			buffer[j].setRecordFrontLink(dataAdd.index_position, add);
			buffer[j].setRecordNextLink(dataAdd.index_position, add);
			buffer[i].setRecordFrontLink(add.index_position, dataAdd);
			buffer[i].setRecordNextLink(add.index_position, dataAdd);
		}
	}
}

address bufferManager::nextRecordPosition(address currentAdd)
{
	address nextAdd;
	int i = readBlockFromDisk(currentAdd.block_position);
	buffer[i].getRecordNextLink(currentAdd.index_position, nextAdd);
	return nextAdd;
}

void bufferManager::rmRecord(address add)
{
	int i = readBlockFromDisk(add.block_position);
	address frontAdd, nextAdd, end;
	end.block_position = end.index_position = -1;
	buffer[i].getRecordFrontLink(add.index_position, frontAdd);
	buffer[i].getRecordNextLink(add.index_position, nextAdd);
	if(frontAdd.block_position == nextAdd.block_position && 
		frontAdd.index_position == nextAdd.index_position)
	{
		buffer[i].rmData(add.index_position);
		i = readBlockFromDisk(frontAdd.block_position);
		buffer[i].setRecordFrontLink(frontAdd.index_position, end);
		buffer[i].setRecordNextLink(frontAdd.index_position, end);
	}
	else
	{
		buffer[i].rmData(add.index_position);
		i = readBlockFromDisk(frontAdd.block_position);
		buffer[i].setRecordNextLink(frontAdd.index_position, nextAdd);
		int j = readBlockFromDisk(nextAdd.block_position);	
		buffer[j].setRecordFrontLink(nextAdd.index_position, frontAdd);
	}
}