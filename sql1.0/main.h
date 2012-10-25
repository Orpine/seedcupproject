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

int fk_word;		//第一关键字。
int sk_word;		//第二关键字。
string fileName;	//操作对象。


int con_count;		//where后条件的个数。
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

typedef struct table_info
{
    string tablename;
    vector<string> colname;
    vector<string> coltype;
    //vector<string> record;
    //vector<colm> colist;
}table_info;

typedef struct database_info
{
    string dbname;
    vector<table_info> tlist;
}db_info;

vector<db_info> dblist;
//全局变量,当前用的数据库
string current_dbname="";
vector<db_info>::iterator db_p;   //全局变量，指向当前的数据库

string getWord(string s, int *tmp);
int interpreter(string s);
void create_database(string dbname) ;
void show_dbs(void);
void show_column(string tablename);
void use_database(string dbname);
void create_table(string filename,vector<string> colname,vector<string> coltype);
void dropDatabase(string dbname)  ;
void dropTable(string fileName);
void dropDbTable(string dbname,string tablename) ;
