#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "stm32f10x.h"

// KEY0  PE4
#define KEY0_PORT 						GPIOE 			
#define KEY0_PORTSOURCE  			GPIO_PortSourceGPIOE		// 中断用 配置外部中断线0与GPIOA的0号引脚的映射关系
#define KEY0_PIN  						GPIO_Pin_4 			
#define KEY0_PINSOURCE   			GPIO_PinSource4  			// 中断用 配置外部中断线0与GPIOA的0号引脚的映射关系
#define KEY0_PORT_RCC					RCC_APB2Periph_GPIOE
#define KEY0_EXTI_RCC					(KEY0_PORT_RCC\
															|RCC_APB2Periph_AFIO)

// KEY1  PE3
#define KEY1_PORT 						GPIOE 						
#define KEY1_PIN  						GPIO_Pin_3 				
#define KEY1_PORT_RCC					RCC_APB2Periph_GPIOE
// KEY2  PE2
#define KEY2_PORT 						GPIOE							
#define KEY2_PIN  						GPIO_Pin_2 				
#define KEY2_PORT_RCC					RCC_APB2Periph_GPIOE

void KEY_init(void);
int IsKeyPressed(GPIO_TypeDef * KEY_PORT,uint16_t KEY_PIN);		//判断是否按下 按下返回1，没按下返回0 


#endif