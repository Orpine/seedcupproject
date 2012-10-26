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
vector<string> selection;   //选取的列名
string operater1;	//条件一中的关系运算符。
string operater2;	//条件二中的关系运算符。
string col1;		//where关键字后第一个条件中涉及的列名。
string col2;		//where关键字后第二个条件中涉及的列名。
string  condition1;	//where关键字后第一个条件中逻辑运算符后的常量。
string  condition2;	//where关键字后第二个条件中逻辑运算符后的常量。

vector<string> insertValue;  	//insert语句中values后括号中的各个值。（存在一个vector变量中）
vector<string> TableCloumns;    //insert语句中table 列的各值

vector<string> Type;		//create语句建表时的列属性，按顺序存在一个vector变量中
vector<string> Colu;		//create语句建表时的列名。
vector<int> uniq;		//create语句建表时的列名。
string primKey;			//create语句建表时定义的该表的primary key

string tableName;
string colName;

typedef struct column_info
{
    string colname;
    string coltype;
    vector<string> line;
}column_info;

typedef struct table_info
{
    string tablename;
    vector<column_info> colist;
}table_info;

typedef struct database_info
{
    string dbname;
    vector<table_info> tlist;
    struct database_info *next;
}db_info;

vector<db_info> dblist;          //全局变量,当前用的数据库
string current_dbname="";
vector<db_info>::iterator db_p;   //全局变量，指向当前的数据库




string getWord(string s, int *tmp);
int interpreter(string s);
bool CreateDatabase(string DbName) ;
bool ShowDatabase(void);
bool ShowColumn(string TableName);
bool UseDatabase(string DbName);
bool CreateTable(string filename,vector<string> colname,vector<string> coltype);
bool DropDatabase(string DbName)  ;
bool DropTable(string fileName);
bool DropDbTable(string DbName,string TableName) ;
bool Select0(string TableName, vector<string> Selection);
bool Select1(vector<string> Selection, string TableName,string Column, string Condition ,string Operator );
bool Insert(string TableName,vector<string> TableCloumn, vector<string> Values);
