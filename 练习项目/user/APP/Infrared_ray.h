#ifndef __INFRARED_RAY_H__
#define __INFRARED_RAY_H__

#include "stm32f10x.h"
#include "SysTick.h"
#include "USART.h"

// IO  Infrared_ray_  红外接收引脚 Send, Receive
#define Infrared_ray_Receive_PORT              GPIOB
#define Infrared_ray_Receive_PIN               GPIO_Pin_9
#define Infrared_ray_Receive_RCC               RCC_APB2Periph_GPIOB

// exti中断
#define Infrared_ray_Receive_EXTI_LINE         EXTI_Line9
#define Infrared_ray_Receive_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define Infrared_ray_Receive_EXTI_PINSOURCE    GPIO_PinSource9


// TIM
#define infrared_ray_TIMx				TIM4
#define infrared_ray_TIMx_RCC	  		RCC_APB1Periph_TIM4
#define infrared_ray_TIMx_CCRx 			CCR4				// PB9 
#define infrared_ray_TIMx_Channel 	    TIM_Channel_4



// PB9
void Infrared_ray_init();




#endif