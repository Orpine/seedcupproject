#include<stdio.h>
#include<math.h>
#include<malloc.h>

double jisuan(char a[])
{
    int i=1,j,k,m,cnt=0,t1=0,t2=0,t3=0;
    char nibo[50],zhan2[50];
    double x,n,l,z=0,zhan3[50];
    typedef struct
    {
        double d1;
        int d2;
    } dd;
    typedef struct
    {
        dd data[50];
        int top;
    } zhan1;
    zhan1 *shu;
    shu=(zhan1 *)malloc(sizeof(zhan1));
    shu->top=0;
    while(a[i]!='\0')
    {
        if(a[i]>='0'&&a[i]<='9')
        {
            z=0;
            j=i+1;
            while(a[j]>='0'&&a[j]<='9')
            {
                j++;
            }
            j--;
            for(k=i; k<=j; k++)
            {
                z=z*10+a[k]-'0';
            }
            j=j+1;
            x=z;
            if(a[j]=='.')
            {
                l=1;
                i=j+1;
                j=i+1;
                while(a[j]>='0'&&a[j]<='9')
                {
                    j++;
                }
                j--;
                for(k=i; k<=j; k++)
                {
                    n=pow(0.1,l);
                    l=l+1;
                    x=x+n*(a[k]-'0');
                }
                i=j+1;
            }
            else i=j;
            shu->data[++shu->top].d1=x;
            shu->data[shu->top].d2=++cnt;
            nibo[++t1]='0'+shu->data[shu->top].d2;
            nibo[t1+1]='\0';
        }
        else if(a[i]=='(')
        {
            zhan2[++t2]=a[i];
            i++;
        }
        else if(a[i]==')')
        {
            j=t2;
            while(zhan2[j]!='(')
            {
                nibo[++t1]=zhan2[j];
                nibo[t1+1]='\0';
                j--;
            }
            t2=j-1;
            i++;
        }
        else if(a[i]=='+')
        {
            while(t2>0&&zhan2[t2]!='(')
            {
                nibo[++t1]=zhan2[t2];
                nibo[t1+1]='\0';
                t2--;
            }
            zhan2[++t2]=a[i];
            i++;
        }
        else if(a[i]=='-')
        {
            if(a[i-1]=='$')
            {
                a[0]='0';
                i=0;
            }
            else if(a[i-1]=='(')
            {
                a[i-1]='0';
                a[i-2]='(';
                i=i-2;
                t2--;
            }
            else
            {
                while(t2>0&&zhan2[t2]!='(')
                {
                    nibo[++t1]=zhan2[t2];
                    nibo[t1+1]='\0';
                    t2--;
                }
                zhan2[++t2]=a[i];
                i++;
            }
        }
        else if(a[i]=='*'||a[i]=='/')
        {
            while(zhan2[t2]=='*'||zhan2[t2]=='/'||zhan2[t2]=='^'||zhan2[t2]=='#')
            {
                nibo[++t1]=zhan2[t2];
                nibo[t1+1]='\0';
                t2--;
            }
            zhan2[++t2]=a[i];
            i++;
        }
        else if(a[i]=='^'||a[i]=='#')
        {
            while(zhan2[t2]=='^'||zhan2[t2]=='#')
            {
                nibo[++t1]=zhan2[t2];
                nibo[t1+1]='\0';
                t2--;
            }
            zhan2[++t2]=a[i];
            i++;
        }
    }
    while(t2>0)
    {
        nibo[++t1]=zhan2[t2];
        nibo[t1+1]='\0';
        t2--;
    }

    j=1;
    t3=0;
    while(j<=t1)
    {
        if(nibo[j]>='0'&&nibo[j]!='^'&&nibo[j]!='#')//
        {
            for(i=1; i<=shu->top; i++)
            {
                if((int)(nibo[j]-'0')==shu->data[i].d2)
                {
                    m=i;
                    break;
                }
            }
            zhan3[++t3]=shu->data[m].d1;

        }
        else if(nibo[j]=='+')
        {
            zhan3[t3-1]=zhan3[t3-1]+zhan3[t3];
            t3--;

        }
        else if(nibo[j]=='-')
        {
            zhan3[t3-1]=zhan3[t3-1]-zhan3[t3];
            t3--;
        }
        else if(nibo[j]=='*')
        {
            zhan3[t3-1]=zhan3[t3-1]*zhan3[t3];
            t3--;
        }
        else if(nibo[j]=='/')
        {
            zhan3[t3-1]=zhan3[t3-1]/zhan3[t3];
            t3--;
        }
        else if(nibo[j]=='^')
        {
            zhan3[t3-1]=pow(zhan3[t3-1],zhan3[t3]);
            t3--;
        }
        else if(nibo[j]=='#')
        {
            zhan3[t3]=sqrt(zhan3[t3]);
        }
        j++;

    }

    return zhan3[t3];


}
int data_handle(string x)
{
        char *a;
        double jieguo;
       // int i=0;
      //  a[0]='$';
        x='$'+x;
       // #表示开方，^表示乘方(支持负数
       // 输入表达式无需输入 = 号

        //a[i+1]='\0';
        a = (char*)x.c_str();
        jieguo=jisuan(a);
       return jieguo;

}

