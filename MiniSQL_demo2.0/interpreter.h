#ifndef _ITERPRETER_H
#define _ITERPRETER_H

#include<afx.h>
#include<set>


class bufferManager;
class categoryManager;
class recordManager;

class interpreter{
public:
	bufferManager* bm;
	categoryManager* cm;
	recordManager* rm;
	std::set<int> iset;
	std::set<float> fset;
	std::set<CString> cset;
	CString currentTableName;
	CString currentDbName;
	int current_a;
	bool has_pk;
	void printString(const CString& c);

public:
	interpreter();
	~interpreter();
	bool InitCommand(CString &cmd);
	bool ExecuteCommand(CString cmd);
	bool insert(CString table_name, CString info);
	bool CreateTable(CString TableName,CString TableInfo);
	bool Delete(CString Table , CString info);
	bool print1(CString Table_name , CString attr);
	bool print2(CString Table_name , CString attr , CString info);
	bool DropTable(CString table_name); //
	bool CreateIndex(CString IndexName, CString TableName, CString AttName, bool unique); //
	bool DropIndex(CString IndexName); //
	bool Select(CString Selection, CString TableName, CString Condition); //
	bool ShowTable();
	bool UseDatabase(CString DbName);
	bool ShowColumn(CString TableName);
	bool ShowDatabase();
	bool CreateDatabase(CString DbName);
	bool Alter(CString TableName,CString AddressName,CString Condition);
};


#endif