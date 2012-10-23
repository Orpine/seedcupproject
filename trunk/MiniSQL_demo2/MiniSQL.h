#ifndef MINI_SQL_H
#define MINI_SQL_H

/*****************************************************************************/
/*****************************************************************************
mini_sql.h文件为整个程序的配置文件，所有配置信息都在这里
******************************************************************************/



/*****************************************************************************/
/*****************************************************************************/
//	包含必要的头文件
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
/*****************************************************************************/




/*****************************************************************************/
/*****************************************************************************/
//	以下是程序中用到的常量定义
#define MAX_FILENAME_LENGTH 256
#define MAX_CMD_LENGTH			256
#define MAX_ATTRNAME_LENGTH	256
#define MAX_RECORD_LENGTH		256

#define TABLE_LIST	"table.list"
#define INDEX_LIST	"index.list"
/*****************************************************************************/




/*****************************************************************************/
/*****************************************************************************/
//	以下是程序中用到的类型相关的宏定义
#define SMALL		1		//	<
#define EQUEL		2		//	==
#define	BIG			3		//	>
#define NEQUAL	4		//	!=
#define GEQUAL	5		//	>=
#define SEQUAL	6 	//	<=

#define CHAR_TYPE 	1
#define	FLOAT_TYPE	2
#define	INT_TYPE		3

#define NULL_OP_TYPE 						-1
#define CREATE_OP_TYPE					1
#define CREATE_TABLE_OP_TYPE		11
#define CREATE_INDEX_OP_TYPE		12
#define DELETE_OP_TYPE					2
#define DELETE_ALL_OP_TYPE			21
#define DELETE_WHERE_OP_TYPE		22
#define DROP_OP_TYPE						3
#define DROP_TABLE_OP_TYPE			31
#define DROP_INDEX_OP_TYPE			32
#define	INSERT_OP_TYPE					4
#define SELECT_OP_TYPE					5
#define SELECT_ALL_OP_TYPE			51
#define SELECT_WHERE_OP_TYPE		52
#define EXECFILE_OP_TYPE				6
#define HELP_OP_TYPE						7
#define	QUIT_OP_TYPE						8

#define ATTR_TYPE_CHAR		1
#define ATTR_TYPE_INT			2
#define ATTR_TYPE_FLOAT		3

#define ATTR_TYPE_PRIMARY	1
#define ATTR_TYPE_UNIQUE	2
#define ATTR_TYPE_NULL		3
/*****************************************************************************/



/*****************************************************************************/
/*****************************************************************************/
//	以下是程序中用到的出错信息定义
#define ERROR_WRONG_CMD_INPUT 			"Wrong command input !"
#define ERROR_EMPTY_CMD_INPUT 			"Empty input !"
#define ERROR_NULL_OP_TYPE 					"No such operate type !"
#define ERROR_CANNOT_OPEN_FILE			"Cannot open the shell file !"
#define ERROR_NOTFULL_CMD						"Not full command in file !"
#define ERROR_NO_FILENAME_INPUT			"No file name input !"
#define ERROR_TABLE_EXIST						"Table already exists !"
#define ERROR_TABLE_NOT_EXIST				"Table not exists, you cannot drop it !"
#define ERROR_NULL_CREATE_TYPE			"Can only create table or index !"
#define ERROR_EMPTY_CREATE_TYPE			"Empty create type input !"
#define ERROR_CREATE_TABLE_PHRASE		"Create table phrase error !"
#define ERROR_EMPTY_DROP_TYPE				"Empty drop type input !"
#define ERROR_NULL_DROP_TYPE				"Can only create table or index !"
#define ERROR_DROP_TABLE_PHRASE			"Drop table phrase error !"
#define ERROR_CREATE_INDEX_PHRASE		"Create index phrase error !"
#define ERROR_INDEX_EXIST						"Index already exists !"
#define ERROR_INDEX_NO_TABLE				"Table not exists, create it first !"
#define ERROR_INDEX_NO_ATTR					"Attr no exists in table, cannot create the index !"
#define ERROR_DROP_INDEX_PHRASE			"Drop index phrase error !"
#define ERROR_INDEX_NOT_EXIST				"Index not exists, you cannot drop it !"
#define ERROR_INSERT_PHRASE					"Insert phrase error !"
#define ERROR_INSERT_NO_TABLE				"Table not exists, cannot insert a record !"
#define ERROR_SELECT_PHRASE					"Select phrase error !"
#define ERROR_SELECT_NO_TABLE				"Table not exists, cannot select records !"
#define ERROR_DELETE_PHRASE					"Delete phrase error !"
#define ERROR_DELETE_NO_TABLE				"Table not exists, cannot delete records !"
/*****************************************************************************/



/*****************************************************************************/
/*****************************************************************************/
//	以下是程序中所用到的结构体定义
//	用于描述表中一个属性在表中的具体信息
typedef struct Attribute
{
	string attr_name;
	int attr_type;				//属性的数据类型，分别为ATTR_TYPE_CHAR, ATTR_TYPE_FLOAT, ATTR_TYPE_INT
	int attr_key_type;		//属性的主键类型，分别为ATTR_TYPE_PRIMARY, ATTR_TYPE_UNIQUE, ATTR_TYPE_NULL
	int attr_len; 				//属性所存放的数据的长度，如果不是ATTR_TYPE_CHAR，则长度标记为1
	//unsigned int attr_start;		//属性在一条记录中的起始位置（从1开始计数）
	int attr_num;				//属性在表中是第几个
}	Attribute;

//	用于描述表的信息
typedef struct Table
{
	string table_name;
	int attr_count;				//表中属性的总个数
	Attribute attrs[32];	//表的所有属性列表
}	Table;

//	用于描述判断条件的信息
typedef struct Condition* Condition_list;
typedef struct Condition
{
	string attr_name;			//条件所对应的属性名
	int op_type;					//条件所用到的比较模式，分别为SMALL,EQUEL,BIG
	string cmp_value;			//条件所需要进行比较的值
	Condition_list next;	//指向下一个条件
}	Condition;

//	用于描述索引信息
typedef struct Index
{
	string index_name;
	string table_name;
	string attr_name;					//	索引所对应的属性
} Index;
/********************************************************************************/




/*****************************************************************************/
/*****************************************************************************/
//	以下是程序中用到的全局变量
extern string error_info;					//用于保存出错信息
extern int opType;
extern Table table;								//用于创建表、选择纪录、删除纪录、插入纪录等
extern Condition_list conditions;	//用于解析的时候保存where条件
extern Index index;								//用于创建索引
extern string table_name;					//用于删除表单
extern string index_name;					//用于删除索引
extern string values[32];					//用于insert操作
extern int value_count;						//用于insert操作
/*****************************************************************************/

#endif
