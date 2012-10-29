#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include<algorithm>
#include<stdio.h>
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
#define TRUNCATE 21
#define AND 12	//logic
#define OR 13

int s_flag=1;
int re_count;       //rename db？table 选择
int fk_word;		//第一关键字。
int sk_word;		//第二关键字。
int OrderDI = 0;
int OrderBy = 0;
int alt_count;      //alter形式选择
int con_count;		//where后条件的个数。
int logic;		//两个条件之间的逻辑连接符

string fileName;	//操作对象。
string tableName;   //表
string colName;    // 列
string colType;  //类型
string new_name;//新的db table name
string old_name;//老的db table name
string DropFword;
string DropSword;
string operater1;	//条件一中的关系运算符。
string operater2;
string operater3;	//条件二中的关系运算符。
string operater4;
string col1;		//where关键字后第一个条件中涉及的列名。
string col2;
string col3;
string col4;
string cond;		//where关键字后第二个条件中涉及的列名。
string  condition1;	//where关键字后第一个条件中逻辑运算符后的常量。
string  condition2;	//where关键字后第二个条件中逻辑运算符后的常量。
string  condition3;
string  condition4;
int logic1;
int logic2;
int logic3;
int Infront;
int Infront1;
int Infront2;
int visit[1000];
int SelectSign = 0;
vector<int> SelectCan;
string condition11;
string OrderColumn = "";
string operater;
string condition;

vector<string> insertValue;  	//insert语句中values后括号中的各个值。（存在一个vector变量中）
vector<string> TableCloumns;    //insert语句中table 列的各值
vector<string> Type;		//create语句建表时的列属性，按顺序存在一个vector变量中
vector<string> Colu;		//create语句建表时的列名。
vector<string> selection;   //选取的列名
vector<string> values;
vector<string> colname;
vector<string> Ucolname;
vector<string> Uvalues;
vector<string> ReturnS;
char KeyWords[31][15]{"int", "float", "text", "create", "table", "database", "column", "use", "insert",
                    "into", "show", "select", "delete", "update", "set", "rename", "drop", "alter", "truncate",
                    "add", "values", "where", "order", "from", "or", "and", "by", "between", "desc", "incr", "like"};

vector<string> Rselection;
string RfileName;
string Rcondition1;
string Roperater1;
string Rcolumn;
int Rcon_count;
int ShowN = 0;

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
int Matching(string ColType,string Value,string Condition,string Condition11,string Operation);
bool CreateDatabase(string DbName) ;
bool ShowDatabase(void);
bool ShowColumn(string TableName);
bool UseDatabase(string DbName);
bool CreateTable(string filename,vector<string> colname,vector<string> coltype);
bool Drop(string FirstWord, string SecondWord) ;
bool Select0(string TableName, vector<string> Selection,string OrderColu, int Orderby, int Orderdi);
bool Select1(vector<string> Selection, string TableName,string Column, string Condition, string Condition11, string Operation, int Shown,string OrderColu, int Orderby, int Orderdi);
bool Select2(vector<string> Selection, string TableName, string Column1, string Condition1,string Operation1,
             string Column2,  string Condition2,  string Operation2, int Logic);
bool Select3(vector<string> Selection, string TableName, string Column1, string Condition1,string Operation1,
             string Column2,  string Condition2,  string Operation2,string Column3, string Condition3,string Operation3, int Logic1, int Logic2, int infront);
bool Select4(vector<string> Selection, string TableName, string Column1, string Condition1,string Operation1,
             string Column2,  string Condition2,  string Operation2,string Column3, string Condition3,string Operation3,
             string Column4, string Condition4,string Operation4, int Logic1, int Logic2, int Logic3,int infront1,int infront2);
bool Insert(string TableName,vector<string> TableCloumn, vector<string> Values);
bool Delete(string TableName, string Column, string Condition, string Condition11, string Operation);
bool Alter_1(string tableName,string delName);
bool Alter(string tablename,string colName,string colType);
bool Alter_2(string tableName,string colName,string colType);
bool Rename_Table(string old_name,string new_name);
bool Rename_Database(string old_name,string new_name);
bool ShowTables(void);
void update_cond1(string filename,vector<string> colname,vector<string> values,string cond,string operater,string condition);
bool truncate(string TableName);
char LikeMatch(string Str1, string Str2);
bool cmp2(string a,string b);
bool cmp1(string a,string b);
bool ShowColumn1(string TableName,int OrderDI);
bool ShowTables1(int OrderDI);
bool ShowDatabase1(int OrderDI);
int logic_handle(string y);
