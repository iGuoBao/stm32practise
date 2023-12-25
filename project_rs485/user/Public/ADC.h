#ifndef __ADC_H__
#define __ADC_H__

#include "stm32f10x.h"

// PA1 ��Ϊadc�ɼ�ͨ�� ����ص�λ��
#define ADC_GPIO_PORT				GPIOA
#define ADC_GPIO_PIN				GPIO_Pin_1
#define ADC_GPIO_RCC				RCC_APB2Periph_GPIOA
#define ADC_GPIO_APB_FUN    RCC_APB2PeriphClockCmd

// ѡ������Ҫ�õ�ADCͨ��
#define ADCx 							  ADC1	
#define ADC_RCC 					  RCC_APB2Periph_ADC1	
#define ADC_APB_FUN 			  RCC_APB2PeriphClockCmd					

// ADC ͨ���궨��
#define ADC_CHANNEL 			  ADC_Channel_1

#define ADC_IRQ 						ADC1_2_IRQn
#define ADC_IRQHandler 			ADC1_2_IRQHandler

void ADCx_GPIO_Init(void);

void ADCx_Mode_Config(void);

float GetValue();

#endif