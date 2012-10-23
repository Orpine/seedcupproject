#include "MiniSQL.h"
#include "Interpreter.h"
#include "API.h"
#include "Catalog_Manager.h"
#include "Record_Manager.h"


string error_info;					//用于保存出错信息
int opType;
Table table;						//用于创建表、选择纪录、删除纪录、插入纪录等
Condition_list conditions;	//用于解析的时候保存where条件
Index index;						//用于创建索引
string table_name;					//用于删除表单
string index_name;					//用于删除索引
string values[32];					//用于insert操作
int value_count;					//用于insert操作
int main()
{
	string SQL_CMD;
	/****************************************************************/
	//			输出MINI_SQL程序信息
cout<<"\t\t***********************************************"<<endl;
	cout<<"\t\t             欢迎使用 MiniSQL !"<<endl;
	cout<<"\t\t                 2008-7-5  "<<endl;     
	cout<<"\t\t     copyright@wgl All rights reserved!  "<<endl;     
	cout<<"\t\t***********************************************"<<endl;
	cout<<endl<<endl;
	/****************************************************************/
	
	//	对系统进行初始化
	ofstream fout;
	//fout.open(TABLE_LIST, ios::noreplace);
	fout.open(TABLE_LIST, ios::in);
	if(fout.is_open() == 0)
        fout.open(TABLE_LIST, ios::app);
	fout.close();
	
	fout.clear();
	//fout.open(INDEX_LIST, ios::noreplace);
	fout.open(INDEX_LIST, ios::in);
	if(fout.is_open() == 0)
		fout.open(INDEX_LIST, ios::app);
	fout.close();
	
	
	//	下面进行程序主体
	while(true)
	{
		//	先将命令字符串初始化
		SQL_CMD = "";
		
		//	等待用户输入命令
		cout << "MINI_SQL->";
		if(!Get_Cmd(SQL_CMD))
			cout << error_info << endl;
		else
		{
			//cout << SQL_CMD << endl;
			
      //SQL_CMD.replace(SQL_CMD.length()-1, 1, " ;");
			SQL_CMD = Word_Depart(SQL_CMD);
			
			//cout << SQL_CMD << endl;
			/*
			int count = 0;
            while(true)
			{
				string word = Get_Word(SQL_CMD, ++count);
				cout << word << endl;
				if(word == ";")
				break;
			}
			system("pause");
			*/
			
			//	对一条用户输入的命令进行解析
			if(!Interpreter(SQL_CMD))
				cout << error_info << endl;
			//	语法检测结束，下面进行语义检测，同时进入内部调用，并且转交信息输出权
			else
				API();
				
		}
	}
	
	system("pause");
	
	return 1;
}
