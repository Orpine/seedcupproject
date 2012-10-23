#include "MiniSQL.h"
#include "Interpreter.h"
#include "API.h"
#include "Catalog_Manager.h"
#include "Record_Manager.h"


string error_info;					//���ڱ��������Ϣ
int opType;
Table table;						//���ڴ�����ѡ���¼��ɾ����¼�������¼��
Condition_list conditions;	//���ڽ�����ʱ�򱣴�where����
Index index;						//���ڴ�������
string table_name;					//����ɾ����
string index_name;					//����ɾ������
string values[32];					//����insert����
int value_count;					//����insert����
int main()
{
	string SQL_CMD;
	/****************************************************************/
	//			���MINI_SQL������Ϣ
cout<<"\t\t***********************************************"<<endl;
	cout<<"\t\t             ��ӭʹ�� MiniSQL !"<<endl;
	cout<<"\t\t                 2008-7-5  "<<endl;     
	cout<<"\t\t     copyright@wgl All rights reserved!  "<<endl;     
	cout<<"\t\t***********************************************"<<endl;
	cout<<endl<<endl;
	/****************************************************************/
	
	//	��ϵͳ���г�ʼ��
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
	
	
	//	������г�������
	while(true)
	{
		//	�Ƚ������ַ�����ʼ��
		SQL_CMD = "";
		
		//	�ȴ��û���������
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
			
			//	��һ���û������������н���
			if(!Interpreter(SQL_CMD))
				cout << error_info << endl;
			//	�﷨��������������������⣬ͬʱ�����ڲ����ã�����ת����Ϣ���Ȩ
			else
				API();
				
		}
	}
	
	system("pause");
	
	return 1;
}
