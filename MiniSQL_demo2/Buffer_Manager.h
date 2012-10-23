/* Buffer_Manager.h
 * ���ͷ�ļ���������CBuffer�Լ��ڱ���ʱ��Ҫ��ѡ��
 */

#ifndef __MBUFFER_H__
#define __MBUFFER_H__

/**************************************************************************************************************/

//����buffer������Ҫ��ϵͳ��⣬����û�н�����ƿռ������
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

using std::string;

/**************************************************************************************************************/

//����ʱҪȷ��buffer��record����ʱ��Ĵ�С
//8KB
#ifdef NORMALL
const int Block_Size = 8192;
#endif
//16KB
#ifdef LARGE
const int Block_Size = 16384;
#endif

//���е��ڲ���
#ifndef DEBUG
const int Block_Hold = 256;
#endif

/**************************************************************************************************************/

//extern struct Record_Info;

//buffer�п���Ϣ�Ķ���
typedef struct Record_Info
{
	char*		attr_value;						//ͳһ��string��������ֵ
	int				counter;							//һ����¼�ڿ��е�λ��
	bool			is_deleted;						//��ֵΪ1������ʱ��Ϊ0��ɾ��ʱ��Ϊ1
	int 		size;
}Record;

struct Block_Info {
    Record_Info    *address;			//���׵ĵ�ַ��
    string			table_name;			//������Ӧ�ı�����
    int 			offset_number;		//�����ļ��е�ƫ������
    bool 			is_written;			//�ÿ���û�б��޸Ĺ���û���޸Ĺ�ֵΪfalse���޸Ĺ�ֵΪtrue��
    bool 			being_used;			//�ÿ��Ƿ�����ʹ�ã�����ʹ��ֵΪtrue��û����ʹ��ֵΪfalse��
    bool 			is_accessed;		//����ʵ��LRU�Ľ����㷨�Ľ�Clock����NRU���㷨ʹ�õı��λ��
};

/**************************************************************************************************************/

class CBuffer {
public:
	//Field:
	
	//Method:
    CBuffer( );
    bool Init( ); //Initialization;
    Block_Info* GetBlock( string table_name, Block_Info* Passed = NULL );	//���½���¼��Ŀ��ʱ��ʹ��
    Block_Info* GetBlock( string table_name, int offset );			//�ڽ��в�ѯ��ʱ��ʹ��
    bool DropTable( string table_name );
     ~CBuffer( );
     
/**************************************************************************************************************/
private:
	// Fields:
	Block_Info* Buffer[ Block_Hold ];
    
    // Methods:
	bool Sched( string table_name, Block_Info* Block );
	bool Sched( string table_name, int offset );
	Block_Info* HDExchange( string table_name, Block_Info* Block, int offset = -1 );
	Block_Info* GBlock( );
	Record_Info* Malloc( int Size );
};

#endif //__MBUFFER_H__
