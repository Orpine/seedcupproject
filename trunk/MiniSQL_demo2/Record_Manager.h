#ifndef		__RECORD_H
#define		__RECORD_H

#include	"MiniSQL.h"
#include	"Buffer_Manager.h"
//#include  "catalog.h"
//#include 	"index.h"

/*************************************************************/

//块中记录的定义,用数组。首地址由block_info传入
//buffer中块信息的定义
/*
typedef struct Record_Info
{		
	char*	attr_value;                 //统一用string保存属性值
	int	counter;			//一条记录在块中的位置
	bool	is_deleted;			//初值为1，插入时置为0，删除时置为1
	int    size;
}Record;

struct Block_Info {
    Record_Info    *address;			//块首的地址；
    string				table_name;			//块所对应的表名；
    int 					offset_number;	//块在文件中的偏移量；
    bool 					is_written;			//该块有没有被修改过，没有修改过值为false，修改过值为true；
    bool 					being_used;			//该块是否正在使用，正在使用值为true，没有在使用值为false；
    bool 					is_accessed;		//用于实现LRU的近似算法改进Clock即（NRU）算法使用的标记位；
};
*/
bool Select(Table table, Condition_list conditions);

//	实现插入纪录的功能
bool Insert(Table table, string attr_value[]);

//	实现删除纪录的功能
bool Delete(Table table, Condition_list conditions);

/*
//条件比较
bool Checkvalue(string value, Condition_list conditions);

//删除表
bool Drop_table(string table);


bool Create_index();

bool Drop_index();
*/

/**********************************************************************************/

#endif
