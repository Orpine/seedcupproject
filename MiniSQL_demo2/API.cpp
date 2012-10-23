#include "API.h"
#include "Catalog_Manager.h"
#include "Record_Manager.h"
#include "Interpreter.h"

void API()
{
	//cout << "Welcome to API(SQL_CMD) !" << endl;
	
	switch(opType)
	{
		//创建表单
		case CREATE_TABLE_OP_TYPE	:
			if(!API_Create_Table())
				cout << error_info << endl;
			break;
		//创建索引
		case CREATE_INDEX_OP_TYPE	:
			if(!API_Create_Index())
				cout << error_info << endl;		
			break;
		//删除表单
		case DROP_TABLE_OP_TYPE	:
			if(!API_Drop_Table())
				cout << error_info << endl;
			break;
		//删除索引
		case DROP_INDEX_OP_TYPE	:
			if(!API_Drop_Index())
				cout << error_info << endl;
			break;
		//插入一条记录
		case INSERT_OP_TYPE	:
			if(!API_Insert())
				cout << error_info << endl;
			break;
		//没有条件的选择纪录
		case SELECT_ALL_OP_TYPE	:
			if(!API_Select())
				cout << error_info << endl;
			break;
		//有条件的选择纪录
		case SELECT_WHERE_OP_TYPE	:
			if(!API_Select())
				cout << error_info << endl;
			break;
		//没有条件的删除纪录
		case DELETE_ALL_OP_TYPE	:
			if(!API_Delete())
				cout << error_info << endl;
			break;
		//有条件的删除纪录
		case DELETE_WHERE_OP_TYPE	:
			if(!API_Delete())
				cout << error_info << endl;
			break;
		//
		default	:
			break;
	}
	
}

bool API_Create_Table()
{
	if(!Create_Table(table))
		return false;
	
	return true;
}

bool API_Drop_Table()
{
	if(!Drop_Table(table_name))
		return false;
	
	return true;
}

bool API_Create_Index()
{
	if(!Create_Index(index))
		return false;
	
	return true;
}

bool API_Drop_Index()
{
	if(!Drop_Index(index_name))
		return false;
	
	return true;
}

void Read_Table_Info()
{
	string tableInfo = table.table_name + ".info";
	ifstream fin;
	fin.open(tableInfo.c_str(), ios::in);
	table.attr_count = 0;
	//读表的信息
	char attr_temp[MAX_ATTRNAME_LENGTH];
	string attr;
	while(!fin.eof())
	{
		fin.getline(attr_temp, MAX_ATTRNAME_LENGTH);
		attr = attr_temp;
		if(attr == "" && fin.eof())
			break;
		
		table.attrs[table.attr_count].attr_name = Get_Word(attr, 1);
		parse_to_int(Get_Word(attr, 2), table.attrs[table.attr_count].attr_type);
		parse_to_int(Get_Word(attr, 3), table.attrs[table.attr_count].attr_key_type);
		parse_to_int(Get_Word(attr, 4), table.attrs[table.attr_count].attr_len);
		parse_to_int(Get_Word(attr, 5), table.attrs[table.attr_count].attr_num);
		
		table.attr_count++;
	}
	fin.close();
}

void Read_Index(string index_name)
{
	index.index_name = index_name;
	ifstream fin;
	fin.open(INDEX_LIST, ios::in);
	char str_temp[MAX_ATTRNAME_LENGTH];
	string str;
	while(!fin.eof())
	{
		fin.getline(str_temp, MAX_ATTRNAME_LENGTH);
		str = str_temp;
		string temp = Get_Word(str, 1);
		if(temp == "" && fin.eof())
			break;
		if(temp == index_name)
		{
			index.table_name = Get_Word(str, 2);
			index.attr_name = Get_Word(str, 3);
		}
		
	}
	fin.close();
}

bool API_Insert()
{
	//for(int i=0; i<value_count; i++)
	//	cout << "test" << values[i] << "test" << endl;
	
	if(!judge_table_exist(table.table_name))
	{
		error_info = ERROR_INSERT_NO_TABLE;
		return false;
	}
	
	Read_Table_Info();
	
	if(table.attr_count != value_count)
	{
		error_info = ERROR_INSERT_PHRASE;
		return false;
	}
	
	//下面对values[]进行类型确认
	for(int i=0; i<table.attr_count; i++)
	{
		if(table.attrs[i].attr_type == ATTR_TYPE_INT)
		{
			int temp;
			if(!parse_to_int(values[i], temp))
			{
				error_info = ERROR_INSERT_PHRASE;
				return false;
			}
		}
		else if(table.attrs[i].attr_type == ATTR_TYPE_CHAR)
		{
			if(values[i].at(0) != '\'')
			{
				error_info = ERROR_INSERT_PHRASE;
				return false;
			}
			if(values[i].at(values[i].length()-1) != '\'')
			{
				error_info = ERROR_INSERT_PHRASE;
				return false;
			}
			
			values[i].assign(values[i], 1, values[i].length()-2);
			
			if(values[i].length() != table.attrs[i].attr_len)
			{
				error_info = ERROR_INSERT_PHRASE;
				return false;
			}
			
		}
		
	}
	
	//for(int i=0; i<value_count; i++)
	//	cout << "test" << values[i] << "test" << endl;
	
	
	/*
	cout << "table_name	:	" << table.table_name << endl;
	for(int i=0; i<table.attr_count; i++)
	{
		cout << table.attrs[i].attr_name << "  ";
		cout << table.attrs[i].attr_type << "  ";
		cout << table.attrs[i].attr_key_type << "  ";
		cout << table.attrs[i].attr_len << "  ";
		cout << table.attrs[i].attr_num << endl;
	}
	*/
	
	if(!Insert(table, values))
		return false;
	
	return true;
}

bool API_Select()
{
	if(!judge_table_exist(table.table_name))
	{
		error_info = ERROR_SELECT_NO_TABLE;
		return false;
	}
	
	Read_Table_Info();
	
	/*
	cout << "table_name	:	" << table.table_name << endl;
	for(int i=0; i<table.attr_count; i++)
	{
		cout << table.attrs[i].attr_name << "  ";
		cout << table.attrs[i].attr_type << "  ";
		cout << table.attrs[i].attr_key_type << "  ";
		cout << table.attrs[i].attr_len << "  ";
		cout << table.attrs[i].attr_num << endl;
	}
	
	
	while(true)
	{
		if(conditions == NULL)
			break;
		cout << conditions->attr_name << "  " << conditions->op_type << "  " << conditions->cmp_value;
		cout << endl;
		
		conditions = conditions->next;
	}
	*/

	if(!Select(table, conditions))
		return false;
		
	return true;
}

bool API_Delete()
{
	if(!judge_table_exist(table.table_name))
	{
		error_info = ERROR_DELETE_NO_TABLE;
		return false;
	}
	
	Read_Table_Info();
	
	/*
	cout << "table_name	:	" << table.table_name << endl;
	for(int i=0; i<table.attr_count; i++)
	{
		cout << table.attrs[i].attr_name << "  ";
		cout << table.attrs[i].attr_type << "  ";
		cout << table.attrs[i].attr_key_type << "  ";
		cout << table.attrs[i].attr_len << "  ";
		cout << table.attrs[i].attr_num << endl;
	}

	while(true)
	{
		if(conditions == NULL)
			break;
		cout << conditions->attr_name << "  " << conditions->op_type << "  " << conditions->cmp_value;
		cout << endl;
		
		conditions = conditions->next;
	}
	*/
	
	if(!Delete(table, conditions))
		return false;
	
	return true;
}
