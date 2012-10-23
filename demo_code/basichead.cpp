#include"basichead.h"


bool condition::statisfy(const attribute_value& a)
{
	if(a.type_no != type) 
		return 0;
	else
	{			
		bool compare_result[6];
		if(a.type_no == 0)
		{	
			CString temp = a.char_value;
			compare_result[0] = (temp == item2);
			compare_result[1] = (temp < item2);
			compare_result[2] = (temp > item2);
			compare_result[3] = (temp <= item2);
			compare_result[4] = (temp >= item2);
			compare_result[5] = (temp != item2);
		}
		if(a.type_no == 1)
		{
			float temp = a.float_value;
			compare_result[0] = (temp == (float)atof(item2));
			compare_result[1] = (temp < (float)atof(item2));
			compare_result[2] = (temp > (float)atof(item2));
			compare_result[3] = (temp <= (float)atof(item2));
			compare_result[4] = (temp >= (float)atof(item2));
			compare_result[5] = (temp != (float)atof(item2));
		}
		if(a.type_no == 2)
		{
			int temp = a.int_value;
			compare_result[0] = (temp == atoi(item2));
			compare_result[1] = (temp < atoi(item2));
			compare_result[2] = (temp > atoi(item2));
			compare_result[3] = (temp <= atoi(item2));
			compare_result[4] = (temp >= atoi(item2));
			compare_result[5] = (temp != atoi(item2));
		}
		return compare_result[operation];
	}
}


attribute_info& attribute_info::operator=(const attribute_info& a)
{
	type = a.type;
	type_count = a.type_count; 
	unique = a.unique;
	attribute_name = a.attribute_name;
	has_index = a.has_index;
	return *this;
}


table_info::table_info(const table_info& a)
{
	attribute_count = a.attribute_count;
	table_name = a.table_name;
	primary_key = a.primary_key;
	for(int i = 0; i < attribute_count; i++)
		info[i] = a.info[i];
}

attribute_info::attribute_info(const attribute_info& a)
{
	type = a.type;
	type_count = a.type_count;
	unique = a.unique;
	attribute_name = a.attribute_name;
	has_index = a.has_index;
}

table_info& table_info::operator=(const table_info& a)
{
	attribute_count = a.attribute_count;
	table_name = a.table_name;
	primary_key = a.primary_key;
	for(int i = 0; i < attribute_count; i++)
		info[i] = a.info[i];
	return *this;
}

attribute_value& attribute_value::operator=(const attribute_value& a)
{
	if(type_no == 0 && char_count != 0)
		delete [] char_value;
	if(a.type_no == 0)
	{
		char_value = new char[a.char_count];
		for(int i = 0; i < a.char_count; i++)
			char_value[i] = a.char_value[i];
		char_count = a.char_count;
		type_no = 0;
	}
	else
	{
		if(a.type_no == 1)
		{
			type_no = 1;
			float_value = a.float_value;
		}
		else
		{
			type_no = 2;
			int_value = a.int_value;
		}
	}
	return *this;
}

attribute_value::attribute_value(const attribute_value& a)
{
	if(a.type_no == 0)
	{
		char_value = new char[a.char_count];
		for(int i = 0; i < a.char_count; i++)
			char_value[i] = a.char_value[i];
		char_count = a.char_count;
		type_no = 0;
		int_value = 0;
		float_value = 0.0;
	}
	else
	{
		if(a.type_no == 1)
		{
			type_no = 1;
			float_value = a.float_value;
			int_value = 0;
			char_value = NULL;
			char_count = 0;
		}
		else
		{
			type_no = 2;
			int_value = a.int_value;
			float_value = 0.0;
			char_value = NULL;
			char_count = 0;
		}
	}
}

record::record(const record& a)
{
	attribute_count = a.attribute_count;
	for(int i = 0; i < a.attribute_count; i++)
		value[i] = a.value[i];
	position = a.position;
}

record& record::operator=(const record& a)
{
	attribute_count = a.attribute_count;
	for(int i = 0; i < a.attribute_count; i++)
		value[i] = a.value[i];
	position = a.position;
	return *this;
}
