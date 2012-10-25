#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include<stdio.h>
#include<stdlib.h>
#include"main.h"
#include<fstream>
using namespace std;

int main()
{
    //int flage=0;
    //freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
    ifstream file;
    file.open("input.txt");
    while(!file.eof())      //�ж��ļ�β��while(file)��ǰ�����������ԡ�
   // while(1)
    {
        string s;
        cout<<">>";
        //��';'��ΪSQL�������ı�־,����һ��SQL���
        getline(file,s,';');
        if(s.empty()) break;
        if(!interpreter(s))
        continue;
        		//��fk_word���б��������ദ��
		switch(fk_word)
		{

			case CREATE:

                if(sk_word==DATABASE)
                    CreateDatabase(fileName);

				else if(sk_word==TABLE)
					CreateTable(fileName,Colu,Type);

				break;

            case USE:
                UseDatabase(fileName);
                break;

            case SHOW:
                if(sk_word==DATABASES)
                    ShowDatabase();
                else if(sk_word==COLUMN)
                    ShowColumn(fileName);
                else cout<<"wait to do"<<endl,cout<<"here"<<endl;
                break;
            //firstKdyΪdrop
			case DROP:
				//ɾ����
				if(sk_word==TABLE)
					DropTable(fileName);

				else if(sk_word==DATABASE)
					DropDatabase(fileName);
				else
					cout<<"Error. Usage: drop table name or index name"<<endl;
				break;
            //fk_wordΪselect
			case SELECT:
				//��where������Ѱ
				if(con_count==0)
					Select0(fileName);
				//һ��where������Ѱ
				else if(con_count==1)
					Select1(fileName,col1,condition1,operater1);
				//����where������Ѱ
				//else
				//	Select(fileName,col1,condition1,operater1,
				//		col2,condition2,operater2,logic);
				break;
            /*
			//fk_wordΪdelete
			case DELETE:
				//������ɾ�����м�¼
				if(con_count==0)
					deleteValue(fileName);
				//����һ��where����ɾ�����������ļ�¼
				else if(con_count==1)
					deleteValue(fileName,col1,condition1,operater1);
				//��������where����ɾ�����������ļ�¼
				else
					deleteValue(fileName,col1,condition1,operater1,
									col2,condition2,operater2,logic);
				break;
			//fk_wordΪinsert
			case INSERT:
				insertRecord(fileName,insertValue);
				break;
			//fk_wordΪquit
			case QUIT:
				break;

			case COMMIT:
                break;

			case EXECFILE:
				break;
            */
		}
    }
   // fclose(stdin );
    return 0;
}


string getWord(string s, int *tmp)		//�Ӻ��������ã���ȡSQL��������һ���ؼ��֡�
{
	string word;
	int idx1,idx2,i;

	while ((s[*tmp] == ' ' || s[*tmp] == 10) && s[*tmp] != 0)	//ȥ��ǰ�����õĿո񼰻��з�
	{
		(*tmp)++;
	}
	idx1 = *tmp;

	if (s[*tmp] == '(' || s[*tmp] == ',' || s[*tmp] == ')')		//�������š����ź����������ر���
	{
		(*tmp)++;
		idx2 = *tmp;
		word = s.substr(idx1,idx2-idx1);
		return word;
	}
	else if (s[*tmp] == 39)					//�Ե��������ַ����ر���
	{
		(*tmp)++;
		while (s[*tmp] != 39 && s[*tmp] !=0)
			(*tmp)++;
		if (s[*tmp] == 39)
		{
			idx1++;
			idx2 = *tmp;
			(*tmp)++;
			word = s.substr(idx1,idx2-idx1);
			return word;
		}
		else
		{
			word = "";
			return word;
		}
	}
	else				//����������������������ͨ����
	{
		while (s[*tmp] != ' ' && s[*tmp] != 10 && s[*tmp] != 0 && s[*tmp] != ')' && s[*tmp] != ',')
			(*tmp)++;
		idx2 = *tmp;
		if (idx1 != idx2)
			word = s.substr(idx1,idx2-idx1);
		else
			word = "";
		i = word.find("char");
		if (i >= 0 && s[*tmp] == ')')
		{
			(*tmp)++;
			idx2 = *tmp;
			word = s.substr(idx1,idx2-idx1);
		}
		return word;
	}
}
int interpreter(string s)
{

	int tmp=0;
	string word;

	word = getWord(s, &tmp);

//��һ�㣬��ȡ��һ���ؼ���
	if (stricmp(word.c_str(), "create") == 0)
		fk_word = CREATE;
    else if(stricmp(word.c_str(), "use") == 0)
        fk_word = USE;
    else if (stricmp(word.c_str(),"show") == 0)
        fk_word =SHOW;
	else if (stricmp(word.c_str(), "select") == 0)
		fk_word = SELECT;
	else if (stricmp(word.c_str(), "drop") == 0)
		fk_word = DROP;
	else if (stricmp(word.c_str(), "delete") == 0)
		fk_word = DELETE;
	else if (stricmp(word.c_str(), "insert") == 0)
		fk_word = INSERT;
	else if (stricmp(word.c_str(), "quit") == 0)
		fk_word = QUIT;
	else if (stricmp(word.c_str(), "commit") == 0)
		fk_word = COMMIT;
	else if (stricmp(word.c_str(), "execfile") ==0)
		fk_word = EXECFILE;
	else
	{
		cout<<"Error, command "<<word<<" not found"<<endl;
		return 0;
	}

//�ڶ���
	if (fk_word == CREATE)		//��һ�ؼ���Ϊcreate������Ҫ��ȡ�ڶ��ؼ����жϴ�������
	{
		word = getWord(s,&tmp);
		if (strcmp(word.c_str(), "table") == 0)
			sk_word = TABLE;
        else if(strcmp(word.c_str(),"database") == 0) //database
            sk_word = DATABASE;
		else
		{
			cout<<"Error, Usage: "<<fk_word<<" table or index fileName"<<endl;
			return 0;
		}
        if (sk_word == DATABASE)          //      �¼ӵ�
        {
            word = getWord(s,&tmp);
			if (!word.empty())			//create database database_name ��ȷ
				fileName = word;
			else
			{
				cout<<"Error, Usage: "<<fk_word<<" table or index fileName"<<endl;
				return 0;
			}
        }
		else if (sk_word == TABLE)
		{
			word = getWord(s,&tmp);
			if (!word.empty())			//create table tablename ��ȷ
				fileName = word;
			else
			{
				cout<<"Error, Usage: "<<fk_word<<" table or index fileName"<<endl;
				return 0;
			}
			if (sk_word == TABLE)			//�ڶ��ؼ���Ϊtable����������
			{
				word = getWord(s,&tmp);
				if (word.empty() || strcmp(word.c_str(),"(") != 0)
				{
					cout<<"Error in syntax!"<<endl;
					return 0;
				}
				else				//�ڶ�ȡ�����ź���һ��¼һ�µ����������ԡ�
				{
					word = getWord(s,&tmp);
					while (!word.empty() && strcmp(word.c_str(),"primary") != 0 && strcmp(word.c_str(),")") != 0)
					{
						Colu.push_back(word);
						word = getWord(s,&tmp);

						if (!word.empty())
							Type.push_back(word);
						else
						{
							cout<<"Error in syntax!"<<endl;
							return 0;
						}

						if (sk_word == TABLE)
						{
							word = getWord(s,&tmp);
							if (strcmp(word.c_str(),"unique") == 0)
							{
								uniq.push_back(1);
								word = getWord(s,&tmp);
								if (strcmp(word.c_str(),",") != 0)
								{
									cout<<"Error in syntax!"<<endl;
									return 0;
								}
							}
							else if (strcmp(word.c_str(),",") == 0 || strcmp(word.c_str(),")") == 0)
								uniq.push_back(0);
							else if (word.empty() || strcmp(word.c_str(),")") != 0)
							{
								cout<<"Error in syntax!"<<endl;
								return 0;
							}
						}
						if (strcmp(word.c_str(),")") != 0)
							word = getWord(s,&tmp);
					}
					if (strcmp(word.c_str(),"primary") == 0)	//����ǰ�����ַ�Ϊprimaryʱ���ж�Ϊ�������壬�˳��������Զ�ȡ��ѭ����
					{
						word = getWord(s,&tmp);
						if (strcmp(word.c_str(),"key") != 0)
						{
							cout<<"Error in syntax!"<<endl;
							return 0;
						}
						else
						{
							word = getWord(s,&tmp);
							if (strcmp(word.c_str(),"(") == 0)
							{
								word = getWord(s,&tmp);
								primKey = word;
								word = getWord(s,&tmp);
								if (strcmp(word.c_str(),")") != 0)
								{
									cout<<"Error in syntax!"<<endl;
									return 0;
								}
							}
							else
							{
								cout<<"Error in syntax!"<<endl;
								return 0;
							}
						}
					}
					else if (word.empty())
					{
						cout<<"Error in syntax!"<<endl;
						return 0;
					}
				}
			}
		}



	}

    else if (fk_word == USE)
    {
        word = getWord(s,&tmp);
        cout<<word<<endl;
        fileName = word;
        word = getWord(s,&tmp);
        //cout<<word<<endl;
        if (!word.empty())
        {
            cout<<"error"<<endl;
            return 0;
        }

    }

    else if (fk_word == SHOW)
    {
        word = getWord(s,&tmp);
        if (strcmp(word.c_str(), "databases") == 0)
        sk_word = DATABASES;
        else
        {
            fileName = word;
            word = getWord(s,&tmp);
            if (strcmp(word.c_str(),"column") == 0)     //show table_name column;
            {
                sk_word = COLUMN;
            }
        }
        /*

        */
    }

	else if (fk_word == SELECT)		//��һ�ؼ���Ϊselect
	{
		word = getWord(s,&tmp);
		if (!word.empty())	//��Ҫminisqlֻ֧��select *�Ĳ��ҷ�ʽ����������Գ���select *����������Ϊ������
        {
            selection = word;
        }
        if (fk_word == SELECT)		//select * ���﷨��ȷ
		{
			word = getWord(s,&tmp);
			if (strcmp(word.c_str(), "from") != 0)
			{
				cout<<"Error in syntax!"<<endl;
				return 0;
			}
		}
		if (fk_word == SELECT)		//select * from���﷨��ȷ
		{
			word = getWord(s,&tmp);		//����
			if (!word.empty())
				fileName = word;
			else
			{
				cout<<"Error in syntax!"<<endl;
				return 0;
			}
		}
		if (fk_word == SELECT)		//��ǰ���﷨����ȷ������£���ȡ��ѯ������
		{
			word = getWord(s,&tmp);
			if (word.empty())	//������
				con_count = 0; //������
			else if (strcmp(word.c_str(),"where") == 0)	//����where
			{
				word = getWord(s,&tmp);		//col1
				if (!word.empty())
				{
					col1 = word;
					con_count = 1;
					word = getWord(s,&tmp);
					if (word.empty())
					{
						con_count = -1;
						cout<<"Error in syntax!"<<endl;
						return 0;
					}
					else if (strcmp(word.c_str(),"<=") == 0)
						operater1 = "<=";
					else if (strcmp(word.c_str(),">=") == 0)
						operater1 = ">=";
					else if (strcmp(word.c_str(),"<") == 0)
						operater1 = "<";
					else if (strcmp(word.c_str(),">") == 0)
						operater1 = ">";
					else if (strcmp(word.c_str(),"==") == 0)   //�Ķ���
						operater1 = "==";
					else if (strcmp(word.c_str(),"~=") == 0)
                        operater1 = "~=";
					else
					{
						con_count = -1;
						cout<<"Error in syntax!"<<endl;
						return 0;
					}
					word = getWord(s,&tmp);
					if (!word.empty())
					{
						if (word[0] == 39 && word[word.size()-1] == 39)
							word = word.substr(1,word.size()-2);
						condition1 = word;
					}
					else
					{
						con_count = -1;
						cout<<"Error in syntax!"<<endl;
						return 0;
					}
				}
				else
				{
					con_count = -1;
					cout<<"Error in syntax!"<<endl;
					return 0;
				}

				word = getWord(s,&tmp);
				if (!word.empty())			//�ڶ�������
				{
					if (strcmp(word.c_str(),"and") == 0)
						logic = AND;
					else if (strcmp(word.c_str(),"or") == 0)
						logic = OR;
					else
					{
						con_count = -1;
						cout<<"Error in syntax!"<<endl;
						return 0;
					}

					word = getWord(s,&tmp);
					if (!word.empty())
					{
						col2 = word;
						con_count = 2;
						word = getWord(s,&tmp);
						if (word.empty())
						{
							con_count = -1;
							cout<<"Error in syntax!"<<endl;
							return 0;
						}
						else if (strcmp(word.c_str(),"<=") == 0)
							operater2 = "<=";
						else if (strcmp(word.c_str(),">=") == 0)
							operater2 = ">=";
						else if (strcmp(word.c_str(),"<") == 0)
							operater2 = "<";
						else if (strcmp(word.c_str(),">") == 0)
							operater2 = ">";
						else if (strcmp(word.c_str(),"==") == 0)
							operater2 = "==";
						else
						{
							con_count = -1;
							cout<<"Error in syntax!"<<endl;
							return 0;
						}
						word = getWord(s,&tmp);
						if (!word.empty())
						{
							condition2 = word;
						}
						else
						{
							con_count = -1;
							cout<<"Error in syntax!"<<endl;
							return 0;
						}
					}
					else
					{
						con_count = -1;
						cout<<"Error in syntax!"<<endl;
						return 0;
					}
				}

			}
			if (con_count < 0)
			{
				cout<<"Error in syntax!"<<endl;
				return 0;
			}
		}

	}

	else if (fk_word == DROP)		//����һ�ؼ���Ϊdropʱ��ͬ���жϵڶ��ؼ�����ȷ����������
	{
		word = getWord(s,&tmp);
		if (strcmp(word.c_str(), "table") == 0)
			sk_word = TABLE;
		else if(strcmp(word.c_str(), "index") == 0)
			sk_word = INDEX;
		else
		{
			cout<<"Error in syntax!"<<endl;
			return 0;
		}
		if (sk_word == TABLE)
		{
			word = getWord(s,&tmp);
			if (!word.empty())
				fileName = word;
			else
			{
				cout<<"Error in syntax!"<<endl;
				return 0;
			}
		}

	}


	else if (fk_word == DELETE)		//����һ�ؼ���Ϊdeleteʱ�ж�ǰ���﷨��ȷ��where��Ĳ���ͬselect��䡣
	{
		word = getWord(s,&tmp);
		if (strcmp(word.c_str(),"from") == 0)
		{
			word = getWord(s,&tmp);
			if (!word.empty())
			{
				fileName = word;
				word = getWord(s,&tmp);
				if (strcmp(word.c_str(),"where") == 0)
				{
					word = getWord(s,&tmp);		//col1
					if (!word.empty())
					{
						col1 = word;
						con_count = 1;
						word = getWord(s,&tmp);
						if (word.empty())
						{
							con_count = -1;
							cout<<"Error in syntax!"<<endl;
							return 0;
						}
						else if (strcmp(word.c_str(),"<=") == 0)
							operater1 = "<=";
						else if (strcmp(word.c_str(),">=") == 0)
							operater1 = ">=";
						else if (strcmp(word.c_str(),"<") == 0)
							operater1 = "<";
						else if (strcmp(word.c_str(),">") == 0)
							operater1 = ">";
						else if (strcmp(word.c_str(),"=") == 0)
							operater1 = "=";
						else
						{
							con_count = -1;
							cout<<"Error in syntax!"<<endl;
							return 0;
						}
						word = getWord(s,&tmp);
						if (!word.empty())
						{
							if (word[0] == 39 && word[word.size()-1] == 39)
								word = word.substr(1,word.size()-2);
							condition1 = word;
						}
						else
						{
							con_count = -1;
							cout<<"Error in syntax!"<<endl;
							return 0;
						}
					}
					else
					{
						con_count = -1;
						cout<<"Error in syntax!"<<endl;
						return 0;
					}

					word = getWord(s,&tmp);
					if (!word.empty())			//�ڶ�������
					{
						if (strcmp(word.c_str(),"and") == 0)
							logic = AND;
						else if (strcmp(word.c_str(),"or") == 0)
							logic = OR;
						else
						{
							con_count = -1;
							cout<<"Error in syntax!"<<endl;
							return 0;
						}

						word = getWord(s,&tmp);
						if (!word.empty())
						{
							col2 = word;
							con_count = 2;
							word = getWord(s,&tmp);
							if (word.empty())
							{
								con_count = -1;
								cout<<"Error in syntax!"<<endl;
								return 0;
							}
							else if (strcmp(word.c_str(),"<=") == 0)
								operater2 = "<=";
							else if (strcmp(word.c_str(),">=") == 0)
								operater2 = ">=";
							else if (strcmp(word.c_str(),"<") == 0)
								operater2 = "<";
							else if (strcmp(word.c_str(),">") == 0)
								operater2 = ">";
							else if (strcmp(word.c_str(),"=") == 0)
								operater2 = "=";
							else
							{
								con_count = -1;
								cout<<"Error in syntax!"<<endl;
								return 0;
							}
							word = getWord(s,&tmp);
							if (!word.empty())
							{
								condition2 = word;
							}
							else
							{
								con_count = -1;
								cout<<"Error in syntax!"<<endl;
								return 0;
							}
						}
						else
						{
							con_count = -1;
							cout<<"Error in syntax!"<<endl;
							return 0;
						}
					}

				}
				else if (!word.empty())
				{
					cout<<"Error in syntax!"<<endl;
					return 0;
				}
			}
			else
			{
				cout<<"Error in syntax!"<<endl;
				return 0;
			}
		}
		else
		{
			cout<<"Error in syntax!"<<endl;
			return 0;
		}
	}

	else if (fk_word == INSERT)		//��һ�ؼ���Ϊinsertʱ
	{
		word = getWord(s,&tmp);
		if (strcmp(word.c_str(),"into") == 0)
		{
			word = getWord(s,&tmp);
			if (!word.empty())
			{
				fileName = word;
				word = getWord(s,&tmp);
				if (strcmp(word.c_str(),"values") == 0)		//��values�����ֵ��һ��ȡ��
				{
					word = getWord(s,&tmp);
					if (strcmp(word.c_str(),"(") == 0)
					{
						word = getWord(s,&tmp);
						while (!word.empty() && strcmp(word.c_str(),")") != 0)
						{
							insertValue.push_back(word);
							word = getWord(s,&tmp);
							if (strcmp(word.c_str(),",") == 0)
								word = getWord(s,&tmp);
						}
						if (strcmp(word.c_str(),")") != 0)
						{
							cout<<"Error in syntax!"<<endl;
							return 0;
						}
					}
					else
					{
						cout<<"Error in syntax!"<<endl;
						return 0;
					}
				}
				else
				{
					cout<<"Error in syntax!"<<endl;
					return 0;
				}
			}
			else
			{
				cout<<"Error in syntax!"<<endl;
				return 0;
			}
		}
		else
		{
			cout<<"Error in syntax!"<<endl;
			return 0;
		}
	}


	else if (fk_word == QUIT)
	{}

	else if (fk_word == COMMIT)
	{}
	else if (fk_word == EXECFILE)
	{
		fileName = getWord(s,&tmp);

	}
	return 1;

}

void CreateDatabase(string DbName)     //�������ݿ�
{
    db_info NewDatabase;
    NewDatabase.dbname=DbName;
    dblist.push_back(NewDatabase);
}

void ShowDatabase(void)
{
    vector<db_info>::iterator it;
    for(it=dblist.begin();it<dblist.end();it++)
    cout<<(*it).dbname<<endl;
}

void ShowColumn(string TableName)     //��ʾ��ǰ���ݿ�ָ����ĸ��е�����
{
    vector<table_info>::iterator it;
    int flag=0;
    it=(*db_p).tlist.begin();
    for(;it<(*db_p).tlist.end();it++)
    {
        if((*it).tablename==TableName)
        {
            flag=1;

           /*vector<string>::iterator sit;
            for(sit=(*it).colname.begin();sit<(*it).colname.end()-1;sit++)
            {
                cout<<(*sit)<<",";
            }
            cout<<*sit<<endl;*/
            unsigned int i;
            for( i = 0; i < (*it).colist.size()-1; i++)
            {

                    cout<<(*it).colist[i].colname;
                    if(i != (*it).colist.size()-2)
                        cout<<",";

            }
            cout<<endl;
        }
        break;
    }
    if(!flag)
    cout<<"error"<<endl;
}

void UseDatabase(string DbName)        //ָ����ǰ�������ݿ�
{
    vector<db_info>::iterator it;
    int flag=0;
    for(it=dblist.begin();it<dblist.end();it++)
    {
        if((*it).dbname==DbName)
        {
            db_p=it;
            current_dbname=DbName;
            flag=1;
            //cout<<"current_dbname is "<<current_dbname<<endl;   //������Ϣ
            break;
        }
    }
    if(flag==0)
    cout<<"error"<<endl;
}

void CreateTable(string filename,vector<string> colname,vector<string> coltype)   //�����������뵽��ǰ���ݿ���
{
    table_info NewTable;
    NewTable.tablename=filename;
    column_info NewClumn;
    unsigned int ii;
    for(ii=0;ii<colname.size();ii++)
    {
        NewClumn.colname=colname[ii];
        NewClumn.coltype=coltype[ii];
        NewTable.colist.push_back(NewClumn);
    }


    NewTable.colist.push_back(NewClumn);

    //���뵽��Ӧ�����ݿ���
    vector<db_info>::iterator it;

    for(it=dblist.begin();it<dblist.end();it++)
    {
        if((*it).dbname==current_dbname)
        {
            (*it).tlist.push_back(NewTable);
            break;
        }
    }
}

void DropDatabase(string DbName)            //ɾ��ָ�������ݿ�
{
    vector<db_info>::iterator it;
    int flag=0;
    for(it=dblist.begin();it<dblist.end();it++)
    {
        if((*it).dbname==DbName)
        {
            if((*it).dbname==current_dbname)
            current_dbname="";
            dblist.erase(it);
            flag=1;
            break;
        }
    }
    if(flag==0)
    cout<<"error"<<endl;
}
void DropTable(string fileName)
{

}
void DropDbTable(string DbName,string TableName)       //ɾ��ָ�����ݿ��ĳ����
{
    vector<db_info>::iterator it;
    int flag=0;
    for(it=dblist.begin();it<dblist.end();it++)
    {
        if((*it).dbname==DbName)
        {
            vector<table_info>::iterator tit;
            for(tit=(*it).tlist.begin();tit<(*it).tlist.end();tit++)
            {
                if((*tit).tablename==TableName)
                {
                    flag=1;

                    (*it).tlist.erase(tit);
                    break;
                }
                if(flag)
                break;
            }
            break;
        }
    }
    if(flag==0)
    cout<<"error"<<endl;
}

void Select0(string TableName)
{
    int flag = 0;
    vector<table_info>::iterator p;
    for(p=(*db_p).tlist.begin();p<(*db_p).tlist.end();p++)
    {
        if((*p).tablename==TableName)
        {
            flag=1;
            unsigned int i;
            unsigned int j;
            for( j = 0; j < (*p).colist[i].line.size(); j++){
                for( i = 0; i < (*p).colist.size(); i++){
                    cout<<(*p).colist[i].line[j]<<",";
                }
            }
            break;
        }
        if(flag)
            break;
    }

}

void Select1(string Selection, string TableName, string Condition ,string  )
{

}
/*
void drop_table(string database_name,string table_name)
{
    vector<db>::iterator it;
    vector<table>::iterator ti;
    for(it=dblist.begin();it<dblist.end();it++)
    {
        if((*it).dbname==database_name)
        {
            for(ti=(*it).tlist.begin();ti<(*it).tlist.end();ti++)
                if((*ti).tablename==table_name)
                  erase(ti);
                else
                cout<<"error"<<endl;
        }
        else cout<<"error"<<endl;
    }
}
*/
