#ifndef __EXTI_H__
#define __EXTI_H__

#include "stm32f10x.h"

#include "Button.h"
#include "LED.h"
#include "USART.h"

#include "SysTick.h"

static void  NVCI_Config();

void EXTI_Key_Config(void);

// KEY0 ÖÐ¶Ïº¯Êý
void KEY0_IRQHandler(void);						



#endif