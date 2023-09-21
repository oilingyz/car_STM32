#include "wifi.h"
#include "syslib.h"

void wifi_setprint(int t,char *a)
{
	printstr(a);
	delay_ms(t);
}

void WIFI_Init(void)
{
	wifi_setprint(1000,"AT+CWMODE=2");
//  wifi_setprint(1000,"AT+RST");
	wifi_setprint(1000,"AT+CWSAP=\"ESP_WIFI\",\"12345678\",1,3,4,0");
	delay_ms(1000);
	delay_ms(1000);
	wifi_setprint(1000,"AT+CIPMUX=1");
	wifi_setprint(1000,"AT+CIPSERVER=1");
}

void WIFI_SendData(char *str)
{
	int len=0;
	while(str[len]!='\0') len++;

	char order[40];
	sprintf(order,"AT+CIPSEND=0,%d",len);
	wifi_setprint(500,order);
	wifi_setprint(0,str);
}

int WIFI_FLAG=0;
void WIFI_Report(void)
{
	if(WIFI_FLAG==1)
	{
		char order[40];
		sprintf(order,"Target number %d has been received",TARGET_NUM);
		WIFI_SendData(order);
	}
	
	if(WIFI_FLAG==2)
		WIFI_SendData("The medication has been delivered");
	
	if(WIFI_FLAG==3)
		WIFI_SendData("The car is blocked by front barrier");
		
	WIFI_FLAG=0;
}
