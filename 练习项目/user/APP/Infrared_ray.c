#include "infrared_ray.h"

u8 Infrared_ray_synchronous_Receive_flag = 0;


u8 Infrared_ray_Receive_Data_Index;
u32 Infrared_ray_Receive_Data[300];


u8 Infrared_ray_first_receive_flag; // 第一次接收 标志
u8 Infrared_ray_Receive_bit;
u8 Infrared_ray_Receive_flag;

u32 Infrared_ray_timeus_up, Infrared_ray_timeus_down;


void Infrared_ray_init()
{
	printf("init....");
	RCC_APB2PeriphClockCmd(Infrared_ray_Receive_RCC, ENABLE); // GPIO复用时钟	
	RCC_APB1PeriphClockCmd(infrared_ray_TIMx_RCC, ENABLE);	  // 定时器时钟
	
	//IO结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	//红外接收IO配置
	GPIO_InitStructure.GPIO_Pin = Infrared_ray_Receive_PIN;  		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ; 		
	GPIO_Init(Infrared_ray_Receive_PORT, &GPIO_InitStructure);
	
	// 图方便反在这里  之前都是写TIM的
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	// TIM4配置 1us
	TIM_TimeBaseStructure.TIM_Prescaler = 0;   //预分频
	TIM_TimeBaseStructure.TIM_Period = 71;  //计数值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;   //分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(infrared_ray_TIMx, &TIM_TimeBaseStructure);
	TIM_Cmd(infrared_ray_TIMx, ENABLE);	// 使能
	
	//---
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	TIM_ICInitStructure.TIM_Channel = infrared_ray_TIMx_Channel;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;		// 上升下降沿捕获
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	// 直接输入源
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;			    // 预分频1  1m
	TIM_ICInitStructure.TIM_ICFilter = 0x0;		// ?滤波值设置
	TIM_ICInit(infrared_ray_TIMx, &TIM_ICInitStructure);

	TIM_ITConfig(infrared_ray_TIMx, TIM_IT_CC4, ENABLE);// 使能TIM4捕获中断
	
	/*
	//中断配置
	EXTI_InitTypeDef EXTI_InitStructure;
	
	EXTI_ClearITPendingBit(Infrared_ray_Receive_EXTI_LINE);
	GPIO_EXTILineConfig(Infrared_ray_Receive_EXTI_PORTSOURCE, Infrared_ray_Receive_EXTI_PINSOURCE);  
	EXTI_InitStructure.EXTI_Line = 	Infrared_ray_Receive_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = 	EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; // 上升下降捕获 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	*/



}


