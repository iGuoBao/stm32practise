#ifndef __EXTI_H__
#define __EXTI_H__

#include "stm32f10x.h"

#include "Button.h"
#include "LED.h"

#include "SysTick.h"


// #ifdef __BUTTON_H__
// KEY0 中断定义
#define KEY0_EXTI_PORT 					KEY0_PORT
#define KEY0_EXTI_PIN 					KEY0_PIN
// 在button头文件定义---#define KEY0_EXTI_RCC 					(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO)	// 开启对应的GPIO AFIO时钟
#define KEY0_EXTI_PORTSOURCE 		KEY0_PORTSOURCE		// 在button.h 定义  中断源与引脚映射用
#define KEY0_EXTI_PINSOURCE  		KEY0_PINSOURCE
#define KEY0_EXTI_LINE 					EXTI_Line4				// EXTI通道选择 0
#define KEY0_EXTI_IRQ 					EXTI4_IRQn				// 中断号  	NVIC中
#define KEY0_IRQHandler 				EXTI4_IRQHandler	// 中断函数名
// #endif	/* __BUTTON_H__ */

static void  NVCI_Config();
void EXTI_Key_Config(void);

void KEY0_IRQHandler(void);						// KEY0 中断函数



#endif