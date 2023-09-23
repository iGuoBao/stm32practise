#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "stm32f10x.h"

// Button引脚宏定义
// KEY0 PE4
#define KEY0_PORT 					GPIOE
#define KEY0_PIN 						GPIO_Pin_4
#define KEY0_PORT_RCC				RCC_APB2Periph_GPIOB

// KEY1 PE3
#define KEY1_PORT 					GPIOE
#define KEY1_PIN 						GPIO_Pin_3
#define KEY1_PORT_RCC				RCC_APB2Periph_GPIOB

// KEY2 PE2
#define KEY2_PORT 					GPIOE
#define KEY2_PIN 						GPIO_Pin_2
#define KEY2_PORT_RCC				RCC_APB2Periph_GPIOB

void KEYinit(void);	//KEY0-2

#endif