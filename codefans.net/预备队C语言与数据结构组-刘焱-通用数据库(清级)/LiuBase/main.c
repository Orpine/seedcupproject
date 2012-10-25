
/*头文件部分*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>





/***************************************************************************************************************/






/*宏定义部分*/


#define TABLE_LENTH 20   //定义表的长度
#define MAX_DATA_LEN 20  //定义最大字段数
#define MAX_NAME_LENTH 20  //定义字段名的最大长度
#define MAX_LEN_FILE_NANE 127  //定义文件名的最大长度
#define MAX_STRING_LENGTH 127 //定义字符串的最大长度
#define OK 1    //操作成功
#define ERROR 0   //操作失败
#define INITSTATUS -1 //初始状态
#define  SUPER_MARKET_MODEL 0//超市模式
#define  OFFICE_MODEL 1//办公模式


int  nModel=SUPER_MARKET_MODEL;//唯一的全局变量,记录系统模式









/***************************************************************************************************************/


/*数据结构定义部分*/



//定义元素类型
union Elemtype
{
	char CHAR;   //字符型
	char STRINR[MAX_STRING_LENGTH];  //字符串型
	int INT;//整数型
	double DOUBLE;//浮点型

};




//定义元素节点类型
struct Node
{
	union Elemtype arr[MAX_DATA_LEN];
	struct Node *next;

};




//字段基本信息结构体
struct Data
{
	char strName[MAX_NAME_LENTH];  //字段名
	int nLen;  //字段长度
	char cType; //字段类型
};





//记录字段基本信息的节点结构体
struct DataNode
{
	struct Data data;//字段基本信息结构体
	struct DataNode *pNext;//指针

};





//记录所有字段信息的表结构体
struct Table
{
	int nLen;//表的长度
	struct Data Head[MAX_NAME_LENTH];//记录字段全部信息的数组


	int nCount;//记录数据容量
};




//定义文件结构
struct File
{
	struct Table *pTable;//表头指针
	struct Node *pHead;//数据区指针
	int    nCount;//数据区容量
};





/***************************************************************************************************************/




/*函数定义部分*/



void SubMenu(struct File *file);
void AddData(struct File *file);
void Read(struct File  *file,char *strFileName);
void MyUpdateData(struct Node *pCur,struct File *file);
void Update( struct File *file);
void  ShowTable(struct Table *pTable);
void ShowData(  union Elemtype  *arr ,struct File *file );
void AddData(struct File *file);
void Add(struct File *file);
void CheckChar(  struct File *file , int *bIsOK , int nIndex  );
void CheckDouble(  struct File *file , int *bIsOK, int nIndex   );
void CheckInt(  struct File *file , int *bIsOK, int nIndex  );
void CheckString(  struct File *file , int *bIsOK , int nIndex  );
void CreateTable(struct Table *pTable);
void Delete(struct File *file);
void DelteFile(  struct File *file );
void Driver();
void Find(struct File *file);
void GetChar(char *pChar);
void GetString(char *str);
int GetStrName(char *str);
void Help();
void InitFile(struct File *file);
void MainMenu();
void MyUpdateData(struct Node *pCur,struct File *file);
void New(struct File *file);
void Open(struct File *file);
void Read(struct File  *file,char *strFileName);
void ReadData(struct File *file,char *strFileName);
void ReadTable(struct File *file,char *strFileName);
void Save(struct File  file,char *strFileName);
void SaveData(struct File  file,char *strFileName);
void SaveTable(struct Table *pTable,char *strFileName);
void ShowData(  union Elemtype  *arr ,struct File *file );
void  ShowTable(struct Table *pTable);
void SubMenu(struct File *file);


/*
 *  函数功能：获取字段类型,并处理异常

 *  输入参数：字段名指针str
 *  输出参数：字段名指针str
 *  返 回 值：无
 */
void GetString(char *str)
{


	while(1)
	{

		gets(str);

		if(strlen(str))
		{
			break;
		}
		printf("输入不可为空\n请在输入一遍\n");

	}

}






/*
 *  函数功能：初始化文件,为表头,数据区分配空间,其余各项置零

 *  输入参数:文件指针
 *  输出参数：无
 *  返 回 值：无
 */
void InitFile(struct File *file)
{
	struct Node *p;
	p=(  struct Node * )malloc(  sizeof(struct Node )  );
	p->next=NULL;
	file->pHead=p;
	file->nCount=0;
	file->pTable=(  struct Table *  )malloc(  sizeof(  struct Table  )  );
	file->pTable->nCount=0;
	file->pTable->nLen=0;
}



/*
 *  函数功能：获取字段名,并处理异常

 *  输入参数：字段名指针str
 *  输出参数：字段名指针str
 *  返 回 值：状态 1 表示输入成功并继续字段的输入  状态 0  退出字段输入
 */


int GetStrName(char *str)
{
	char strChoice[20];
	char ch;


	while(1)
	{


		/*吸收回车符*/
	//    ch=getchar();

		/*截取字符段*/
		gets(str);



		if(  strlen( str ) )
		{

		/*输入字符串非空则返回*/

			return OK;
		}
/*		else if( ERROR==IsRight(str) )
		{
			printf("%s已存在,请重命名:\n ");
			continue ;

		}*/
		else
		{

			/*
			输入字符串为空则人机交互,
			判断是误操作还是退出建库
			*/
			printf("退出建库?(Y/any key)");
			gets(strChoice);
			if('Y'==strChoice[0])
			{
				return ERROR;
			}
			else
			{
				printf("请输入数据名:\n");
				continue;

			}
		}


	}

}


int IsRight( struct Table *pTable, char *str )
{
	int i;
	int nCount;
//	printf("~~~~~%d ~~~~",pTable->nLen);
	for( i=0 ,nCount=MAX_DATA_LEN; i < nCount ; i++ )
	{
		if( 0 == strcmp( pTable->Head[i].strName, str))
		{
			return ERROR;
		}
	}
	return OK;
}





/*
 *  函数功能：建表并加载信息

 *  输入参数：表指针
 *  输出参数：记录所有字段信息的Table指针
 *  返 回 值：无
 */

void CreateTable(struct Table *pTable)
{
	int len=0;
	char string[20];
	char strChoice[20];
	struct Data data;





	printf("请输入数据名:\n");
	gets(data.strName);


//	puts(data.strName);



	if(!strlen(data.strName))
	{
			printf("退出建库?(Y/any key)");
			gets(strChoice);
			if('Y'==strChoice[0])
			{
				pTable->nLen=0;
				return ;
			}
			else
			{
				printf("请输入数据名:\n");
				gets(data.strName);




	puts(data.strName);




			}

	}

           printf("请输入数据类型:\n");
            while(1)
			{
				 GetString(string);
			//	gets(string);
				 if(  string[0]=='i' || string[0]=='s' ||string[0]=='c' || string[0]=='d'  )
				 {
					 break;
				 }
				 else
				 {
					 printf("对不起,本软件支持的数据类型为:\n char(字符型) int(整数型) double(浮点型) string(字符串型)\n 不支持该数据类型,请重新输入:\n");
					 continue;
				 }

			}

	     	data.cType=string[0];
			switch (string[0])
			{
			    case 's':
					 printf("请输入数据长度:\n");
		             scanf("%d",&data.nLen);


					 getchar();


					 break;
				case 'c':
					data.nLen=1;
					break;
				case 'i':
					data.nLen=2;
					break;
				case 'd':
					data.nLen=4;
					break;

			}


		    pTable->Head[len++]=data;





	while(len<TABLE_LENTH)
	{


		printf("请输入数据名:\n");

		if(  ERROR == GetStrName(data.strName))
		{
			puts(data.strName);
		   pTable->nLen=len;
		   	printf("成功建立表头!\n");


			return;

		}
		else if( ERROR ==IsRight( pTable , data.strName ) )
		{
			printf("%s已存在,请重命名\n  ",data.strName );
			continue;
		}
		else
		{
		    printf("请输入数据类型:\n");
            while(1)
			{
				 GetString(string);
				 if(  string[0]=='i' || string[0]=='s' ||string[0]=='c' || string[0]=='d'  )
				 {
					 break;
				 }
				 else
				 {
					 printf("不支持该数据类型,请重新输入:\n");
					 continue;
				 }

			}

	     	data.cType=string[0];
			switch (string[0])
			{
			    case 's':
					 printf("请输入数据长度:\n");
		             scanf("%d",&data.nLen);
					 break;
				case 'c':
					data.nLen=1;
					break;
				case 'i':
					data.nLen=2;
					break;
				case 'd':
					data.nLen=4;
					break;

			}


		    pTable->Head[len++]=data;
		}

	}

	pTable->nLen=len;





}






/*
 *  函数功能：打开文件,获取表头

 *  输入参数：表指针,文件名
 *  输出参数：记录所有字段信息的Table指针
 *  返 回 值：无
 */
void ReadTable(struct File *file,char *strFileName)
{
		FILE *pFILE;
		struct Table *pTable=file->pTable;





	if(   ERROR== (pFILE=fopen(strFileName,"rb+")))
	{
		printf("文件%s无法打开!\n",strFileName);
		return;
	}
	else
	{
		fread(pTable, sizeof( struct Table),1,pFILE);
		file->nCount=file->pTable->nCount;
		fclose(pFILE);


		printf("\n成功解读文件%s的表头!\n",strFileName);

	}

}













/*
 *  函数功能：将表存入文件

 *  输入参数：表指针,文件名指针
 *  输出参数：记录所有字段信息的Table指针以及文件名
 *  返 回 值：无
 */

void SaveTable(struct Table *pTable,char *strFileName)
{

	FILE *pFILE;




    	if(!pTable)
	{
		printf("表指针为空,无法保存!\n");
		return;
	}



	if(   ERROR== (   pFILE =  fopen(  strFileName  ,"wb+")  )  )
	{
		printf("文件%s无法打开!\n",strFileName);
		return;
	}
	else
	{
		fwrite(  pTable,   sizeof(  struct Table  ),1,pFILE);
		fclose(pFILE);


		printf("成功在文件%s中保存表头!\n",strFileName);

	}

}


/*
 *  函数功能：显示文件表头

 *  输入参数：表指针
 *  输出参数：无
 *  返 回 值：无
 */
void  ShowTable(struct Table *pTable)
{
	int i;



	if(!pTable)
	{
		printf("表指针为空,无法解读!\n");
		return;
	}
	printf("\n\n本数据文件最大字段数为:%d\n当前字段数为:%d\n各字段信息如下:\n",TABLE_LENTH ,pTable->nLen);
	printf("字段名\t\t字段长度\t\t数据类型\n");


	for(i=0;i<pTable->nLen;i++)
	{
		printf("%s\t\t%d\t\t\t%c\n",pTable->Head[i].strName,pTable->Head[i].nLen,pTable->Head[i].cType);


	}
	printf("\n\n");


}



/*
 *  函数功能：在文件的数据区追加数据
 *  输入参数：表指针pTable,文件名指针strFileName
 *  输出参数：无
 *  返 回 值：无
 */
void SaveData(struct File  file,char *strFileName)
{
	FILE *pFILE;
	struct Table *pTable=file.pTable;

	struct Node *pCur=file.pHead->next;
	int nCount;







	if(!pTable)
	{
		printf("表指针为空,无法解读文件结构!\n");
		return;

	}
	else
	{
		if(   ERROR == ( pFILE = fopen(strFileName,"ab" )  )   )
		{
			printf("文件%s无法打开!\n",strFileName);
			return;
		}
		else
		{
			if(!pCur||!pCur->next)
			{
				printf("文件为空,请确认数据已加载!\n");
				return;
			}

			for(  nCount=0;  nCount<file.nCount   ;nCount++,pCur=pCur->next)
			{
			//	printf("已存储第%d个数据项%c\n",nCount,pCur->arr[0].CHAR);

				fwrite(  pCur->arr,  sizeof(  union Elemtype  )*MAX_DATA_LEN  ,  1  ,  pFILE  );

			}

            printf("已成功将%d个记录保存在文件%s\n",nCount,strFileName);
			fclose(pFILE);

		}

	}





}




/*
 *  函数功能：显示元组内容

 *  输入参数：元组指针arr,文件指针file
 *  输出参数：无
 *  返 回 值：无
 */
void ShowData(  union Elemtype  *arr ,struct File *file )
{
	struct Table table=*(file->pTable);//获取文件表头
	int nLen=file->pTable->nLen;//获取文件字段总数
	int i;
	char type;


	/*按照表头信息逐个显示数据*/
	for(  i=0 ;  i< nLen ; i++ )
	{


		type=table.Head[i].cType;

		/*输出字段名*/
		printf("\n%s:",table.Head[i].strName);



			switch (type)
			{
		                     case 'c':
								 printf("\t%c",arr[i].CHAR);

								 break;
							 case 's':
								 printf("\t%s",arr[i].STRINR);

								  break;
							 case 'd':
								 printf("\t%.2lf",arr[i].DOUBLE);

								  break;
							case 'i':
								printf("\t%d",arr[i].INT);

								  break;



							 default:
								 printf("无法识别的数据类型!\n");




			}


	}
	puts("");






}



/*
 *  函数功能：读取文件数据区

 *  输入参数：表指针pTable,文件名指针strFileName
 *  输出参数：无
 *  返 回 值：无
 */
void ReadData(struct File *file,char *strFileName)
{

		FILE *pFILE;

		char type;
		struct Table t;
		struct Table *pTable=file->pTable;
		struct Node *pCur;
		struct Node data;
		int i,j;







	if(!pTable)
	{
		printf("表指针为空,无法解读文件结构!\n");
		return;

	}


		if(   ERROR == ( pFILE = fopen(strFileName,"rb" )  )   )
		{
			printf("文件%s无法打开!\n",strFileName);
			return;
		}
/*		if(  NULL ==file->pHead->next)
		{
			printf("文件数据区为空!\n");
			return;

		}

*/


 //        printf("正在读取文件%s的数据区\n\n",strFileName);
			fread(&t,sizeof(struct Table),1,pFILE);


			for(  i=0  ;   i<file->pTable->nCount    ;  i++   )
			{





				    pCur = (   struct Node *   )malloc(   sizeof(   struct Node  )   );
					fread(data.arr,sizeof(union Elemtype)*MAX_DATA_LEN,1,pFILE);






//					printf("\n正在读取第%d个元素\n",i+1);

				for(j=0;j<file->pTable->nLen;j++)
				{


					type=pTable->Head[j].cType;




					switch (type)
					{
		                     case 'c':
								 pCur->arr[j].CHAR=data.arr[j].CHAR;
								 printf("%c\n", pCur->arr[j].CHAR);
								 break;
							 case 's':
							//	 pCur->arr[j].STRINR=data.arr[j].STRINR;
							//	 pCur->arr[j].STRINR[19]=0;
							//	  puts(   data.arr[j].STRINR);
								 strcpy(pCur->arr[j].STRINR,data.arr[j].STRINR);
								 puts( pCur->arr[j].STRINR);
								  break;
							 case 'd':
								 pCur->arr[j].DOUBLE=data.arr[j].DOUBLE;
								 printf("%.2lf\n", pCur->arr[j].DOUBLE);
								  break;
							case 'i':
								 pCur->arr[j].INT=data.arr[j].INT;
								 printf("%d\n", pCur->arr[j].INT);
								  break;



							 default:
								 printf("无法识别的数据类型!\n");

					}


				}


 //              printf("已读取第%d个元素\n\n",i+1);
			//	file->nCount++;
				pCur->next=file->pHead->next;
				file->pHead->next=pCur;

			}


            file->nCount=file->pTable->nCount;
            //file->nCount=i;
		//	printf("%d\n",file->nCount);
 //           printf("成功解读文件%s的数据区中的%d个数据\n",strFileName,file->nCount);
			fclose(pFILE);






























}



/*
 *  函数功能：打开已有文件

 *  输入参数:文件指针
 *  输出参数：文件指针
 *  返 回 值：无
 */
void Open(struct File *file)
{



    struct File file2;
	struct Node *pCur;
	char strFileName[MAX_STRING_LENGTH];
	int i;
	printf("请输入文件名:\n");
	 gets(strFileName);
	 strcat(strFileName,".txt");
	 getchar();
	 Read(file,strFileName);
	 SubMenu(file);



//	printf("文件打开成功!\n");

}







/*
 *  函数功能：显示帮助文档

 *  输入参数:无
 *  输出参数：无
 *  返 回 值：无
 */
void Help()
{
//	printf("建设中......\n");
	printf("新建文件按'N'\n打开文件按'O'\n帮助按'H'\n");
}




/*
 *  函数功能：添加数据

 *  输入参数:文件指针
 *  输出参数：无
 *  返 回 值：无
 */
void Add(struct File *file)
{
	AddData(file);

}



/*
 *  函数功能：检索出满足条件的int型数据

 *  输入参数:文件指针,逻辑数组指针,字段序号
 *  输出参数：逻辑数组指针
 *  返 回 值：无
 */
void CheckInt(  struct File *file , int *bIsOK, int nIndex  )
{
	int nLow, nMiddle ,nHigh;
	int i,j,k;
	int bFlag=OK;
	int nCount=file->nCount;
	char  strChoice[20];
	struct Node *pCur=file->pHead->next;


	while( bFlag )
	{
		printf("准确查找('e')\n模糊查找('m')\n");
		gets(strChoice);
		getchar();
		switch (  strChoice[0]  )
		{
		case 'e':
			printf("请输入匹配数据:\n");
			scanf("%d",&nMiddle);
			for(   i=0  ;  (  i  <  nCount  ) && ( pCur )  ;  i++,   pCur = pCur->next  )
			{
				if(   (  (INITSTATUS==bIsOK[i]) && (nMiddle!=pCur->arr[nIndex].INT))
					  ||  (   (OK==bIsOK[i]) &&(nMiddle!=pCur->arr[nIndex].INT) )   )
				{
					bIsOK[i]=ERROR;
				}
				else if(   (INITSTATUS==bIsOK[i])  && (pCur->arr[nIndex].INT==nMiddle)  )
				{
					bIsOK[i]=OK;
				}


			}


			bFlag=ERROR;
			break;
		case 'm':
				printf("请输入待查区间的下限和上限:\n");
			scanf("%d %d",&nLow,&nHigh);
			while(nLow>=nHigh)
			{
                    printf("你输入的参数有误!\n");
					printf("请输入待查区间的下限和上限:\n");
			        scanf("%d %d",&nLow,&nHigh);

			}


			for(   i=0  ;  (  i  <  nCount  ) && ( pCur )  ;  i++,   pCur = pCur->next  )
			{
				if(   (  (INITSTATUS==bIsOK[i]) && ( (pCur->arr[nIndex].INT<nLow)||(pCur->arr[nIndex].INT>nHigh)))
					  ||  (   (OK==bIsOK[i]) &&(  (pCur->arr[nIndex].INT<nLow)  ||  (pCur->arr[nIndex].INT>nHigh) ) )   )
				{
					bIsOK[i] = ERROR;
				}
				else if(   (INITSTATUS==bIsOK[i])  && ( (pCur->arr[nIndex].INT>=nLow)&&(pCur->arr[nIndex].INT<=nHigh))  )
				{
					bIsOK[i] = OK;
				}


			}


				bFlag=ERROR;
			break;
		default:
			printf("无效键!请在输入:\n");
			break;


		}


	}


}




/*
 *  函数功能：检索出满足条件的double型数据

 *  输入参数:文件指针,逻辑数组指针
 *  输出参数：逻辑数组指针
 *  返 回 值：无
 */
void CheckDouble(  struct File *file , int *bIsOK, int nIndex   )
{
		double nLow, nMiddle ,nHigh;
	int i,j,k;
	int bFlag=OK;
	int nCount=file->nCount;
	char  strChoice[20];
	struct Node *pCur=file->pHead->next;


	while( bFlag )
	{
		printf("准确查找('e')\n模糊查找('m')\n");
		gets(strChoice);
		getchar();
		switch (  strChoice[0]  )
		{
		case 'e':
			printf("请输入匹配数据:\n");
			scanf("%lf",&nMiddle);
			for(   i=0  ;  (  i  <  nCount  ) && ( pCur )  ;  i++,   pCur = pCur->next  )
			{
				if(   (  (INITSTATUS==bIsOK[i]) && (nMiddle!=pCur->arr[nIndex].DOUBLE))
					  ||  (   (OK==bIsOK[i]) &&(nMiddle!=pCur->arr[nIndex].DOUBLE) )   )
				{
					bIsOK[i]=ERROR;
				}
				else if(   (INITSTATUS==bIsOK[i])  && (pCur->arr[nIndex].DOUBLE==nMiddle)  )
				{
					bIsOK[i]=OK;
				}


			}


			bFlag=ERROR;
			break;
		case 'm':
				printf("请输入待查区间的下限和上限:\n");
			scanf("%lf %lf",&nLow,&nHigh);
			while(nLow>=nHigh)
			{
                    printf("你输入的参数有误!\n");
					printf("请输入待查区间的下限和上限:\n");
			        scanf("%lf %lf",&nLow,&nHigh);

			}


			for(   i=0  ;  (  i  <  nCount  ) && ( pCur )  ;  i++,   pCur = pCur->next  )
			{
				if(   (  (INITSTATUS==bIsOK[i]) && ( (pCur->arr[nIndex].DOUBLE<nLow)||(pCur->arr[nIndex].DOUBLE>nHigh)))
					  ||  (   (OK==bIsOK[i]) &&(  (pCur->arr[nIndex].DOUBLE<nLow)  ||  (pCur->arr[nIndex].DOUBLE>nHigh) ) )   )
				{
					bIsOK[i] = ERROR;
				}
				else if(   (INITSTATUS==bIsOK[i])  && ( (pCur->arr[nIndex].DOUBLE>=nLow)&&(pCur->arr[nIndex].DOUBLE<=nHigh))  )
				{
					bIsOK[i] = OK;
				}


			}


				bFlag=ERROR;
			break;
		default:
			printf("无效键!请在输入:\n");
			break;


		}


	}






}




/*
 *  函数功能：检索出满足条件的char型数据

 *  输入参数:文件指针,逻辑数组指针
 *  输出参数：逻辑数组指针
 *  返 回 值：无
 */
void CheckChar(  struct File *file , int *bIsOK , int nIndex  )
{
	char nMiddle;
	int i,j,k;
	int bFlag=OK;
	int nCount=file->nCount;
	char  strChoice[20];
	struct Node *pCur=file->pHead->next;



			printf("请输入匹配数据:\n");
			scanf("%c",&nMiddle);
			for(   i=0  ;  (  i  <  nCount  ) && ( pCur )  ;  i++,   pCur = pCur->next  )
			{
				if(   (  (INITSTATUS==bIsOK[i]) && (nMiddle!=pCur->arr[nIndex].CHAR))
					  ||  (   (OK==bIsOK[i]) &&(nMiddle!=pCur->arr[nIndex].CHAR) )   )
				{
					bIsOK[i]=ERROR;
				}
				else if(   (INITSTATUS==bIsOK[i])  && (pCur->arr[nIndex].CHAR==nMiddle)  )
				{
					bIsOK[i]=OK;
				}


			}







}




/*
 *  函数功能：检索出满足条件的string型数据

 *  输入参数:文件指针,逻辑数组指针
 *  输出参数：逻辑数组指针
 *  返 回 值：无
 */
void CheckString(  struct File *file , int *bIsOK , int nIndex  )
{
	char nMiddle[MAX_STRING_LENGTH];
	int i,j,k;
	int bFlag=OK;
	int nCount=file->nCount;
	char  strChoice[20];
	struct Node *pCur=file->pHead->next;



			printf("请输入匹配数据:\n");
			scanf("%s",&nMiddle);
			getchar();
			for(   i=0  ;  (  i  <  nCount  ) && ( pCur )  ;  i++,   pCur = pCur->next  )
			{
				if(   (  (INITSTATUS==bIsOK[i]) && (strcmp(pCur->arr[nIndex].STRINR,nMiddle)))
					  ||  (   (OK==bIsOK[i]) &&(strcmp(pCur->arr[nIndex].STRINR,nMiddle)) )   )
				{
					bIsOK[i]=ERROR;
				}
				else if(   (INITSTATUS==bIsOK[i])  && (!strcmp(pCur->arr[nIndex].STRINR,nMiddle))  )
				{
					bIsOK[i]=OK;
				}


			}




}


/*
 *  函数功能：删除记录

 *  输入参数:数据区指针
 *  输出参数：输出满足条件的数据项
 *  返 回 值：无
 */

void MyDeletData(struct Node *pCur)
{
	struct Node *pNext;
	if(  (!pCur)  || (!pCur->next) )
	{
		printf("指针为空,删除失败!\n");
		return ;
	}
	pNext=pCur->next;
	pCur->next=pNext->next;
	free(pNext);

}





/*
 *  函数功能：组合条件查询显示

 *  输入参数:文件指针
 *  输出参数：输出满足条件的数据项
 *  返 回 值：无
 */
void Find(struct File *file)
{


	struct Table table  =  *(  file->pTable  );//获取文件表头
	struct Node *pCur;


	int i,j,k;
	int nLen=file->pTable->nLen;//  获取字段总数
	int nCount=file->nCount;//  获取数据区数据容量
	int bFlag=OK;
	int *bIsOK;//  记录各数据项是否满足要求:OK表示满足,ERROR表示不满足

	char type;//字段类型
	char strDataName[  MAX_LEN_FILE_NANE  ];
	char strChoice[20];




    bIsOK=(int *)malloc(   sizeof( int )*nCount );//分配空间


	for( i=0; i < nCount;i++)
	{

		bIsOK[i]=INITSTATUS;//初始化各项为不满足
	}


	ShowTable(&table);//显示文件各字段信息

	while(  bFlag )
	{
		printf("请输入需满足条件的字段名:\n");
		gets(strDataName);
	//	getchar();
		if(!strlen(strDataName))
		{
			printf("你确定结束查询?(Y/any key)\n");
			gets(strChoice);

			if('Y'==strChoice[0])
			{
				bFlag=ERROR;
				continue;
			}
		}


		for(  j=0  ;   j < nLen   ;   j++  )
		{
			if(   !strcmp(  table.Head[j].strName,  strDataName ))
			{
				break;
			}


		}
		if(  j >= nLen)
		{
			printf("无此字段名,请再输入\n");
			continue;
		}
		type=table.Head[j].cType;

		switch(type)
		{
		case 'c':
			CheckChar(file,bIsOK,j);getchar();

			break;
		case 's':
			CheckString(file,bIsOK,j);
			break;
		case 'i':
			CheckInt(file,bIsOK,j);
			break;
		case 'd':
			CheckDouble(file,bIsOK,j);
			break;
		default:
			break;
		}


	}
	for(k=0,i=0,pCur=file->pHead->next; pCur &&i<nCount;i++,pCur=pCur->next)
	{
		if(OK==bIsOK[i])
		{
			ShowData(pCur->arr,file);
			k++;
		}

	}
	if( !k)
	{
		printf("对不起,没有满足条件的数据\n");
	}





}

void MyUpdateData(struct Node *pCur,struct File *file)
{
		struct Table table  =  *(  file->pTable  );//获取文件表头
//	struct Node *pCur;


	int i,j,k;
	int nLen=file->pTable->nLen;//  获取字段总数
	int nCount=file->nCount;//  获取数据区数据容量
	int bFlag=OK;
	int *bIsOK;//  记录各数据项是否满足要求:OK表示满足,ERROR表示不满足

	char type;//字段类型
	char strDataName[  MAX_LEN_FILE_NANE  ];
	char strChoice[20];




    bIsOK=(int *)malloc(   sizeof( int )*nCount );//分配空间


	for( i=0; i<nCount;i++)
	{

		bIsOK[i]=INITSTATUS;//初始化各项为不满足
	}


	ShowTable(&table);//显示文件各字段信息

	while(  bFlag )
	{
		printf("请输入需满足更新的字段名:\n");
		gets(strDataName);
	//	getchar();
		if(!strlen(strDataName))
		{
			printf("你确定结束更新?(Y/any key)\n");
			gets(strChoice);

			if('Y'==strChoice[0])
			{
				bFlag=ERROR;
				continue;
			}
		}


		for(  j=0  ;   j < nLen   ;   j++  )
		{
			if(   !strcmp(  table.Head[j].strName,  strDataName ))
			{
				break;
			}


		}
		if(  j >= nLen)
		{
			printf("无此字段名,请在输入\n");
			continue;
		}
		type=table.Head[j].cType;
		printf("请输入更新内容:\n");

		switch(type)
		{
		case 'c':
			printf("请输入更新内容:\n");
			scanf("%c",&(pCur->arr[j].CHAR));
			break;
		case 's':
			scanf("%s",pCur->arr[j].STRINR);


			break;
		case 'i':
			scanf("%d",&(pCur->arr[j].INT));

			break;
		case 'd':
			scanf("%lf",&(pCur->arr[j].DOUBLE));

			break;
		default:
			break;
		}


	}
/*	for(i=0,pCur=file->pHead->next; pCur &&i<nCount;i++,pCur=pCur->next)
	{
		if(OK==bIsOK[i])
		{
			ShowData(pCur->arr,file);
		}

	}

*/

}



/*
 *  函数功能：更新数据

 *  输入参数:文件指针
 *  输出参数：无
 *  返 回 值：无
 */
void Update( struct File *file)
{
//		printf("建设中......\n");
		struct Table table  =  *(  file->pTable  );//获取文件表头
	struct Node *pCur;


	int i,j,k;
	int nLen=file->pTable->nLen;//  获取字段总数
	int nCount=file->nCount;//  获取数据区数据容量
	int bFlag=OK;
	int *bIsOK;//  记录各数据项是否满足要求:OK表示满足,ERROR表示不满足

	char type;//字段类型
	char strDataName[  MAX_LEN_FILE_NANE  ];
	char strChoice[20];




    bIsOK=(int *)malloc(   sizeof( int )*nCount );//分配空间


	for( i=0; i<nCount;i++)
	{

		bIsOK[i]=INITSTATUS;//初始化各项为不满足
	}


	ShowTable(&table);//显示文件各字段信息

	while(  bFlag )
	{
		printf("请输入需满足条件的字段名:\n");
		gets(strDataName);
	//	getchar();
		if(!strlen(strDataName))
		{
			printf("你确定结束更新记录前筛选?(Y/any key)\n");
			gets(strChoice);

			if('Y'==strChoice[0])
			{
				bFlag=ERROR;
				continue;
			}
		}


		for(  j=0  ;   j < nLen   ;   j++  )
		{
			if(   !strcmp(  table.Head[j].strName,  strDataName ))
			{
				break;
			}


		}
		if(  j >= nLen)
		{
			printf("无此字段名,请在输入\n");
			continue;
		}
		type=table.Head[j].cType;

		switch(type)
		{
		case 'c':
			CheckChar(file,bIsOK,j);
			break;
		case 's':
			CheckString(file,bIsOK,j);
			break;
		case 'i':
			CheckInt(file,bIsOK,j);
			break;
		case 'd':
			CheckDouble(file,bIsOK,j);
			break;
		default:
			break;
		}


	}



	for(i=0,k=0,pCur=file->pHead->next; pCur &&i<nCount;i++,pCur=pCur->next)
	{
		if(OK==bIsOK[i])
		{
			ShowData(pCur->arr,file);
			MyUpdateData(pCur,file);
		}

	}
	if(!k)
	{
		printf("没有满足要求的数据:\n");
		return;
	}
	printf("数据更新成功\n");







}



/*
 *  函数功能：删除数据

 *  输入参数:文件指针
 *  输出参数：无
 *  返 回 值：无
 */

void Delete(struct File *file)
{
//		printf("建设中......\n");
		struct Table table  =  *(  file->pTable  );//获取文件表头
	struct Node *pCur;


	int i,j,k;
	int nLen=file->pTable->nLen;//  获取字段总数
	int nCount=file->nCount;//  获取数据区数据容量
	int bFlag=OK;
	int *bIsOK;//  记录各数据项是否满足要求:OK表示满足,ERROR表示不满足

	char type;//字段类型
	char strDataName[  MAX_LEN_FILE_NANE  ];
	char strChoice[20];




    bIsOK=(int *)malloc(   sizeof( int )*nCount );//分配空间


	for( i=0; i<nCount;i++)
	{

		bIsOK[i]=INITSTATUS;//初始化各项为不满足
	}


	ShowTable(&table);//显示文件各字段信息

	while(  bFlag )
	{
		printf("请输入需满足条件的字段名:\n");
		gets(strDataName);
	//	getchar();
		if(!strlen(strDataName))
		{
			printf("你确定结束查询?(Y/any key)\n");
			gets(strChoice);

			if('Y'==strChoice[0])
			{
				bFlag=ERROR;
				continue;
			}
		}


		for(  j=0  ;   j < nLen   ;   j++  )
		{
			if(   !strcmp(  table.Head[j].strName,  strDataName ))
			{
				break;
			}


		}
		if(  j >= nLen)
		{
			printf("无此字段名,请在输入\n");
			continue;
		}
		type=table.Head[j].cType;

		switch(type)
		{
		case 'c':
			CheckChar(file,bIsOK,j);
			break;
		case 's':
			CheckString(file,bIsOK,j);
			break;
		case 'i':
			CheckInt(file,bIsOK,j);
			break;
		case 'd':
			CheckDouble(file,bIsOK,j);
			break;
		default:
			break;
		}


	}
	for(i=0,k,pCur=file->pHead; pCur->next &&i<nCount;i++,pCur=pCur->next)
	{
		if(OK==bIsOK[i])
		{
			printf("正在删除下数据:\n");
			ShowData(pCur->next->arr,file);
			MyDeletData(pCur);
			printf("删除完毕\n");

		}

	}

	file->nCount-=k;
	file->pTable->nCount-=k;
	if( !k)
	{
		printf("对不起,没有满足条件的数据\n");
	}





}



/*
 *  函数功能：新建文件

 *  输入参数:文件指针
 *  输出参数：文件指针
 *  返 回 值：无
 */
void New(struct File *file)
{
	char strFileName[MAX_LEN_FILE_NANE]="NONAME.txt";


//	puts(strFileName);
	printf("\n请输入新建数据库的各字段信息:\n");

	CreateTable(file->pTable);

	SubMenu(file);


//	printf("文件新建成功!\n");



}










void GetChar(char *pChar)

{
	char ch;
	while(  ch=='\n'|| ch=='?')
	{
		scanf("%c",&ch);
	}
	*pChar=ch;

}



/*
 *  函数功能: 追加记录

 *  输入参数:文件指针
 *  输出参数：无
 *  返 回 值：无
 */
void AddData(struct File *file)
{




	struct Table table=*(file->pTable);
	struct Node *pCur;
	int i;
	int nCount=0;



	char strChoice[20];

	char type;

	int nLen=file->pTable->nLen;







	printf("\n\n文件共有%d个字段\n\n",nLen);


	if(  (!file) || (!file->pHead)  )
	{
		printf("文件加载数据失败,请确认文件是否受损!\n");
		return;
	}



/*
				printf("请依次输入数据:\n");
				pCur=(struct Node *)malloc(  sizeof(struct Node)  );
				for(    i=0;   i<nLen   ;i++   )
				{


					printf("请输入%s:\n",table.Head[i].strName);
				//	getchar();
					type=table.Head[i].cType;
					switch (type)
					{

					case 'c':

					//	getchar();
						scanf(   "%c",   &((  pCur->arr[i]).CHAR));
							getchar();


					//	printf("\n已添加数据项:%c\n",pCur->arr[i].CHAR);


						break;

							 case 's':
								 GetString(pCur->arr[i].STRINR);

								  break;
							 case 'd':
								 	scanf(   "%d",   &((  pCur->arr[i]).DOUBLE));


								  break;
							case 'i':
									scanf(   "%d",   &((  pCur->arr[i]).INT));

								  break;



							 default:
								 printf("无法识别的数据类型!\n");

					}
				}
				pCur->next=file->pHead->next;
				file->pHead->next=pCur;
					file->nCount++;




*/
		while(1)
		{



			printf("添加数据('a')\n退出(any key)\n");
		  // GetString(strChoice);
			gets(strChoice);
			//	getchar();

			if( 'a' != strChoice[0] )
			{

				 printf("\n已成功添加%d个数据\n\n",nCount);
                	file->pTable->nCount=file->nCount;
					return ;



			}

					pCur=   ( struct Node * )malloc(  sizeof(  struct Node  )  );

				printf("请依次输入数据:\n");
				for(i=0;i<nLen;i++)
				{

					printf("请输入%s:\n",table.Head[i].strName);






					type=table.Head[i].cType;
				//	getchar();
					switch (type)
					{
							case 'c':

					/*	 while(  '\n' != (  ch=getchar()))
						 {

						 }
						 */
						scanf(   "%s",   strChoice);
							//	GetChar(&(pCur->arr[i].CHAR));
						pCur->arr[i].CHAR=strChoice[0];
						//	printf("\n已添加数据项:%c\n",pCur->arr[i].CHAR);
						getchar();
						break;
						// pCur->arr[i].CHAR=ch;

							 case 's':
								 GetString(pCur->arr[i].STRINR);

							//	 gets(pCur->arr[i].STRINR);






							//	 puts(pCur->arr[i].STRINR);
							//	  getchar();



								  break;
							 case 'd':
								 	scanf(   "%lf",   &((  pCur->arr[i]).DOUBLE));
										printf("\n已添加数据项:%.2lf\n",pCur->arr[i].DOUBLE);

									getchar();


								  break;
							case 'i':
									scanf(   "%d",   &((  pCur->arr[i]).INT));
								//		printf("\n已添加数据项:%d\n",pCur->arr[i].INT);
										getchar();

								  break;



							 default:
								 printf("无法识别的数据类型!\n");


					}

				}







				pCur->next=file->pHead->next;
				file->pHead->next=pCur;
				file->nCount++;
				nCount++;







			}
















}







/*
 *  函数功能：从文件中读取数据,并存入文件结构体中

 *  输入参数: 文件指针,文件名
 *  输出参数：文件指针
 *  返 回 值：无
 */
void Read(struct File  *file,char *strFileName)
{


//	printf("\n正在解读文件%s的数据\n",strFileName);

    /*读取文件表头*/
	ReadTable(file,strFileName);

	ShowTable(file->pTable);

	/*读取文件数据区*/
	ReadData(file,strFileName);



//	printf("\n成功解读文件%s\n",strFileName);


}


/*
 *  函数功能：释放文件结构体的空间

 *  输入参数:文件指针
 *  输出参数：无
 *  返 回 值：无
 */
void DelteFile(  struct File *file )
{

	free(file);

}



/*
 *  函数功能:在文件中储存数据

 *  输入参数: 文件指针,文件名
 *  输出参数：文件指针
 *  返 回 值：无
 */
void Save(struct File  file,char *strFileName)
{


	printf("\n\n正在储存数据\n\n");



    /*存储文件表头*/
	SaveTable(file.pTable,strFileName);


	/*存储文件数据区*/
	SaveData(file,strFileName);



	printf("\n\n已储存数据\n\n");



}


/*
 *  函数功能：显示子菜单

 *  输入参数:文件指针
 *  输出参数：无
 *  返 回 值：无
 */
void SubMenu(struct File *file)
{


	char strChoice[20];
	char strFileName[MAX_LEN_FILE_NANE];
	int flag =OK;
	int isSave=ERROR;




	while(  flag )
	{
		printf("追加('a')\n");
		printf("查询('f')\n");
		printf("更新('u')\n");
		printf("删除('d')\n");
		printf("保存('s')\n");
		printf("退出(any key)\n");
		gets(strChoice);
		switch (strChoice[0])
		{
		case 'a':
			Add(file);
			break;
		case 'f':
			Find(file);
			break;
		case 'u':
			Update(file);
			break;
		case 'd':
			Delete(file);
			break;
		case 's':
				printf("请输入文件名\n");
	        gets(strFileName);
	       strcat(strFileName,".txt");
	        getchar();
			Save(*file,strFileName);
			isSave=OK;
			break;
		default:

			printf("你真的退出子菜单?('Y'/any key)");


					GetString(strChoice);



					if('Y'==strChoice[0])
					{

							flag=ERROR;
							if(!isSave)
							{


								     printf("你尚未存盘\n");
									 printf("请输入文件名\n");
	                                   gets(strFileName);
	                                  strcat(strFileName,".txt");
	                                  getchar();
			                         Save(*file,strFileName);

							}


					      break;

					}
					else
					{
						continue;
					}

		}
	}


}


void SetSystem()
{
	int nFlag =1;
//  SUPER_MARKET_MODEL 超市模式
//  OFFICE_MODEL 办公模式
	char ch[20];
	printf("\n 本系统的存储模式:\n 超市模式\t 适合于频繁添加,删除记录的场合\n 办公模式\t 适合于排序查询频繁的场合\n当前模式为:");
	if ( SUPER_MARKET_MODEL ==  nModel )
	{
		printf("超市模式\n");

	}
	else
	{
		printf("办公模式\n");
	}
	printf("请选择模式:\n 超市模式('S ')\n办公模式('O')\n 其他键退出\n ");
	while(  nFlag )
	{
	//	scanf("%c",&ch);
		gets(ch);
	//	printf("%c\n",ch[0]);
		//	getchar();

		switch (ch[0])
		{
		case 'S':
		case 's':
			nModel=SUPER_MARKET_MODEL;
			printf("你选择了超市模式\n ");
			nFlag=0;

			break;
		case 'O':
		case 'o':
			nModel= OFFICE_MODEL;
			printf ("你选择了办公模式\n ");
			nFlag=0;
			break;
		default :
			nFlag=0;





		}
	//	getchar();
	}


}




/*
 *  函数功能：显示菜单,进入消息循环

 *  输入参数:无
 *  输出参数：无
 *  返 回 值：无
 */
void MainMenu()
{
	char strChoice[20];
	int flag=OK;
	struct File file;
	InitFile(&file);

		printf("欢迎使用LiuDataBase通用数据库软件\n\n\n");
		printf("Copyright (c) 2006,华中科技大学Dian团队\n");
		printf("All rights reserved.\n\n");
		printf("文件名称：LiuDataBase\n");
		printf("摘    要：模拟交互式的SOL的基本功能:动态建表,组合条件查询\n");
		printf("          支持的数据类型为:char(字符型)int(整数型)double(浮点型)string(字符串型)\n");
//		printf("          double(浮点型) string(字符串型)\n");
		printf("当前版本：清级\n");
		printf("作    者：电信0401 刘焱\n\n\n");



		while( flag )
		{

			printf("\t主菜单\n");
			printf("打开('O')\n");
			printf("新建('N')\n");
			printf("帮助('H')\n");

			printf("设置('S')\n");
			printf("退出('Q')\n");
				GetString(strChoice);
				switch (strChoice[0])
				{
				case 'O':
				case 'o':
						Open(&file);
						continue;
				case  'N':
				case 'n':
					    New(&file);
					    continue;
				case 'H':
				case 'h':
					Help();
					continue;
				case 'S':
				case	's':
					SetSystem();
					continue;
				case  'Q':
				case 'q':
					printf("你真的退出主菜单?('Y'/any key)");
					GetString(strChoice);
					if('Y'==strChoice[0])
					{

							flag=ERROR;
					      break;

					}
					else
					{
						continue;
					}




				default:
					printf("你按了无效键,建议使用帮助('H')\n");
					continue;




				}


		}

}












/*
 *  函数功能：驱动程序,检测个函数的功能以及接口

 *  输入参数：无
 *  输出参数：无
 *  返 回 值：无
 */
void Driver()
{




	  struct Node *pCur;
	  struct File file1,file2;
	  int i;
	  InitFile(  &file1  );
	  CreateTable(file1.pTable);
	  ShowTable(file1.pTable);
//	  AddData(  &file1  );

//	  Save(  file1,  "data.txt"  );

//  InitFile(&file2);

 //   Read(&file2,"hudie.txt");

//	 for(      i=0  ,  pCur=file2.pHead->next  ;   i <file2.nCount ;  pCur=pCur->next ,i++)
//	 {
//		 ShowData(pCur->arr,&file2);

//	 }







}
void main()
{
//	Driver();
	MainMenu();
	getchar();
}












































