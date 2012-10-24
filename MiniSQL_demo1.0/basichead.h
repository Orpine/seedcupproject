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
	int char_count;     // 务必确保字符数组最后以'\0'结尾
	float float_value;
	int int_value;
	int type_no; //指明是哪个类型，0-char,1-float,2-int
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
	CString type; // 该属性是什么类型的，int? float? char?
	int type_count; //针对char类型，有几个?
	bool unique; //该属性值是否唯一
	CString attribute_name; // 属性名字
	bool has_index; //该属性上是否有索引
	
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
	int operation; // 0是=,1是<,2是>,3是<=,4是>=,5是!=
	int type; //item1,item2是什么类型的,0是char,1是float,2是int
	
	bool statisfy(const attribute_value& a);
};


#endif