#ifndef		__RECORD_H
#define		__RECORD_H

#include	"MiniSQL.h"
#include	"Buffer_Manager.h"
//#include  "catalog.h"
//#include 	"index.h"

/*************************************************************/

//���м�¼�Ķ���,�����顣�׵�ַ��block_info����
//buffer�п���Ϣ�Ķ���
/*
typedef struct Record_Info
{		
	char*	attr_value;                 //ͳһ��string��������ֵ
	int	counter;			//һ����¼�ڿ��е�λ��
	bool	is_deleted;			//��ֵΪ1������ʱ��Ϊ0��ɾ��ʱ��Ϊ1
	int    size;
}Record;

struct Block_Info {
    Record_Info    *address;			//���׵ĵ�ַ��
    string				table_name;			//������Ӧ�ı�����
    int 					offset_number;	//�����ļ��е�ƫ������
    bool 					is_written;			//�ÿ���û�б��޸Ĺ���û���޸Ĺ�ֵΪfalse���޸Ĺ�ֵΪtrue��
    bool 					being_used;			//�ÿ��Ƿ�����ʹ�ã�����ʹ��ֵΪtrue��û����ʹ��ֵΪfalse��
    bool 					is_accessed;		//����ʵ��LRU�Ľ����㷨�Ľ�Clock����NRU���㷨ʹ�õı��λ��
};
*/
bool Select(Table table, Condition_list conditions);

//	ʵ�ֲ����¼�Ĺ���
bool Insert(Table table, string attr_value[]);

//	ʵ��ɾ����¼�Ĺ���
bool Delete(Table table, Condition_list conditions);

/*
//�����Ƚ�
bool Checkvalue(string value, Condition_list conditions);

//ɾ����
bool Drop_table(string table);


bool Create_index();

bool Drop_index();
*/

/**********************************************************************************/

#endif
