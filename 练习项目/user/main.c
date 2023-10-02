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
	setSysClkHSE();				
	
	// 外设初始化 开始
	LED_init();						
	JLED_init();
	KEY_init();
	Beep_Init(PWM);
	// 外设初始化 结束

	delay_init();					// systick
	EXTI_Key_Config();		// 中断设置
	EXTI_USART1_Config(115200);


	while(1)
	{
		printf("data=%d\r\n",123);

		delay_ms(500);
	}
}


