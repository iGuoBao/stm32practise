#ifndef __BUTTON_H__
#define __BUTTON_H__


#include "stm32f10x.h"


#include "exti.h"
#include "LED.h"
#include "SysTick.h"

// KEY0  PE4
#define KEY0_PORT 						GPIOE 			
#define KEY0_PORTSOURCE  			GPIO_PortSourceGPIOE		// 中断用 配置外部中断线0与GPIOA的0号引脚的映射关系
#define KEY0_PIN  						GPIO_Pin_4 			
#define KEY0_PINSOURCE   			GPIO_PinSource4  			// 中断用 配置外部中断线0与GPIOA的0号引脚的映射关系
#define KEY0_PORT_RCC					RCC_APB2Periph_GPIOE
// 中断部分
#define KEY0_EXTI_RCC					(KEY0_PORT_RCC|RCC_APB2Periph_AFIO)
#define KEY0_EXTI_PORT 					KEY0_PORT
#define KEY0_EXTI_PIN 					KEY0_PIN
#define KEY0_EXTI_PORTSOURCE 		KEY0_PORTSOURCE		// 在button.h 定义  中断源与引脚映射用
#define KEY0_EXTI_PINSOURCE  		KEY0_PINSOURCE
#define KEY0_EXTI_LINE 					EXTI_Line4				// EXTI通道选择 4
#define KEY0_EXTI_IRQ 					EXTI4_IRQn				// 中断号  	NVIC中
#define KEY0_IRQHandler 				EXTI4_IRQHandler	// 中断函数名

// KEY1  PE3
#define KEY1_PORT 						GPIOE 						
#define KEY1_PORTSOURCE  			GPIO_PortSourceGPIOE		
#define KEY1_PIN  						GPIO_Pin_3 		
#define KEY1_PINSOURCE   			GPIO_PinSource3
#define KEY1_PORT_RCC					RCC_APB2Periph_GPIOE
#define KEY1_EXTI_RCC					(KEY1_PORT_RCC|RCC_APB2Periph_AFIO)
// 中断部分
#define KEY1_EXTI_PORT 					KEY1_PORT
#define KEY1_EXTI_PIN 					KEY1_PIN
#define KEY1_EXTI_PORTSOURCE 		KEY1_PORTSOURCE		
#define KEY1_EXTI_PINSOURCE  		KEY1_PINSOURCE
#define KEY1_EXTI_LINE 					EXTI_Line3				
#define KEY1_EXTI_IRQ 					EXTI3_IRQn				
#define KEY1_IRQHandler 				EXTI3_IRQHandler

// KEY2  PE2
#define KEY2_PORT 						GPIOE						
#define KEY2_PORTSOURCE  			GPIO_PortSourceGPIOE	
#define KEY2_PIN  						GPIO_Pin_2 	
#define KEY2_PINSOURCE   			GPIO_PinSource2
#define KEY2_PORT_RCC					RCC_APB2Periph_GPIOE
#define KEY2_EXTI_RCC					(KEY2_PORT_RCC|RCC_APB2Periph_AFIO)			
// 中断部分
#define KEY2_EXTI_PORT 					KEY2_PORT
#define KEY2_EXTI_PIN 					KEY2_PIN
#define KEY2_EXTI_PORTSOURCE 		KEY2_PORTSOURCE		
#define KEY2_EXTI_PINSOURCE  		KEY2_PINSOURCE
#define KEY2_EXTI_LINE 					EXTI_Line2				
#define KEY2_EXTI_IRQ 					EXTI2_IRQn				
#define KEY2_IRQHandler 				EXTI2_IRQHandler	


// WKUP  PA0
#define WKUP_PORT 						GPIOA					
#define WKUP_PORTSOURCE  			GPIO_PortSourceGPIOA	
#define WKUP_PIN  						GPIO_Pin_0 				
#define WKUP_PINSOURCE   			GPIO_PinSource0
#define WKUP_PORT_RCC					RCC_APB2Periph_GPIOA
#define WKUP_EXTI_RCC					(WKUP_PORT_RCC|RCC_APB2Periph_AFIO)
// 中断部分
#define WKUP_EXTI_PORT 					WKUP_PORT
#define WKUP_EXTI_PIN 					WKUP_PIN
#define WKUP_EXTI_PORTSOURCE 		WKUP_PORTSOURCE		
#define WKUP_EXTI_PINSOURCE  		WKUP_PINSOURCE
#define WKUP_EXTI_LINE 					EXTI_Line0				
#define WKUP_EXTI_IRQ 					EXTI0_IRQn				
#define WKUP_IRQHandler 				EXTI0_IRQHandler	



	



void KEY_init(void);


int IsKeyPressed(GPIO_TypeDef * KEY_PORT,uint16_t KEY_PIN);		//判断是否按下 按下返回1，没按下返回0 
int getPressKeyStation(GPIO_TypeDef * KEY_PORT,uint16_t KEY_PIN);

#endif