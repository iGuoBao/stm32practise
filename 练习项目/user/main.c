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


int main(void)
{	
	setSysClkHSE();				// 设置HSE 为时钟源
	delay_init();
	LED_init();						// LED0 1 初始化 默认亮
	// JLED_init();				// JLED1-8 初始化 默认亮
	KEY_init();
	EXTI_Key_Config();
	while(1)
	{
		
	}
}
