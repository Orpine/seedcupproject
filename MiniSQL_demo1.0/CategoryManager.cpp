#include"basichead.h"
#include"CategoryManager.h"
#include"bufferManager.h"

char* categoryManager::transformTableInfo(table_info a, int& count)
{
	int size[32];
	int table_size, attribute_size = 0;
	for(int i = 0; i < a.attribute_count; i++)
	{
	     size[i] = a.info[i].attribute_name.GetLength() + a.info[i].type.GetLength() + sizeof(int) + sizeof(char)*2 + 2;
	}

	for(i = 0; i < a.attribute_count; i++)
		attribute_size += size[i];
    table_size = a.table_name.GetLength() + a.primary_key.GetLength() + a.attribute_count*sizeof(int) + attribute_size + 2 +8;
		
    char* b = new char[table_size];
	char* p = b;
	_tcscpy(p, a.table_name);
	p += a.table_name.GetLength();
	*p = '\0';
	p += 1;
    _tcscpy(p, a.primary_key);
    p += a.primary_key.GetLength();
	*p = '\0';
    p += 1;
	
		
	for(i=0; i < a.attribute_count; i++)
	{	
		*((int*)p) = size[i];
		p += 4; 
        	_tcscpy(p, a.info[i].attribute_name);
		p += a.info[i].attribute_name.GetLength();
 		*p = '\0';
		p += 1;
       		*p = (char)a.info[i].unique;
		p += 1;
		_tcscpy(p, a.info[i].type);
		p += a.info[i].type.GetLength();
		*p = '\0';
		p += 1;
		*((int*)p) = a.info[i].type_count;
		p += 4;
        	*p = (char)a.info[i].has_index;
		p += 1;
	}
    count = table_size;
	return b;
}

table_info categoryManager::transformArrayToTableInfo(char* b, int count)
{
	table_info a;
	int i, k;
	int size, upper;
	for(i = 0; i < count && *(b + i) != '\0'; i++)
    {
        a.table_name += *(b + i);
	}
    for(i += 1; i < count && *(b + i) != '\0' ; i++) 
    {
		a.primary_key += *(b + i);
	}
	i += 1; 

	for(k = 0; i < count; i++,k++)
	{
		size = *((int*)(b + i));
		i += 4;
		upper = i + size;
		for(; i < upper && *(b + i) != '\0'; i++)
       	{
			a.info[k].attribute_name += *(b + i);
		}

		i += 1;
		a.info[k].unique = (*(b + i)) == 1 ? true : false;

        for(i += 1; i < upper && *(b + i) != '\0'; i++)
        {
			a.info[k].type += *(b + i);			
		}
		i += 1;
		a.info[k].type_count = *((int*)(b + i));
		i += 4;
		a.info[k].has_index = (*(b + i)) == 1 ? true : false;
	}
	a.attribute_count = k - 1;
	return a;
} 

void categoryManager::saveTable(table_info a)
{
	int arrysize;
	char* p = transformTableInfo(a, arrysize);
	bmp->addInfo(p, arrysize);
	delete [] p;
}


bool categoryManager::readTable(CString table_name, table_info& tableInfo)
{
	int arrysize;
	char* p;
	
	p = bmp->readInfo(table_name, arrysize);
	if(arrysize != -1)
	{
		tableInfo = transformArrayToTableInfo(p, arrysize);
		return true;
	}
	else
		return false;
}

void categoryManager::dropTable(CString table_name)
{
	bmp->rmInfo(table_name);
}