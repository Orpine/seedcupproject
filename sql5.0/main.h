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
#define ALTER 17
#define RENAME 18
#define UPDATE 19

#define TABLE 6   //second key
#define INDEX 7
#define UNKNOWN 8
#define DATABASE 9
#define DATABASES 10
#define COLUMN 11

#define AND 12	//logic
#define OR 13


int re_count;       //rename db？table 选择
int fk_word;		//第一关键字。
int sk_word;		//第二关键字。
string fileName;	//操作对象。
string tableName;   //表
string colName;    // 列
string colType;  //类型
string new_name;//新的db table name
string old_name;//老的db table name

string DropFword;
string DropSword;

int alt_count;      //alter形式选择
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

vector<string> values;
string operater;
string condition;
vector<string> colname;
string cond;

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

typedef struct db_info
{
    string dbname;
    vector<table_info> tlist;
}db_info;

vector<db_info> dblist;          //全局变量,当前用的数据库
string current_dbname="";
vector<db_info>::iterator db_p;   //全局变量，指向当前的数据库




string getWord(string s, int *tmp);
int interpreter(string s);
int Matching(string ColType,string Value,string Condition,string Operation);
bool CreateDatabase(string DbName) ;
bool ShowDatabase(void);
bool ShowColumn(string TableName);
bool UseDatabase(string DbName);
bool CreateTable(string filename,vector<string> colname,vector<string> coltype);
bool Drop(string FirstWord, string SecondWord) ;
bool Select0(string TableName, vector<string> Selection);
bool Select1(vector<string> Selection, string TableName,string Column, string Condition ,string Operation );
bool Insert(string TableName,vector<string> TableCloumn, vector<string> Values);
bool Delete(string TableName, string Column, string Condition, string Operation);
bool Alter_1(string tableName,string delName);
void Alter(string tablename,string colName,string colType);
bool Alter_2(string tableName,string colName,string colType);
bool Rename_Table(string old_name,string new_name);
bool Rename_Database(string old_name,string new_name);
bool ShowTables(void);
void update_cond1(string filename,vector<string> colname,vector<string> values,string cond,string operater,string condition);
