#ifndef _BASIC_H
#define _BASIC_H

#include<afx.h>

class Exception
{
public:
	CString m_str;
	Exception(CString a = "")
	{
		m_str = a;
	}
};

class address
{
	public:
	int block_position;
	int index_position;
};

class attribute_value
{
	public:
	char* char_value;
	int char_count;     // ���ȷ���ַ����������'\0'��β
	float float_value;
	int int_value;
	int type_no; //ָ�����ĸ����ͣ�0-char,1-float,2-int
	attribute_value()
	{
		char_value = NULL;
		char_count = 0;
		float_value = 0;
		int_value = 0;
		type_no = 1;
	}
	attribute_value(const attribute_value&);
	attribute_value& operator=(const attribute_value&);
	~attribute_value()
	{
		if(type_no == 0)
			delete [] char_value;
	}
};

class record
{
public:
	attribute_value value[32];
	int attribute_count;
	address position;
	record() {};
	record(const record& a);
	record& operator=(const record& a);
};


class attribute_info
{
public:
	CString type; // ��������ʲô���͵ģ�int? float? char?
	int type_count; //���char���ͣ��м���?
	bool unique; //������ֵ�Ƿ�Ψһ
	CString attribute_name; // ��������
	bool has_index; //���������Ƿ�������
	
	attribute_info() {}
	attribute_info(const attribute_info&);
	attribute_info& operator=(const attribute_info& a);
	int getSize()
	{
		if(type == "int")
			return sizeof(int);
		if(type == "float")
			return sizeof(float);
		if(type == "char")
			return type_count;
	}
};

class table_info
{
public:
	int attribute_count;
	attribute_info info[32];
	CString table_name;
	CString primary_key;
	
	table_info() {};
	table_info(const table_info& a);
	table_info& operator=(const table_info& a);
	int getRecordSize()
	{
		int totalSize = 0;
		for(int i = 0; i < attribute_count; i++)
			totalSize += info[i].getSize();
		return totalSize;
	}
};

class condition
{
public:
	int item1;
	CString item2;
	int operation; // 0��=,1��<,2��>,3��<=,4��>=,5��!=
	int type; //item1,item2��ʲô���͵�,0��char,1��float,2��int
	
	bool statisfy(const attribute_value& a);
};


#endif