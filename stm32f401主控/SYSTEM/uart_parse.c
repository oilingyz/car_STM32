#include "uart_parse.h"                                                                                                          
#include <stdio.h>
#include <stdlib.h>
#include "syslib.h"

int Print_Flag=1;
	

void printarray(float* array,int n)
{
	printf("%s\r\n",sbz_format(array,n));
}

void printfloat(float data)
{
	float d[1]={data};
	printarray(d,1);
}

void printstr(char* str)
{
	printf("%s\r\n",str);
}

void arraycopy(float a[],float b[],int len)
{
	for (int i=0;i<len;i++)
	{
		b[i]=a[i];
	}
}

void SYN6288_SPEAK(char *a)
{
	Print_Flag=2;
	printf("%s",a);
	Print_Flag=1;
}

int syn6288_flag=0;
void SYN6288_Report(void)
{
	char buffer[40];
	sprintf(buffer, "药物已送达%d号病房", TARGET_NUM);
	if(syn6288_flag==1)
	{
		syn6288_flag=0;
		SYN6288_SPEAK(buffer);
		delay_ms(1000);
		delay_ms(1000);
		delay_ms(1000);	
	}
}

//float myatof(char *a)
//{
//	float sig=1;
//	if(a[0]=='-') sig=-1;
//	int len=0,lo=0;
//	while(a[lo]=='.'||a[lo]=='\0')
//	{
//		lo++;
//	}
//	
//	
//}

char datatrans[50];
char* sbz_format(float *data,int size)
{

int size_data=size;
int i=0,j=0,trans_count=1;

datatrans[0]='&';

while(i<size_data)
{
	char data_cha[20];
	
	sprintf(data_cha,"%f",data[i]);
	
	datatrans[trans_count]='!';
	
	while(data_cha[j]!='\0')
	{
		trans_count++;
		datatrans[trans_count]=data_cha[j];
		j++;
	}
	j=0;
	
	trans_count++;
	datatrans[trans_count]='!';
	trans_count++;
	
	i++;
}
datatrans[trans_count]='*';
datatrans[trans_count+1]='\0';

return datatrans;
}

int sbz_parse(char *data, float *output,int STA,int len)
{
    int i = 0, j = 0;
    int flag = -1;
    int num_rec = 0;
    char array[20];

    while(i<=STA)
    {
      if(data[i]=='&')
      {
          while(data[i]!='*')
          {
					//		printfloat(i);
              if(flag==1&&data[i]!='!')
              {
                  *(array+j)=data[i];
                  j++;
              }
              if (flag==1&&data[i]=='!')
              {
                *(array+j) = '\0';
                *(output+num_rec)=atof(array);
                num_rec++;
                j=0;
              }
              if(data[i]=='!')
              {
                flag*=(-1);
              }
              i++;
         }
         break;
     }
     else
     {
       i++;
     }
   }
		if(num_rec!=len) return 0;
		else return 1;
}


void sbz_parse_new(char *data, float *output)
{
    int i = 0, j = 0;
    int num_rec = 0;
    char array[20];

    while(1)
    {
      if(data[i]=='[')
      {
					i++;
          while(data[i]!=']')
          {
              if(data[i]!='('&&data[i]!=')')
              {
                  *(array+j)=data[i];
                  j++;
              }
              if (data[i]==')')
              {
                *(array+j) = '\0';
                *(output+num_rec)=atof(array);
                num_rec++;
                j=0;
//								printstr(array);
//								printfloat(*(output+num_rec));
              }
              i++;
         }
         break;
     }
     else
     {
       i++;
     }
   }
}

void VL53L0_parse(char *data, float *output)
{
	char trans[20];
	int j=0;
	for (int i=0;data[i]!='m';i++)
	{
		if(data[i]>='0'&&data[i]<='9')
			*(trans+j)=data[i],j++;
	}
	*output=atof(trans);
}
