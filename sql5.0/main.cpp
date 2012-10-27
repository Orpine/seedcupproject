#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include<stdio.h>
#include<stdlib.h>
#include"main.h"
#include<fstream>
using namespace std;

int main()
{
    //int flage=0;
    //freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
    ifstream file;
    file.open("input.txt");
    while(!file.eof())      //判定文件尾用while(file)或前面那样都可以。
        // while(1)
    {
        string s;
        int tf;
        cout<<">>"<<endl;
        //以';'作为SQL语句结束的标志,输入一条SQL语句
        getline(file,s,';');
        if(s.empty()) break;
        if(!interpreter(s))
            continue;
        //对fk_word进行遍历，分类处理
        switch(fk_word)
        {

        case CREATE:

            if(sk_word==DATABASE)
                tf = CreateDatabase(fileName);

            else if(sk_word==TABLE)
                tf = CreateTable(fileName,Colu,Type);

            break;

        case USE:
            tf = UseDatabase(fileName);
            break;

        case SHOW:
            if(sk_word==DATABASES)
                tf = ShowDatabase();
            else if(sk_word==COLUMN)
                tf = ShowColumn(fileName);
            else if(sk_word==TABLE)
                ShowTables();
            else
                cout<<"error"<<endl;
            break;
            //firstKdy为drop
        case DROP:
            //删除表
            tf = Drop( DropFword, DropSword);
            break;
            //fk_word为select
        case SELECT:
            //无where条件查寻
            if(con_count==0)
                tf = Select0(fileName,selection);
            //一个where条件查寻
            else if(con_count==1)
                tf = Select1(selection,fileName,col1,condition1,operater1);
            //二个where条件查寻
            //else
            //	Select(fileName,col1,condition1,operater1,
            //		col2,condition2,operater2,logic);
            break;
            //fk_word为insert
        case INSERT:
            // cout<<"13"<<endl;
            Insert(fileName,TableCloumns,insertValue);
            break;
            //fk_word为delete
        case DELETE:
            Delete(fileName,col1, condition1, operater1);
            break;
        case ALTER:
            if(alt_count==1)
            {
                Alter(tableName,colName,colType);//添加列
            }
            else if(alt_count==2)
            {
                Alter_1(tableName,colName);//删除列
            }
            else if(alt_count==3)
            {
                Alter_2(tableName,colName,colType); //修改列类型
            }
            break;
        case RENAME:
            if(re_count==1)
            {
                Rename_Table(old_name,new_name);
            }
            else if(re_count==2)
            {
                Rename_Database(old_name,new_name);
            }
           // cout<<old_name+"->"+new_name<<endl;
            //cout<<re_count<<endl;
            break;
             case UPDATE:

                update_cond1( fileName,colname, values,cond,operater1,condition1);
               break;
        }
        //if(!tf)
        // cout<<"error"<<endl;
    }

    // fclose(stdin );
    return 0;
}


string getWord(string s, int *tmp)		//子函数，作用：读取SQL命令中下一个关键字。
{
    string word;
    int idx1,idx2,i;

    while ((s[*tmp] == ' ' || s[*tmp] == 10) && s[*tmp] != 0)	//去除前面无用的空格及换行符
    {
        (*tmp)++;
    }
    idx1 = *tmp;

    if (s[*tmp] == '(' || s[*tmp] == ',' || s[*tmp] == ')')		//对左括号、逗号和右括号做特别处理。
    {
        (*tmp)++;
        idx2 = *tmp;
        word = s.substr(idx1,idx2-idx1);
        return word;
    }
    else if (s[*tmp] == 39)					//对单引号内字符做特别处理。
    {
        (*tmp)++;
        while (s[*tmp] != 39 && s[*tmp] !=0)
            (*tmp)++;
        if (s[*tmp] == 39)
        {
            idx1++;
            idx2 = *tmp;
            (*tmp)++;
            word = s.substr(idx1,idx2-idx1);
            return word;
        }
        else
        {
            word = "";
            return word;
        }
    }
    else				//除上述几种特殊情况外的普通处理
    {
        while (s[*tmp] != ' ' && s[*tmp] != 10 && s[*tmp] != 0 && s[*tmp] != ')' && s[*tmp] != ','&& s[*tmp] != '(')
            (*tmp)++;
        idx2 = *tmp;
        if (idx1 != idx2)
            word = s.substr(idx1,idx2-idx1);
        else
            word = "";
        i = word.find("char");
        if (i >= 0 && s[*tmp] == ')')
        {
            (*tmp)++;
            idx2 = *tmp;
            word = s.substr(idx1,idx2-idx1);
        }
        return word;
    }
}
int interpreter(string s)
{

    int tmp=0;
    string word;

    word = getWord(s, &tmp);

    //第一层，读取第一个关键字
    if (stricmp(word.c_str(), "create") == 0)
        fk_word = CREATE;
    else if(stricmp(word.c_str(), "use") == 0)
        fk_word = USE;
    else if (stricmp(word.c_str(),"show") == 0)
        fk_word =SHOW;
    else if (stricmp(word.c_str(), "select") == 0)
        fk_word = SELECT;
    else if (stricmp(word.c_str(), "drop") == 0)
        fk_word = DROP;
    else if (stricmp(word.c_str(), "delete") == 0)
        fk_word = DELETE;
    else if (stricmp(word.c_str(), "insert") == 0)
        fk_word = INSERT;
    else if (strcmp(word.c_str(), "alter") ==0)
        fk_word = ALTER;
    else if (strcmp(word.c_str(), "rename") ==0)
        fk_word = RENAME;
    else if (stricmp(word.c_str(), "update") ==0)
		fk_word = UPDATE;
    else
    {
        cout<<"Error, command1 "<<word<<" not found"<<endl;
        return 0;
    }

//第二层
    if (fk_word == CREATE)		//第一关键字为create，则需要读取第二关键字判断创建对象。
    {
        word = getWord(s,&tmp);
        if (stricmp(word.c_str(), "table") == 0)
            sk_word = TABLE;
        else if(stricmp(word.c_str(),"database") == 0) //database
            sk_word = DATABASE;
        else
        {
            cout<<"Error, Usage: "<<fk_word<<" table or index fileName"<<endl;
            return 0;
        }
        if (sk_word == DATABASE)          //      新加的
        {
            word = getWord(s,&tmp);
            if (!word.empty())	 		//create database database_name 正确
            {
                fileName = word;
                word = getWord(s,&tmp);
                if (!word.empty())			//create database database_name 正确
                    cout<<"error";
            }
            else
            {
                cout<<"Error, Usage: "<<fk_word<<" table or index fileName"<<endl;
                return 0;
            }
        }
        else if (sk_word == TABLE)
        {
            word = getWord(s,&tmp);
            if (!word.empty())			//create table tablename 正确
                fileName = word;
            else
            {
                cout<<"Error, Usage: "<<fk_word<<" table or index fileName"<<endl;
                return 0;
            }
            if (sk_word == TABLE)			//第二关键字为table，即创建表
            {
                word = getWord(s,&tmp);
                if (word.empty() || strcmp(word.c_str(),"(") != 0)
                {
                    cout<<"Error in syntax!1"<<endl;
                    return 0;
                }
                else				//在读取左括号后逐一记录一下的列名和属性。
                {
                    word = getWord(s,&tmp);
                    while (!word.empty() && strcmp(word.c_str(),"primary") != 0 && strcmp(word.c_str(),")") != 0)
                    {
                        Colu.push_back(word);
                        word = getWord(s,&tmp);

                        if (!word.empty())
                            Type.push_back(word);
                        else
                        {
                            cout<<"Error in syntax!"<<endl;
                            return 0;
                        }

                        if (sk_word == TABLE)
                        {
                            word = getWord(s,&tmp);
                            if (strcmp(word.c_str(),"unique") == 0)
                            {
                                uniq.push_back(1);
                                word = getWord(s,&tmp);
                                if (strcmp(word.c_str(),",") != 0)
                                {
                                    cout<<"Error in syntax!"<<endl;
                                    return 0;
                                }
                            }
                            else if (strcmp(word.c_str(),",") == 0 || strcmp(word.c_str(),")") == 0)
                                uniq.push_back(0);
                            else if (word.empty() || strcmp(word.c_str(),")") != 0)
                            {
                                cout<<"Error in syntax!"<<endl;
                                return 0;
                            }
                        }
                        if (strcmp(word.c_str(),")") != 0)
                            word = getWord(s,&tmp);
                    }
                    /*if (strcmp(word.c_str(),"primary") == 0)	//当当前操作字符为primary时，判断为主键定义，退出列名属性读取的循环。
                    {
                    	word = getWord(s,&tmp);
                    	if (strcmp(word.c_str(),"key") != 0)
                    	{
                    		cout<<"Error in syntax!"<<endl;
                    		return 0;
                    	}
                    	else
                    	{
                    		word = getWord(s,&tmp);
                    		if (strcmp(word.c_str(),"(") == 0)
                    		{
                    			word = getWord(s,&tmp);
                    			primKey = word;
                    			word = getWord(s,&tmp);
                    			if (strcmp(word.c_str(),")") != 0)
                    			{
                    				cout<<"Error in syntax!"<<endl;
                    				return 0;
                    			}
                    		}
                    		else
                    		{
                    			cout<<"Error in syntax!"<<endl;
                    			return 0;
                    		}
                    	}
                    }*/
                    if (word.empty())
                    {
                        cout<<"Error in syntax!"<<endl;
                        return 0;
                    }
                }
            }
        }
    }

    else if (fk_word == USE)
    {
        word = getWord(s,&tmp);
        fileName = word;
        word = getWord(s,&tmp);
        if (!word.empty())
        {
            cout<<"error"<<endl;
            return 0;
        }

    }
else if (fk_word == UPDATE)
    {
        //int con_count;
        word = getWord(s,&tmp);
        fileName = word;
        word = getWord(s,&tmp);
        if (strcmp(word.c_str(),"set") == 0)
        {
            //cout<<"^^^"<<word<<endl;
            word = getWord(s,&tmp);
            if (strcmp(word.c_str(),"(") == 0)
            {
                word = getWord(s,&tmp);
                while (!word.empty() && strcmp(word.c_str(),")") != 0)
                {
                    if(strcmp(word.c_str(),",") != 0)
                       colname.push_back(word);
                       //Colu.push_back(word);
                    word = getWord(s,&tmp);
                }
                if (strcmp(word.c_str(),")") != 0)
                {
                    cout<<"Error in syntax!"<<endl;
                    return 0;
                }
                word = getWord(s,&tmp);
                //cout<<"***"<<word<<endl;
                 if(strcmp(word.c_str(),"=") == 0)
                {
                    word = getWord(s,&tmp);
                    //cout<<"here"<<" "<<word<<endl;
                    if (strcmp(word.c_str(),"(") == 0)
                    {
                        word = getWord(s,&tmp);
                       // cout<<word<<"###"<<endl;
                        while (!word.empty() && strcmp(word.c_str(),")") != 0 )
                        {
                            if (strcmp(word.c_str(),",") != 0)
                                values.push_back(word);
                            word = getWord(s,&tmp);
                        }
                        if (strcmp(word.c_str(),")") != 0)
                        {
                            cout<<"ppError in syntax!"<<endl;
                            return 0;
                        }
                    }
                    else
                    {
                        cout<<"error11"<<endl;
                        return 0;
                    }
                }
                else
                {
                    cout<<"error22"<<endl;
                    return 0;
                }
            }
            else
            {
                cout<<"error33"<<endl;
                return 0;
            }
            word = getWord(s,&tmp);
            if (strcmp(word.c_str(),"where") == 0)
            {
                word = getWord(s,&tmp);
                //cout<<word<<"@@@"<<endl;
				if (!word.empty())
				{
					cond = word;                                    //一个条件的情况
					con_count = 1;
					word = getWord(s,&tmp);
					//cout<<word<<"###"<<endl;
					if (word.empty())
					{
						con_count = -1;
						cout<<"Error in syntax! 3"<<endl;
						return 0;
					}

					else if (strcmp(word.c_str(),"<=") == 0)
						operater1 = "<=";
					else if (strcmp(word.c_str(),">=") == 0)
						operater1 = ">=";
					else if (strcmp(word.c_str(),"<") == 0)
						operater1 = "<";
					else if (strcmp(word.c_str(),">") == 0)
						operater1 = ">";
					else if (strcmp(word.c_str(),"==") == 0)
						operater1 = "==";
					else
					{
						con_count = -1;
						cout<<"Error in syntax! 4"<<endl;
						return 0;
					}
					word = getWord(s,&tmp);
					if (!word.empty())
					{
						if (word[0] == 39 && word[word.size()-1] == 39)
							word = word.substr(1,word.size()-2);
						condition1 = word;
						//cout<<condition1<<"uuu"<<endl;
					}
					else
					{
						con_count = -1;
						cout<<"Error in syntax! 5"<<endl;
						return 0;
					}
				}
				else
				{
					con_count = -1;
					cout<<"Error in syntax! 6"<<endl;
					return 0;
				}
            }
        }
        else
        {
            cout<<"error44"<<endl;
            return 0;
        }
    }
     else if (fk_word == SHOW)
    {
        word = getWord(s,&tmp);
        if (strcmp(word.c_str(), "databases") == 0)
        {

             sk_word = DATABASES;
        }
         else  if (strcmp(word.c_str(),"tables") == 0)     //show tables;
            {
                sk_word = TABLE;
            }

        else
        {
            fileName = word;
            word = getWord(s,&tmp);
            if (strcmp(word.c_str(),"column") == 0)     //show table_name column;
            {
                sk_word = COLUMN;
            }


        }

    }

    else if (fk_word == SELECT)		//第一关键字为select
    {

        do
        {
            word = getWord(s,&tmp);
            //cout<<word.c_str()<<endl;
            if (!word.empty())	//又要minisql只支持select *的查找方式，所以这里对除了select *以外的情况作为错误处理。
            {
                selection.push_back(word);
            }
            else
            {
                cout<<"error"<<endl;
                return 0;
            }
            word = getWord(s,&tmp);
        }
        while(word == ",");


        if (fk_word == SELECT)		//select 后语法正确
        {
            if (stricmp(word.c_str(), "from") != 0)
            {
                cout<<"Error in syntax!16"<<endl;
                cout<<word.c_str()<<endl;
                return 0;
            }
        }
        if (fk_word == SELECT)		//select * from后语法正确
        {
            word = getWord(s,&tmp);		//表名
            if (!word.empty())
                fileName = word;
            else
            {
                cout<<"Error in syntax!17"<<endl;
                return 0;
            }
        }
        if (fk_word == SELECT)		//在前面语法均正确的情况下，读取查询条件。
        {
            word = getWord(s,&tmp);
            if (word.empty())	//无条件
                con_count = 0; //条件数
            else if (stricmp(word.c_str(),"where") == 0)	//存在where
            {
                word = getWord(s,&tmp);		//col1
                if (!word.empty())
                {
                    col1 = word;
                    con_count = 1;
                    word = getWord(s,&tmp);
                    if (word.empty())
                    {
                        con_count = -1;
                        cout<<"Error in syntax!18"<<endl;
                        return 0;
                    }
                    else if (strcmp(word.c_str(),"<=") == 0)
                        operater1 = "<=";
                    else if (strcmp(word.c_str(),">=") == 0)
                        operater1 = ">=";
                    else if (strcmp(word.c_str(),"<") == 0)
                        operater1 = "<";
                    else if (strcmp(word.c_str(),">") == 0)
                        operater1 = ">";
                    else if (strcmp(word.c_str(),"==") == 0)   //改动了
                        operater1 = "==";
                    else if (strcmp(word.c_str(),"~=") == 0)
                        operater1 = "~=";
                    else
                    {
                        con_count = -1;
                        cout<<"Error in syntax!19"<<endl;
                        return 0;
                    }
                    word = getWord(s,&tmp);
                    if (!word.empty())
                    {
                        if (word[0] == 39 && word[word.size()-1] == 39)
                            word = word.substr(1,word.size()-2);
                        condition1 = word;
                    }
                    else
                    {
                        con_count = -1;
                        cout<<"Error in syntax!20"<<endl;
                        return 0;
                    }
                }
                else
                {
                    con_count = -1;
                    cout<<"Error in syntax!21"<<endl;
                    return 0;
                }

                word = getWord(s,&tmp);
                if (!word.empty())			//第二个条件
                {
                    if (stricmp(word.c_str(),"and") == 0)
                        logic = AND;
                    else if (stricmp(word.c_str(),"or") == 0)
                        logic = OR;
                    else
                    {
                        con_count = -1;
                        cout<<"Error in syntax!22"<<endl;
                        return 0;
                    }

                    word = getWord(s,&tmp);
                    if (!word.empty())
                    {
                        col2 = word;
                        con_count = 2;
                        word = getWord(s,&tmp);
                        if (word.empty())
                        {
                            con_count = -1;
                            cout<<"Error in syntax!23"<<endl;
                            return 0;
                        }
                        else if (strcmp(word.c_str(),"<=") == 0)
                            operater2 = "<=";
                        else if (strcmp(word.c_str(),">=") == 0)
                            operater2 = ">=";
                        else if (strcmp(word.c_str(),"<") == 0)
                            operater2 = "<";
                        else if (strcmp(word.c_str(),">") == 0)
                            operater2 = ">";
                        else if (strcmp(word.c_str(),"==") == 0)
                            operater2 = "==";
                        else
                        {
                            con_count = -1;
                            cout<<"Error in syntax!24"<<endl;
                            return 0;
                        }
                        word = getWord(s,&tmp);
                        if (!word.empty())
                        {
                            condition2 = word;
                        }
                        else
                        {
                            con_count = -1;
                            cout<<"Error in syntax!25"<<endl;
                            return 0;
                        }
                    }
                    else
                    {
                        con_count = -1;
                        cout<<"Error in syntax!26"<<endl;
                        return 0;
                    }
                }

            }
            if (con_count < 0)
            {
                cout<<"Error in syntax!27"<<endl;
                return 0;
            }
        }

    }

    else if (fk_word == DROP)		//当第一关键字为drop时，同样判断第二关键字以确定操作对象
    {
        DropFword = getWord(s,&tmp);
        DropSword = getWord(s,&tmp);
        word = getWord(s,&tmp);
        if(word.empty())
            return 1;
        else
            cout<<"error"<<endl;
        return 0;
    }

    else if (fk_word == DELETE)		//当第一关键字为delete时判断前面语法正确后，where后的操作同select语句。
    {
        word = getWord(s,&tmp);
        if (stricmp(word.c_str(),"from") == 0)
        {
            word = getWord(s,&tmp);
            if (!word.empty())
            {
                fileName = word;
                word = getWord(s,&tmp);
                if (stricmp(word.c_str(),"where") == 0)
                {
                    word = getWord(s,&tmp);		//col1
                    if (!word.empty())
                    {
                        col1 = word;
                        word = getWord(s,&tmp);
                        if (word.empty())
                        {
                            con_count = -1;
                            cout<<"Error in syntax!1"<<endl;
                            return 0;
                        }
                        else if (strcmp(word.c_str(),"<=") == 0)
                            operater1 = "<=";
                        else if (strcmp(word.c_str(),">=") == 0)
                            operater1 = ">=";
                        else if (strcmp(word.c_str(),"<") == 0)
                            operater1 = "<";
                        else if (strcmp(word.c_str(),">") == 0)
                            operater1 = ">";
                        else if (strcmp(word.c_str(),"==") == 0)
                            operater1 = "==";
                        else if (strcmp(word.c_str(),"~=") == 0)
                            operater1 = "~=";
                        else
                        {
                            con_count = -1;
                            cout<<"Error in syntax!2"<<endl;
                            return 0;
                        }
                        word = getWord(s,&tmp);
                        if (!word.empty())
                        {
                            if (word[0] == 39 && word[word.size()-1] == 39)
                                word = word.substr(1,word.size()-2);
                            condition1 = word;
                        }
                        else
                        {
                            con_count = -1;
                            cout<<"Error in syntax!3"<<endl;
                            return 0;
                        }
                    }
                    else
                    {
                        con_count = -1;
                        cout<<"Error in syntax!4"<<endl;
                        return 0;
                    }
                }
                else if (!word.empty())
                {
                    cout<<"Error in syntax!5"<<endl;
                    return 0;
                }
            }
            else
            {
                cout<<"Error in syntax!6"<<endl;
                return 0;
            }
        }
        else
        {
            cout<<"Error in syntax!7"<<endl;
            return 0;
        }
    }

    else if (fk_word == INSERT)		//第一关键字为insert时
    {

        word = getWord(s,&tmp);
        if (stricmp(word.c_str(),"into") == 0)
        {
            word = getWord(s,&tmp);
            if (!word.empty())
            {
                fileName = word;
                word = getWord(s,&tmp);
                if (stricmp(word.c_str(),"values") == 0)		//对values后面的值逐一读取。
                {
                    word = getWord(s,&tmp);
                    if (strcmp(word.c_str(),"(") == 0)
                    {
                        word = getWord(s,&tmp);
                        while (!word.empty() && strcmp(word.c_str(),")") != 0)
                        {
                            //cout<<"11"<<endl;
                            insertValue.push_back(word);
                            word = getWord(s,&tmp);
                            if (strcmp(word.c_str(),",") == 0)
                            {
                                word = getWord(s,&tmp);
                                //cout<<"12"<<endl;
                            }
                        }
                        if (strcmp(word.c_str(),")") != 0)
                        {
                            cout<<"Error in syntax!1"<<endl;
                            return 0;
                        }
                    }
                    else
                    {
                        cout<<"Error in syntax!2"<<endl;
                        return 0;
                    }
                }
                else if(word == "(")
                {
                    word = getWord(s,&tmp);
                    TableCloumns.push_back(word);
                    word = getWord(s,&tmp);
                    //cout<<"error1"<<endl;
                    while(word == ",")
                    {
                        word = getWord(s,&tmp);
                        if (!word.empty())	//又要minisql只支持select *的查找方式，所以这里对除了select *以外的情况作为错误处理。
                        {
                            TableCloumns.push_back(word);
                        }
                        else
                        {
                            cout<<"error"<<endl;
                            return 0;
                        }
                        word = getWord(s,&tmp);
                    }
                    word = getWord(s,&tmp);
                    if (stricmp(word.c_str(),"values") == 0)		//对values后面的值逐一读取。
                    {
                        word = getWord(s,&tmp);
                        if (strcmp(word.c_str(),"(") == 0)
                        {
                            word = getWord(s,&tmp);
                            while (!word.empty() && strcmp(word.c_str(),")") != 0)
                            {
                                //cout<<"11"<<endl;
                                insertValue.push_back(word);
                                word = getWord(s,&tmp);
                                if (strcmp(word.c_str(),",") == 0)
                                {
                                    word = getWord(s,&tmp);
                                    //cout<<"12"<<endl;
                                }
                            }
                            if (strcmp(word.c_str(),")") != 0)
                            {
                                cout<<"Error in syntax!1"<<endl;
                                return 0;
                            }
                        }
                        else
                        {
                            cout<<"Error in syntax!2"<<endl;
                            return 0;
                        }
                    }
                    else
                    {
                        cout<<"Error in syntax!3"<<endl;
                        return 0;
                    }
                }

                else
                {
                    cout<<"Error in syntax!4"<<endl;
                    return 0;
                }
            }
            else
            {
                cout<<"Error in syntax!5"<<endl;
                return 0;
            }
        }
    }
     else if (fk_word == ALTER)
    {
         alt_count=0;
        word = getWord(s,&tmp);
        if(strcmp(word.c_str(),"table") == 0)
        {
            word = getWord(s,&tmp);//table名
            if (!word.empty())
            {
                tableName=word;
                word = getWord(s,&tmp);//add
                if(strcmp(word.c_str(),"add") == 0)
                {
                    if(!word.empty())
                    {
                        word = getWord(s,&tmp);//添加项的名字
                        colName=word;
                        if(!word.empty())
                        {
                            word = getWord(s,&tmp);//添加项的类型
                            colType=word;
                        }
                        else
                            colType="none";//无输入则空类型

                        alt_count=1;
                        //Alter(tableName,colName,colType);-----------
                    }

                }
                else if(strcmp(word.c_str(),"drop") == 0)
                {
                    if(!word.empty())
                    {
                        word = getWord(s,&tmp);//删除项的名字
                        if(!word.empty())
                        {
                                if(strcmp(word.c_str(),"column") == 0)
                                {
                                    word = getWord(s,&tmp);
                                    colName=word;
                                    alt_count=2;
                                     // Alter_1(tableName,colName);
                                }
                        }

                    }

                }
                else if(strcmp(word.c_str(),"alter") == 0)
                {
                    if(!word.empty())
                    {
                        word = getWord(s,&tmp);
                        if(!word.empty())
                        {
                                if(strcmp(word.c_str(),"column") == 0)
                                {
                                    word = getWord(s,&tmp);
                                    colName=word;
                                  if(!word.empty())
                                  {
                                     word = getWord(s,&tmp);
                                    if(!stricmp(word.c_str(),"int") || !stricmp(word.c_str(),"float")||!stricmp(word.c_str(), "text"))//类型不可以错
                                    {
                                        colType=word;//修改的类型的名字
                                        // Alter_2(tableName,colName,colType);
                                        alt_count=3;
                                    }
                                  }
                                }
                        }
                        //colName=word;
                       /* if(!word.empty())
                        {
                            word = getWord(s,&tmp);//修改的类型的名字
                            colType=word;
                        }
                        */

                    }

                }

            }

        }
        if(alt_count!=1&&alt_count!=2&&alt_count!=3)
      cout<<"error"<<endl;

    }

    else if (fk_word == RENAME)
    {
        word = getWord(s,&tmp);
        if(strcmp(word.c_str(),"table") == 0)
        {
            word = getWord(s,&tmp);//old table名
            old_name=word;
            if (!word.empty())
            {
                word = getWord(s,&tmp);//table名
                new_name=word;
                re_count=1;
            }
            else cout<<"ERROR"<<endl;
        }
        else if(strcmp(word.c_str(),"database") == 0)
        {
            word = getWord(s,&tmp);//old database名
            old_name=word;
            if (!word.empty())
            {
                word = getWord(s,&tmp);//new database名
                new_name=word;
                re_count=2;
            }
            else cout<<"ERROR"<<endl;
        }
        else cout<<"ERROR"<<endl;
    }
    return 1;

}

bool CreateDatabase(string DbName)     //创建数据库
{
    db_info NewDatabase;
    NewDatabase.dbname=DbName;
    dblist.push_back(NewDatabase);
    return 1;
}

bool ShowDatabase(void)
{
    vector<db_info>::iterator it;
    int sign = 0;
    for(it=dblist.begin(); it<dblist.end(); it++)
    {
        cout<<(*it).dbname<<endl;
        sign = 1;
    }
     if(!sign)
        cout<<"$"<<endl;
     return 1;

}

bool ShowTables(void)
{
    int flag=0;
     vector<table_info>::iterator p;
    for(p=(*db_p).tlist.begin(); p<(*db_p).tlist.end(); p++)
    {
        cout<<(*p).tablename;
        if(p<(*db_p).tlist.end()-1) cout<<",";
        flag=1;
    }
    cout<<endl;
    if(!flag) cout<<"$"<<endl;
    return 1;
}
bool ShowColumn(string TableName)     //显示当前数据库指定表的各列的名字
{
    vector<table_info>::iterator it;
    int flag=0;
    for(it=(*db_p).tlist.begin(); it<(*db_p).tlist.end(); it++)
    {
        if((*it).tablename==TableName)
        {
            flag=1;
            unsigned int i;
            for( i = 0; i < (*it).colist.size(); i++)
            {
                cout<<(*it).colist[i].colname;
                if(i != (*it).colist.size()-1)
                    cout<<",";
            }
            cout<<endl;
        }
        if(flag)
            break;
    }
    if(!flag)
        cout<<"error"<<endl;
        return 1;
}

bool UseDatabase(string DbName)        //指定当前操作数据库
{
    vector<db_info>::iterator it;
    int flag=0;
    for(it=dblist.begin(); it<dblist.end(); it++)
    {
        if((*it).dbname==DbName)
        {
            db_p=it;
            current_dbname=DbName;
            flag=1;
            //cout<<"current_dbname is "<<current_dbname<<endl;   //调试信息
            break;
        }
    }
    if(flag==0)
        cout<<"error"<<endl;
    return 1;
}

bool CreateTable(string filename,vector<string> colname,vector<string> coltype)   //创建表，并加入到当前数据库中
{
    table_info NewTable;
    NewTable.tablename=filename;
    column_info NewClumn;
    unsigned int ii;
    for(ii=0; ii<colname.size(); ii++)
    {
        if(!stricmp(coltype[ii].c_str(), "int") || !stricmp(coltype[ii].c_str(), "float") ||
                !stricmp(coltype[ii].c_str(), "text"))
        {
            NewClumn.colname = colname[ii];
            NewClumn.coltype = coltype[ii];
            NewTable.colist.push_back(NewClumn);
        }
        else
            return 0;
    }
    Colu.clear();
    Type.clear();
    //加入到对应的数据库中
    (*db_p).tlist.push_back(NewTable);
    return 1;

}

bool Drop(string FirstWord, string SecondWord)            //删除指定的数据库
{
    vector<db_info>::iterator it;
    vector<table_info>::iterator p_table;
    int sign = 0;
    for(it=dblist.begin(); it<dblist.end(); it++)
    {
        if((*it).dbname==FirstWord && SecondWord.empty())
        {
            dblist.erase(it);
            return 1;
        }
        else if((*it).dbname==FirstWord && !SecondWord.empty())
        {
            for(p_table = (*it).tlist.begin(); p_table < (*it).tlist.end(); p_table ++)
            {
                if((*p_table).tablename == SecondWord)
                {
                    (*it).tlist.erase(p_table);
                    return 1;
                }
            }
        }
        else if(SecondWord.empty())
        {
            for(p_table = (*db_p).tlist.begin(); p_table < (*db_p).tlist.end(); p_table ++)
            {
                if((*p_table).tablename == FirstWord)
                {
                    (*db_p).tlist.erase(p_table);
                    return 1;
                }
            }

                cout<<"error"<<endl;
                return 1;
        }
        else
            cout<<"error"<<endl;
        return 1;
    }
}

bool Select0(string TableName,vector<string> Selection)
{
    int flag = 0;
    vector<table_info>::iterator p;
    for(p=(*db_p).tlist.begin(); p<(*db_p).tlist.end(); p++)
    {
        if((*p).tablename==TableName)
        {
            flag=1;
            unsigned int i = 0;
            unsigned int j = 0;
            unsigned int k = 0;
            unsigned int m = 0;
            if(Selection[0] == "*")
            {
                for( j = 0; j < (*p).colist[0].line.size(); j++)
                {
                    for( i = 0; i < (*p).colist.size(); i++)
                    {
                        for(k = 0; k < (*p).colist[i].line[j].size(); k++)
                            cout<<(*p).colist[i].line[j].at(k);
                        if(i != (*p).colist.size()-1)
                            cout<<",";
                    }
                    cout<<endl;
                }
                selection.clear();
            }
            else
            {
                // cout<<(*p).colist.size()<<endl;
                for( j = 0; j < (*p).colist[0].line.size(); j++)
                {
                    for( i = 0; i < (*p).colist.size(); i++)
                    {
                        for(m = 0; m < Selection.size(); m ++)
                        {
                            if(Selection[m] == (*p).colist[i].colname)
                            {
                                for(k = 0; k < (*p).colist[i].line[j].size(); k++)
                                    cout<<(*p).colist[i].line[j].at(k);
                                if(m != Selection.size()-1)
                                    cout<<",";
                            }
                        }
                    }
                    cout<<endl;
                }
            }
            selection.clear();
        }
        if(flag)
            break;
    }
    return 1;
}

bool Select1(vector<string> Selection, string TableName,string Column, string Condition ,string Operation )

{
    int flag = 0;
    int k = 0;
    vector<table_info>::iterator p;
    for(p=(*db_p).tlist.begin(); p<(*db_p).tlist.end(); p++)
    {
        if((*p).tablename==TableName)
        {
            flag=1;
            unsigned int i = 0;
            for( i = 0; i < (*p).colist.size(); i++)
            {
                if((*p).colist[i].colname == Column)
                {
                    k = 1;
                    break;
                }
            }

            if((*p).colist[i].coltype == "int")
                ;
            else if((*p).colist[i].coltype == "float")
                ;

        }
        if(flag)
            break;
    }
}
bool Insert(string TableName, vector<string> TableCloumn, vector<string> Values)

{
    int sign  = 0;
    vector<int> ColSnum;  //存放输入信息的列标，用于给信息为空的列置“#”
    vector<table_info>::iterator p;
    for(p=(*db_p).tlist.begin(); p<(*db_p).tlist.end(); p++)
    {
        if((*p).tablename==TableName)
        {
            if(TableCloumn.size() == 0)
            {
                unsigned int i = 0;
                for( i = 0; i < (*p).colist.size(); i++)
                    (*p).colist[i].line.push_back(Values[i]);
                insertValue.clear();
                return 1;
            }
            else
            {
                unsigned int i = 0;
                unsigned int j = 0;
                unsigned int k = 0;

                for(j = 0; j < TableCloumn.size(); j ++)
                {
                    for( i = 0; i < (*p).colist.size(); i++)
                    {
                        if(j == 0)
                            (*p).colist[i].line.push_back("#");
                        if(TableCloumn[j] == (*p).colist[i].colname)
                        {
                            (*p).colist[i].line[(*p).colist[i].line.size()-1] = Values[j];
                            //  ColSnum.push_back(i);
                        }
                    }
                }
                /* if(ColSnum.size()< ((*p).colist.size())){
                      cout<<(*p).colist.size();
                      cout<<ColSnum.size();
                       for(k = 0;k < ColSnum.size() ; k++){
                      for( i = 0; i < (*p).colist.size(); i++){

                              if(ColSnum[k]!= i){
                                  (*p).colist[i].line.push_back("#");
                              }
                          }
                       }
                      ColSnum.clear();
                      }*/
                insertValue.clear();
                TableCloumns.clear();
                return 1;
            }

        }
    }
    return 0;
}

bool Delete(string TableName, string Column, string Condition, string Operation)
{
    string value;
    int sign = 0;
    int flag = 0;
    string ColType;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    vector<int> LineNum;  //存行标
    vector<table_info>::iterator p_table;
    vector<column_info>::iterator p_col;
    vector<string>::iterator p_line;
    for(p_table = (*db_p).tlist.begin(); p_table<(*db_p).tlist.end(); p_table ++)
    {
        if((*p_table).tablename==TableName)
        {
            for(p_col = (*p_table).colist.begin(); p_col < (*p_table).colist.end(); p_col ++)
            {
                if((*p_col).colname == Column)
                {
                    ColType = (*p_col).coltype;
                    flag = 1;
                }
                for(i = 0; i < (*p_col).line.size(); i ++)
                {
                    value = (*p_col).line[i];
                    sign = Matching(ColType, value, Condition, Operation);
                    if(sign)
                        LineNum.push_back(i);
                }
                for(j = 0; j < (*p_table).colist.size(); j ++)
                {
                    for(k = 0; k < LineNum.size(); k++)
                    {
                        (*p_table).colist[j].line.erase((*p_table).colist[j].line.begin()+LineNum[k]);
                    }
                }
                if(flag)
                    break;
            }
            return 1;
        }
    }
    return 0;
}

int  Matching(string ColType,string Value,string Condition,string Operation)
{
    int tmp;
    //比较value 和 cond，将value 和 cond的差记为tmp
    const char* value;
    value = Value.c_str();
    const char * cond;
    cond = Condition.c_str();
    if(ColType=="int")
    {
        int * v;
        v=(int *)value;
        int cv;
        cv=atoi(cond);
        tmp=(*v)-cv;
    }

    else if(ColType=="float")
    {
        float * v;
        v=(float *)value;
        float cv;
        cv=(float)atof(cond);

        if((*v)<cv)
            tmp=-1;
        else if((*v)==cv)
            tmp=0;
        else
            tmp=1;
    }
    else
    {
        tmp=strcmp(value,cond);

    }

    //通过不同的operater和两者的差，来最后确定是否满足条件
    if(Operation=="<")
    {
        if(tmp<0)
            return 1;
        else
            return 0;
    }
    else if(Operation=="<=")
    {
        if(tmp<=0)
            return 1;
        else
            return 0;
    }
    else if(Operation==">")
    {
        if(tmp>0)
            return 1;
        else
            return 0;
    }
    else if(Operation==">=")
    {
        if(tmp>=0)
            return 1;
        else
            return 0;
    }
    else if(Operation=="==")
    {
        if(tmp==0)
            return 1;
        else
            return 0;
    }
    else if(Operation=="!=")
    {
        if(tmp!=0)
            return 1;
        else
            return 0;
    }
    //提示比较出错
    else
    {
        //cout<<"Fail to compare values"<<endl;
        return -1;
    }
}

void Alter(string tablename,string colName,string coltype)
{
    column_info a;
    //cout<<colName<<endl;
    a.colname=colName;
    a.coltype=coltype;
    // cout<<a.colname<<endl;
    //cout<<a.coltype<<endl;
    vector<table_info>::iterator p;

    int flag=0;
    for(p=(*db_p).tlist.begin(); p<(*db_p).tlist.end(); p++)
    {
        if((*p).tablename==tablename)
        {
            flag=1;
            break;
        }

    }
    //int i=(*p).colist.size();
    if(flag)
    {
        (*p).colist.push_back(a);
        return ;
    }
}

bool Alter_1(string tablename,string colName)
{
    // cout<<"i am the king"<<endl;
    vector<table_info>::iterator p;
    int flag=0;
    for(p=(*db_p).tlist.begin(); p<(*db_p).tlist.end(); p++)
    {
        if((*p).tablename==tablename)
        {
            flag=1;
            break;
        }

    }
    if(flag)
    {
        for(int i = 0; i < (*p).colist.size(); i++)
        {
            if((*p).colist[i].colname == colName)
            {
                (*p).colist.erase((*p).colist.begin()+i);
                break;
            }
        }

    }
    return 1;
}

bool Alter_2(string tablename,string colName,string colType)
{
    //cout<<"i am the king"<<endl;
    vector<table_info>::iterator p;
    int flag=0;
    for(p=(*db_p).tlist.begin(); p<(*db_p).tlist.end(); p++)
    {
        if((*p).tablename==tablename)
        {
            //cout<<"i am the king"<<endl;
            flag=1;
            break;
        }
    }
    if(flag)
    {
        for(int i = 0; i < (*p).colist.size(); i++)
        {
           // cout<<"i am the king"<<endl;
         // cout<<(*p).colist[i].colname<<endl;
            if((*p).colist[i].colname == colName)
            {
              //  cout<<"i am the king"<<endl;
                (*p).colist[i].coltype=colType;
                break;
            }
        }
    }
    return 1
    ;
}
bool Rename_Database(string old_name,string new_name)
{
    vector<db_info>::iterator it;
    for(it=dblist.begin(); it<dblist.end(); it++)
    {
        if((*it).dbname==old_name)
        {
            (*it).dbname=new_name;
         //   cout<<(*it).dbname<<endl;
         return 1;
        }
    }
    return 0;
}
bool Rename_Table(string old_name,string new_name)
{
    vector<table_info>::iterator p;
    for(p=(*db_p).tlist.begin(); p<(*db_p).tlist.end(); p++)
    {
        if((*p).tablename==old_name)
        {
            (*p).tablename=new_name;
            // cout<<(*p).tablename<<endl;
             return 1;
        }
    }
    return 0;
}
void update_cond1(string filename,vector<string> colname,vector<string> values,string cond,string operater,string condition)
{

    unsigned int ii,j,k,i;
    int flag=0;
    int flag2=0;
    vector<table_info>::iterator p;
    if(current_dbname=="")
    cout<<"error"<<endl;
    else
    {
        //cout<<"!!rrr"<<endl;
        for(p=(*db_p).tlist.begin();p<(*db_p).tlist.end();p++)
        {
            if((*p).tablename==filename)
            {

                flag=1;
                if((*p).colist.size()==0)
                {
                    cout<<"no colname"<<endl;
                    return ;
                }
                if((*p).colist.empty())        //表中没有数据
                {
                    cout<<"no data in table"<<endl;
                    return ;
                }

                //vector<string>::iterator sit=find((*it).colname.begin(),(*it).colname.end(),cond);
                for(  i = 0; i < (*p).colist.size()-1; i++){
                            if(cond == (*p).colist[i].colname){
                                ii=i;
                                 break;
                            }
                        }
                if(ii==(*p).colist.size())
                {
                    cout<<"error"<<endl;
                    return ;
                }
                //ii=sit-(*it).colist.begin();                //  ii为值为cond的列下标
                //cout<<ii<<endl;
                for(j=0;j<(*p).colist[0].line.size();j++)
                {
                    if(Matching((*p).colist[ii].coltype,(*p).colist[ii].line[j],condition,operater)) //  如果满足条件
                    {

                        int f;
                        flag2=1;
                        for(k=0;k<colname.size();k++)
                        {
                            //vector<string>::iterator fcit=find((*it).colname.begin(),(*it).colname.end(),colname[k]);
                            //unsigned f=fcit-(*it).colname.begin();
                            for( i = 0; i < (*p).colist.size()-1; i++){
                            if(colname[k] == (*p).colist[i].colname){
                               f=i;  break;
                            }
                        }
                        //cout<<"$$$"<<endl;
                          // cout<<values[k]<<endl;
                            (*p).colist[f].line[j]=values[k];
                        }

                    }
                }
                if(!flag2)
                cout<<"$"<<endl;
                break;
            }
        }
        if(!flag)
        cout<<"error"<<endl;
    }
}


