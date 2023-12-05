#include "stm32f10x.h"         

// 用户外设
#include "LED.h"
#include "Button.h"
#include "RTC.h"
//#include "beep.h"
//#include "EEPROM_AT24C02.h"
//#include "tftlcd.h"
//#include "animations.h"

// 公共
#include "SysTick.h"		// 滴答 以后不会使用这种
#include "setSysClk.h"	// 72M

// 中断
#include "exti.h"

// 协议
//#include "i2c.h"
#include "USART.h"

int main(void)
{	
	setSysClkHSE();				
	LED_init();						
	KEY_init();

	
	
	delay_Config();					// systick
	EXTI_Key_Config();		// 中断设置
	EXTI_USARTn_Config(1,9600);
	EXTI_USARTn_Config(2,9600);
	RS485_ENABLE(1);
	printf("usart2_init\r\n");	
	BASIC_TIM4_Config();
	//------ app
	
	RTC_Init();
	printf("RTC_init\r\n");	

	extern u8 buffer[BUFFER_SIZE];
	extern u8 writeIndex;
	//------ app

	
	while(1)
	{
		delay_ms(500);
		SetLED(1,1);
		delay_ms(500);
		SetLED(1,0);
			

	}

	
}


