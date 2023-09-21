#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "setSysClk.h"

int main(void)
{
	setSysClkHSE();		// 设置HSE 为时钟源
	LEDinit();				// LED0 1 初始化 默认亮
	JLEDinit();				// JLED1-8 初始化 默认亮
	while(1)
	{
		
	}
}
