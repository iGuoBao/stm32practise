#include "stm32f10x.h"    // Device header

// 公共
#include "setSysClk.h"

// 用户外设
#include "LED.h"
#include "Button.h"





int main(void)
{
<<<<<<< Updated upstream
	setSysClkHSE();		// 设置HSE 为时钟源
	LEDinit();				// LED0 1 初始化 默认亮
	JLEDinit();				// JLED1-8 初始化 默认亮
=======
	set_SysClkHSE();		// 设置HSE 为时钟源
	LED_init();					// LED0 1 初始化 默认亮
	JLED_init();				// JLED1-8 初始化 默认亮
>>>>>>> Stashed changes
	while(1)
	{
		if(IsButtonPressed(KEY0_PORT,KEY0_PIN))
		{
			GPIO_WriteBit(LED0_PORT, LED0_PIN, !GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN)); // 电平取反
		}
	}
}
