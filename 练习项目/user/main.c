#include "stm32f10x.h"         

// 用户外设
#include "LED.h"
#include "Button.h"
#include "beep.h"

// 公共
#include "SysTick.h"		// 滴答 以后不会使用这种
#include "setSysClk.h"	// 72M

// 中断
#include "exti.h"

#include "USART.h"

int main(void)
{	
	setSysClkHSE();				// 设置HSE 为时钟源
	delay_init();
	LED_init();						// LED0 1 初始化 默认亮
	// JLED_init();				// JLED1-8 初始化 默认亮
	KEY_init();
	USART1_Init(19200);
	EXTI_Key_Config();
	EXTI_USART1_Config();
	Beep_Init();
	
	EXTI_Key_Config();		// 中断设置
	
	Beep_On();
	delay_ms(200);
	Beep_Off();
	
	while(1)
	{
		USART_SendData(USART1,0x22);
		delay_ms(500);
	}
}
