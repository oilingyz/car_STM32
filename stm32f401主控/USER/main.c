#include "syslib.h"

/* IO口

 串口1 双车通信：TX PA9 RX PA10
 串口2 OPENMV  RX PA3
			 SYN8266 ：TX PA2
 
 左轮：
		PWM PB0 PB1 编码器TIM4 PB6 PB7
 右轮：  
    PWM PB4 PB5 编码器TIM2 PA0 PA1

	红外: PB9
	
	RGBLED: RLED PB2 GLED PB10
	
	
*/



int main(void)
{
	delay_init(84);

	MOTO2_TIM3_A4950_Init(1); //TIM3 PB 0 1 4 5 ; 电机驱动PWM初始化，PWM频率10KHZ
	
	uart_init(9600); 		//TX PA9 RX PA10 预留蓝牙/WIFI
	uart2_init(9600); 	//PA3 OPENMV PA2 SYN6288	`
	
	RGBLED_Init();  //R PB2  G PB10 指示灯
  LED_Init();
	
	HW_Init(); //红外药物检测 PB9
	Encoder_TIM2_TIM4_TIM9_Init(15); //TIM2 PA0 PA1  TIM4 PB6 PB7 编码器初始化
	
  TIM10_IRQ_Init(20);  //主中断 20ms中断1次
	
	while(1)
	{
		MAX_SPEED=10;      	 //小车最大速度限制
		MODE=HOST;           //设置小车角色，主机或从机  HOST/SLAVE
    PUT_TEST_HW();       //药物放置检测，有使用delay不放进中断
		LED=~LED;
		
		delay_ms(500);
	}
	
}



