#ifndef __EXTI_H__
#define __EXTI_H__

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

static void  NVCI_Config();

void EXTI_Key_Config(void);
void EXTI_USARTn_Config(u8 number,u32 b);
	
#endif