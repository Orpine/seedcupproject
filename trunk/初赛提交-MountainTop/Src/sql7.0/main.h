#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include<algorithm>
#include<stdio.h>
using namespace std;

#define CREATE 0
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

#define TABLE 6
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
char KeyWords[31][15] = {"int", "float", "text", "create", "table", "database", "column", "use", "insert",
                    "into", "show", "select", "delete", "update", "set", "rename", "drop", "alter", "truncate",
                    "add", "values", "where", "order", "from", "or", "and", "by", "between", "desc", "incr", "like"};

vector<string> Rselection;
string RfileName;
string Rcondition1;
string Roperater1;
string Rcolumn;
int Rcon_count;
int ShowN = 0;

typedef struct column_info    //列结构
{
    string colname;     //列名
    string coltype;   //列类型
    vector<string> line;   //行
}column_info;

typedef struct table_info        //表结构
{
    string tablename;     //表名
    vector<column_info> colist;   //列
}table_info;

typedef struct db_info    //库 结构
{
    string dbname;    //库名
    vector<table_info> tlist;   //表
}db_info;

vector<db_info> dblist;          //全局变量,当前用的数据库
string current_dbname="";
vector<db_info>::iterator db_p;   //全局变量，指向当前的数据库

string getWord(string s, int *tmp);
int interpreter(string s);           //SQL语句解析函数
int Matching(string ColType,string Value,string Condition,string Condition11,string Operation); //处理where后条件
bool CreateDatabase(string DbName) ;   //创建数据库
bool ShowDatabase(void);                   //显示数据库
bool ShowColumn(string TableName);        //显示表的列名
bool UseDatabase(string DbName);          //指定当前数据库
bool CreateTable(string filename,vector<string> colname,vector<string> coltype);     //创建表
bool Drop(string FirstWord, string SecondWord) ;       //删除表或数据库
bool Select0(string TableName, vector<string> Selection,string OrderColu, int Orderby, int Orderdi);   //选取函数，where后无条件
bool Select1(vector<string> Selection, string TableName,string Column, string Condition, string Condition11, string Operation, int Shown,string OrderColu, int Orderby, int Orderdi); //where后1条件
bool Select2(vector<string> Selection, string TableName, string Column1, string Condition1,string Operation1,
             string Column2,  string Condition2,  string Operation2, int Logic);  //where后2条件
bool Select3(vector<string> Selection, string TableName, string Column1, string Condition1,string Operation1,
             string Column2,  string Condition2,  string Operation2,string Column3, string Condition3,string Operation3, int Logic1, int Logic2, int infront);//where后3条件
bool Select4(vector<string> Selection, string TableName, string Column1, string Condition1,string Operation1,
             string Column2,  string Condition2,  string Operation2,string Column3, string Condition3,string Operation3,
             string Column4, string Condition4,string Operation4, int Logic1, int Logic2, int Logic3,int infront1,int infront2);//where后4条件
bool Insert(string TableName,vector<string> TableCloumn, vector<string> Values);     //插入函数
bool Delete(string TableName, string Column, string Condition, string Condition11, string Operation);   //删除函数
bool Alter_1(string tableName,string delName);       //插入列
bool Alter(string tablename,string colName,string colType);    //删除已有列
bool Alter_2(string tableName,string colName,string colType);   //修改列数据
bool Rename_Table(string old_name,string new_name);          //重命名表
bool Rename_Database(string old_name,string new_name);    //重命名库
bool ShowTables(void);           //显示当前数据库所有表
void update_cond1(string filename,vector<string> colname,vector<string> values,string cond,string operater,string condition);  //修改表中数据
bool truncate(string TableName);   //删除表中数据保留表中结构
char LikeMatch(string Str1, string Str2);
bool cmp2(string a,string b);
bool cmp1(string a,string b);
bool ShowColumn1(string TableName,int OrderDI);    //排序输出列名
bool ShowTables1(int OrderDI);
bool ShowDatabase1(int OrderDI);
int logic_handle(string y);
