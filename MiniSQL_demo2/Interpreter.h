#ifndef INTERPRETER_H
#define INTERPRETER_H

/*******************************************************************************/
//	������Ҫ��ͷ�ļ�
#include "MiniSQL.h"
/*******************************************************************************/



/*******************************************************************************/
//	����ԭ������

//	�ӱ�׼�����豸��ȡ�û������һ������
bool Get_Cmd(string & SQL_CMD);

//	�õ��������ͣ�������
int Get_Operate_Type(string & SQL_CMD);

//	���û������������н���
bool Interpreter(string & SQL_CMD);

//	�õ�SQL_CMD�е�count�����ʣ�������
string Get_Word(string SQL_CMD, int count, char stop = ' ');

//	���ص�����ϵͳ
void Exit_To_System();

//	��ӡ������Ϣ
void Help_Mini_Sql();

//	����һ���ű��ļ������������
bool Exec_File(string & SQL_CMD);

//	��create���Ͳ��������﷨���
bool Check_OP_Create(string & SQL_CMD);

//	��create table���������﷨���
bool Check_OP_Create_Table(string & SQL_CMD);

//	��intStr���������
bool parse_to_int(string intStr, int & result);

//	��create index���������﷨���
bool Check_OP_Create_Index(string & SQL_CMD);

//	��������ÿ�����ʷ���
string Word_Depart(string SQL_CMD);

//	��delete���Ͳ��������﷨���
bool Check_OP_Delete(string & SQL_CMD);

//	��drop���Ͳ��������﷨���
bool Check_OP_Drop(string & SQL_CMD);

//	��drop table���������﷨���
bool Check_OP_Drop_Table(string & SQL_CMD);

//	��drop index���������﷨���
bool Check_OP_Drop_Index(string & SQL_CMD);

//	��insert���Ͳ��������﷨���
bool Check_OP_Insert(string & SQL_CMD);

//	��select���Ͳ��������﷨���
bool Check_OP_Select(string & SQL_CMD);

//	�жϱȽϵ�����
int Check_CMP_Type(string & type);

/*******************************************************************************/




#endif
