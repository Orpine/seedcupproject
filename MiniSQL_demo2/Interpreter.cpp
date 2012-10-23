#include "Interpreter.h"
#include "API.h"
#include "Catalog_Manager.h"

bool Get_Cmd(string & SQL_CMD)
{
	string line;
	while(true)
	{
		cin >> line;
		if(SQL_CMD.length() != 0)
			line = " " + line;
		SQL_CMD.append(line);
		int pos = SQL_CMD.find(";");
		//	����Ѿ�������";"������Ƿ�
		if(pos != -1)
		{
			//	���������Ƿ����滹�����룬�򱨴�
			if(pos != SQL_CMD.length()-1)
			{
				error_info = ERROR_WRONG_CMD_INPUT;
				return false;
			}
			//	����������һ��������򱨴�
			else if(pos == 0)
				{
					error_info = ERROR_EMPTY_CMD_INPUT;
					return false;
				}
				else
					return true;
		}
		//	���û������";"������Ƿ����������������
	}
}

bool Interpreter(string & SQL_CMD)
{
	opType = Get_Operate_Type(SQL_CMD);
	
	//cout << "opType	:	" << opType << endl;
	
	switch(opType)
	{
		//	create function
		case CREATE_OP_TYPE	:
			if(!Check_OP_Create(SQL_CMD))
				return false;
			break;
		
		//	delete function
		case DELETE_OP_TYPE	:
			if(!Check_OP_Delete(SQL_CMD))
				return false;
			break;
		
		//	drop function
		case DROP_OP_TYPE		:
			if(!Check_OP_Drop(SQL_CMD))
				return false;
			break;
		
		//	insert function
		case INSERT_OP_TYPE	:
			if(!Check_OP_Insert(SQL_CMD))
				return false;
			break;
		
		//	select function
		case SELECT_OP_TYPE	:
			if(!Check_OP_Select(SQL_CMD))
				return false;
			break;
		
		//	execfile function
		case EXECFILE_OP_TYPE	:
			if(!Exec_File(SQL_CMD))
				return false;
			break;
		
		//	help function
		case HELP_OP_TYPE			:
			Help_Mini_Sql();
			break;
		
		//	exit function
		case QUIT_OP_TYPE			:
			cout << endl;
			cout << "*******************************************************************************" << endl;
			cout << "                          Thanks for using MiniSQL !                           " << endl;
			cout << "*******************************************************************************" << endl;
			cout << endl;
			Exit_To_System();
			break;
		
		//	error function-type
		default	:
			error_info = ERROR_NULL_OP_TYPE;
      return false;
	}
	
	return true;
}

string Get_Word(string SQL_CMD, int count, char stop)
{
	string tmp;
	int begin = 0;
	int end = 0;
	
	int ps = 0;
	
	bool is_value = false;

	for(int i=0; i<SQL_CMD.length(); i++)
	{
		if(SQL_CMD.at(i) == '\'')
		{
			if(is_value)
				is_value = false;
			else
				is_value = true;
		}
		if(SQL_CMD.at(i) == stop && !is_value)
		{
			if(SQL_CMD.at(i-1) != stop)
			{
				ps++;
				if(ps == count-1 )
        	begin = i+1;
  		}
      else 
      	begin++;
		}
		if(ps == count)
		{
			end = i;
			break;
		}
	}

	tmp.assign(SQL_CMD, begin, end - begin);
	return tmp;
}

int Get_Operate_Type(string & SQL_CMD)
{
	string opStr = Get_Word(SQL_CMD, 1);
	
	if(opStr == "create")					return CREATE_OP_TYPE;
	else if(opStr == "delete")		return DELETE_OP_TYPE;
	else if(opStr == "drop")			return DROP_OP_TYPE;
	else if(opStr == "insert")		return INSERT_OP_TYPE;
	else if(opStr == "select")		return SELECT_OP_TYPE;
	else if(opStr == "execfile")	return EXECFILE_OP_TYPE;
	else if(opStr == "help")			return HELP_OP_TYPE;
	else if(opStr == "quit")			return QUIT_OP_TYPE;
		else												return NULL_OP_TYPE;
}

void Exit_To_System()
{
	exit(-1);
}

void Help_Mini_Sql()
{
	cout << endl;
	cout << "*******************************************************************************" << endl;
	cout << "                          Welcome to use MiniSQL !                             " << endl;
	cout << "*******************************************************************************" << endl;
	cout << endl;
	cout << "key_word               phrase                             function" << endl;
	cout << endl;
	
	//cout << "create    :" << endl;
	cout << "create table     create table table_name (         Create a new table !" << endl;
	cout << "                    attr_name_1 attr_type_1 ," << endl;
	cout << "                    attr_name_2 attr_type_2 ," << endl;
	cout << "                    attr_name_3 attr_type_3 ," << endl;
	cout << "                       ......" << endl;
	cout << "                    primary key ( attr_name )" << endl;
	cout << "                                   );" << endl;
	cout << "create index     create index index_name           Create a new index !" << endl;
	cout << "                    on table_name (atrr_name);" << endl;
	
	//cout << "delete    :  " << endl;
	cout << "delete from      delete from table_name;           Delete all records !" << endl;
	cout << "                        or" << endl;
	cout << "                 delete from table_name            Delete records selectly !" << endl;
	cout << "                    where conditon_list;" << endl;
	
	//cout << "drop      :  "" << endl;
	cout << "drop table       drop table table_name;            Delete an old table !" << endl;
	cout << "drop index       drop index index_name;            Delete an old index !" << endl;
	
	//cout << "insert    :  " << endl;
	cout << "insert into      insert into table_name values (   Insert a record !" << endl;
	cout << "                    attr_value_1" << endl;
	cout << "                    attr_value_2" << endl;
	cout << "                    		..." << endl;
	cout << "                    attr_value_n" << endl;
	cout << "                                               );" << endl;
	
	//cout << "select    :  " << endl;
	cout << "select *         select * from table_name;         Select records !" << endl;
	cout << "                        or" << endl;
	cout << "                 select * from table-name          Select records selectly !" << endl;
	cout << "                    where conditon_list;" << endl;
	
	//cout << "execfile  :  " << endl;
	cout << "execfile         execfile file_name;               Run a shell file !" << endl;
	
	//cout << "help      :  " << endl;
	cout << "help             help;                             Print help infomation !" << endl;
	
	//cout << "quit      :  " << endl;
	cout << "quit             quit;                             Exit to OS !" << endl;
	
	cout << endl;
	cout << "*******************************************************************************" << endl;
	cout << endl;
}

bool Exec_File(string & SQL_CMD)
{
	string CMD;
	char cmd[MAX_CMD_LENGTH];
	//char fileName[MAX_FILENAME_LENGTH];
	string fileName = Get_Word(SQL_CMD, 2);
	if(fileName == ";")
	{
		error_info =	ERROR_NO_FILENAME_INPUT;
		return false;	
	}
	
	ifstream fin;
	//fin.open(fileName.c_str(), ios::nocreate);
	fin.open(fileName.c_str(), ios::in);
    	
	if(fin.is_open() == 0)
	{
		error_info = ERROR_CANNOT_OPEN_FILE;
		
		cout << fileName << endl;
		
		return false;
	}
	
	while(true)
	{
		fin.getline(cmd, MAX_CMD_LENGTH);
		CMD = cmd;
		//	��ȡ����
		if(CMD == "" && fin.eof())
			break;
		if(CMD.find(";") == -1)
		{
			error_info = ERROR_NOTFULL_CMD;
			return false;
		}
		
		//CMD.replace(CMD.length()-1, 1, " ;");
		CMD = Word_Depart(CMD);
		
		//cout << CMD << endl;
		
		if(!Interpreter(CMD))
				cout << error_info << endl;
		else
				API();
		
	}
	
	//	���������͸�ԭ
	opType = EXECFILE_OP_TYPE;
	
	fin.close();
	return true;
}

string Word_Depart(string SQL_CMD)
{
	//���潫 ( , ) ����
	char temp[MAX_CMD_LENGTH];
	int count = 0;
	
	for(int i=0; i<SQL_CMD.length(); i++)
	{
		if(SQL_CMD.at(i) == '(' || SQL_CMD.at(i) == ')' || SQL_CMD.at(i) == ',' || SQL_CMD.at(i) == ';')
		{
			temp[count++] = ' ';
			temp[count++] = SQL_CMD.at(i);
			temp[count++] = ' ';
		}
		else
			temp[count++] = SQL_CMD.at(i);
	}
	temp[count++] = '\0';
	SQL_CMD = temp;
	
	string result = "";
	count = 0;
	
	while(true)
	{
		string word = Get_Word(SQL_CMD, ++count);
		if(word != ";")
			result = result + word + " ";
		else
		{
			result += ";";
			break;
		}
	}
	
	return result;
}

bool Check_OP_Create(string & SQL_CMD)
{
	//cout << "Check_OP_Create() has not finished ..........." << endl;
	string sub_OP_Str = Get_Word(SQL_CMD, 2);
	
	if(sub_OP_Str == "table")
	{
		opType = CREATE_TABLE_OP_TYPE;
		if(!Check_OP_Create_Table(SQL_CMD))
		{
			//cout << "Read Table info fail ............." << endl;
			return false;
		}
		else
		{
			//cout << "Read Table info success ............" << endl;
			/*
			cout << "table_name	:	" << table.table_name << endl;
			cout << "attr_count	:	"	<< table.attr_count	<< endl;
			for(int i=0; i<table.attr_count; i++)
			{
				cout << "table.attrs[" << i << "]	:	";
				cout << table.attrs[i].attr_name << "  " << table.attrs[i].attr_type << "  ";
				cout << table.attrs[i].attr_key_type << "  " << table.attrs[i].attr_len << "  ";
				cout << table.attrs[i].attr_num << endl;
			}
			*/
			return true;
		}
	}
	else if(sub_OP_Str == "index")
	{
		opType = CREATE_INDEX_OP_TYPE;
		if(!Check_OP_Create_Index(SQL_CMD))
		{
			//cout << "Read Index info fail ............." << endl;
			return false;
		}
		else
		{
			//cout << "Read Index info success ............" << endl;
			/*
			cout << "index_name	:	" << index.index_name << endl;
			cout << "table_name	:	"	<< index.table_name << endl;
			cout << "attr_name	:	" << index.attr_name << endl;
			*/
			return true;
		}
	}
	else if(sub_OP_Str == ";")
	{
		error_info = ERROR_EMPTY_CREATE_TYPE;
		return false;
	}
	else
	{
		error_info = ERROR_NULL_CREATE_TYPE;
		return false;
	}
}

bool Check_OP_Create_Table(string & SQL_CMD)
{
	//cout << "Check_OP_Create_Table() has not finished ..........." << endl;
	
	string temp;
	
	int attr_count = 0;
	
	if(SQL_CMD.find(",") == -1)
	{
		error_info = ERROR_CREATE_TABLE_PHRASE;
		return false;
	}
	
	while(true)
	{
		attr_count ++;
		temp = Get_Word(SQL_CMD, attr_count, ',');
		if(temp.at(temp.length()-1) == ';')
			break;
	}
	
	table.attr_count = attr_count-1;
	
	//��ȡ����
	temp = Get_Word(SQL_CMD, 3);
	if(temp == "," || temp == "(" || temp == ")" || temp == ";")
	{
		error_info = ERROR_CREATE_TABLE_PHRASE;
		return false;
	}
	table.table_name = temp;
	
	if(Get_Word(SQL_CMD, 4) != "(")
	{
		error_info = ERROR_CREATE_TABLE_PHRASE;
		return false;
	}
	
	//����Ϊ��ȡtable.attr_count��������Ϣ
	int word_count = 4;
	for(int i=0; i<table.attr_count; i++)
	{
		temp = Get_Word(SQL_CMD, ++word_count);
		if(temp == "," || temp == "(" || temp == ")" || temp == ";")
		{
			error_info = ERROR_CREATE_TABLE_PHRASE;
			return false;
		}
		table.attrs[i].attr_name = temp;
		
		temp = Get_Word(SQL_CMD, ++word_count);
		//���������������Ϊchar(n)
		if(temp == "char")
		{
			table.attrs[i].attr_type = ATTR_TYPE_CHAR;
			
			if(Get_Word(SQL_CMD, ++word_count) != "(")
			{
				error_info = ERROR_CREATE_TABLE_PHRASE;
				return false;
			}
			temp = Get_Word(SQL_CMD, ++word_count);
			
			//////////////////////////////////////////////////
			//��tempת��������
			
			int result;
			if(!parse_to_int(temp, result))
			{
				error_info = ERROR_CREATE_TABLE_PHRASE;
				return false;
			}
			
			table.attrs[i].attr_len = result;
			
			if(Get_Word(SQL_CMD, ++word_count) != ")")
			{
				error_info = ERROR_CREATE_TABLE_PHRASE;
				return false;
			}
		}
		//���������������Ϊint
		else if(temp == "int")
		{
			table.attrs[i].attr_type = ATTR_TYPE_INT;
			table.attrs[i].attr_len = 1;
		}
		//���������������Ϊfloat
		else if(temp == "float")
		{
			table.attrs[i].attr_type = ATTR_TYPE_FLOAT;
			table.attrs[i].attr_len = 1;
		}
		//��������������ͳ���
		else
			{
				error_info = ERROR_CREATE_TABLE_PHRASE;
				return false;
			}
		
		temp = Get_Word(SQL_CMD, ++word_count);
		//�����������Ϊunique
		if(temp == "unique")
		{
			if(Get_Word(SQL_CMD, ++word_count) != ",")
			{
				error_info = ERROR_CREATE_TABLE_PHRASE;
				return false;
			}
			table.attrs[i].attr_key_type = ATTR_TYPE_UNIQUE;
		}
		else if(temp == ",")
			table.attrs[i].attr_key_type = ATTR_TYPE_NULL;
		//����������ͳ���
		else
			{
				error_info = ERROR_CREATE_TABLE_PHRASE;
				return false;
			}
		
		// �����������б����ǵڼ���
		table.attrs[i].attr_num = i + 1;
	
	}
	
	//���潫Ҫ�õ�primary_key
	if(Get_Word(SQL_CMD, ++word_count) != "primary")
	{
		error_info = ERROR_CREATE_TABLE_PHRASE;
		return false;
	}
	if(Get_Word(SQL_CMD, ++word_count) != "key")
	{
		error_info = ERROR_CREATE_TABLE_PHRASE;
		return false;
	}
	if(Get_Word(SQL_CMD, ++word_count) != "(")
	{
		error_info = ERROR_CREATE_TABLE_PHRASE;
		return false;
	}
	
	/////////////////////////////////////////
	//�����ȥprimary_key����������
	temp = Get_Word(SQL_CMD, ++word_count);
	bool attr_ok = false;		//����ȷ�������Ƿ���ȷ
	for(int j=0; j<table.attr_count; j++)
	{
		if(table.attrs[j].attr_name == temp)
		{
			table.attrs[j].attr_key_type = ATTR_TYPE_PRIMARY;
			attr_ok = true;
			break;
		}
		
	}
	if(!attr_ok)
	{
		error_info = ERROR_CREATE_TABLE_PHRASE;
		return false;
	}
	
	///////////////////////////////////////////
	
	if(Get_Word(SQL_CMD, ++word_count) != ")")
	{
		error_info = ERROR_CREATE_TABLE_PHRASE;
		return false;
	}
	
	//��ȡ�����б����
	if(Get_Word(SQL_CMD, ++word_count) != ")")
	{
		error_info = ERROR_CREATE_TABLE_PHRASE;
		return false;
	}
	if(Get_Word(SQL_CMD, ++word_count) != ";")
	{
		error_info = ERROR_CREATE_TABLE_PHRASE;
		return false;
	}
	
	return true;
}

bool parse_to_int(string intStr, int & result)
{
    result = 0;
    for(int i=0; i<intStr.length(); i++)
    {
        int temp = 0;
        if(intStr.at(i) == '0')    temp = 0;
        else if(intStr.at(i) == '1')        temp = 1;
        else if(intStr.at(i) == '2')        temp = 2;
        else if(intStr.at(i) == '3')        temp = 3;
        else if(intStr.at(i) == '4')        temp = 4;
        else if(intStr.at(i) == '5')        temp = 5;
        else if(intStr.at(i) == '6')        temp = 6;
        else if(intStr.at(i) == '7')        temp = 7;
        else if(intStr.at(i) == '8')        temp = 8;
        else if(intStr.at(i) == '9')        temp = 9;
        else        return false;
        
        result = 10 * result + temp;
    }
    return true;
}

bool Check_OP_Create_Index(string & SQL_CMD)
{
	//cout << "Check_OP_Create_Index() has not finished ..........." << endl;

	//�õ���Ҫ������������
	index.index_name = Get_Word(SQL_CMD, 3);
	if(index.index_name == ";")
	{
		error_info = ERROR_CREATE_INDEX_PHRASE;
		return false;
	}
	
	if(Get_Word(SQL_CMD, 4) != "on")
	{
		error_info = ERROR_CREATE_INDEX_PHRASE;
		return false;
	}
	
	//�õ���Ҫ��������������Ӧ�ı���
	index.table_name = Get_Word(SQL_CMD, 5);
	if(index.index_name == ";")
	{
		error_info = ERROR_CREATE_INDEX_PHRASE;
		return false;
	}
	
	//����õ���Ҫ��������������Ӧ��������
	if(Get_Word(SQL_CMD, 6) != "(")
	{
		error_info = ERROR_CREATE_INDEX_PHRASE;
		return false;
	}
	
	index.attr_name = Get_Word(SQL_CMD, 7);
	if(index.attr_name == ";")
	{
		error_info = ERROR_CREATE_INDEX_PHRASE;
		return false;
	}
	
	if(Get_Word(SQL_CMD, 8) != ")")
	{
		error_info = ERROR_CREATE_INDEX_PHRASE;
		return false;
	}
	
	if(Get_Word(SQL_CMD, 9) != ";")
	{
		error_info = ERROR_CREATE_INDEX_PHRASE;
		return false;
	}
		
	return true;
}

bool Check_OP_Delete(string & SQL_CMD)
{
	//cout << "Check_OP_Delete() has not finished ..........." << endl;
	
	if(Get_Word(SQL_CMD, 2) != "from")
	{
		error_info = ERROR_DELETE_PHRASE;
		return false;
	}
	
	//ȡ����Ҫɾ����¼�ı���
	string temp = Get_Word(SQL_CMD, 3);
	if(temp == ";")
	{
		error_info = ERROR_DELETE_PHRASE;
		return false;
	}
	table.table_name = temp;
	// �����û��������ѡ����ֱ������
	if(Get_Word(SQL_CMD, 4) == ";")
	{
		opType = DELETE_ALL_OP_TYPE;
		conditions = NULL;
		return true;
	}
	//�������where�Ӿ��select�����н���
	if(Get_Word(SQL_CMD, 4) != "where")
	{
		error_info = ERROR_DELETE_PHRASE;
		return false;
	}
	//��ɨ��һ���ܹ��м�������
	int cond_count = 1;
	for(int j=1; ; j++)
	{
		if(Get_Word(SQL_CMD, j) == ";")
			break;
		if(Get_Word(SQL_CMD, j) == "and")
			cond_count++;
	}
	//cout << cond_count << endl;
	//�����ȡ��һ������
	conditions = new Condition;

	conditions->next = NULL;

	temp = Get_Word(SQL_CMD, 5);
	if(temp == ";" || temp == "," || temp == "(" || temp == ")" || Check_CMP_Type(temp) != -1)
	{
		error_info = ERROR_DELETE_PHRASE;
		return false;
	}
	conditions->attr_name = temp;
	temp = Get_Word(SQL_CMD, 6);
	if(Check_CMP_Type(temp) == -1)
	{
		error_info = ERROR_DELETE_PHRASE;
		return false;
	}
	conditions->op_type = Check_CMP_Type(temp);
	temp = Get_Word(SQL_CMD, 7);
	if(temp == ";" || temp == "," || temp == "(" || temp == ")" || Check_CMP_Type(temp) != -1)
	{
		error_info = ERROR_DELETE_PHRASE;
		return false;
	}

	//����''
	if(temp.find('\'') != -1)
	{
		temp = Get_Word(temp, 1, '\'');
		temp = temp.assign(temp, 1, temp.length()-1);
	}

	conditions->cmp_value = temp;
	
	//���ֻ��һ���Ƚ�����,�����Ϸ���
	if(cond_count == 1)
	{
		opType = DELETE_WHERE_OP_TYPE;
		return true;
	}
	
	//��ȡʣ�༸���Ƚ�����
	for(int i=1; i<cond_count; i++)
	{
		Condition_list cond = new Condition;
		
		if(Get_Word(SQL_CMD, 4+4*i) != "and")
		{
			error_info = ERROR_SELECT_PHRASE;
			return false;
		}
		temp = Get_Word(SQL_CMD, 5+4*i);
		if(temp == ";" || temp == "," || temp == "(" || temp == ")" || Check_CMP_Type(temp) != -1)
		{
			error_info = ERROR_SELECT_PHRASE;
			return false;
		}
		cond->attr_name = temp;
		temp = Get_Word(SQL_CMD, 6+4*i);
		if(Check_CMP_Type(temp) == -1)
		{
			error_info = ERROR_SELECT_PHRASE;
			return false;
		}
		cond->op_type = Check_CMP_Type(temp);
		temp = Get_Word(SQL_CMD, 7+4*i);
		if(temp == ";" || temp == "," || temp == "(" || temp == ")" || Check_CMP_Type(temp) != -1)
		{
			error_info = ERROR_SELECT_PHRASE;
			return false;
		}

		//����''
		if(temp.find('\'') != -1)
		{
			temp = Get_Word(temp, 1, '\'');
			temp = temp.assign(temp, 1, temp.length()-1);
		}

		cond->cmp_value = temp;
		
		//���潫cond������ӵ���������β��
		//cond->next = NULL;
		//conditions->next = cond;
		cond->next = conditions;
		conditions = cond;
	}
	
	opType = DELETE_WHERE_OP_TYPE;
	
	return true;
}

bool Check_OP_Drop(string & SQL_CMD)
{
	//cout << "Check_OP_Drop() has not finished ..........." << endl;
	
	string sub_OP_Str = Get_Word(SQL_CMD, 2);
	
	if(sub_OP_Str == "table")
	{
		opType = DROP_TABLE_OP_TYPE;
		if(!Check_OP_Drop_Table(SQL_CMD))
			return false;
		else
			return true;
	}
	else if(sub_OP_Str == "index")
	{
		opType = DROP_INDEX_OP_TYPE;
		if(!Check_OP_Drop_Index(SQL_CMD))
			return false;
		else
		return true;
	}
	else if(sub_OP_Str == ";")
	{
		error_info = ERROR_EMPTY_DROP_TYPE;
		return false;
	}
	else
	{
		error_info = ERROR_NULL_DROP_TYPE;
		return false;
	}
	
	return true;
}

bool Check_OP_Drop_Table(string & SQL_CMD)
{
	//cout << "Check_OP_Drop_Table() has not finished ..........." << endl;
	
	//��ȡҪɾ���ı���
	table_name = Get_Word(SQL_CMD, 3);
	if(table_name == ";")
	{
		error_info = ERROR_DROP_TABLE_PHRASE;
		return false;
	}
	
	if(Get_Word(SQL_CMD, 4) != ";")
	{
		error_info = ERROR_DROP_TABLE_PHRASE;
		return false;
	}
	
	return true;
}

bool Check_OP_Drop_Index(string & SQL_CMD)
{
	//cout << "Check_OP_Drop_Index() has not finished ..........." << endl;
	
	//��ȡҪɾ����������
	index_name = Get_Word(SQL_CMD, 3);
	if(index_name == ";")
	{
		error_info = ERROR_DROP_INDEX_PHRASE;
		return false;
	}
	
	if(Get_Word(SQL_CMD, 4) != ";")
	{
		error_info = ERROR_DROP_INDEX_PHRASE;
		return false;
	}
	
	return true;
}

bool Check_OP_Insert(string & SQL_CMD)
{
	//cout << "Check_OP_Insert() has not finished ..........." << endl;
	
	//cout << SQL_CMD << endl;
	
	int count = 0;
	string temp;
	
	if(SQL_CMD.find(",") == -1)
	{
		error_info = ERROR_INSERT_PHRASE;
		return false;
	}
	while(true)
	{
		count ++;
		temp = Get_Word(SQL_CMD, count, ',');
		if(temp.at(temp.length()-1) == ';')
			break;
		//cout << temp << endl;
	}
	value_count = count;
	
	if(Get_Word(SQL_CMD, 2) != "into")
	{
		error_info = ERROR_INSERT_PHRASE;
		return false;
	}
	
	//�õ���Ҫ�����¼�ı���
	temp = Get_Word(SQL_CMD, 3);
	if(temp == "," || temp == "(" || temp == ")" || temp == ";")
	{
		error_info = ERROR_INSERT_PHRASE;
		return false;
	}
	table.table_name = temp;
	
	if(Get_Word(SQL_CMD, 4) != "values")
	{
		error_info = ERROR_INSERT_PHRASE;
		return false;
	}
	if(Get_Word(SQL_CMD, 5) != "(")
	{
		error_info = ERROR_INSERT_PHRASE;
		return false;
	}
	
	//����õ�value_count������
	//ȡ�õ�һ������
	temp = Get_Word(SQL_CMD, 6);
	if(temp == "," || temp == "(" || temp == ")" || temp == ";")
	{
		error_info = ERROR_INSERT_PHRASE;
		return false;
	}
	values[0] = temp;
	
	for(int i=1; i<value_count; i++)
	{
		if(Get_Word(SQL_CMD, 6+2*i-1) != ",")
		{
			error_info = ERROR_INSERT_PHRASE;
			return false;
		}
		temp = Get_Word(SQL_CMD, 6+2*i);
		if(temp == "," || temp == "(" || temp == ")" || temp == ";")
		{
			error_info = ERROR_INSERT_PHRASE;
			return false;
		}
		values[i] = temp;
	}
	
	/*
	if(Get_Word(SQL_CMD, 7) != ",")
	{
		error_info = ERROR_INSERT_PHRASE;
		return false;
	}
	//ȡ���м�ļ�������
	for(int i=2; i<value_count; i++)
	{
		values[i-1] = Get_Word(SQL_CMD, i, ',');
		char value_temp[values[i-1].length()];
		
		for(int j=1; j<values[i-1].length()-1; j++)
			value_temp[j-1] = values[i-1].at(j);
		value_temp[values[i-1].length()-2] = '\0';
		values[i-1] = value_temp;
	}
	
	//ȡ�����һ������
	temp = Get_Word(SQL_CMD, 4+2*value_count);
	if(temp == "," || temp == "(" || temp == ")" || temp == ";")
	{
		error_info = ERROR_INSERT_PHRASE;
		return false;
	}
	values[value_count-1] = temp;
	*/
	
	if(Get_Word(SQL_CMD, 5+2*value_count) != ")")
	{
		error_info = ERROR_INSERT_PHRASE;
		return false;
	}
	if(Get_Word(SQL_CMD, 6+2*value_count) != ";")
	{
		error_info = ERROR_INSERT_PHRASE;
		return false;
	}
	
	return true;
}

bool Check_OP_Select(string & SQL_CMD)
{
	//cout << "Check_OP_Select() has not finished ..........." << endl;
	
	if(Get_Word(SQL_CMD, 2) != "*")
	{
		error_info = ERROR_SELECT_PHRASE;
		return false;
	}
	if(Get_Word(SQL_CMD, 3) != "from")
	{
		error_info = ERROR_SELECT_PHRASE;
		return false;
	}
	
	//ȡ��Ҫ����ѡ������ı�ı���
	string temp = Get_Word(SQL_CMD, 4);
	if(temp == ";")
	{
		error_info = ERROR_SELECT_PHRASE;
		return false;
	}
	table.table_name = temp;
	
	// �����û��������ѡ����ֱ������
	if(Get_Word(SQL_CMD, 5) == ";")
	{
		opType = SELECT_ALL_OP_TYPE;
		conditions = NULL;
		return true;
	}
	
	//�������where�Ӿ��select�����н���
	if(Get_Word(SQL_CMD, 5) != "where")
	{
		error_info = ERROR_SELECT_PHRASE;
		return false;
	}
	//��ɨ��һ���ܹ��м�������
	int cond_count = 1;
	for(int g=1; ; g++)
	{
		if(Get_Word(SQL_CMD, g) == ";")
			break;
		if(Get_Word(SQL_CMD, g) == "and")
			cond_count++;
	}
	//cout << cond_count << endl;
	//�����ȡ��һ������
	conditions = new Condition;

	conditions->next = NULL;

	temp = Get_Word(SQL_CMD, 6);
	if(temp == ";" || temp == "," || temp == "(" || temp == ")" || Check_CMP_Type(temp) != -1)
	{
		error_info = ERROR_SELECT_PHRASE;
		return false;
	}
	conditions->attr_name = temp;
	temp = Get_Word(SQL_CMD, 7);
	if(Check_CMP_Type(temp) == -1)
	{
		error_info = ERROR_SELECT_PHRASE;
		return false;
	}
	conditions->op_type = Check_CMP_Type(temp);
	temp = Get_Word(SQL_CMD, 8);
	if(temp == ";" || temp == "," || temp == "(" || temp == ")" || Check_CMP_Type(temp) != -1)
	{
		error_info = ERROR_SELECT_PHRASE;
		return false;
	}

	//����''
	if(temp.find('\'') != -1)
	{
		temp = Get_Word(temp, 1, '\'');
		temp = temp.assign(temp, 1, temp.length()-1);
	}

	conditions->cmp_value = temp;
	
	//���ֻ��һ���Ƚ�����,�����Ϸ���
	if(cond_count == 1)
	{
		opType = SELECT_WHERE_OP_TYPE;
		return true;
	}
	
	//��ȡʣ�༸���Ƚ�����
	for(int i=1; i<cond_count; i++)
	{
		Condition_list cond = new Condition;
		
		if(Get_Word(SQL_CMD, 5+4*i) != "and")
		{
			error_info = ERROR_SELECT_PHRASE;
			return false;
		}
		temp = Get_Word(SQL_CMD, 6+4*i);
		if(temp == ";" || temp == "," || temp == "(" || temp == ")" || Check_CMP_Type(temp) != -1)
		{
			error_info = ERROR_SELECT_PHRASE;
			return false;
		}
		cond->attr_name = temp;
		temp = Get_Word(SQL_CMD, 7+4*i);
		if(Check_CMP_Type(temp) == -1)
		{
			error_info = ERROR_SELECT_PHRASE;
			return false;
		}
		cond->op_type = Check_CMP_Type(temp);
		temp = Get_Word(SQL_CMD, 8+4*i);
		if(temp == ";" || temp == "," || temp == "(" || temp == ")" || Check_CMP_Type(temp) != -1)
		{
			error_info = ERROR_SELECT_PHRASE;
			return false;
		}

		//����''
		if(temp.find('\'') != -1)
		{
			temp = Get_Word(temp, 1, '\'');
			temp = temp.assign(temp, 1, temp.length()-1);
		}

		cond->cmp_value = temp;
		
		//���潫cond������ӵ���������β��
		//cond->next = NULL;
		//conditions->next = cond;
		cond->next = conditions;
		conditions = cond;
	}
	
	opType = SELECT_WHERE_OP_TYPE;
	return true;
}

int Check_CMP_Type(string & type)
{
	if(type == "<")		return SMALL;
	if(type == "=")		return EQUEL;
	if(type == ">")		return BIG;	
	if(type == "!=")	return NEQUAL;
	if(type == ">=")	return GEQUAL;
	if(type == "<=")	return SEQUAL;
	
	return -1;
}

