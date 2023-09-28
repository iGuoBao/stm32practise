#ifndef __EXTI_H__
#define __EXTI_H__

#include "stm32f10x.h"

#include "Button.h"
#include "LED.h"
#include "beep.h"
#include "USART.h"
#include "SysTick.h"



static void  NVCI_Config();

void EXTI_Key_Config(void);
void EXTI_USART1_Config(void);


// 中断函数
void KEY0_IRQHandler(void);					
void KEY1_IRQHandler(void);	
void KEY2_IRQHandler(void);	
void WKUP_IRQHandler(void);	


#endif