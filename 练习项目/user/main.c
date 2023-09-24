#include "stm32f10x.h"         

// 用户外设
#include "LED.h"
#include "Button.h"

// 公共
#include "setSysClk.h"

int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);							// 配置组别
	setSysClkHSE();				// 设置HSE 为时钟源
	LED_init();						// LED0 1 初始化 默认亮
	// JLED_init();				// JLED1-8 初始化 默认亮
	KEY_init();
	
	while(1)
	{
		if(IsKeyPressed(KEY0_PORT,KEY0_PIN))
		{
			GPIO_WriteBit(LED0_PORT, LED0_PIN, !GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN));		// 取反
		}
		else if(IsKeyPressed(KEY1_PORT,KEY1_PIN))
		{
			GPIO_WriteBit(LED1_PORT, LED1_PIN, !GPIO_ReadOutputDataBit(LED1_PORT, LED1_PIN));		// 取反
		}
		else if(IsKeyPressed(KEY2_PORT,KEY2_PIN))
		{
			GPIO_WriteBit(LED0_PORT, LED0_PIN, !GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN));		// 取反
		}
	}
}
