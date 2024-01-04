#ifndef __ADC_H__
#define __ADC_H__

#include "stm32f10x.h"

// PA1 作为adc采集通道 与板载电位器
#define ADC_GPIO_PORT				GPIOA
#define ADC_GPIO_PIN				GPIO_Pin_1
#define ADC_GPIO_RCC				RCC_APB2Periph_GPIOA
#define ADC_GPIO_APB_FUN    RCC_APB2PeriphClockCmd

// 选择我们要用的ADC通道
#define ADCx 							  ADC1	
#define ADC_RCC 					  RCC_APB2Periph_ADC1	
#define ADC_APB_FUN 			  RCC_APB2PeriphClockCmd					

// ADC 通道宏定义
#define ADC_CHANNEL 			  ADC_Channel_1

#define ADC_IRQ 						ADC1_2_IRQn
#define ADC_IRQHandler 			ADC1_2_IRQHandler

void ADCx_GPIO_Init(void);

void ADCx_Mode_Config(void);

float GetValue();

#endif