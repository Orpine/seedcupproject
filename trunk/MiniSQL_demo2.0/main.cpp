#include"basichead.h"
#include"DBFile.h"
#include"block.h"
#include"bufferManager.h"
#include"recordManager.h"
#include"CategoryManager.h"
#include"interpreter.h"
#include<afxwin.h>


#include<iostream>
using namespace std;


int main()
{
	char cmd[10000];
	int flage=0;
//	int i = 0;
	CString a,temp;
	interpreter b;
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	/*if(freopen("d:\\test.txt","r",stdin)==NULL){
   
        exit(-1);
        }
	for( i = 0; (cmd[i] = getchar())!=EOF;i++);
		printf("%s",cmd);
        
*/ 
	while(1)
	{
	
		a = "";
		do
		{
			gets(cmd);
			a += " ";
			a += cmd;
			flage=1;

		}
		while(a.GetAt(a.GetLength() - 1) != ';');
		if(!flage)break;
	//	AfxMessageBox(a);

		if(a == " quit;")
			break;
		
		CString temp = a;
		temp.MakeLower();
		if(temp.Find("create") != -1 || temp.Find("drop") != -1
			|| temp.Find("select") != -1 || temp.Find("insert") != -1||temp.Find("alter table") != -1
			|| temp.Find("delete") != -1 || temp.Find("show") != -1|| temp.Find("use") != -1)
		{	
			if(b.ExecuteCommand(a))
				;
			else
				cout << "error" << endl;
		}
		else
		{
			cout << "error" << endl;
		}
		flage=0;
	}
//	fclose(stdin);
	return 0;
}
