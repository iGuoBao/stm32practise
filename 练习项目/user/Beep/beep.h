#ifndef __BEEP_H__
#define __BEEP_H__

#include "stm32f10x.h"

// Beep PB8
#define Beep_PORT 					GPIOB
#define Beep_PIN 						GPIO_Pin_8
#define Beep_PORT_RCC				RCC_APB2Periph_GPIOB

void Beep_Init(void);
void Beep_On(void);
void Beep_Off(void);

#endif