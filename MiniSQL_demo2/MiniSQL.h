#ifndef MINI_SQL_H
#define MINI_SQL_H

/*****************************************************************************/
/*****************************************************************************
mini_sql.h�ļ�Ϊ��������������ļ�������������Ϣ��������
******************************************************************************/



/*****************************************************************************/
/*****************************************************************************/
//	������Ҫ��ͷ�ļ�
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
/*****************************************************************************/




/*****************************************************************************/
/*****************************************************************************/
//	�����ǳ������õ��ĳ�������
#define MAX_FILENAME_LENGTH 256
#define MAX_CMD_LENGTH			256
#define MAX_ATTRNAME_LENGTH	256
#define MAX_RECORD_LENGTH		256

#define TABLE_LIST	"table.list"
#define INDEX_LIST	"index.list"
/*****************************************************************************/




/*****************************************************************************/
/*****************************************************************************/
//	�����ǳ������õ���������صĺ궨��
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
//	�����ǳ������õ��ĳ�����Ϣ����
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
//	�����ǳ��������õ��Ľṹ�嶨��
//	������������һ�������ڱ��еľ�����Ϣ
typedef struct Attribute
{
	string attr_name;
	int attr_type;				//���Ե��������ͣ��ֱ�ΪATTR_TYPE_CHAR, ATTR_TYPE_FLOAT, ATTR_TYPE_INT
	int attr_key_type;		//���Ե��������ͣ��ֱ�ΪATTR_TYPE_PRIMARY, ATTR_TYPE_UNIQUE, ATTR_TYPE_NULL
	int attr_len; 				//��������ŵ����ݵĳ��ȣ��������ATTR_TYPE_CHAR���򳤶ȱ��Ϊ1
	//unsigned int attr_start;		//������һ����¼�е���ʼλ�ã���1��ʼ������
	int attr_num;				//�����ڱ����ǵڼ���
}	Attribute;

//	�������������Ϣ
typedef struct Table
{
	string table_name;
	int attr_count;				//�������Ե��ܸ���
	Attribute attrs[32];	//������������б�
}	Table;

//	���������ж���������Ϣ
typedef struct Condition* Condition_list;
typedef struct Condition
{
	string attr_name;			//��������Ӧ��������
	int op_type;					//�������õ��ıȽ�ģʽ���ֱ�ΪSMALL,EQUEL,BIG
	string cmp_value;			//��������Ҫ���бȽϵ�ֵ
	Condition_list next;	//ָ����һ������
}	Condition;

//	��������������Ϣ
typedef struct Index
{
	string index_name;
	string table_name;
	string attr_name;					//	��������Ӧ������
} Index;
/********************************************************************************/




/*****************************************************************************/
/*****************************************************************************/
//	�����ǳ������õ���ȫ�ֱ���
extern string error_info;					//���ڱ��������Ϣ
extern int opType;
extern Table table;								//���ڴ�����ѡ���¼��ɾ����¼�������¼��
extern Condition_list conditions;	//���ڽ�����ʱ�򱣴�where����
extern Index index;								//���ڴ�������
extern string table_name;					//����ɾ����
extern string index_name;					//����ɾ������
extern string values[32];					//����insert����
extern int value_count;						//����insert����
/*****************************************************************************/

#endif
