
/*ͷ�ļ�����*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>





/***************************************************************************************************************/






/*�궨�岿��*/


#define TABLE_LENTH 20   //�����ĳ���
#define MAX_DATA_LEN 20  //��������ֶ���
#define MAX_NAME_LENTH 20  //�����ֶ�������󳤶�
#define MAX_LEN_FILE_NANE 127  //�����ļ�������󳤶�
#define MAX_STRING_LENGTH 127 //�����ַ�������󳤶�
#define OK 1    //�����ɹ�
#define ERROR 0   //����ʧ��
#define INITSTATUS -1 //��ʼ״̬
#define  SUPER_MARKET_MODEL 0//����ģʽ
#define  OFFICE_MODEL 1//�칫ģʽ


int  nModel=SUPER_MARKET_MODEL;//Ψһ��ȫ�ֱ���,��¼ϵͳģʽ









/***************************************************************************************************************/


/*���ݽṹ���岿��*/



//����Ԫ������
union Elemtype
{
	char CHAR;   //�ַ���
	char STRINR[MAX_STRING_LENGTH];  //�ַ�����
	int INT;//������
	double DOUBLE;//������

};




//����Ԫ�ؽڵ�����
struct Node
{
	union Elemtype arr[MAX_DATA_LEN];
	struct Node *next;

};




//�ֶλ�����Ϣ�ṹ��
struct Data
{
	char strName[MAX_NAME_LENTH];  //�ֶ���
	int nLen;  //�ֶγ���
	char cType; //�ֶ�����
};





//��¼�ֶλ�����Ϣ�Ľڵ�ṹ��
struct DataNode
{
	struct Data data;//�ֶλ�����Ϣ�ṹ��
	struct DataNode *pNext;//ָ��

};





//��¼�����ֶ���Ϣ�ı�ṹ��
struct Table
{
	int nLen;//��ĳ���
	struct Data Head[MAX_NAME_LENTH];//��¼�ֶ�ȫ����Ϣ������


	int nCount;//��¼��������
};




//�����ļ��ṹ
struct File
{
	struct Table *pTable;//��ͷָ��
	struct Node *pHead;//������ָ��
	int    nCount;//����������
};





/***************************************************************************************************************/




/*�������岿��*/



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
 *  �������ܣ���ȡ�ֶ�����,�������쳣

 *  ����������ֶ���ָ��str
 *  ����������ֶ���ָ��str
 *  �� �� ֵ����
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
		printf("���벻��Ϊ��\n��������һ��\n");

	}

}






/*
 *  �������ܣ���ʼ���ļ�,Ϊ��ͷ,����������ռ�,�����������

 *  �������:�ļ�ָ��
 *  �����������
 *  �� �� ֵ����
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
 *  �������ܣ���ȡ�ֶ���,�������쳣

 *  ����������ֶ���ָ��str
 *  ����������ֶ���ָ��str
 *  �� �� ֵ��״̬ 1 ��ʾ����ɹ��������ֶε�����  ״̬ 0  �˳��ֶ�����
 */


int GetStrName(char *str)
{
	char strChoice[20];
	char ch;


	while(1)
	{


		/*���ջس���*/
	//    ch=getchar();

		/*��ȡ�ַ���*/
		gets(str);



		if(  strlen( str ) )
		{

		/*�����ַ����ǿ��򷵻�*/

			return OK;
		}
/*		else if( ERROR==IsRight(str) )
		{
			printf("%s�Ѵ���,��������:\n ");
			continue ;

		}*/
		else
		{

			/*
			�����ַ���Ϊ�����˻�����,
			�ж�������������˳�����
			*/
			printf("�˳�����?(Y/any key)");
			gets(strChoice);
			if('Y'==strChoice[0])
			{
				return ERROR;
			}
			else
			{
				printf("������������:\n");
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
 *  �������ܣ�����������Ϣ

 *  �����������ָ��
 *  �����������¼�����ֶ���Ϣ��Tableָ��
 *  �� �� ֵ����
 */

void CreateTable(struct Table *pTable)
{
	int len=0;
	char string[20];
	char strChoice[20];
	struct Data data;





	printf("������������:\n");
	gets(data.strName);


//	puts(data.strName);



	if(!strlen(data.strName))
	{
			printf("�˳�����?(Y/any key)");
			gets(strChoice);
			if('Y'==strChoice[0])
			{
				pTable->nLen=0;
				return ;
			}
			else
			{
				printf("������������:\n");
				gets(data.strName);




	puts(data.strName);




			}

	}

           printf("��������������:\n");
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
					 printf("�Բ���,�����֧�ֵ���������Ϊ:\n char(�ַ���) int(������) double(������) string(�ַ�����)\n ��֧�ָ���������,����������:\n");
					 continue;
				 }

			}

	     	data.cType=string[0];
			switch (string[0])
			{
			    case 's':
					 printf("���������ݳ���:\n");
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


		printf("������������:\n");

		if(  ERROR == GetStrName(data.strName))
		{
			puts(data.strName);
		   pTable->nLen=len;
		   	printf("�ɹ�������ͷ!\n");


			return;

		}
		else if( ERROR ==IsRight( pTable , data.strName ) )
		{
			printf("%s�Ѵ���,��������\n  ",data.strName );
			continue;
		}
		else
		{
		    printf("��������������:\n");
            while(1)
			{
				 GetString(string);
				 if(  string[0]=='i' || string[0]=='s' ||string[0]=='c' || string[0]=='d'  )
				 {
					 break;
				 }
				 else
				 {
					 printf("��֧�ָ���������,����������:\n");
					 continue;
				 }

			}

	     	data.cType=string[0];
			switch (string[0])
			{
			    case 's':
					 printf("���������ݳ���:\n");
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
 *  �������ܣ����ļ�,��ȡ��ͷ

 *  �����������ָ��,�ļ���
 *  �����������¼�����ֶ���Ϣ��Tableָ��
 *  �� �� ֵ����
 */
void ReadTable(struct File *file,char *strFileName)
{
		FILE *pFILE;
		struct Table *pTable=file->pTable;





	if(   ERROR== (pFILE=fopen(strFileName,"rb+")))
	{
		printf("�ļ�%s�޷���!\n",strFileName);
		return;
	}
	else
	{
		fread(pTable, sizeof( struct Table),1,pFILE);
		file->nCount=file->pTable->nCount;
		fclose(pFILE);


		printf("\n�ɹ�����ļ�%s�ı�ͷ!\n",strFileName);

	}

}













/*
 *  �������ܣ���������ļ�

 *  �����������ָ��,�ļ���ָ��
 *  �����������¼�����ֶ���Ϣ��Tableָ���Լ��ļ���
 *  �� �� ֵ����
 */

void SaveTable(struct Table *pTable,char *strFileName)
{

	FILE *pFILE;




    	if(!pTable)
	{
		printf("��ָ��Ϊ��,�޷�����!\n");
		return;
	}



	if(   ERROR== (   pFILE =  fopen(  strFileName  ,"wb+")  )  )
	{
		printf("�ļ�%s�޷���!\n",strFileName);
		return;
	}
	else
	{
		fwrite(  pTable,   sizeof(  struct Table  ),1,pFILE);
		fclose(pFILE);


		printf("�ɹ����ļ�%s�б����ͷ!\n",strFileName);

	}

}


/*
 *  �������ܣ���ʾ�ļ���ͷ

 *  �����������ָ��
 *  �����������
 *  �� �� ֵ����
 */
void  ShowTable(struct Table *pTable)
{
	int i;



	if(!pTable)
	{
		printf("��ָ��Ϊ��,�޷����!\n");
		return;
	}
	printf("\n\n�������ļ�����ֶ���Ϊ:%d\n��ǰ�ֶ���Ϊ:%d\n���ֶ���Ϣ����:\n",TABLE_LENTH ,pTable->nLen);
	printf("�ֶ���\t\t�ֶγ���\t\t��������\n");


	for(i=0;i<pTable->nLen;i++)
	{
		printf("%s\t\t%d\t\t\t%c\n",pTable->Head[i].strName,pTable->Head[i].nLen,pTable->Head[i].cType);


	}
	printf("\n\n");


}



/*
 *  �������ܣ����ļ���������׷������
 *  �����������ָ��pTable,�ļ���ָ��strFileName
 *  �����������
 *  �� �� ֵ����
 */
void SaveData(struct File  file,char *strFileName)
{
	FILE *pFILE;
	struct Table *pTable=file.pTable;

	struct Node *pCur=file.pHead->next;
	int nCount;







	if(!pTable)
	{
		printf("��ָ��Ϊ��,�޷�����ļ��ṹ!\n");
		return;

	}
	else
	{
		if(   ERROR == ( pFILE = fopen(strFileName,"ab" )  )   )
		{
			printf("�ļ�%s�޷���!\n",strFileName);
			return;
		}
		else
		{
			if(!pCur||!pCur->next)
			{
				printf("�ļ�Ϊ��,��ȷ�������Ѽ���!\n");
				return;
			}

			for(  nCount=0;  nCount<file.nCount   ;nCount++,pCur=pCur->next)
			{
			//	printf("�Ѵ洢��%d��������%c\n",nCount,pCur->arr[0].CHAR);

				fwrite(  pCur->arr,  sizeof(  union Elemtype  )*MAX_DATA_LEN  ,  1  ,  pFILE  );

			}

            printf("�ѳɹ���%d����¼�������ļ�%s\n",nCount,strFileName);
			fclose(pFILE);

		}

	}





}




/*
 *  �������ܣ���ʾԪ������

 *  ���������Ԫ��ָ��arr,�ļ�ָ��file
 *  �����������
 *  �� �� ֵ����
 */
void ShowData(  union Elemtype  *arr ,struct File *file )
{
	struct Table table=*(file->pTable);//��ȡ�ļ���ͷ
	int nLen=file->pTable->nLen;//��ȡ�ļ��ֶ�����
	int i;
	char type;


	/*���ձ�ͷ��Ϣ�����ʾ����*/
	for(  i=0 ;  i< nLen ; i++ )
	{


		type=table.Head[i].cType;

		/*����ֶ���*/
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
								 printf("�޷�ʶ�����������!\n");




			}


	}
	puts("");






}



/*
 *  �������ܣ���ȡ�ļ�������

 *  �����������ָ��pTable,�ļ���ָ��strFileName
 *  �����������
 *  �� �� ֵ����
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
		printf("��ָ��Ϊ��,�޷�����ļ��ṹ!\n");
		return;

	}


		if(   ERROR == ( pFILE = fopen(strFileName,"rb" )  )   )
		{
			printf("�ļ�%s�޷���!\n",strFileName);
			return;
		}
/*		if(  NULL ==file->pHead->next)
		{
			printf("�ļ�������Ϊ��!\n");
			return;

		}

*/


 //        printf("���ڶ�ȡ�ļ�%s��������\n\n",strFileName);
			fread(&t,sizeof(struct Table),1,pFILE);


			for(  i=0  ;   i<file->pTable->nCount    ;  i++   )
			{





				    pCur = (   struct Node *   )malloc(   sizeof(   struct Node  )   );
					fread(data.arr,sizeof(union Elemtype)*MAX_DATA_LEN,1,pFILE);






//					printf("\n���ڶ�ȡ��%d��Ԫ��\n",i+1);

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
								 printf("�޷�ʶ�����������!\n");

					}


				}


 //              printf("�Ѷ�ȡ��%d��Ԫ��\n\n",i+1);
			//	file->nCount++;
				pCur->next=file->pHead->next;
				file->pHead->next=pCur;

			}


            file->nCount=file->pTable->nCount;
            //file->nCount=i;
		//	printf("%d\n",file->nCount);
 //           printf("�ɹ�����ļ�%s���������е�%d������\n",strFileName,file->nCount);
			fclose(pFILE);






























}



/*
 *  �������ܣ��������ļ�

 *  �������:�ļ�ָ��
 *  ����������ļ�ָ��
 *  �� �� ֵ����
 */
void Open(struct File *file)
{



    struct File file2;
	struct Node *pCur;
	char strFileName[MAX_STRING_LENGTH];
	int i;
	printf("�������ļ���:\n");
	 gets(strFileName);
	 strcat(strFileName,".txt");
	 getchar();
	 Read(file,strFileName);
	 SubMenu(file);



//	printf("�ļ��򿪳ɹ�!\n");

}







/*
 *  �������ܣ���ʾ�����ĵ�

 *  �������:��
 *  �����������
 *  �� �� ֵ����
 */
void Help()
{
//	printf("������......\n");
	printf("�½��ļ���'N'\n���ļ���'O'\n������'H'\n");
}




/*
 *  �������ܣ��������

 *  �������:�ļ�ָ��
 *  �����������
 *  �� �� ֵ����
 */
void Add(struct File *file)
{
	AddData(file);

}



/*
 *  �������ܣ�����������������int������

 *  �������:�ļ�ָ��,�߼�����ָ��,�ֶ����
 *  ����������߼�����ָ��
 *  �� �� ֵ����
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
		printf("׼ȷ����('e')\nģ������('m')\n");
		gets(strChoice);
		getchar();
		switch (  strChoice[0]  )
		{
		case 'e':
			printf("������ƥ������:\n");
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
				printf("�����������������޺�����:\n");
			scanf("%d %d",&nLow,&nHigh);
			while(nLow>=nHigh)
			{
                    printf("������Ĳ�������!\n");
					printf("�����������������޺�����:\n");
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
			printf("��Ч��!��������:\n");
			break;


		}


	}


}




/*
 *  �������ܣ�����������������double������

 *  �������:�ļ�ָ��,�߼�����ָ��
 *  ����������߼�����ָ��
 *  �� �� ֵ����
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
		printf("׼ȷ����('e')\nģ������('m')\n");
		gets(strChoice);
		getchar();
		switch (  strChoice[0]  )
		{
		case 'e':
			printf("������ƥ������:\n");
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
				printf("�����������������޺�����:\n");
			scanf("%lf %lf",&nLow,&nHigh);
			while(nLow>=nHigh)
			{
                    printf("������Ĳ�������!\n");
					printf("�����������������޺�����:\n");
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
			printf("��Ч��!��������:\n");
			break;


		}


	}






}




/*
 *  �������ܣ�����������������char������

 *  �������:�ļ�ָ��,�߼�����ָ��
 *  ����������߼�����ָ��
 *  �� �� ֵ����
 */
void CheckChar(  struct File *file , int *bIsOK , int nIndex  )
{
	char nMiddle;
	int i,j,k;
	int bFlag=OK;
	int nCount=file->nCount;
	char  strChoice[20];
	struct Node *pCur=file->pHead->next;



			printf("������ƥ������:\n");
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
 *  �������ܣ�����������������string������

 *  �������:�ļ�ָ��,�߼�����ָ��
 *  ����������߼�����ָ��
 *  �� �� ֵ����
 */
void CheckString(  struct File *file , int *bIsOK , int nIndex  )
{
	char nMiddle[MAX_STRING_LENGTH];
	int i,j,k;
	int bFlag=OK;
	int nCount=file->nCount;
	char  strChoice[20];
	struct Node *pCur=file->pHead->next;



			printf("������ƥ������:\n");
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
 *  �������ܣ�ɾ����¼

 *  �������:������ָ��
 *  ����������������������������
 *  �� �� ֵ����
 */

void MyDeletData(struct Node *pCur)
{
	struct Node *pNext;
	if(  (!pCur)  || (!pCur->next) )
	{
		printf("ָ��Ϊ��,ɾ��ʧ��!\n");
		return ;
	}
	pNext=pCur->next;
	pCur->next=pNext->next;
	free(pNext);

}





/*
 *  �������ܣ����������ѯ��ʾ

 *  �������:�ļ�ָ��
 *  ����������������������������
 *  �� �� ֵ����
 */
void Find(struct File *file)
{


	struct Table table  =  *(  file->pTable  );//��ȡ�ļ���ͷ
	struct Node *pCur;


	int i,j,k;
	int nLen=file->pTable->nLen;//  ��ȡ�ֶ�����
	int nCount=file->nCount;//  ��ȡ��������������
	int bFlag=OK;
	int *bIsOK;//  ��¼���������Ƿ�����Ҫ��:OK��ʾ����,ERROR��ʾ������

	char type;//�ֶ�����
	char strDataName[  MAX_LEN_FILE_NANE  ];
	char strChoice[20];




    bIsOK=(int *)malloc(   sizeof( int )*nCount );//����ռ�


	for( i=0; i < nCount;i++)
	{

		bIsOK[i]=INITSTATUS;//��ʼ������Ϊ������
	}


	ShowTable(&table);//��ʾ�ļ����ֶ���Ϣ

	while(  bFlag )
	{
		printf("�������������������ֶ���:\n");
		gets(strDataName);
	//	getchar();
		if(!strlen(strDataName))
		{
			printf("��ȷ��������ѯ?(Y/any key)\n");
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
			printf("�޴��ֶ���,��������\n");
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
		printf("�Բ���,û����������������\n");
	}





}

void MyUpdateData(struct Node *pCur,struct File *file)
{
		struct Table table  =  *(  file->pTable  );//��ȡ�ļ���ͷ
//	struct Node *pCur;


	int i,j,k;
	int nLen=file->pTable->nLen;//  ��ȡ�ֶ�����
	int nCount=file->nCount;//  ��ȡ��������������
	int bFlag=OK;
	int *bIsOK;//  ��¼���������Ƿ�����Ҫ��:OK��ʾ����,ERROR��ʾ������

	char type;//�ֶ�����
	char strDataName[  MAX_LEN_FILE_NANE  ];
	char strChoice[20];




    bIsOK=(int *)malloc(   sizeof( int )*nCount );//����ռ�


	for( i=0; i<nCount;i++)
	{

		bIsOK[i]=INITSTATUS;//��ʼ������Ϊ������
	}


	ShowTable(&table);//��ʾ�ļ����ֶ���Ϣ

	while(  bFlag )
	{
		printf("��������������µ��ֶ���:\n");
		gets(strDataName);
	//	getchar();
		if(!strlen(strDataName))
		{
			printf("��ȷ����������?(Y/any key)\n");
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
			printf("�޴��ֶ���,��������\n");
			continue;
		}
		type=table.Head[j].cType;
		printf("�������������:\n");

		switch(type)
		{
		case 'c':
			printf("�������������:\n");
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
 *  �������ܣ���������

 *  �������:�ļ�ָ��
 *  �����������
 *  �� �� ֵ����
 */
void Update( struct File *file)
{
//		printf("������......\n");
		struct Table table  =  *(  file->pTable  );//��ȡ�ļ���ͷ
	struct Node *pCur;


	int i,j,k;
	int nLen=file->pTable->nLen;//  ��ȡ�ֶ�����
	int nCount=file->nCount;//  ��ȡ��������������
	int bFlag=OK;
	int *bIsOK;//  ��¼���������Ƿ�����Ҫ��:OK��ʾ����,ERROR��ʾ������

	char type;//�ֶ�����
	char strDataName[  MAX_LEN_FILE_NANE  ];
	char strChoice[20];




    bIsOK=(int *)malloc(   sizeof( int )*nCount );//����ռ�


	for( i=0; i<nCount;i++)
	{

		bIsOK[i]=INITSTATUS;//��ʼ������Ϊ������
	}


	ShowTable(&table);//��ʾ�ļ����ֶ���Ϣ

	while(  bFlag )
	{
		printf("�������������������ֶ���:\n");
		gets(strDataName);
	//	getchar();
		if(!strlen(strDataName))
		{
			printf("��ȷ���������¼�¼ǰɸѡ?(Y/any key)\n");
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
			printf("�޴��ֶ���,��������\n");
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
		printf("û������Ҫ�������:\n");
		return;
	}
	printf("���ݸ��³ɹ�\n");







}



/*
 *  �������ܣ�ɾ������

 *  �������:�ļ�ָ��
 *  �����������
 *  �� �� ֵ����
 */

void Delete(struct File *file)
{
//		printf("������......\n");
		struct Table table  =  *(  file->pTable  );//��ȡ�ļ���ͷ
	struct Node *pCur;


	int i,j,k;
	int nLen=file->pTable->nLen;//  ��ȡ�ֶ�����
	int nCount=file->nCount;//  ��ȡ��������������
	int bFlag=OK;
	int *bIsOK;//  ��¼���������Ƿ�����Ҫ��:OK��ʾ����,ERROR��ʾ������

	char type;//�ֶ�����
	char strDataName[  MAX_LEN_FILE_NANE  ];
	char strChoice[20];




    bIsOK=(int *)malloc(   sizeof( int )*nCount );//����ռ�


	for( i=0; i<nCount;i++)
	{

		bIsOK[i]=INITSTATUS;//��ʼ������Ϊ������
	}


	ShowTable(&table);//��ʾ�ļ����ֶ���Ϣ

	while(  bFlag )
	{
		printf("�������������������ֶ���:\n");
		gets(strDataName);
	//	getchar();
		if(!strlen(strDataName))
		{
			printf("��ȷ��������ѯ?(Y/any key)\n");
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
			printf("�޴��ֶ���,��������\n");
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
			printf("����ɾ��������:\n");
			ShowData(pCur->next->arr,file);
			MyDeletData(pCur);
			printf("ɾ�����\n");

		}

	}

	file->nCount-=k;
	file->pTable->nCount-=k;
	if( !k)
	{
		printf("�Բ���,û����������������\n");
	}





}



/*
 *  �������ܣ��½��ļ�

 *  �������:�ļ�ָ��
 *  ����������ļ�ָ��
 *  �� �� ֵ����
 */
void New(struct File *file)
{
	char strFileName[MAX_LEN_FILE_NANE]="NONAME.txt";


//	puts(strFileName);
	printf("\n�������½����ݿ�ĸ��ֶ���Ϣ:\n");

	CreateTable(file->pTable);

	SubMenu(file);


//	printf("�ļ��½��ɹ�!\n");



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
 *  ��������: ׷�Ӽ�¼

 *  �������:�ļ�ָ��
 *  �����������
 *  �� �� ֵ����
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







	printf("\n\n�ļ�����%d���ֶ�\n\n",nLen);


	if(  (!file) || (!file->pHead)  )
	{
		printf("�ļ���������ʧ��,��ȷ���ļ��Ƿ�����!\n");
		return;
	}



/*
				printf("��������������:\n");
				pCur=(struct Node *)malloc(  sizeof(struct Node)  );
				for(    i=0;   i<nLen   ;i++   )
				{


					printf("������%s:\n",table.Head[i].strName);
				//	getchar();
					type=table.Head[i].cType;
					switch (type)
					{

					case 'c':

					//	getchar();
						scanf(   "%c",   &((  pCur->arr[i]).CHAR));
							getchar();


					//	printf("\n�����������:%c\n",pCur->arr[i].CHAR);


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
								 printf("�޷�ʶ�����������!\n");

					}
				}
				pCur->next=file->pHead->next;
				file->pHead->next=pCur;
					file->nCount++;




*/
		while(1)
		{



			printf("�������('a')\n�˳�(any key)\n");
		  // GetString(strChoice);
			gets(strChoice);
			//	getchar();

			if( 'a' != strChoice[0] )
			{

				 printf("\n�ѳɹ����%d������\n\n",nCount);
                	file->pTable->nCount=file->nCount;
					return ;



			}

					pCur=   ( struct Node * )malloc(  sizeof(  struct Node  )  );

				printf("��������������:\n");
				for(i=0;i<nLen;i++)
				{

					printf("������%s:\n",table.Head[i].strName);






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
						//	printf("\n�����������:%c\n",pCur->arr[i].CHAR);
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
										printf("\n�����������:%.2lf\n",pCur->arr[i].DOUBLE);

									getchar();


								  break;
							case 'i':
									scanf(   "%d",   &((  pCur->arr[i]).INT));
								//		printf("\n�����������:%d\n",pCur->arr[i].INT);
										getchar();

								  break;



							 default:
								 printf("�޷�ʶ�����������!\n");


					}

				}







				pCur->next=file->pHead->next;
				file->pHead->next=pCur;
				file->nCount++;
				nCount++;







			}
















}







/*
 *  �������ܣ����ļ��ж�ȡ����,�������ļ��ṹ����

 *  �������: �ļ�ָ��,�ļ���
 *  ����������ļ�ָ��
 *  �� �� ֵ����
 */
void Read(struct File  *file,char *strFileName)
{


//	printf("\n���ڽ���ļ�%s������\n",strFileName);

    /*��ȡ�ļ���ͷ*/
	ReadTable(file,strFileName);

	ShowTable(file->pTable);

	/*��ȡ�ļ�������*/
	ReadData(file,strFileName);



//	printf("\n�ɹ�����ļ�%s\n",strFileName);


}


/*
 *  �������ܣ��ͷ��ļ��ṹ��Ŀռ�

 *  �������:�ļ�ָ��
 *  �����������
 *  �� �� ֵ����
 */
void DelteFile(  struct File *file )
{

	free(file);

}



/*
 *  ��������:���ļ��д�������

 *  �������: �ļ�ָ��,�ļ���
 *  ����������ļ�ָ��
 *  �� �� ֵ����
 */
void Save(struct File  file,char *strFileName)
{


	printf("\n\n���ڴ�������\n\n");



    /*�洢�ļ���ͷ*/
	SaveTable(file.pTable,strFileName);


	/*�洢�ļ�������*/
	SaveData(file,strFileName);



	printf("\n\n�Ѵ�������\n\n");



}


/*
 *  �������ܣ���ʾ�Ӳ˵�

 *  �������:�ļ�ָ��
 *  �����������
 *  �� �� ֵ����
 */
void SubMenu(struct File *file)
{


	char strChoice[20];
	char strFileName[MAX_LEN_FILE_NANE];
	int flag =OK;
	int isSave=ERROR;




	while(  flag )
	{
		printf("׷��('a')\n");
		printf("��ѯ('f')\n");
		printf("����('u')\n");
		printf("ɾ��('d')\n");
		printf("����('s')\n");
		printf("�˳�(any key)\n");
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
				printf("�������ļ���\n");
	        gets(strFileName);
	       strcat(strFileName,".txt");
	        getchar();
			Save(*file,strFileName);
			isSave=OK;
			break;
		default:

			printf("������˳��Ӳ˵�?('Y'/any key)");


					GetString(strChoice);



					if('Y'==strChoice[0])
					{

							flag=ERROR;
							if(!isSave)
							{


								     printf("����δ����\n");
									 printf("�������ļ���\n");
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
//  SUPER_MARKET_MODEL ����ģʽ
//  OFFICE_MODEL �칫ģʽ
	char ch[20];
	printf("\n ��ϵͳ�Ĵ洢ģʽ:\n ����ģʽ\t �ʺ���Ƶ�����,ɾ����¼�ĳ���\n �칫ģʽ\t �ʺ��������ѯƵ���ĳ���\n��ǰģʽΪ:");
	if ( SUPER_MARKET_MODEL ==  nModel )
	{
		printf("����ģʽ\n");

	}
	else
	{
		printf("�칫ģʽ\n");
	}
	printf("��ѡ��ģʽ:\n ����ģʽ('S ')\n�칫ģʽ('O')\n �������˳�\n ");
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
			printf("��ѡ���˳���ģʽ\n ");
			nFlag=0;

			break;
		case 'O':
		case 'o':
			nModel= OFFICE_MODEL;
			printf ("��ѡ���˰칫ģʽ\n ");
			nFlag=0;
			break;
		default :
			nFlag=0;





		}
	//	getchar();
	}


}




/*
 *  �������ܣ���ʾ�˵�,������Ϣѭ��

 *  �������:��
 *  �����������
 *  �� �� ֵ����
 */
void MainMenu()
{
	char strChoice[20];
	int flag=OK;
	struct File file;
	InitFile(&file);

		printf("��ӭʹ��LiuDataBaseͨ�����ݿ����\n\n\n");
		printf("Copyright (c) 2006,���пƼ���ѧDian�Ŷ�\n");
		printf("All rights reserved.\n\n");
		printf("�ļ����ƣ�LiuDataBase\n");
		printf("ժ    Ҫ��ģ�⽻��ʽ��SOL�Ļ�������:��̬����,���������ѯ\n");
		printf("          ֧�ֵ���������Ϊ:char(�ַ���)int(������)double(������)string(�ַ�����)\n");
//		printf("          double(������) string(�ַ�����)\n");
		printf("��ǰ�汾���弶\n");
		printf("��    �ߣ�����0401 ����\n\n\n");



		while( flag )
		{

			printf("\t���˵�\n");
			printf("��('O')\n");
			printf("�½�('N')\n");
			printf("����('H')\n");

			printf("����('S')\n");
			printf("�˳�('Q')\n");
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
					printf("������˳����˵�?('Y'/any key)");
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
					printf("�㰴����Ч��,����ʹ�ð���('H')\n");
					continue;




				}


		}

}












/*
 *  �������ܣ���������,���������Ĺ����Լ��ӿ�

 *  �����������
 *  �����������
 *  �� �� ֵ����
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












































