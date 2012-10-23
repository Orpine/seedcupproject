#ifndef CATALOG_H
#define CATALOG_H

/*******************************************************************************/
//	������Ҫ��ͷ�ļ�
#include "MiniSQL.h"
/*******************************************************************************/



/*******************************************************************************/
//	����ԭ������

//	������
bool Create_Table(Table & table_temp);

//	ɾ����
bool Drop_Table(string & table_name);

//	��������
bool Create_Index(Index & index_temp);

//	ɾ������
bool Drop_Index(string & index_name);

//	�ж������Ƿ����Ψһ�ԣ�����ATTR_TYPE_PRIMARY, ATTR_TYPE_UNIQUE
bool judge_attr_unique(string & table_name, string & attr_name);

//	���ұ�����������ҵ�����������д��attr_name�������true�����򷵻�false
bool find_primary(string & table_name, string & attr_name);

//	�жϱ��Ƿ����
bool judge_table_exist(string & table_name);

//	�ж��������Ƿ����
bool judge_index_exist(string & index_name);

//	�ж������ڱ����Ƿ����
bool judge_attr_in_table(string & table_name, string & attr_name);
/*******************************************************************************/

#endif
