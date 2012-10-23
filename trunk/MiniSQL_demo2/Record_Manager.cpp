#include "Record_Manager.h"
#define NORMALL

/********************record中的全局变量******************************/

int total_block_number = 0;					//table对应的总块数
int total_record_number = 0;				//块对应的总记录数
int current_record = 0;
int record_size = 1;  
string value[32];
bool isdisplay = false;
//string* reserve = new string[1000];
//int reservecount = 0;
						//总共找到的记录个数
struct Block_Info* newblock;
CBuffer onebuffer;

int getLength(int i) {
	int j = 1;
	for (; i / 10 != 0; j++, i /= 10);
	return j;
}

void clearValue() {
	for (int i = 0; i < 32 && value[i] != ""; value[i].erase(), i++);
}

void show() {
	if (!isdisplay) {
		for (int i = 0; i < table.attr_count; i++) 
			cout << table.attrs[i].attr_name << '\t';
		cout << endl;
	}
    isdisplay = true;
	for(int i = 0; value[i] != "" && i < 32; i++) {
		cout << value[i] << '\t';
		value[i].erase();
	}
	
	cout << endl;
}

void memStore(Record_Info*& des, bool b, int s, int c, const void* ch, int len) {
        memcpy((char*)des, &b, sizeof(bool));
        memcpy((char*)des + sizeof(bool), &s, sizeof(int));
        memcpy((char*)des + sizeof(bool) + sizeof(int), &c, sizeof(int));
        memcpy((char*)des + sizeof(bool) + sizeof(int) * 2, ch, len);
/*
		static int count = 0;
		if (count == 204) {
			int length = sizeof(bool) + sizeof(int) * 2 + len;
			for (int i = 0; i < length; cout << ((char*)des)[i++]);
			cout << endl;
			count++;
		} else {
			count++;
		}*/
}

void memStore(Record_Info*& des, bool& b) {
	 memcpy((char*)des, &b, sizeof(bool));
}

void memRestore(void* sou, bool& b, int& s, int& c, void*& ch) {
	b = *((bool*)(char*)sou);
	s = *((int*)((char*)sou + sizeof(bool)));
	c = *((int*)((char*)sou + sizeof(bool) + sizeof(int)));
	ch = (char*)sou + sizeof(bool) + sizeof(int) * 2;
}

bool memRestore(void* sou) {
	bool b;
	b = *((bool*)(char*)sou);
	return b;
}
void memRestore(Record_Info* sou, int& size,  void*& ch) {/*
	for (int i = 0; i < record_size; i++) {
		cout << ((char*)sou)[i];
	}
	cout << endl;*/

	size = *((int*)((char*)sou + sizeof(bool)));
	ch = (char*)sou + sizeof(bool) + sizeof(int) * 2;
}
int getLength(float f) {
	int lon = f * 100000;
	for (; lon % 10 == 0; lon /= 10);
	return getLength(lon); 
}

int getRecSize(int size) {
	return (size % 4 ? (size / 4 + 1) * 4 : size);
}
bool Checkvalue(string& value, Condition_list conditions, Table table, int attr_type)
{
	int 	intvalue;
	double floatvalue;
	//int attr_type ;
    /*
	for(int i = 0; i< table.attr_count; i++) {
		if(table.attrs[i].attr_name == conditions ->attr_name)
			attr_type = table.attrs[i].attr_type;
	}*/
	switch(attr_type)
	{
		case ATTR_TYPE_INT:
		{
			intvalue = atoi(value.c_str());
			switch(conditions ->op_type)
			{
				case SMALL :
					return (intvalue < (atoi(conditions ->cmp_value.c_str())));
				case EQUEL : 
					return (intvalue == (atoi(conditions ->cmp_value.c_str())));
				case BIG :
					return (intvalue > (atoi(conditions ->cmp_value.c_str())));
				case SEQUAL :
					return (intvalue <= (atoi(conditions ->cmp_value.c_str())));
				case GEQUAL :
					return (intvalue >= (atoi(conditions ->cmp_value.c_str())));
				case NEQUAL :
					return (intvalue != (atoi(conditions ->cmp_value.c_str())));
			}
		}
		break;
		case ATTR_TYPE_CHAR :
		{
			switch(conditions ->op_type)
			{
				case SMALL :
					return (value < conditions ->cmp_value);
				case EQUEL :
					return (value == conditions ->cmp_value);
				case BIG :
					return (value > conditions ->cmp_value);
				case SEQUAL :
					return (value <= conditions ->cmp_value);
				case GEQUAL :
					return (value >= conditions ->cmp_value);
				case NEQUAL :
					return (value != conditions ->cmp_value);
			}
		}
		break;
		case ATTR_TYPE_FLOAT :
		{
			floatvalue = atof(value.c_str());
			switch(conditions ->op_type)
			{
				case SMALL :
					return (floatvalue < (atoi(conditions ->cmp_value.c_str())));
				case EQUEL : 
					return (floatvalue == (atoi(conditions ->cmp_value.c_str())));
				case BIG :
					return (floatvalue > (atoi(conditions ->cmp_value.c_str())));
				case SEQUAL :
					return (floatvalue <= (atoi(conditions ->cmp_value.c_str())));
				case GEQUAL :
					return (floatvalue >= (atoi(conditions ->cmp_value.c_str())));
				case NEQUAL :
					return (floatvalue != (atoi(conditions ->cmp_value.c_str())));
			}
		}
		break;
		return false;
	}	
	return false;
}



string* RecToStr(void* rec, Table table, int size) {
	clearValue();
	char* temrec = new char[size];
	for (int h = 0; h < size; h++) {
		temrec[h] = ((char*)rec)[h];
		//cout << temrec[h];
		//cout << ((char*)rec)[h] << "\t";
	}
	//cout << endl;
	string tem = ""; float ftem; int item; char buffer[20];
	for (int i = 0, j; i < table.attr_count; i++) {
		switch (table.attrs[i].attr_type){
			case ATTR_TYPE_CHAR:
				for (j = 0; j < table.attrs[i].attr_len; j++)
					tem += *(temrec++);
				value[i].assign(tem);
				tem = ""; break;
			case ATTR_TYPE_INT:				
				item = ((int*)temrec)[0];
				temrec += 4;
				_itoa(item, buffer, 10);
				tem = string(buffer);
				value[i].assign(tem);
				tem = ""; break;
			case ATTR_TYPE_FLOAT:
				ftem = *((float*)temrec);
				int decimal, sign;
				temrec += 4;
				tem = string(_ecvt(ftem, 16, &decimal, &sign));
				tem.insert(decimal, ".");
				value[i].assign(tem);
				tem = ""; break;			
		}
	}
	//delete temrec->attr_value;
	temrec -= size;
	delete [] temrec;
	return value;
}

string Convertvalue(Table table, string attr_value[])
{
	string svalue;
/*
	for (int qwer = 0; qwer < 32; qwer++) {
		cout << attr_value[qwer];
	}
*/	
	for(int i = 0; i < table.attr_count; i++) {			//把属性值连接成一个sring， 记录为定长
		if(table.attrs[i].attr_type == ATTR_TYPE_CHAR) {
			svalue.append(attr_value[i]);
	//		cout << svalue << endl;
	//		cout << attr_value[i] << endl;
		}
		if(table.attrs[i].attr_type == ATTR_TYPE_INT) {
			int intem = atoi(attr_value[i].c_str());	
			char* temp1 = (char *)calloc(1,sizeof(int));
			*((int *)temp1) = intem; 				
			for(int l1 = 0; l1 < sizeof(int); l1++) 
				svalue += temp1[l1];
		}	
		if(table.attrs[i].attr_type == ATTR_TYPE_FLOAT) {	
			float intem = (float)atof(attr_value[i].c_str());	
			char* temp2 = (char *)calloc(1,sizeof(float));
			*((float *)temp2) = intem;
			for(int l2 = 0; l2 < sizeof(float); l2++) 
				svalue +=  temp2[l2];
		}
	}
//DEBUG
//	cout << svalue << endl;

	return svalue;
}

Record_Info* Malloc(int Size) {
	return ( Record_Info* )( new char[ Size ] );
}

bool Insertnoindex(Table table, string attr_value[])
{
	struct Record_Info* newrecord;

	string svalue ;
	
	svalue = Convertvalue(table, attr_value);

//DEBUG
//	cout << svalue << endl;


	record_size = getRecSize(svalue.size()) + 12;
	//total_record_number = (8192 / record_size) - 2;	//块大小 8K
	total_record_number = 8192 / record_size;			//块大小 8K
	
	if(total_block_number == 0 && current_record == 0) {												//判断是否有块
		//newblock = (Block_Info*)(new Block_Info());
		//newblock ->address = Malloc(8192); 
		onebuffer.Init();
		newblock = NULL;
		newblock = onebuffer.GetBlock(table.table_name, newblock);
		newblock ->table_name = table.table_name;
		newblock ->offset_number = total_block_number;			//有些问题,只能有一张表？？？？？？？？
	}

	newrecord = (Record_Info*)((char*)newblock->address + current_record * record_size);
	
	if(current_record < total_record_number ) {			// 若块未满
	/*	memcpy(newrecord, svalue.c_str(), svalue.size()); */
		/*cout << svalue << endl;
		for (int i = 0; i < svalue.size(); i++) {
			//cout << svalue.at(i)  << " " << ((char*)newrecord)[i] << "\t";
			cout << ((char*)newrecord)[i];
		}
		cout  << endl;*//*
		newrecord->size = svalue.size();
		cout << &(newrecord->size) << endl;
		newrecord ->counter = current_record;
		cout << &(newrecord->counter) << endl;
		cout << &(newrecord->attr_value) << endl;
		memcpy(newrecord->attr_value, svalue.c_str(), svalue.size());*/
		bool flag = false;
		memStore(newrecord, flag, svalue.size(), current_record, 
			svalue.c_str(), svalue.size());

/*		newrecord->attr_value = new char[newrecord->size];
		for(int k = 0 ;k < newrecord->size;k++)
			//((char*)newrecord)[k+8] = svalue[k];
			newrecord->attr_value[k] = svalue[k];
		//strcpy(newrecord->attr_value, svalue.c_str());*/
		//newrecord->is_deleted = 0;	
		newblock->is_written = true;
		newblock->being_used = true;
		current_record++;
		if(current_record >= total_record_number){			//若块满则取下一块
			current_record = 0;
			newblock ->being_used = 0;
			total_block_number++;
			newblock = onebuffer.GetBlock(table.table_name, newblock);
			newblock ->table_name = table.table_name;
			newblock ->offset_number = total_block_number;	
		}
	}
	return true;
}

bool Insert(Table table, string attr_value[])
{
	static int j = 0;
	if(Insertnoindex(table, attr_value)) {
		//cout << ++j << "\tInsert success.\n";
		return true;
	}
//		cout << "Insert success.\n";
	else  {
		return false;
	}
		//cout << "false.\n";
}

bool Isaccording(Table table, Condition_list conditions, string* str)
{
	int condition_count = 0, condition_number = 0;
	Condition_list conditiontemp = conditions;

	if(conditions == NULL )
		return true;
	while(conditiontemp != NULL) {
		condition_count ++;
		conditiontemp = conditiontemp ->next;
	}
	conditiontemp = conditions;
	
	while(conditiontemp != NULL) {
		show();
		//for(int i = 0; i <= table.attr_count, table.attrs[i].attr_name != conditiontemp ->attr_name; i++);

		for (int i = 0; i < 32 && str[i] != ""; i++) {
			cout << str[i] << '\t';
		}
     cout << endl;
	 int j;
		for(j = 0; j <= table.attr_count; j++) {
			if (table.attrs[j].attr_name == conditiontemp ->attr_name) break;
		}

		//cout << "i : " << i << "   attr_name : " << table.attrs[i].attr_name << "   cond_attr_name : ";
		//cout << conditions ->attr_name << endl;
		cout << "sdkghoih : " << str[i] << endl;


		bool b = Checkvalue(value[j], conditiontemp, table, table.attrs[j].attr_type);
		if(b/*Checkvalue(str[i], conditiontemp, table, table.attrs[i].attr_type)*/) { 
					condition_number ++;
		}
		else return false;
		conditiontemp = conditiontemp->next;
	}

	if(condition_count == condition_number)
		return true;
	else 
		return false;
}
//把属性连接成一串以便保存、输出
string Connect(string* ss, int count)
{
	string stemp = "";
	
	for(int i = 0; i < count;i++) {
		stemp += ss[i];
		stemp += " ";
	}
	return stemp;
}

//完全不用索引的查询
bool Findnoindex(Table table, Condition_list conditions)
{
	//int recordi = current_record;				//查询时当前块中记录的个数
	struct Block_Info* blocka;
	struct Record_Info* recorda;
	string* str ;
	string	 stemp ;
	int recordi;
	bool is_success = false;

	for(int blocki = total_block_number; blocki >= 0; blocki--) {
		if(blocki != total_block_number) {
			recordi = total_record_number;
			//debug
			blocka = onebuffer.GetBlock(table.table_name, blocki);
		} else {
			recordi = current_record;
			blocka = newblock;
		}
		
		blocka ->being_used = 1;
		//reservecount = 0;
		for (int i = 0; i < recordi; i++) {
			recorda = (Record_Info*)((char*)blocka ->address + i * record_size);
			
			void* mid = new char[record_size];
			if(memRestore(recorda) == 0) {
				int size;
				memRestore(recorda, size, mid);
				/*str = */RecToStr(mid, table, size);
				if(Isaccording(table, conditions, value)) {	
					show();
					is_success = true;
				}
			} 
			//delete (char*)mid;
		}
		//	recordi--;				
		//}
		blocka ->being_used = 0;
			
	}	
	//return reserve;
	if(is_success)
		return true;
	else
		error_info = "Couldn't find any record!\n";
	return false;	
}

bool Select(Table table, Condition_list conditions)
{
	if(Findnoindex(table,conditions)) {
		return true;
		//cout << "Select suceess.\n";
	}
	else {
		error_info = "Couldn't find any record.\n";
		return false;
		//cout << error_info;
	}
		
}
bool Deletenoindex(Table table, Condition_list conditions)
{
	struct Block_Info* blocka;
	struct Record_Info* recorda;
	string* str ;
	string	 stemp ;
	int recordi;
	bool is_success = false;

	for(int blocki = total_block_number; blocki >= 0; blocki--) {
		if(blocki != total_block_number) {
			recordi = total_record_number;
			//debug
			blocka = onebuffer.GetBlock(table.table_name, blocki);
		} else {
			recordi = current_record;
			blocka = newblock;
		}
		
		blocka ->being_used = 1;
		for (int i = 0; i < recordi; i++) {
			void* mid = new char[record_size];
			recorda = (Record_Info*)((char*)blocka ->address + i * record_size);
			if(memRestore(recorda) == 0) {
				int size;
				memRestore(recorda, size, mid);
				//----------------
				/*
				for (int j = 0; j < size; j++) {
					cout << ((char*)mid)[j];
				}
				cout << endl;
				*/RecToStr(mid, table, size);
				if(Isaccording(table, conditions,value)) {	
					bool btem = true;
					memStore(recorda, btem);
					is_success = true;
				}	
				//delete (char*)mid;
			} 
		}
		blocka ->being_used = 0;
	}	
	if(is_success)
		return true;
	else
		error_info = "Couldn't find any record!\n";
	return false;	
}

bool Delete(Table table, Condition_list conditions)
{
	if(Deletenoindex(table, conditions))
		return true;
		//cout << "Delete success.\n";
	else
		return false;
		//cout << error_info;
}
/*
int main()
{
	string value0[] = {"caca","123","1.23"};
	string value1[] = {"lost","222","2.22"};
	string value2[] = {"have","333","3.33"};
	string value3[] = {"temp","444","4.44"};
	
	
	Table table;
	table.table_name = "cat";
	table.attr_count = 3;
	table.attrs[0].attr_name = "char";
	table.attrs[0].attr_type = ATTR_TYPE_CHAR;
	table.attrs[0].attr_key_type = ATTR_TYPE_PRIMARY;
	table.attrs[0].attr_len = 4;
	table.attrs[0].attr_num = 1;
	
	
	table.attrs[1].attr_name = "int";
	table.attrs[1].attr_type = ATTR_TYPE_INT;
	table.attrs[1].attr_key_type = ATTR_TYPE_UNIQUE;
	table.attrs[1].attr_len = 1;
	table.attrs[1].attr_num = 2;
	
	
	table.attrs[2].attr_name = "float";
	table.attrs[2].attr_type = ATTR_TYPE_FLOAT;
	table.attrs[2].attr_key_type = ATTR_TYPE_NULL;
	table.attrs[2].attr_len = 1;
	table.attrs[2].attr_num = 3;

	Condition_list condi = (Condition*)(new Condition());
	Condition_list condi2 = (Condition*)(new Condition());
	
	condi->attr_name = "char";
	condi->op_type = BIG;
	condi->cmp_value = "a";
	condi->next = NULL;
	
	Insert(table,value0);
	Insert(table,value1);
	Insert(table,value2);
	Insert(table,value3);

	Select(table,condi);
	
	condi2->attr_name = "int";
	condi2->op_type = SMALL;
	condi2->cmp_value = "200";
	condi2->next = NULL;
	
	Delete(table,condi2);
	
	Select(table,condi);
	
	return 0;
}*/
