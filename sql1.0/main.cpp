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
    while(!file.eof())      //判定文件尾用while(file)或前面那样都可以。
   // while(1)
    {
        string s;
        cout<<">>";
        //以';'作为SQL语句结束的标志,输入一条SQL语句
        getline(cin,s,';');
        //if(s.empty()) break;
        if(!interpreter(s))
        continue;
        		//对fk_word进行遍历，分类处理
		switch(fk_word)
		{

			case CREATE:

                if(sk_word==DATABASE)
                    create_database(fileName);

				else if(sk_word==TABLE)
					create_table(fileName,col,type);

				break;

            case USE:
                use_database(fileName);
                break;

            case SHOW:
                if(sk_word==DATABASES)
                    show_dbs();
                else if(sk_word==COLUMN)
                    show_column(fileName);
                else cout<<"wait to do"<<endl,cout<<"here"<<endl;
                break;
            //firstKdy为drop
			case DROP:
				//删除表
				if(sk_word==TABLE)
					dropTable(fileName);

				else if(sk_word==DATABASE)
					dropDatabase(fileName);
				else
					cout<<"Error. Usage: drop table name or index name"<<endl;
				break;
            /*
			//fk_word为select
			case SELECT:
				//无where条件查寻
				if(con_count==0)
					printRecord(fileName);
				//一个where条件查寻
				else if(con_count==1)
					printRecord(fileName,col1,condition1,operater1);
				//二个where条件查寻
				else
					printRecord(fileName,col1,condition1,operater1,
						col2,condition2,operater2,logic);
				break;

			//fk_word为delete
			case DELETE:
				//无条件删除所有记录
				if(con_count==0)
					deleteValue(fileName);
				//根据一个where条件删除满足条件的记录
				else if(con_count==1)
					deleteValue(fileName,col1,condition1,operater1);
				//根据两个where条件删除满足条件的记录
				else
					deleteValue(fileName,col1,condition1,operater1,
									col2,condition2,operater2,logic);
				break;
			//fk_word为insert
			case INSERT:
				insertRecord(fileName,insertValue);
				break;
			//fk_word为quit
			case QUIT:
				break;

			case COMMIT:
                break;

			case EXECFILE:
				break;
            */
		}
    }
    fclose(stdin );
    return 0;
}


string getWord(string s, int *tmp)		//子函数，作用：读取SQL命令中下一个关键字。
{
	string word;
	int idx1,idx2,i;

	while ((s[*tmp] == ' ' || s[*tmp] == 10) && s[*tmp] != 0)	//去除前面无用的空格及换行符
	{
		(*tmp)++;
	}
	idx1 = *tmp;

	if (s[*tmp] == '(' || s[*tmp] == ',' || s[*tmp] == ')')		//对左括号、逗号和右括号做特别处理。
	{
		(*tmp)++;
		idx2 = *tmp;
		word = s.substr(idx1,idx2-idx1);
		return word;
	}
	else if (s[*tmp] == 39)					//对单引号内字符做特别处理。
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
	else				//除上述几种特殊情况外的普通处理
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

//第一层，读取第一个关键字
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

//第二层
	if (fk_word == CREATE)		//第一关键字为create，则需要读取第二关键字判断创建对象。
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
        if (sk_word == DATABASE)          //      新加的
        {
            word = getWord(s,&tmp);
			if (!word.empty())			//create database database_name 正确
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
			if (!word.empty())			//create table tablename 正确
				fileName = word;
			else
			{
				cout<<"Error, Usage: "<<fk_word<<" table or index fileName"<<endl;
				return 0;
			}
			if (sk_word == TABLE)			//第二关键字为table，即创建表
			{
				word = getWord(s,&tmp);
				if (word.empty() || strcmp(word.c_str(),"(") != 0)
				{
					cout<<"Error in syntax!"<<endl;
					return 0;
				}
				else				//在读取左括号后逐一记录一下的列名和属性。
				{
					word = getWord(s,&tmp);
					while (!word.empty() && strcmp(word.c_str(),"primary") != 0 && strcmp(word.c_str(),")") != 0)
					{
						col.push_back(word);
						word = getWord(s,&tmp);
						if (!word.empty())
							type.push_back(word);
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
					if (strcmp(word.c_str(),"primary") == 0)	//当当前操作字符为primary时，判断为主键定义，退出列名属性读取的循环。
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

	else if (fk_word == SELECT)		//第一关键字为select
	{
		word = getWord(s,&tmp);
		if (strcmp(word.c_str(), "*") != 0)	//又要minisql只支持select *的查找方式，所以这里对除了select *以外的情况作为错误处理。
		{
			cout<<"Error in syntax!"<<endl;
			return 0;
		}
		if (fk_word == SELECT)		//select * 后语法正确
		{
			word = getWord(s,&tmp);
			if (strcmp(word.c_str(), "from") != 0)
			{
				cout<<"Error in syntax!"<<endl;
				return 0;
			}
		}
		if (fk_word == SELECT)		//select * from后语法正确
		{
			word = getWord(s,&tmp);		//表名
			if (!word.empty())
				fileName = word;
			else
			{
				cout<<"Error in syntax!"<<endl;
				return 0;
			}
		}
		if (fk_word == SELECT)		//在前面语法均正确的情况下，读取查询条件。
		{
			word = getWord(s,&tmp);
			if (word.empty())	//无条件
				con_count = 0;
			else if (strcmp(word.c_str(),"where") == 0)	//存在where
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
				if (!word.empty())			//第二个条件
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
			if (con_count < 0)
			{
				cout<<"Error in syntax!"<<endl;
				return 0;
			}
		}
	}



	else if (fk_word == DROP)		//当第一关键字为drop时，同样判断第二关键字以确定操作对象
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


	else if (fk_word == DELETE)		//当第一关键字为delete时判断前面语法正确后，where后的操作同select语句。
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
					if (!word.empty())			//第二个条件
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



	else if (fk_word == INSERT)		//第一关键字为insert时
	{
		word = getWord(s,&tmp);
		if (strcmp(word.c_str(),"into") == 0)
		{
			word = getWord(s,&tmp);
			if (!word.empty())
			{
				fileName = word;
				word = getWord(s,&tmp);
				if (strcmp(word.c_str(),"values") == 0)		//对values后面的值逐一读取。
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

void create_database(string dbname)     //创建数据库
{
    db_info new_database;
    new_database.dbname=dbname;
    dblist.push_back(new_database);
}

void show_dbs(void)
{
    vector<db_info>::iterator it;
    for(it=dblist.begin();it<dblist.end();it++)
    cout<<(*it).dbname<<endl;
}

void show_column(string tablename)     //显示当前数据库指定表的各列的名字
{
    vector<table_info>::iterator it;
    int flag=0;
    it=(*db_p).tlist.begin();
    for(;it<(*db_p).tlist.end();it++)
    {
        if((*it).tablename==tablename)
        {
            flag=1;
            vector<string>::iterator sit;
            for(sit=(*it).colname.begin();sit<(*it).colname.end()-1;sit++)
            {
                cout<<(*sit)<<",";
            }
            cout<<*sit<<endl;
        }
        break;
    }
    if(!flag)
    cout<<"error"<<endl;
}

void use_database(string dbname)        //指定当前操作数据库
{
    vector<db_info>::iterator it;
    int flag=0;
    for(it=dblist.begin();it<dblist.end();it++)
    {
        if((*it).dbname==dbname)
        {
            db_p=it;
            current_dbname=dbname;
            flag=1;
            //cout<<"current_dbname is "<<current_dbname<<endl;   //调试信息
            break;
        }
    }
    if(flag==0)
    cout<<"error"<<endl;
}

void create_table(string filename,vector<string> colname,vector<string> coltype)   //创建表，并加入到当前数据库中
{
    table_info new_table;
    new_table.tablename=filename;
    new_table.colname=colname;
    new_table.coltype=coltype;
    //加入到对应的数据库中
    vector<db_info>::iterator it;

    for(it=dblist.begin();it<dblist.end();it++)
    {
        if((*it).dbname==current_dbname)
        {
            (*it).tlist.push_back(new_table);
            break;
        }
    }
}

void dropDatabase(string dbname)            //删除指定的数据库
{
    vector<db_info>::iterator it;
    int flag=0;
    for(it=dblist.begin();it<dblist.end();it++)
    {
        if((*it).dbname==dbname)
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
void dropTable(string fileName)
{

}
void dropDbTable(string dbname,string tablename)       //删除指定数据库的某个表
{
    vector<db_info>::iterator it;
    int flag=0;
    for(it=dblist.begin();it<dblist.end();it++)
    {
        if((*it).dbname==dbname)
        {
            vector<table_info>::iterator tit;
            for(tit=(*it).tlist.begin();tit<(*it).tlist.end();tit++)
            {
                if((*tit).tablename==tablename)
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
