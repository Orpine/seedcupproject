#ifndef _CATEGORY_MANAGER_H
#define _CATEGORY_MANAGER_H

#include"basichead.h"
class bufferManager;

class categoryManager
{
private:
	bufferManager* bmp;
public:
	// ------------------------------------ basic function ------------------------------
	void setbufferManager(bufferManager* b)
	{
		this->bmp = b;
	}
	char* transformTableInfo(table_info a, int& count);
	table_info transformArrayToTableInfo(char* b, int count);

	// ------------------------------------ user interface function ----------------------
    void saveTable(table_info a);
    bool readTable(CString table_name, table_info& tableInfo);
	void dropTable(CString table_name);

};

#endif
