#include <iostream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;
#define CREATE 0  //first key
#define USE 100
#define SELECT 1
#define DROP 2
#define DELETE 3
#define INSERT 4
#define SHOW 5
#define QUIT 14
#define COMMIT 15
#define EXECFILE 16

#define TABLE 6   //second key
#define INDEX 7
#define UNKNOWN 8
#define DATABASE 9
#define DATABASES 10
#define COLUMN 11

#define AND 12	//logic
#define OR 13

int firstKey;		//第一关键字。
int secondKey;		//第二关键字。
string fileName;	//操作对象。


int condNum;		//where后条件的个数。
int logic;		//两个条件之间的逻辑连接符。
string operater1;	//条件一中的关系运算符。
string operater2;	//条件二中的关系运算符。
string col1;		//where关键字后第一个条件中涉及的列名。
string col2;		//where关键字后第二个条件中涉及的列名。
string  condition1;	//where关键字后第一个条件中逻辑运算符后的常量。
string  condition2;	//where关键字后第二个条件中逻辑运算符后的常量。

vector<string> insertValue;  	//insert语句中values后括号中的各个值。（存在一个vector变量中）


vector<string> type;		//create语句建表时的列属性，按顺序存在一个vector变量中
vector<string> col;		//create语句建表时的列名。
vector<int> uniq;		//create语句建表时的列名。
string primKey;			//create语句建表时定义的该表的primary key

string tableName;
string colName;

typedef struct colunmn
{
    string colname;
    string type;
    vector<string> record;
}colm;

typedef struct table
{
    string tablename;
    vector<string> colname;
    vector<string> coltype;
    //vector<string> record;
    //vector<colm> colist;
}table;

typedef struct database
{
    string dbname;
    vector<table> tlist;
}db;

vector<db> dblist;
//全局变量,当前用的数据库
string current_dbname="";
vector<db>::iterator db_p;   //全局变量，指向当前的数据库

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
	if (strcmp(word.c_str(), "create") == 0)
		firstKey = CREATE;
    else if(strcmp(word.c_str(), "use") == 0)
        firstKey = USE;
    else if (strcmp(word.c_str(),"show") == 0)
        firstKey =SHOW;
	else if (strcmp(word.c_str(), "select") == 0)
		firstKey = SELECT;
	else if (strcmp(word.c_str(), "drop") == 0)
		firstKey = DROP;
	else if (strcmp(word.c_str(), "delete") == 0)
		firstKey = DELETE;
	else if (strcmp(word.c_str(), "insert") == 0)
		firstKey = INSERT;
	else if (strcmp(word.c_str(), "quit") == 0)
		firstKey = QUIT;
	else if (strcmp(word.c_str(), "commit") == 0)
		firstKey = COMMIT;
	else if (strcmp(word.c_str(), "execfile") ==0)
		firstKey = EXECFILE;
	else
	{
		cout<<"Error, command "<<word<<" not found"<<endl;
		return 0;
	}

//第二层
	if (firstKey == CREATE)		//第一关键字为create，则需要读取第二关键字判断创建对象。
	{
		word = getWord(s,&tmp);
		if (strcmp(word.c_str(), "table") == 0)
			secondKey = TABLE;
        else if(strcmp(word.c_str(),"database") == 0) //database
            secondKey = DATABASE;
		else if(strcmp(word.c_str(), "index") == 0)
			secondKey = INDEX;
		else
		{
			cout<<"Error, Usage: "<<firstKey<<" table or index fileName"<<endl;
			return 0;
		}
        if (secondKey == DATABASE)          //      新加的
        {
            word = getWord(s,&tmp);
			if (!word.empty())			//create database database_name 正确
				fileName = word;
			else
			{
				cout<<"Error, Usage: "<<firstKey<<" table or index fileName"<<endl;
				return 0;
			}
        }
		else if (secondKey == TABLE)
		{
			word = getWord(s,&tmp);
			if (!word.empty())			//create table tablename 正确
				fileName = word;
			else
			{
				cout<<"Error, Usage: "<<firstKey<<" table or index fileName"<<endl;
				return 0;
			}
			if (secondKey == TABLE)			//第二关键字为table，即创建表
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

						if (secondKey == TABLE)
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
		else if (secondKey == INDEX)			//当第二关键字为index时，判定为创建索引。
		{
			word = getWord(s,&tmp);
			if (!word.empty())			//create index indexname 正确
				fileName = word;
			else
			{
				cout<<"Error in syntax!"<<endl;
				return 0;
			}
			if (secondKey == INDEX)			//对创建索引的语句进行深入语法判断
			{
				word = getWord(s,&tmp);
				if (strcmp(word.c_str(),"on") == 0)
				{
					word = getWord(s,&tmp);
					if (!word.empty())
					{
						tableName = word;
						word = getWord(s,&tmp);
						if (strcmp(word.c_str(),"(") == 0)
						{
							word = getWord(s,&tmp);
							if (!word.empty())
							{
								colName = word;
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
		}
	}

    else if (firstKey == USE)
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

    else if (firstKey == SHOW)
    {
        word = getWord(s,&tmp);
        if (strcmp(word.c_str(), "databases") == 0)
        secondKey = DATABASES;
        else
        {
            fileName = word;
            word = getWord(s,&tmp);
            if (strcmp(word.c_str(),"column") == 0)     //show table_name column;
            {
                secondKey = COLUMN;
            }
        }
        /*

        */
    }

	else if (firstKey == SELECT)		//第一关键字为select
	{
		word = getWord(s,&tmp);
		if (strcmp(word.c_str(), "*") != 0)	//又要minisql只支持select *的查找方式，所以这里对除了select *以外的情况作为错误处理。
		{
			cout<<"Error in syntax!"<<endl;
			return 0;
		}
		if (firstKey == SELECT)		//select * 后语法正确
		{
			word = getWord(s,&tmp);
			if (strcmp(word.c_str(), "from") != 0)
			{
				cout<<"Error in syntax!"<<endl;
				return 0;
			}
		}
		if (firstKey == SELECT)		//select * from后语法正确
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
		if (firstKey == SELECT)		//在前面语法均正确的情况下，读取查询条件。
		{
			word = getWord(s,&tmp);
			if (word.empty())	//无条件
				condNum = 0;
			else if (strcmp(word.c_str(),"where") == 0)	//存在where
			{
				word = getWord(s,&tmp);		//col1
				if (!word.empty())
				{
					col1 = word;
					condNum = 1;
					word = getWord(s,&tmp);
					if (word.empty())
					{
						condNum = -1;
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
						condNum = -1;
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
						condNum = -1;
						cout<<"Error in syntax!"<<endl;
						return 0;
					}
				}
				else
				{
					condNum = -1;
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
						condNum = -1;
						cout<<"Error in syntax!"<<endl;
						return 0;
					}

					word = getWord(s,&tmp);
					if (!word.empty())
					{
						col2 = word;
						condNum = 2;
						word = getWord(s,&tmp);
						if (word.empty())
						{
							condNum = -1;
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
							condNum = -1;
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
							condNum = -1;
							cout<<"Error in syntax!"<<endl;
							return 0;
						}
					}
					else
					{
						condNum = -1;
						cout<<"Error in syntax!"<<endl;
						return 0;
					}
				}

			}
			if (condNum < 0)
			{
				cout<<"Error in syntax!"<<endl;
				return 0;
			}
		}
	}



	else if (firstKey == DROP)		//当第一关键字为drop时，同样判断第二关键字以确定操作对象
	{
		word = getWord(s,&tmp);
		if (strcmp(word.c_str(), "table") == 0)
			secondKey = TABLE;
		else if(strcmp(word.c_str(), "index") == 0)
			secondKey = INDEX;
		else
		{
			cout<<"Error in syntax!"<<endl;
			return 0;
		}
		if (secondKey == TABLE)
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
		else if (secondKey == INDEX)
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


	else if (firstKey == DELETE)		//当第一关键字为delete时判断前面语法正确后，where后的操作同select语句。
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
						condNum = 1;
						word = getWord(s,&tmp);
						if (word.empty())
						{
							condNum = -1;
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
							condNum = -1;
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
							condNum = -1;
							cout<<"Error in syntax!"<<endl;
							return 0;
						}
					}
					else
					{
						condNum = -1;
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
							condNum = -1;
							cout<<"Error in syntax!"<<endl;
							return 0;
						}

						word = getWord(s,&tmp);
						if (!word.empty())
						{
							col2 = word;
							condNum = 2;
							word = getWord(s,&tmp);
							if (word.empty())
							{
								condNum = -1;
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
								condNum = -1;
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
								condNum = -1;
								cout<<"Error in syntax!"<<endl;
								return 0;
							}
						}
						else
						{
							condNum = -1;
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



	else if (firstKey == INSERT)		//第一关键字为insert时
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


	else if (firstKey == QUIT)
	{}

	else if (firstKey == COMMIT)
	{}
	else if (firstKey == EXECFILE)
	{
		fileName = getWord(s,&tmp);

	}
	return 1;

}

void create_database(string dbname)     //创建数据库
{
    db new_database;
    new_database.dbname=dbname;
    dblist.push_back(new_database);
}

void show_dbs(void)
{
    vector<db>::iterator it;
    for(it=dblist.begin();it<dblist.end();it++)
    cout<<(*it).dbname<<endl;
}

void show_column(string tablename)     //显示当前数据库指定表的各列的名字
{
    vector<table>::iterator it;
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
    vector<db>::iterator it;
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
    table new_table;
    new_table.tablename=filename;
    new_table.colname=colname;
    new_table.coltype=coltype;
    //加入到对应的数据库中
    vector<db>::iterator it;
    for(it=dblist.begin();it<dblist.end();it++)
    {
        if((*it).dbname==current_dbname)
        {
            (*it).tlist.push_back(new_table);
            break;
        }
    }
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
int main()
{
    cout<<"*******************Welocme to use our MiniSQL**********************"<<endl;
    while(1)
    {
        string s;
        cout<<">>";
        //以';'作为SQL语句结束的标志,输入一条SQL语句
        getline(cin,s,';');
        if(!interpreter(s))
        continue;
        		//对firstKey进行遍历，分类处理
		switch(firstKey)
		{

			case CREATE:

                if(secondKey==DATABASE)
                    create_database(fileName);

				else if(secondKey==TABLE)
					create_table(fileName,col,type);

				break;

            case USE:
                use_database(fileName);
                break;

            case SHOW:
                if(secondKey==DATABASES)
                    show_dbs();
                else if(secondKey==COLUMN)
                    show_column(fileName);
                else cout<<"wait to do"<<endl,cout<<"here"<<endl;
                break;
            /*
			//firstKey为select
			case SELECT:
				//无where条件查寻
				if(condNum==0)
					printRecord(fileName);
				//一个where条件查寻
				else if(condNum==1)
					printRecord(fileName,col1,condition1,operater1);
				//二个where条件查寻
				else
					printRecord(fileName,col1,condition1,operater1,
						col2,condition2,operater2,logic);
				break;
			//firstKdy为drop
			case DROP:
				//删除表
				if(secondKey==TABLE)
					dropTable(fileName);
				//删除索引
				else if(secondKey==INDEX)
					dropIndex(fileName);
				else
					cout<<"Error. Usage: drop table name or index name"<<endl;
				break;
			//firstKey为delete
			case DELETE:
				//无条件删除所有记录
				if(condNum==0)
					deleteValue(fileName);
				//根据一个where条件删除满足条件的记录
				else if(condNum==1)
					deleteValue(fileName,col1,condition1,operater1);
				//根据两个where条件删除满足条件的记录
				else
					deleteValue(fileName,col1,condition1,operater1,
									col2,condition2,operater2,logic);
				break;
			//firstKey为insert
			case INSERT:
				insertRecord(fileName,insertValue);
				break;
			//firstKey为quit
			case QUIT:
				break;

			case COMMIT:
                break;

			case EXECFILE:
				break;
            */
		}
    }
    return 0;
}
