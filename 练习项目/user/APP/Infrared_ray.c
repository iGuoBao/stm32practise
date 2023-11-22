#include "infrared_ray.h"

int Infrared_ray_Receive_Data[16];


u8 Infrared_ray_first_receive_flag; // ��һ�ν��� ��־
u8 Infrared_ray_Receive_bit;

u32 Infrared_ray_time_steps_up;
u32 Infrared_ray_time_steps_down;


void Infrared_ray_Init()
{
	printf("init....");

	RCC_APB2PeriphClockCmd(Infrared_ray_Receive_RCC | RCC_APB2Periph_AFIO, ENABLE); 	
	RCC_APB1PeriphClockCmd(infrared_ray_TIMx_RCC, ENABLE);
	
	//IO�ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	//�������IO����
	GPIO_InitStructure.GPIO_Pin = Infrared_ray_Receive_PIN;  		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ; 		
	GPIO_Init(Infrared_ray_Receive_PORT, &GPIO_InitStructure);
	
		// ͼ���㷴������  ֮ǰ����дTIM��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Period = 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;   //��Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(infrared_ray_TIMx, &TIM_TimeBaseStructure);
	TIM_Cmd(infrared_ray_TIMx, ENABLE);	// ʹ��
	
	//---
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	TIM_ICInitStructure.TIM_Channel = infrared_ray_TIMx_Channel;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;		// 2
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; // ֱ������Դ
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;						// Ԥ��Ƶ1  1m
	TIM_ICInitStructure.TIM_ICFilter = 0x0;		// ?�˲�ֵ����
	TIM_ICInit(infrared_ray_TIMx, &TIM_ICInitStructure);

	TIM_ITConfig(infrared_ray_TIMx, TIM_IT_CC4, ENABLE);// ʹ��TIM4�����ж�
	
	
	//�ж�����
	EXTI_InitTypeDef EXTI_InitStructure;
	
	EXTI_ClearITPendingBit(Infrared_ray_Receive_EXTI_LINE);
	GPIO_EXTILineConfig(Infrared_ray_Receive_EXTI_PORTSOURCE, Infrared_ray_Receive_EXTI_PINSOURCE);  
	EXTI_InitStructure.EXTI_Line = 		Infrared_ray_Receive_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = 		EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);




}


