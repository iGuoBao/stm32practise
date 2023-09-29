#ifndef __TIM_H__
#define __TIM_H__

#include "stm32f10x.h"


#define BASIC_TIM6 									TIM6
#define BASIC_TIM6_APBxClock_FUN 		RCC_APB1PeriphClockCmd		
#define BASIC_TIM6_CLK 							RCC_APB1Periph_TIM6
#define BASIC_TIM6_IRQ 							TIM6_IRQn
#define BASIC_TIM6_IRQHandler 			TIM6_IRQHandler

#define BASIC_TIM7 									TIM7
#define BASIC_TIM7_APBxClock_FUN 		RCC_APB1PeriphClockCmd
#define BASIC_TIM7_CLK 							RCC_APB1Periph_TIM7
#define BASIC_TIM7_IRQ 							TIM7_IRQn
#define BASIC_TIM7_IRQHandler 			TIM7_IRQHandler


void BASIC_TIM6_Config(void);
void TIM6_DelayMs(int Ms);

#endif