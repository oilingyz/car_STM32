#include "syslib.h"

/* IO��

 ����1 ˫��ͨ�ţ�TX PA9 RX PA10
 ����2 OPENMV  �RRX PA3
			 SYN8266 ��TX PA2
 
 ���֣�
		PWM PB0 PB1 ������TIM4 PB6 PB7
 ���֣�  
    PWM PB4 PB5 ������TIM2 PA0 PA1

	����: PB9
	
	RGBLED: RLED PB2 GLED PB10
	
	
*/



int main(void)
{
	delay_init(84);

	MOTO2_TIM3_A4950_Init(1); //TIM3 PB 0 1 4 5 ; �������PWM��ʼ����PWMƵ��10KHZ
	
	uart_init(9600); 		//TX PA9 RX PA10 Ԥ������/WIFI
	uart2_init(9600); 	//PA3 OPENMV PA2 SYN6288	`
	
	RGBLED_Init();  //R PB2  G PB10 ָʾ��
  LED_Init();
	
	HW_Init(); //����ҩ���� PB9
	Encoder_TIM2_TIM4_TIM9_Init(15); //TIM2 PA0 PA1  TIM4 PB6 PB7 ��������ʼ��
	
  TIM10_IRQ_Init(20);  //���ж� 20ms�ж�1��
	
	while(1)
	{
		MAX_SPEED=10;      	 //С������ٶ�����
		MODE=HOST;           //����С����ɫ��������ӻ�  HOST/SLAVE
    PUT_TEST_HW();       //ҩ����ü�⣬��ʹ��delay���Ž��ж�
		LED=~LED;
		
		delay_ms(500);
	}
	
}



