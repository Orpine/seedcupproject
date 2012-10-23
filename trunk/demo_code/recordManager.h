#ifndef _RECORD_MANAGER_H
#define _RECORD_MANAGER_H

#include"basichead.h"
#include"afxtempl.h"
class bufferManager;

class recordManager
{
private:
	bufferManager* bmp;
public:
	// ----------------------------- basic function --------------------------------
	void setbufferManager(bufferManager* bmp)
	{
		this->bmp = bmp;
	}
	char* record_to_array(record new_record, int& size);
	record* array_to_record(char* record_pointer,table_info record_info);

	// ----------------------------- user interface function ------------------------
	CArray<record, record&>*
	readRecords(CString table_name, table_info tableInfo, CArray<condition, condition&>* cp = NULL);
	void storeRecord(CString table_name, record data);
	void rmRecord(CString table_name, table_info* tableInfo = NULL, CArray<condition, condition&>* cp = NULL);
};

#endif