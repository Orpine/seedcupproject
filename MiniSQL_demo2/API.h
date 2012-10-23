#ifndef	API_H
#define	API_H

/*******************************************************************************/
//	包含必要的头文件
#include "MiniSQL.h"
/*******************************************************************************/



/*******************************************************************************/
//	函数原型声明

//	API主程序
void API();

//	创建表时的内部调用
bool API_Create_Table();

//	删除表时的内部调用
bool API_Drop_Table();

//	创建索引时的内部调用
bool API_Create_Index();

//	删除索引时的内部调用
bool API_Drop_Index();

//	读取表信息
void Read_Table_Info();

//	读取索引信息
void Read_Index(string index_name);

//	插入纪录时的内部调用
bool API_Insert();

//	选择纪录时的内部调用
bool API_Select();

//	删除纪录时的内部调用
bool API_Delete();

/*******************************************************************************
//	下面是需要Record模块实现的功能

//	实现选择纪录的功能
bool Select(Table table, Condition_list conditions);

//	实现插入纪录的功能
bool Insert(Table table, string attr_value[]);

//	实现删除纪录的功能
bool Delete(Table table, Condition_list conditions);
********************************************************************************/

/*******************************************************************************/

#endif
