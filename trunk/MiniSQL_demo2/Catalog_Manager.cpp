#include "Catalog_Manager.h"
#include "Interpreter.h"

bool Create_Table(Table & table_temp)
{
	ofstream fout;
	
	bool exist = judge_table_exist(table_temp.table_name);
	if(exist)
	{
		error_info = ERROR_TABLE_EXIST;
		return false;
	}
	
	//�ڱ��б��ļ�������һ���¼
	fout.open(TABLE_LIST, ios::app);
	fout << table_temp.table_name << endl;
	fout.close();
	
	//��������Ϣ�ļ�
	//ofstream fout;
    string tableInfo = table_temp.table_name + ".info";
	//fin.open(tableInfo.c_str(), ios::noreplace);
	/*
    fout.open(tableInfo.c_str(), ios::in);
	if(fout.is_open() == 0) 
		fout.open(tableInfo.c_str(), ios::app);
	fout.close();
	*/
	//д����Ϣ
	fout.open(tableInfo.c_str(), ios::app);
	for(int i=0; i<table_temp.attr_count; i++)
	{
		fout << table_temp.attrs[i].attr_name << "  ";
		fout << table_temp.attrs[i].attr_type << "  ";
		fout << table_temp.attrs[i].attr_key_type << "  ";
		fout << table_temp.attrs[i].attr_len << "  ";
		fout << table_temp.attrs[i].attr_num;
		fout << endl;
	}
	fout.close();
	
	
	
	//����ȷ����Ҫ����Ҫ
	//���������ݼ�¼�ļ�
	string tableRecord = table_temp.table_name + "_sql.rec";
	//fin.open(tableRecord.c_str(), ios::noreplace);
	fout.open(tableRecord.c_str(), ios::in);
	if(fout.is_open() == 0) 
		fout.open(tableRecord.c_str(), ios::app);
	fout.close();
	
	return true;
}

bool Create_Index(Index & index)
{
	//cout << "Create_Index() has not finished ..........." << endl;
	
	bool exist = judge_index_exist(index.index_name);
	if(exist)
	{
		error_info = ERROR_INDEX_EXIST;
		return false;
	}
	
	//���������Ӧ�ı�����
	if(!judge_table_exist(index.table_name))
	{
		error_info = ERROR_INDEX_NO_TABLE;
		return false;
	}
	
	//�����Ӧ�������ڱ����в�����
	if(!judge_attr_in_table(index.table_name, index.attr_name))
	{
		error_info = ERROR_INDEX_NO_ATTR;
		return false;
	}
	
	//�������б��ļ�������һ���¼
	ofstream fout;
	fout.open(INDEX_LIST, ios::app);
	fout << index.index_name << "  " << index.table_name << "  " << index.attr_name << endl;
	fout.close();
	
	//	����ȷ����Ҫ����Ҫ
	//�����������ݼ�¼�ļ�
	ofstream fin;
	string indexRecord = index.index_name + "_index.rec";
	//fin.open(indexRecord.c_str(), ios::noreplace);
	fin.open(indexRecord.c_str(), ios::app);
	fin.close();
	
	return true;
}

bool Drop_Table(string & table_name)
{
	//cout << "Drop_Table() has not finished ..........." << endl;
	
	bool exist = judge_table_exist(table_name);
	if(!exist)
	{
		error_info = ERROR_TABLE_NOT_EXIST;
		return false;
	}
	
	//		����֪����Ҫ����Ҫ
	//	ɾ�������ݼ�¼�ļ�
	string delRecordFile = "del " + table_name + "_sql.rec";
	system(delRecordFile.c_str());
	
	//	ɾ������Ϣ�ļ�
	string delInfoFile = "del " + table_name + ".info";
	system(delInfoFile.c_str());
		
	//	����Ϊ���б��ļ���ɾ��һ���¼
	string table_list = "";
	char tableName_temp[MAX_RECORD_LENGTH];
	string tableName;
	ifstream fin;
	fin.open(TABLE_LIST, ios::in);
	while(!fin.eof())
	{
		fin.getline(tableName_temp, MAX_RECORD_LENGTH);
		tableName = tableName_temp;
		
		if(tableName == "" && fin.eof())
			break;
		
		if(tableName != table_name && tableName != "")
		{
			table_list += tableName;
			table_list += "\n";
		}
	}
	fin.close();
	
	//fin.open(TABLE_LIST, ios::trunc);
	//fin.close();
	
	ofstream fout;
	fout.open(TABLE_LIST, ios::out|ios::trunc);
	fout << table_list;
	fout.close();
	
	
	return true;
}

bool Drop_Index(string & index_name)
{
	//cout << "Drop_Index() has not finished ..........." << endl;
	
	bool exist = judge_index_exist(index_name);
	if(!exist)
	{
		error_info = ERROR_INDEX_NOT_EXIST;
		return false;
	}
	
	//	����֪����Ҫ����Ҫ
	//	ɾ���������ݼ�¼�ļ�
	string delRecordFile = "del " + index_name + "_index.rec";
	system(delRecordFile.c_str());
	
	//	����Ϊ�����б��ļ���ɾ��һ���¼
	string index_list = "";
	char indexName_temp[MAX_RECORD_LENGTH];
	string indexName;
	ifstream fin;
	fin.open(INDEX_LIST, ios::in);
	
	while(!fin.eof())
	{
		fin.getline(indexName_temp, MAX_RECORD_LENGTH);
		indexName = indexName_temp;
		indexName = Get_Word(indexName, 1);
		
		if(indexName == "" && fin.eof())
			break;
		
		if(indexName != index_name && indexName != "")
		{
			indexName = indexName_temp;
            index_list += indexName;
            index_list += "\n";
		}
	}
	fin.close();
	
	//fin.open(INDEX_LIST, ios::trunc);
	//fin.close();
	
	//cout << index_list;
	
	ofstream fout;
	fout.open(INDEX_LIST, ios::out|ios::trunc);
	fout << index_list;
	fout.close();
	
	return true;
}

bool judge_attr_unique(string & table_name, string & attr_name)
{
	
	cout << "judge_attr_unique() has not finished ..........." << endl;
	
	
	return true;
}

bool find_primary(string & table_name, string & attr_name)
{
	
	cout << "find_primary() has not finished ..........." << endl;
	
	
	return true;
}

bool judge_table_exist(string & table_name)
{
	bool exist = false;
	ifstream fin;
	fin.open(TABLE_LIST, ios::in);
	
	char tableName_temp[MAX_FILENAME_LENGTH];
	string tableName;
	while(!fin.eof())
	{
		fin.getline(tableName_temp, MAX_FILENAME_LENGTH);
		tableName = tableName_temp;
		
		if(tableName == "" && fin.eof())
			break;
		
		if(tableName == table_name)
		{
			exist = true;
			break;
		}
	}
	fin.close();
	
	return exist;
}

bool judge_index_exist(string & index_name)
{
	bool exist = false;
	ifstream fin;
	fin.open(INDEX_LIST, ios::in);
	
	char indexName_temp[MAX_ATTRNAME_LENGTH];
	string indexName;
	while(!fin.eof())
	{
		fin.getline(indexName_temp, MAX_ATTRNAME_LENGTH);
		indexName = indexName_temp;
		
		indexName = Get_Word(indexName, 1);
		
		if(indexName == "" && fin.eof())
			break;
		
		if(indexName == index_name)
		{
			exist = true;
			break;
		}
	}
	fin.close();
	
	return exist;
}

bool judge_attr_in_table(string & table_name, string & attr_name)
{
	bool exist = false;
	
	string tableInfo = table_name + ".info";
	ifstream fin;
	fin.open(tableInfo.c_str(), ios::in);
	
	char attrName_temp[MAX_ATTRNAME_LENGTH];
	string attrName;
	while(!fin.eof())
	{
		fin.getline(attrName_temp, MAX_ATTRNAME_LENGTH);
		attrName = attrName_temp;
		attrName = Get_Word(attrName, 1);
		if(attrName == "" && fin.eof())
			break;
		if(attrName == attr_name)
		{
			exist = true;
			break;
		}
	}
	
	fin.close();
	return exist;
}

