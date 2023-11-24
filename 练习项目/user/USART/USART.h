#ifndef __USART_H__
#define __USART_H__

#include "stm32f10x.h"
#include "stdio.h" // 标准库

#define BUFFER_SIZE		128	// 最大接受字节数量  	
 	
#define USART_TX_CLK  					( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 )
#define USART_TX_Port  					GPIOA
#define USART_TX_PIN 					GPIO_Pin_9
#define USART_RX_CLK  					( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 )
#define USART_RX_Port  					GPIOA
#define USART_RX_PIN 					GPIO_Pin_10	
//---------USART2----------
// RS485 RE-PD7  PA2-USART2_TX  PA3/USART2_RX
#define USART2_TX_CLK  						RCC_APB2Periph_GPIOA
#define USART2_TX_CLK2 						RCC_APB1Periph_USART2 //RCC_APB1PeriphClockCmd  RCC_APB2Periph_AFIO
#define USART2_TX_Port  					GPIOA
#define USART2_TX_PIN 						GPIO_Pin_2
#define USART2_RX_CLK  						RCC_APB2Periph_GPIOA
#define USART2_RX_Port  					GPIOA
#define USART2_RX_PIN 						GPIO_Pin_3	
#define USART2_RS485_RE_CLK  		  RCC_APB2Periph_GPIOD
#define USART2_RS485_RE_CLK2 			RCC_APB1Periph_USART2 
#define USART2_RS485_RE_Port  		GPIOD
#define USART2_RS485_RE_PIN 			GPIO_Pin_7


void USARTn_Init(u8 number,u32 bound);
void RS485_ENABLE(u8 work_station);
void RS485_send_data(u8 buf);
void RS485_send_cmd(u8 buf[],u8 len);


#endif