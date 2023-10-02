#ifndef __USART_H__
#define __USART_H__

#include "stm32f10x.h"
#include "stdio.h" // 标准库

#define BUFFER_SIZE		128	// 最大接受字节数量  	

extern u8 buffer[BUFFER_SIZE];
extern u16 writeIndex;

 	
#define USART_TX_CLK  					( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 )
#define USART_TX_Port  					GPIOA
#define USART_TX_PIN 						GPIO_Pin_9


#define USART_RX_CLK  					( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 )
#define USART_RX_Port  					GPIOA
#define USART_RX_PIN 						GPIO_Pin_10	


void USART1_Init(u32 bound);

void sendString(char* str);
u8 getDate();

#endif