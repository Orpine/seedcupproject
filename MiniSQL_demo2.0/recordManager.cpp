#include"bufferManager.h"
#include"recordManager.h"

#include<iostream>
using namespace std;

// ------------------------------- basic function ---------------------------------------
char* recordManager::record_to_array(record new_record, int& size)
{
	size=0;
	int record_num;
	for (record_num=0;record_num<new_record.attribute_count;record_num++)
	{
		if (new_record.value[record_num].type_no==0)
		{
			size+=new_record.value[record_num].char_count;	
		}
		else
		{
			size+=4;
		}

	}
	size=size+4*6;
	char* record_array=new char[size];
	char* record_pointer=record_array;
	for (record_num=0;record_num<new_record.attribute_count;record_num++)
	{
		if (new_record.value[record_num].type_no==0)
		{
			for (int tempi=0;tempi<new_record.value[record_num].char_count;tempi++,record_array++)
			{
				*record_array=new_record.value[record_num].char_value[tempi];
			}
		}
		else if (new_record.value[record_num].type_no==1)
		{
			*((float *)record_array)=new_record.value[record_num].float_value;
			record_array+=4;
		}
		else if (new_record.value[record_num].type_no==2)
		{
			*((int *)record_array)=new_record.value[record_num].int_value;
			record_array+=4;
		}
	}
	return  record_pointer;
}

record* recordManager::array_to_record(char* record_pointer,table_info record_info)
{
	record* return_record = new record;
	(*return_record).attribute_count=record_info.attribute_count;
	for(int i=0;i<record_info.attribute_count;i++)
	{
		if(record_info.info[i].type=="int")
		{
			(*return_record).value[i].int_value=*((int *)record_pointer);
			(*return_record).value[i].type_no=2;
			record_pointer+=4;
		}
		else if (record_info.info[i].type=="text")
		{
			(*return_record).value[i].char_value= new char[record_info.info[i].type_count];
			(*return_record).value[i].char_count=record_info.info[i].type_count;
			char *p = (*return_record).value[i].char_value;
			for(int j = 0; j < record_info.info[i].type_count; j++)
				p[j] = record_pointer[j];
			record_pointer+=record_info.info[i].type_count;
			(*return_record).value[i].type_no=0;
		}
		else if (record_info.info[i].type=="float")
		{
			(*return_record).value[i].float_value=*((float *)record_pointer);
			(*return_record).value[i].type_no=1;
			record_pointer+=4;
		}		
	}
	return return_record;
}


// -------------------------------- user interface function ------------------------------
CArray<record, record&>* 
recordManager::readRecords(CString table_name, table_info tableInfo, CArray<condition, condition&>* cp)
{
	if(cp == NULL)
	{
		address add, headadd;
		CArray<record, record&>* rp = new CArray<record, record&>;
		bmp->findTableEntry(table_name, add);
		if(add.block_position == -1 || add.index_position == -1)
		{
			delete rp;
			return NULL;
		}

		headadd = add;
		int size;
		char* content;
		record* p;
		
		add = bmp->nextRecordPosition(add);
		if(add.block_position != -1 && add.index_position != -1)
		{
			while(add.block_position != headadd.block_position || add.index_position != headadd.index_position)
			{
				content = bmp->readData(add,size);
				p = array_to_record(content, tableInfo);
				p->position = add;
				rp->Add(*p);
				delete [] content;
				add = bmp->nextRecordPosition(add);
			}
			return rp;
		}
		else
		{
			delete rp;
			return NULL;
		}
	}
	else
	{
		address add, headadd;
		CArray<record, record&>* rp = new CArray<record, record&>;
		bmp->findTableEntry(table_name, add);
		if(add.block_position == -1 || add.index_position == -1)
		{
			delete rp;
			return NULL;
		}
		
		headadd = add;
		int size;
		char* content;
		record* p;
		
		add = bmp->nextRecordPosition(add);
		if(add.block_position != -1 && add.index_position != -1)
		{
			while(add.block_position != headadd.block_position || add.index_position != headadd.index_position)
			{
				content = bmp->readData(add,size);
				p = array_to_record(content, tableInfo);			
	

				p->position = add;
				for(int i = 0; i < cp->GetSize(); i++)
				{
					attribute_value av = p->value[(*cp)[i].item1];
					if(!(*cp)[i].statisfy(av))
						break;
				}
				if(i == cp->GetSize())
					rp->Add(*p);
				
				delete [] content;
				add = bmp->nextRecordPosition(add);
			}
			return rp;
		}
		else
		{
			delete rp;
			return NULL;
		}
	}
}



void recordManager::storeRecord(CString table_name, record data)
{
	char* head;
	int size;
	head = record_to_array(data, size);
	bmp->addRecord(table_name, head, size);
	delete [] head;
}



void 
recordManager::rmRecord(CString table_name, table_info* tableInfo, CArray<condition, condition&>* cp)
{
	CArray<record, record&>* rp;
	if(cp == NULL)
	{
		address headAdd, add, nextAdd;
		bmp->findTableEntry(table_name, headAdd);
		if(headAdd.block_position == -1 || headAdd.index_position == -1)
			return;
		else
		{
			add = bmp->nextRecordPosition(headAdd);
			if(add.block_position != -1 && add.index_position != -1)
			{
				while(headAdd.block_position != add.block_position 
					|| headAdd.index_position != add.index_position)
				{
					int i = bmp->readBlockFromDisk(add.block_position);
					bmp->buffer[i].getRecordNextLink(add.index_position, nextAdd);
					bmp->buffer[i].rmData(add.index_position);
					add = nextAdd;
				}
				bmp->rmTableEntry(table_name);
			}
			else
				bmp->rmTableEntry(table_name);
		}
	}
	else
	{
		rp = readRecords(table_name, *tableInfo, cp);
		if(rp != NULL)
		{
			for(int i = 0; i < rp->GetSize(); i++)
			{
				bmp->rmRecord((*rp)[i].position);
			}
			delete rp;
		}
	}
}