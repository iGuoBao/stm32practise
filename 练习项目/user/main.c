#include "stm32f10x.h"         

// 用户外设
#include "LED.h"
#include "Button.h"
#include "beep.h"
#include "EEPROM_AT24C02.h"
#include "tftlcd.h"
#include "animations.h"

// 公共
#include "SysTick.h"		// 滴答 以后不会使用这种 RTOS心脏
#include "setSysClk.h"	// 72M

// 中断
#include "exti.h"

// 协议
#include "i2c.h"
#include "USART.h"

int main(void)
{	

	setSysClkHSE();				

	LED_init();
	KEY_init();
	Beep_Init(PWM);

	
	delay_Config();					// systick
	BASIC_TIM3_Config();
	BASIC_TIM6_Config();
	EXTI_Key_Config();		// 中断设置
	
	
	while(1)
	{
	
		
	}
}


