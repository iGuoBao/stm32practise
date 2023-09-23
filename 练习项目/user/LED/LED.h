#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"

// LED引脚宏定义
// LED0 PB5
#define LED0_PORT 					GPIOB
#define LED0_PIN 						GPIO_Pin_5
#define LED0_PORT_RCC				RCC_APB2Periph_GPIOB
// LED1 PE5
#define LED1_PORT 					GPIOE
#define LED1_PIN 						GPIO_Pin_5
#define LED1_PORT_RCC				RCC_APB2Periph_GPIOE



// JLED1-8 PC0-7
// JLED1
#define JLED1_PORT 						GPIOC
#define JLED1_PIN 						GPIO_Pin_0
#define JLED1_PORT_RCC				RCC_APB2Periph_GPIOC
// JLED2
#define JLED2_PORT 						GPIOC
#define JLED2_PIN 						GPIO_Pin_1
#define JLED2_PORT_RCC				RCC_APB2Periph_GPIOC
// JLED3
#define JLED3_PORT 						GPIOC
#define JLED3_PIN 						GPIO_Pin_2
#define JLED3_PORT_RCC				RCC_APB2Periph_GPIOC
// JLED4
#define JLED4_PORT 						GPIOC
#define JLED4_PIN 						GPIO_Pin_3
#define JLED4_PORT_RCC				RCC_APB2Periph_GPIOC
// JLED5
#define JLED5_PORT 						GPIOC
#define JLED5_PIN 						GPIO_Pin_4
#define JLED5_PORT_RCC				RCC_APB2Periph_GPIOC
// JLED6
#define JLED6_PORT 						GPIOC
#define JLED6_PIN 						GPIO_Pin_5
#define JLED6_PORT_RCC				RCC_APB2Periph_GPIOC
// JLED7
#define JLED7_PORT 						GPIOC
#define JLED7_PIN 						GPIO_Pin_6
#define JLED7_PORT_RCC				RCC_APB2Periph_GPIOC
// JLED8
#define JLED8_PORT 						GPIOC
#define JLED8_PIN 						GPIO_Pin_7
#define JLED8_PORT_RCC				RCC_APB2Periph_GPIOC



// 初始化
void LEDinit(void);
void JLEDinit(void);



#endif