#ifndef __USART_H__
#define __USART_H__

#include "stm32f10x.h"

// 串口输出
#define USART_TX_CLK  					( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 )
#define USART_TX_Port  					GPIOA
#define USART_TX_PIN 						GPIO_Pin_2
// 串口输入
#define USART_RX_CLK  					( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 )
#define USART_RX_Port  					GPIOA
#define USART_RX_PIN 						GPIO_Pin_3


void USART1_Init(u32 bound);




#endif