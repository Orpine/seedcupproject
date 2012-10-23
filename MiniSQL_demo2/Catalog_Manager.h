#ifndef CATALOG_H
#define CATALOG_H

/*******************************************************************************/
//	包含必要的头文件
#include "MiniSQL.h"
/*******************************************************************************/



/*******************************************************************************/
//	函数原型声明

//	创建表
bool Create_Table(Table & table_temp);

//	删除表
bool Drop_Table(string & table_name);

//	创建索引
bool Create_Index(Index & index_temp);

//	删除索引
bool Drop_Index(string & index_name);

//	判断属性是否具有唯一性，包括ATTR_TYPE_PRIMARY, ATTR_TYPE_UNIQUE
bool judge_attr_unique(string & table_name, string & attr_name);

//	查找表的主键，若找到，将属性名写在attr_name里，并返回true，否则返回false
bool find_primary(string & table_name, string & attr_name);

//	判断表是否存在
bool judge_table_exist(string & table_name);

//	判断索引表是否存在
bool judge_index_exist(string & index_name);

//	判断属性在表中是否存在
bool judge_attr_in_table(string & table_name, string & attr_name);
/*******************************************************************************/

#endif
