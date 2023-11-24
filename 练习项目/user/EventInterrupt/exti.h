#ifndef __EXTI_H__
#define __EXTI_H__


#define TEST_DEFINE  1    




#include "stm32f10x.h"

#include "Button.h"
#include "LED.h"
#include "beep.h"
#include "USART.h"
#include "SysTick.h"
#include "TIM.h"
#include "ADC.h"
#include "RTC.h"
#include "animations.h"
#include "tftlcd.h"
#include "infrared_ray.h"


static void  NVCI_Config();

void EXTI_Key_Config(void);
void EXTI_USART1_Config(u32 b);


// 中断函数
void KEY0_IRQHandler(void);					
void KEY1_IRQHandler(void);	
void KEY2_IRQHandler(void);	
void WKUP_IRQHandler(void);	
void USART1_IRQHandler(void);
void TIM6_IRQHandler(void);
	
#endif