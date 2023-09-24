#include "stm32f10x.h"         

// 用户外设
#include "LED.h"
#include "Button.h"

// 中断
#include "exti.h"

// 公共
#include "setSysClk.h"

int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);							// 配置组别
	setSysClkHSE();				// 设置HSE 为时钟源
	LED_init();						// LED0 1 初始化 默认亮
	// JLED_init();				// JLED1-8 初始化 默认亮
	KEY_init();
	EXTI_Key_Config();
	
	while(1)
	{

	}
}
