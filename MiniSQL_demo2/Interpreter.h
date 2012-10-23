#ifndef INTERPRETER_H
#define INTERPRETER_H

/*******************************************************************************/
//	包含必要的头文件
#include "MiniSQL.h"
/*******************************************************************************/



/*******************************************************************************/
//	函数原型声明

//	从标准输入设备读取用户输入的一条命令
bool Get_Cmd(string & SQL_CMD);

//	得到操作类型，并返回
int Get_Operate_Type(string & SQL_CMD);

//	对用户输入的命令进行解析
bool Interpreter(string & SQL_CMD);

//	得到SQL_CMD中第count个单词，并返回
string Get_Word(string SQL_CMD, int count, char stop = ' ');

//	返回到操作系统
void Exit_To_System();

//	打印帮助信息
void Help_Mini_Sql();

//	解析一个脚本文件里的所有命令
bool Exec_File(string & SQL_CMD);

//	对create类型操作进行语法检测
bool Check_OP_Create(string & SQL_CMD);

//	对create table操作进行语法检测
bool Check_OP_Create_Table(string & SQL_CMD);

//	将intStr翻译成数字
bool parse_to_int(string intStr, int & result);

//	对create index操作进行语法检测
bool Check_OP_Create_Index(string & SQL_CMD);

//	将命令中每个单词分离
string Word_Depart(string SQL_CMD);

//	对delete类型操作进行语法检测
bool Check_OP_Delete(string & SQL_CMD);

//	对drop类型操作进行语法检测
bool Check_OP_Drop(string & SQL_CMD);

//	对drop table操作进行语法检测
bool Check_OP_Drop_Table(string & SQL_CMD);

//	对drop index操作进行语法检测
bool Check_OP_Drop_Index(string & SQL_CMD);

//	对insert类型操作进行语法检测
bool Check_OP_Insert(string & SQL_CMD);

//	对select类型操作进行语法检测
bool Check_OP_Select(string & SQL_CMD);

//	判断比较的类型
int Check_CMP_Type(string & type);

/*******************************************************************************/




#endif
