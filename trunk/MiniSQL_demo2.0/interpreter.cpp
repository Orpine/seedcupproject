#include"interpreter.h"
#include"CategoryManager.h"
#include"recordManager.h"
#include"bufferManager.h"
#include<iostream>
#include<iomanip>
using namespace std;

#include<afxwin.h>

void PrintCString(CString a)
{
	for (int i=0; i<a.GetLength(); i++)
		cout << a.GetAt(i);
	cout << endl;
}

interpreter::interpreter()
{
	cm = new categoryManager;
	rm = new recordManager;
	bm = new bufferManager;
	cm->setbufferManager(bm);
	rm->setbufferManager(bm);
}

interpreter::~interpreter()
{
	delete cm;
	delete rm;
	delete bm;
}

bool interpreter::InitCommand(CString &cmd)       //初始化SQL命令;检查是否有语法错误，如单括号，单引号，将\t,\n等合并为一个空格
{
	int i,j,k,l;
	CString stack;
	stack.Empty();
	for(i=0;i < cmd.GetLength();i++)     //检查括号
	{
		if(cmd[i] == '(')
			stack.Insert(stack.GetLength(),'(');
		else if(cmd[i] == ')')
		{
			if(stack.GetLength() > 0 && stack[stack.GetLength()-1] == '(')
				stack.Delete(stack.GetLength()-1,1);
			else
			{
				//cout<< "error右括号不匹配!" << endl;
				return false;
			}
		}
	}
	if(stack.GetLength() != 0)
	{
		//cout << "error左括号不匹配!" << endl;
		return false;
	}
	for(i=0,j=0;i<cmd.GetLength();i++)     //检查引号
	{
		if(cmd[i] == '\'')
			j++;
	}
	if(j%2 == 1)
	{
		cout << "error单引号不匹配!" << endl;
		return false;
	}
	cmd.Replace('\t',' ');
	cmd.Replace('\n',' ');
	cmd.Replace('\r',' ');  
	for(;cmd.GetLength() > 0 && cmd[0] == ' ';)
		cmd.Delete(0,1);					       //简化语句
	if(cmd.GetLength() == 0)
	{
		cout << "语句为空!" << endl;
		return false;
	}
	for(;cmd[cmd.GetLength()-1] == ' ';)
		cmd.Delete(cmd.GetLength()-1,1);
	if(cmd[cmd.GetLength()-1] != ';')          //不会出现吧
	{
		cout << "表达式应以分号结尾!" << endl;
		return false;
	}
	for(i=0,j=0;i<cmd.GetLength();i++)
	{
		if(cmd[i] == '\'')
			j++;
		if(j%2 == 0 && cmd[i] == ' ' && cmd[i+1] == ' ')
		{
			cmd.Delete(i+1,1);
			i--;
		}
	}
	for(i=0,j=0,k=0,l=0;i<cmd.GetLength();i++)
	{
		if(cmd[i] == '\'')
			j++;
		if(cmd[i] == '(')
			k++;
		if(cmd[i] == ')')
			l++;
		if(k == 1 && j%2 == 0 && cmd[i] == '(')
		{
			if(cmd[i-1] != ' ')
			{
				cmd.Insert(i,' ');
				i++;
			}
			if(cmd[i+1]==' ')
				cmd.Delete(i+1,1);
		}
		if(k == l && j%2 == 0 && cmd[i] == ')')
			if(cmd[i-1] == ' ')
				cmd.Delete(i-1,1);
		if(cmd[i] == ',')
		{
			if(cmd[i-1] == ' ')
			{
				cmd.Delete(i-1,1);
				i--;
			}
			if(cmd[i+1] == ' ')
				cmd.Delete(i+1,1);
		}
		if(j%2 == 0 && cmd[i] == ';')
			if(cmd[i-1] == ' ')
			{
				cmd.Delete(i-1,1);
				i--;
			}
		if(j%2 == 0 && cmd[i] == '!')
		{
			cmd.Insert(i,' ');
			i++;
		}
		if(j%2 == 0 && (cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '='))
		{
			if(i == 0)
			{
				cout << "表达式错误!" << endl;
				return false;
			}
			if(cmd[i-1] != '<' && cmd[i-1] != '>' && cmd[i-1] != '=' && cmd[i-1] != ' ' && cmd[i-1] != '!')
			{
				cmd.Insert(i,' ');
				i++;
			}
			if(cmd[i+1] != '<' && cmd[i+1] != '>' && cmd[i+1] != '=' && cmd[i+1] != ' ' &&cmd[i] != '!')
			{
				cmd.Insert(i+1,' ');
				i++;
			}
		}
	}
	return true;
}


bool interpreter::ExecuteCommand(CString cmd)      //执行sql命令
{
	if(InitCommand(cmd))
	{
		int i,j,k;
		CString temp = cmd;
		temp.MakeLower();
		if(temp.Find("create database") == 0)
		{	
			CString DbName;
			for(i=0,j=0;cmd[i]!='(' && i<cmd.GetLength();i++)
				if(cmd[i] == ' ')
					j++;
		
			if(j == 2)
			{
				for(i=16;cmd.GetAt(i)!=';';i++)
					DbName += cmd.GetAt(i);                            //数据库名存在DbName中

			}
			else
			{
				cout << "error" << endl;
				return false;
			}
		
			if(CreateDatabase(DbName) == 0)
				return false;
		}
		else if(temp.Find("use") == 0)
		{
			CString DbName;
			for(i=0,j=0;i<cmd.GetLength();i++)
				if(cmd[i] == ' ')
					j++;
			if(j == 1)
			{
				for(i=4;cmd[i]!=';';i++)
					DbName += cmd[i];
			}
			else
			{
				cout << "有语法错误!" << endl;

				return false;
			}
		//	AfxMessageBox(TableName);
			if(UseDatabase(DbName) == 0){
					printf("111");
				return false;
			}
		}
		else if(temp.Find("create table") == 0)
		{
			CString TableName,TableInfo;
			for(i=0,j=0;cmd[i]!='(' && i<cmd.GetLength();i++)
				if(cmd[i] == ' ')
					j++;
			if(j == 3)
			{
				for(i=13;cmd.GetAt(i)!=' ';i++)
					TableName += cmd.GetAt(i);                            //表名存在TableName中
				if(cmd.GetAt(i+1)!='(')
				{
					cout << "在create table附近有语法错误!" << endl;
					return false;
				}
				for(i+=1;cmd.GetAt(i)!=';';i++)
					TableInfo += cmd.GetAt(i);       // TableInfo存（）里面的内容


			}
			else
			{
				cout << "在create table附近有语法错误!" << endl;
				return false;
			}
		//	AfxMessageBox(TableName);
		//	AfxMessageBox(TableInfo);
			if(CreateTable(TableName,TableInfo) == 0)
				return false;
			}
	else if(temp.Find("drop") == 0)
		{
			CString TableName;
			for(i=0,j=0;i<cmd.GetLength();i++)
				if(cmd[i] == ' ')
					j++;
			if(j == 1)
			{
				for(i=5;cmd[i]!=';';i++)
					TableName += cmd[i];
			}
			else
			{
				cout << "在drop table附近有语法错误!" << endl;

				return false;
			}
		//	AfxMessageBox(TableName);
			if(DropTable(TableName) == 0){
				return false;}
		}
		else if(temp.Find("create index") == 0 || temp.Find("create unique index") == 0)
		{
			CString IndexName,On,TableName,AttName;
			bool unique;
			for(i=0,j=0;i<cmd.GetLength();i++)
				if(cmd[i] == ' ')
					j++;
			if(j == 5)
			{
				unique = 0;
				for(i=13;cmd[i]!=' ';i++)
					IndexName += cmd[i];
				for(i+=1;temp[i]!=' ';i++)
					On += temp[i];
				if(On = "on")
				{
					for(i+=1;cmd[i]!=' ' && cmd[i]!='(';i++)
						TableName += cmd[i];
					if(cmd[i] == '(')
					{
						for(i+=1;cmd[i]!=')';i++)
							AttName += cmd[i];
					}
					if(cmd[i+1] == '(')
					{
						for(i+=2;cmd[i]!=')';i++)
							AttName += cmd[i];
					}
					else
					{
						cout << "在create index附近有语法错误!" << endl;
						return false;
					}
				}
				else
				{
					cout << "在create index附近有语法错误!" << endl;
					return false;
				}
			}
			else
			{
				if(j == 6)
				{
					unique = 1;
					for(i=20;cmd[i]!=' ';i++)
						IndexName += cmd[i];
					for(i+=1;temp[i]!=' ';i++)
						On += temp[i];
					if(On = "on")
					{
						for(i+=1;cmd[i]!=' ' && cmd[i]!='(';i++)
							TableName += cmd[i];
						if(cmd[i] == '(')
						{
							for(i+=1;cmd[i]!=')';i++)
								AttName += cmd[i];
						}
						if(cmd[i+1] == '(')
						{
							for(i+=2;cmd[i]!=')';i++)
								AttName += cmd[i];
						}
						else
						{
							cout << "在create index附近有语法错误!" << endl;
							return false;
						}
					}
				}
				else
				{
					cout << "在create index附近有语法错误!" << endl;
					return false;
				}
			}
		//	AfxMessageBox(IndexName);
		//	AfxMessageBox(TableName);
		//	AfxMessageBox(AttName);
			if(CreateIndex(IndexName,TableName,AttName, unique) == 0)
				return false;
		}

		else if(temp.Find("select") == 0)
		{
			CString Selection,From,TableName,Where,Condition;
			for(i=0,j=0;i<cmd.GetLength();i++)
				if(cmd[i] == ' ')
					j++;
			if(j == 3)
			{
				for(i=7;cmd[i]!=' ';i++)
					Selection += cmd[i];
				Selection += ";";
				for(i+=1;temp[i]!=' ';i++)
					From += temp[i];
				if(From == "from")
					for(i+=1;cmd[i]!=';';i++)
						TableName += cmd[i];
				else
				{
					cout << "在select附近有语法错误!" << endl;
					return false;
				}
			}
			else if(j >= 5)
			{
				for(i=7;cmd[i]!=' ';i++)
					Selection += cmd[i];
				Selection += ";";
				for(i+=1;temp[i]!=' ';i++)
					From += temp[i];
				if(From == "from")
				{
					for(i+=1;cmd[i]!=' ';i++)
						TableName += cmd[i];
					for(i+=1;temp[i]!=' ';i++)
						Where += temp[i];
					if(Where == "where")
						for(i+=1;cmd[i]!=';';i++)
							Condition += cmd[i];
					Condition = " where " + Condition +";";
				}
				else
				{
					cout << "在select附近有语法错误!" << endl;
					return false;
				}
			}
			else
			{
				cout << "在select附近有语法错误!" << endl;
				return false;
			}
		//	AfxMessageBox(Selection);
		//	AfxMessageBox(TableName);
		//	AfxMessageBox(Condition);
			if(Select(Selection,TableName,Condition) == 0)
				return false;
		}
		else if(temp.Find("insert into") == 0)
		{
			CString TableName,Values,TableInfo;
			for(i=0,j=0,k=0;i<cmd.GetLength();i++)
			{
				if(cmd[i] == '\'')
					k++;
				if(k%2 == 0 && cmd[i] == ' ')
					j++;
			}
			if(j == 4)
			{
				for(i=12;cmd.GetAt(i)!=' ';i++)
					TableName += cmd.GetAt(i);
				for(i+=1;cmd.GetAt(i)!=' ';i++)
					Values += temp.GetAt(i);
				if(Values == "values")
				{
					if(cmd.GetAt(i+1) !='(')
					{
						cout << "insert into附近有语法错误!" << endl;
						return false;
					}
					else
					{
						for(i+=1;cmd.GetAt(i)!=';';i++)
						TableInfo += cmd.GetAt(i);
					}
				}
				else
				{
					cout << "insert into附近有语法错误!" << endl;
					return false;
				}
			}
			else
			{
				cout << "在insert into附近有语法错误!" << endl;
				return false;
			}
		//	AfxMessageBox(TableName);
		//	AfxMessageBox(TableInfo);
			if(insert(TableName,TableInfo) == 0)
				return false;
		}
		else if(temp.Find("delete from") == 0)
		{
			CString TableName,Where,Condition;
			for(i=0,j=0;i<cmd.GetLength();i++)
				if(cmd[i] == ' ')
					j++;
			if(j == 2)
				for(i=12;cmd.GetAt(i)!=';';i++)
					TableName += cmd.GetAt(i);
			else if(j >= 4)
			{
				for(i=12;cmd.GetAt(i)!=' ';i++)
					TableName += cmd.GetAt(i);
				if(temp.Find("where") == i+1)
				{
					for(i+=1;temp.GetAt(i)!=' ';i++)
						Where += temp.GetAt(i);
					if(Where == "where")
					{
						for(i+=1;cmd.GetAt(i)!=';';i++)
							Condition += cmd.GetAt(i);
						Condition = " where " + Condition + ";";
					}
					else
					{
						cout << "在delete from附近有语法错误!" << endl;
						return false;
					}
				}
				else
				{
					cout << "在delete from附近有语法错误!" << endl;
					return false;
				}
			}
			else
			{
				cout << "在delete from附近有语法错误!" << endl;
				return false;
			}
		//	AfxMessageBox(TableName);
		//	AfxMessageBox(Condition);
			if(Delete(TableName,Condition) == 0)
				return false;
		}
		else if(temp.Find("show tables") == 0)
		{
			
			if( cmd[11]==';')
			{
				if(ShowTable() == 0){
				return false;
				}
			}		
			else
			{
				return false;
			}	
		}
		else if(temp.Find("show databases") == 0)
		{
			
			if( cmd[14]==';')
			{
				if(ShowDatabase() == 0){
				return false;
				}
			}		
			else
			{
				return false;
			}	
		}
		else if(temp.Find("show") == 0)
		{	
			CString TableName,Column;
			for(i=0,j=0;i<cmd.GetLength();i++)
				if(cmd[i] == ' ')
					j++;
		
			if(j == 2)
			{
				for(i=5;cmd.GetAt(i)!=' ';i++)
					TableName += cmd.GetAt(i);
			
				for(i+=1;cmd.GetAt(i)!=';';i++)
					Column += cmd.GetAt(i);
				
				if(stricmp(Column,"column") == 0)
				
					if(ShowColumn(TableName) == 0)
						return false;
				
			}
			else
				return false;
		}
		if(temp.Find("create table") == 0 || temp.Find("drop") == 0 ||
			temp.Find("create index") == 0 || temp.Find("create unique index") == 0 ||
			 temp.Find("drop index") == 0 || temp.Find("select") == 0 ||
			 temp.Find("insert into") == 0 || temp.Find("delete from") == 0||temp.Find("create database") == 0 ||
			 temp.Find("show tables") == 0 || (temp.Find("show") == 0) || (temp.Find("use") == 0))
		{
			return true;
		}
		else
			return false;
		
	}
	else
		return false;
}
bool interpreter::UseDatabase(CString DbName)
{
	if(currentDbName == DbName)
		return 1;
	else 
		return 0;
}
bool interpreter::ShowTable()
{
	printf("%s\n",currentTableName);
	return 1;
}
bool interpreter::ShowDatabase()
{
	printf("%s\n",currentDbName);
	return 1;
}
bool interpreter::ShowColumn(CString TableName)
{
	int flag;
	char temp[255];
	CString s;
    table_info Table_info;
	CArray<record, record&>* rp;
	int num,jj;
	int attrflag;
	int at[32];

	flag = cm->readTable(TableName , Table_info);

	if(flag == 0)
	{
		//cout << "不存在该表" << endl;
		return 0;
	}

	rp = rm->readRecords(TableName, Table_info);

	if(rp == NULL || rp->GetSize() == 0)
	{
		//cout << "没有找到记录1!" << endl;
		return 1;
	}

	num = rp->GetSize();

	cout.setf(ios::right);

		
		for(int a=0;a<Table_info.attribute_count;a++)
		{
			printString(Table_info.info[a].attribute_name);
			if(a<Table_info.attribute_count-1)
				printf(",");
		}
		cout << endl;

		int attrCount = 0;
			
	cout.unsetf(ios::right);
	delete rp;
	return 1;
}
bool interpreter::insert(CString table_name, CString info)
{
	char temp[255];
	table_info Table_info;
	int ii=0,jj=0,flag=1,count=0,size;
	CString type;
	record Record;

	flag = cm->readTable(table_name, Table_info);

	if(flag == 0)
	{
		cout << "不存在这个表" <<endl;
		return 0;
	}

	if(table_name != currentTableName)             //当前表名
	{
		currentTableName = table_name;
		iset.clear();
		fset.clear();
		cset.clear();
		CString pk;
		pk = Table_info.primary_key;
		for(int i = 0; i < Table_info.attribute_count; i++)
		{
			if(Table_info.info[i].attribute_name == pk)
			{
				current_a = i;
				break;
			}
		}
		if(i == Table_info.attribute_count)
			has_pk = false;
		else
			has_pk = true;
	}


	while(info[ii]!=')')
	{
		ii++;
		jj=0;
		size=0;
		type="int";

		while(info[ii]!=',' && info[ii]!=')')
		{
			if(info[ii]=='\'')       // find the type
				type="text";
			if(info[ii]=='.')
				type="float";

			temp[jj++] = info[ii++]; //get the info
			size++;
		}

		if(Table_info.info[count].type!=type)
		{
			cout << "第" << count+1 << "个格式出错" << endl;
			return 0;
		}
		else
		if(type=="text")
		{
			Record.value[count].type_no = 0;
			Record.value[count].char_value = new char[Table_info.info[count].type_count];
			Record.value[count].char_count = Table_info.info[count].type_count;
			for(int k=1;temp[k]!='\'';)
			{
				Record.value[count].char_value[k-1]=temp[k];
				k++;
				if(k - 1 > Table_info.info[count].type_count - 1)
				{
					cout << "超过字符数限制!" << endl;
					return 0;
				}
			}
			Record.value[count].char_value[k-1]='\0';
		}
		else
		if(type=="float")
		{
			int k=0;
			float kk=1.0;
			Record.value[count].type_no = 1;
			Record.value[count].float_value = 0.0;
			while(temp[k]!='.')
			{
				Record.value[count].float_value = Record.value[count].float_value*10+(temp[k++]-'0');
			}
			k++;
			while(k<size)
			{
				kk=kk*0.1;
				Record.value[count].float_value = Record.value[count].float_value + (temp[k++]-'0')*kk;
			}
		}
		else
		{
			int k=0;
			Record.value[count].type_no = 2;
			Record.value[count].int_value = 0;
			while(k<size)
				Record.value[count].int_value = Record.value[count].int_value*10+temp[k++]-'0';
		}
		count++;
	}

	if(Table_info.attribute_count != count)
	{
		cout << "属性个数不符合." << endl;
		return 0;
	}
	else
		Record.attribute_count=Table_info.attribute_count;

	if(Record.value[current_a].type_no == 0 && has_pk == true)
	{
		CString temp;
		temp = Record.value[current_a].char_value;
		set<CString>::const_iterator cit;
		cit = cset.find(temp);
		if(cit == cset.end())
			cset.insert(temp);
		else
		{
			cout << "有重复值输入!" << endl;
			return 0;
		}
	}

	if(Record.value[current_a].type_no == 1 && has_pk == true)
	{
		float temp;
		temp = Record.value[current_a].float_value;
		set<float>::const_iterator cit;
		cit = fset.find(temp);
		if(cit == fset.end())
			fset.insert(temp);
		else
		{
			cout << "有重复值输入!" << endl;
			return 0;
		}
	}

	if(Record.value[current_a].type_no == 2 && has_pk == true)
	{
		int temp;
		temp = Record.value[current_a].int_value;
		set<int>::const_iterator cit;
		cit = iset.find(temp);
		if(cit == iset.end())
		{
			iset.insert(temp);
		}
		else
		{
			cout << "有重复值输入!" << endl;
			return 0;
		}
	}
	rm->storeRecord(table_name, Record);
	return 1;
}

bool interpreter::CreateDatabase(CString DbName)
{
	currentDbName = DbName;
	return 1;
}
bool interpreter::CreateTable(CString TableName,CString TableInfo)
{
	int i,j,k;
	table_info tb;                                    //table_info 为表结构
	tb.table_name = TableName; 
	currentTableName = TableName;
	TableInfo.Delete(0,1);                            //删除右括号
	TableInfo.Insert(TableInfo.GetLength()-1,' ');
	char* c = new char[TableInfo.GetLength()+1];
	_tcscpy(c,TableInfo);                                    //拷贝字符串
	for(i=0,j=0;i<TableInfo.GetLength();i++)
	{
		if(c[i] == '\'')
			j++;
		if(j%2 == 0 && c[i] == ',' || c[i] == ' ')
			c[i] = '\0';
	}
	char* p = c;
	for(k=0;;k++)
	{
		CString AttName,AttType,s,temp;                  //每一行的，类名，和类型
		int AttTypeCount;
		AttName = p;
		p += AttName.GetLength()+1;
		if(AttName == ")")
			break;
	
		tb.info[k].attribute_name = AttName;                      //类名，存在tb中
		s = p;
		for(i=0;i<s.GetLength() && s.GetAt(i)!='(';i++)            
			AttType += s[i];
		p += AttType.GetLength()+1;
		if(AttType!="int" && AttType!="float" && AttType!="text")
		{
			cout << "类型错误!" << endl;
			return false;
		}
		tb.info[k].type = AttType;
		if(AttType == "text" )//&& i != s.GetLength() && s[i] == '(' && s[s.GetLength()-1] == ')')
		{
			//s.TrimLeft(AttType);
		//	s.Delete(0,1);
		//	s.Delete(s.GetLength()-1,1);
			AttTypeCount = 30;
			tb.info[k].type_count = AttTypeCount;
		//	p += s.GetLength()+2;
		//	s = p;
		}
		else if(AttType != "text")
		{
			AttTypeCount = 1;
			tb.info[k].type_count = AttTypeCount;
		}
		else
		{
			cout << "在char附近有语法错误!" << endl;
			return false;
		}
		/*if(s == "unique")
		{
			tb.info[k].unique = true;
			s = p;
			p += s.GetLength()+1;
		}
		else
			tb.info[k].unique = false;*/
	}
	tb.attribute_count = k;
	cm->saveTable(tb);
	delete [] c;
	return true;
}


bool interpreter::Delete(CString table_name, CString info)
{
	char temp[255];
	CString s;
	table_info Table_info;
	int ii,jj,flag=1,count=0,size,i;
	CString type;
	CArray<condition , condition&>* rp = new CArray<condition, condition&>;

	condition* cp;

	flag = cm->readTable(table_name, Table_info);


	if(flag == 0)
	{
		cout << "不存在该表" << endl;
		return 0;
	}

	if(info.GetLength() == 0)
	{
		rm->rmRecord(table_name);
		return 1;
	}

	ii = 0;
	size = 0;
	while(info[ii] != ';')
	{
		if(info[ii++] == ' ')size++;
	}

	if(size%4 != 0)
	{
		cout << "格式有误" << endl;
		return 0;
	}

	size = size/4;
	cp = new condition[size];

	ii = 0;
	while(info[ii]!=';')
	{
		ii++;
		while(info[ii++]!=' '){}

		jj = 0;
		while(info[ii]!=' ')
		{
			temp[jj++] = info[ii++];
		}
		temp[jj] = '\0';

		for(i = 0;i<Table_info.attribute_count;i++)
		{
			if(temp == Table_info.info[i].attribute_name)
			{
				 cp[count].item1 = i;
				 break;
			}
		}
		if(i == Table_info.attribute_count)
		{
			cout << "第 " << count + 1 << "个条件的属性不存在!" << endl;
			return 0;
		}

		ii++;
		jj = 0;
		while(info[ii]!=' ')
		{
			temp[jj++] = info[ii++];
		}
		temp[jj] = '\0';
		s = temp;

		if(s == "=")
			cp[count].operation = 0;
		else
		if(s == "<")
			cp[count].operation = 1;
		else
		if(s == ">")
			cp[count].operation = 2;
		else
		if(s == "<=")
			cp[count].operation = 3;
		else
		if(s == ">=")
			cp[count].operation = 4;
		else
		if(s == "<>")
			cp[count].operation = 5;

		ii++;
		jj = 0;
		type = "int";
		while(info[ii]!=' ' && info[ii]!=';')
		{
			if(info[ii]=='\'')
				type="text";
			if(info[ii]=='.')
				type="float";

			temp[jj++] = info[ii++];
		}
		temp[jj] = '\0';



		if(Table_info.info[i].type != type)
		{
			cout << "类型不符" << endl;

			return 0;
		}
		else
		{
			if(type == "int")
			{
				cp[count].type = 2;
				cp[count].item2 = temp;
			}
			else
			if(type == "float")
			{
				cp[count].type = 1;
				cp[count].item2 =temp;
			}
			else
			if(type == "text")
			{
				cp[count].type = 0;
				int iii=1;
				while(temp[iii]!='\'')
				{
					temp[iii-1] = temp[iii];
					iii++;
				}
				temp[iii-1] = '\0';
				cp[count].item2 = temp;
			}
		}
		rp->Add(cp[count]);
		count++;
	}
	rm->rmRecord(table_name, &Table_info, rp);
	delete rp;
	return 1;
}

void interpreter::printString(const CString& c)                           //输出字符串
{
	int size = c.GetLength();
	char* array = new char[size + 1];
	strcpy(array, c);
	cout.width(20);
	cout << array;
	delete [] array;
}

bool interpreter::Select(CString Selection, CString TableName, CString Condition)
{
	bool flag;
	if(Condition.GetLength() == 0)
		flag = print1(TableName, Selection);                       //改一下，tablename不需要输出
	else
		flag = print2(TableName, Selection, Condition);
	return flag;
}

bool interpreter::print1(CString Table_name , CString attr)
{
	int flag;
	char temp[255];
	CString s;
    table_info Table_info;
	CArray<record, record&>* rp;
	int num,jj;
	int attrflag;
	int at[32];

	flag = cm->readTable(Table_name , Table_info);

	if(flag == 0)
	{
		//cout << "不存在该表" << endl;
		return 0;
	}

	rp = rm->readRecords(Table_name, Table_info);

	if(rp == NULL || rp->GetSize() == 0)
	{
		//cout << "没有找到记录1!" << endl;
		return 1;
	}

	num = rp->GetSize();

	cout.setf(ios::right);
	if(attr == "*;")
	{
		for(int a=0;a<Table_info.attribute_count;a++)
		{
			//	printString("列名");
		}
	//	cout << endl;
		for(a=0;a<Table_info.attribute_count;a++)
		{
		//	printString(Table_info.info[a].attribute_name);
		}
		//cout << endl;

		for(int b=num - 1;b>=0;b--)
		{
			for(a=0;a<Table_info.attribute_count;a++)
			{
				if(Table_info.info[a].type == "text")
					cout << setw(20) << (*rp)[b].value[a].char_value;
				else
				if(Table_info.info[a].type == "float")
					cout << setw(20) << (*rp)[b].value[a].float_value;
				else
				if(Table_info.info[a].type == "int")
					cout << setw(20) << (*rp)[b].value[a].int_value;
				if(a<Table_info.attribute_count-1)
					printf(",");
			}
			cout << endl;
		}
	}
	else
	{
		int attrCount = 0;
		int ai = 0;
		int na;
		attr.Insert(0,',');
		while(attr[ai]!=';')
		{
			jj = 0;
			ai++;
			while( (attr[ai]!=',')&& (attr[ai]!=';'))
			{
				temp[jj++] = attr[ai++];
			}
			temp[jj] = '\0';
			s = temp;
			attrflag = 0;
			for(na=0;na<Table_info.attribute_count;na++)
			{
				if(s == Table_info.info[na].attribute_name)
				{
					at[attrCount] = na;
					attrflag = 1;
					break;
				}
			}
			if(attrflag == 0)
			{
				//cout << "第" << attrCount+1 << "个属性名未找到" << endl;
				return 0;
			}
			attrCount++;
		}
		for(int a=0;a<attrCount;a++)
		{
		//	printString("列名");
		}
	//	cout << endl;
		for(a=0;a<attrCount;a++)
		{
		//	printString(Table_info.info[(at[a])].attribute_name);
		}
	//	cout << endl;

		for(int b=num-1;b>=0;b--)
		{
			for(a=0;a<attrCount;a++)
			{
				if(Table_info.info[at[a]].type == "text")
					cout << setw(20) << (*rp)[b].value[at[a]].char_value;
				else
				if(Table_info.info[at[a]].type == "float")
					cout << setw(20) << (*rp)[b].value[at[a]].float_value;
				else
				if(Table_info.info[at[a]].type == "int")
					cout << setw(20) << (*rp)[b].value[at[a]].int_value;
				if(a<Table_info.attribute_count-1)
					printf(",");
			}
			cout << endl;
		}
	}
	cout.unsetf(ios::right);
	delete rp;
	return 1;
}

bool interpreter::DropIndex(CString indexName)
{
	return 1;
}

bool interpreter::print2(CString Table_name , CString attr , CString info)
{
	int flag;
	char temp[255];
	CString s,type;
    table_info Table_info;
	CArray<record, record&>* rp;
	CArray<condition , condition&>* ccp = new CArray<condition, condition&>;
	condition* cp;
	int num,jj,ii,size,i,count;
	int attrflag;
	int at[32];

	flag = cm->readTable(Table_name , Table_info);

	if(flag == 0)
	{
		cout << "不存在该表" << endl;
		return 0;
	}

	ii = 0;
	size = 0;
	while(info[ii] != ';')
	{
		if(info[ii++] == ' ')size++;
	}

	if(size%4 != 0)
	{
		cout << "格式有误" << endl;
		return 0;
	}

	size = size/4;
	cp = new condition[size];

	ii = 0;
	count = 0;
	while(info[ii]!=';')
	{
		ii++;
		while(info[ii++]!=' '){}

		jj = 0;
		while(info[ii]!=' ')
		{
			temp[jj++] = info[ii++];
		}
		temp[jj] = '\0';

		for(i = 0;i<Table_info.attribute_count;i++)
		{
			if(temp == Table_info.info[i].attribute_name)
			{
				 cp[count].item1 = i;
				 break;
			}
		}

		if(i == Table_info.attribute_count)
		{
			cout << "第 " << count + 1 << "个条件的属性不存在!" << endl;
			return 0;
		}

		ii++;
		jj = 0;
		while(info[ii]!=' ')
		{
			temp[jj++] = info[ii++];
		}
		temp[jj] = '\0';
		s = temp;

		if(s == "==")
			cp[count].operation = 0;
		else
		if(s == "<")
			cp[count].operation = 1;
		else
		if(s == ">")
			cp[count].operation = 2;
		else
		if(s == "<=")
			cp[count].operation = 3;
		else
		if(s == ">=")
			cp[count].operation = 4;
		else
		if(s == "<>")
			cp[count].operation = 5;
		else
		{

			return 0;
		}
		ii++;
		jj = 0;
		type = "int";
		while(info[ii]!=' ' && info[ii]!=';')
		{
			if(info[ii]=='\'')
				type="text";
			if(info[ii]=='.')
				type="float";

			temp[jj++] = info[ii++];
		}
		temp[jj] = '\0';



		if(Table_info.info[i].type != type)
		{
			cout << "类型不符" << endl;

			return 0;
		}
		else
		{
			if(type == "int")
			{
				cp[count].type = 2;
				cp[count].item2 = temp;
			}
			else
			if(type == "float")
			{
				cp[count].type = 1;
				cp[count].item2 =temp;
			}
			else
			if(type == "text")
			{
				cp[count].type = 0;
				int iii=1;
				while(temp[iii]!='\'')
				{
					temp[iii-1] = temp[iii];
					iii++;
				}
				temp[iii-1] = '\0';
				cp[count].item2 = temp;
			}
		}
		ccp->Add(cp[count]);
		count++;
	}

	rp = rm->readRecords(Table_name, Table_info , ccp);

	if(rp == NULL || rp->GetSize() == 0)
	{
		cout << "没有找到记录!" << endl;
		return 1;
	}
	num = rp->GetSize();
	cout.setf(ios::right);
	if(attr == "*;")
	{
		for(int a=0;a<Table_info.attribute_count;a++)
		{
		//	printString("列名");
		}
		//cout << endl;
		for(a=0;a<Table_info.attribute_count;a++)
		{
		//	printString(Table_info.info[a].attribute_name);
		}
	//	cout << endl;

		for(int b=num-1;b>=0;b--)
		{
			for(a=0;a<Table_info.attribute_count;a++)
			{
				if(Table_info.info[a].type == "text")
					cout << setw(20) << (*rp)[b].value[a].char_value;
				else
				if(Table_info.info[a].type == "float")
					cout << setw(20) << (*rp)[b].value[a].float_value;
				else
				if(Table_info.info[a].type == "int")
					cout << setw(20) << (*rp)[b].value[a].int_value;
				if(a<Table_info.attribute_count-1)
					printf(",");
			}
			cout << endl;
		}
	}
	else
	{
		int attrCount = 0;
		int ai = 0;
		int na;
		attr.Insert(0,',');
		while(attr[ai]!=';')
		{
			jj = 0;
			ai++;
			while( (attr[ai]!=',')&& (attr[ai]!=';'))
			{
				temp[jj++] = attr[ai++];
			}
			temp[jj] = '\0';
			s = temp;
			attrflag = 0;
			for(na=0;na<Table_info.attribute_count;na++)
			{
				if(s == Table_info.info[na].attribute_name)
				{
					at[attrCount] = na;
					attrflag = 1;
					break;
				}
			}
			if(attrflag == 0)
			{
				cout << "第" << attrCount+1 << "个属性名未找到" << endl;
				return 0;
			}
			attrCount++;
		}
		for(int a=0;a<attrCount;a++)
		{
		//	printString("列名");
		}
	//	cout << endl;
		for(a=0;a<attrCount;a++)
		{
		//	printString(Table_info.info[(at[a])].attribute_name);
		}
	//	cout << endl;

		for(int b=num-1;b>=0;b--)
		{
			for(a=0;a<attrCount;a++)
			{
				if(Table_info.info[at[a]].type == "text")
					cout << setw(20) << (*rp)[b].value[at[a]].char_value;
				else
				if(Table_info.info[at[a]].type == "float")
					cout << setw(20) << (*rp)[b].value[at[a]].float_value;
				else
				if(Table_info.info[at[a]].type == "int")
					cout << setw(20) << (*rp)[b].value[at[a]].int_value;
				if(a<Table_info.attribute_count-1)
					printf(",");
			}
			cout << endl;
		}
	}
	cout.unsetf(ios::right);
	delete rp;
	delete ccp;
	return 1;
}

bool interpreter::CreateIndex(CString IndexName, CString TableName, CString AttName, bool unique)
{
	table_info a;
	if(cm->readTable(TableName, a))
	{
		for(int i = 0; i < a.attribute_count; i++)
			if(a.info[i].attribute_name == AttName)
				break;
		if(i == a.attribute_count)
		{
			cout << "不存在此属性!" << endl;
			return 0;
		}
		if(a.info[i].unique == false && unique == false)
		{
			cout << "该属性不唯一，无法创建index!" << endl;
			return 0;
		}
	}
	else
	{
		cout << "不存在此表" << endl;
		return 0;
	}
	return 1;
}

bool interpreter::DropTable(CString tableName)
{
	rm->rmRecord(tableName);
	cm->dropTable(tableName);
	return 1;
}

