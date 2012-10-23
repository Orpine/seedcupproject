/* Buffer_Manager.h
 * 这个头文件定义了类CBuffer以及在编译时需要的选项
 */

#ifndef __MBUFFER_H__
#define __MBUFFER_H__

/**************************************************************************************************************/

//定义buffer管理需要的系统类库，但是没有解决名称空间的问题
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

using std::string;

/**************************************************************************************************************/

//编译时要确定buffer与record交换时块的大小
//8KB
#ifdef NORMALL
const int Block_Size = 8192;
#endif
//16KB
#ifdef LARGE
const int Block_Size = 16384;
#endif

//持有的内部块
#ifndef DEBUG
const int Block_Hold = 256;
#endif

/**************************************************************************************************************/

//extern struct Record_Info;

//buffer中块信息的定义
typedef struct Record_Info
{
	char*		attr_value;						//统一用string保存属性值
	int				counter;							//一条记录在块中的位置
	bool			is_deleted;						//初值为1，插入时置为0，删除时置为1
	int 		size;
}Record;

struct Block_Info {
    Record_Info    *address;			//块首的地址；
    string			table_name;			//块所对应的表名；
    int 			offset_number;		//块在文件中的偏移量；
    bool 			is_written;			//该块有没有被修改过，没有修改过值为false，修改过值为true；
    bool 			being_used;			//该块是否正在使用，正在使用值为true，没有在使用值为false；
    bool 			is_accessed;		//用于实现LRU的近似算法改进Clock即（NRU）算法使用的标记位；
};

/**************************************************************************************************************/

class CBuffer {
public:
	//Field:
	
	//Method:
    CBuffer( );
    bool Init( ); //Initialization;
    Block_Info* GetBlock( string table_name, Block_Info* Passed = NULL );	//在新建记录条目的时候使用
    Block_Info* GetBlock( string table_name, int offset );			//在进行查询的时候使用
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
