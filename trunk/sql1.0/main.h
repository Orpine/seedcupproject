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

int fk_word;		//��һ�ؼ��֡�
int sk_word;		//�ڶ��ؼ��֡�
string fileName;	//��������


int con_count;		//where�������ĸ�����
int logic;		//��������֮����߼����ӷ���
string operater1;	//����һ�еĹ�ϵ�������
string operater2;	//�������еĹ�ϵ�������
string col1;		//where�ؼ��ֺ��һ���������漰��������
string col2;		//where�ؼ��ֺ�ڶ����������漰��������
string  condition1;	//where�ؼ��ֺ��һ���������߼��������ĳ�����
string  condition2;	//where�ؼ��ֺ�ڶ����������߼��������ĳ�����

vector<string> insertValue;  	//insert�����values�������еĸ���ֵ��������һ��vector�����У�


vector<string> type;		//create��佨��ʱ�������ԣ���˳�����һ��vector������
vector<string> col;		//create��佨��ʱ��������
vector<int> uniq;		//create��佨��ʱ��������
string primKey;			//create��佨��ʱ����ĸñ��primary key

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
//ȫ�ֱ���,��ǰ�õ����ݿ�
string current_dbname="";
vector<db_info>::iterator db_p;   //ȫ�ֱ�����ָ��ǰ�����ݿ�

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
