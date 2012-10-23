#ifndef _BUFFER_MANAGER_H
#define _BUFFER_MANAGER_H

#include"DBFile.h"
#include"block.h"
#include<set>

class bufferManager
{
public:
	dbfile file;
	block buffer[100];
	std::set<int> bufferContainer;

public:
	// ---------------------------  basic buffer function ------------------------------
	bufferManager();
	~bufferManager();
	int readBlockFromDisk(int block_position);
	int findReplaceBlock();

	// --------------------------- user interface function -----------------------------
	int storeData(char* head, int size, address& return_value);
	char* readData(address position, int& size);  // 将指定位置的数据保存到数组中，并返回
												  // 数组的头地址和数组的大小。
	void rmData(address position);
	int addTableEntry(CString table_name, address& return_value);


	// ---------------------------- advanced interface function --------------------------
	void addRecord(CString table_name, char* head, int size);  //undone
	void addInfo(char* head, int size);

	char* readInfo(CString table_name, int& size);

	void rmInfo(CString table_name);
	void rmRecord(address add);
	
	void findTableEntry(CString table_name, address& return_value);
	void rmTableEntry(CString table_name);
	address nextRecordPosition(address currentAdd);
};


#endif
