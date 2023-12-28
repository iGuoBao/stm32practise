#include "TIM.h"

u8 TIM4_100ms_step = 0;

void TIM3_CH2_PWM_Init(u16 per,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 开启时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);//改变指定管脚的映射	
	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //自动装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //分频系数
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);	
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC2Init(TIM3,&TIM_OCInitStructure); //输出比较通道2初始化
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable); //使能TIMx在 CCR2 上的预装载寄存器
	TIM_ARRPreloadConfig(TIM3,ENABLE);//使能预装载寄存器
	
	TIM_Cmd(TIM3,ENABLE); //使能定时器
		
}


void BASIC_TIM4_Config(void)
{
	// 开时钟
	BASIC_TIM4_APBxClock_FUN(BASIC_TIM4_CLK, ENABLE);	
	
	// 基础定时器时钟结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	// TIM4配置 1
	TIM_TimeBaseStructure.TIM_Period = 1 - 1;					// 自动重装值   PER = 1 000 000 / HZ
	TIM_TimeBaseStructure.TIM_Prescaler = 72 -1;				// 预分频系数  1440hz 估值
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 向上计数
	TIM_TimeBaseInit(BASIC_TIM4, &TIM_TimeBaseStructure); 
	
	TIM_ITConfig(BASIC_TIM4,TIM_IT_Update,DISABLE);	  	// 开启溢出中断
	TIM_Cmd(BASIC_TIM4, ENABLE);	// 使能
	
}

void SetBASIC_TIM4_Hz(int Hz)
{
	float Period = 1000000 / Hz; 
		// 基础定时器时钟结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	// TIM4配置
	TIM_TimeBaseStructure.TIM_Period = Period ;								
	TIM_TimeBaseStructure.TIM_Prescaler = 71;									
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 向上计数
	TIM_TimeBaseInit(BASIC_TIM4, &TIM_TimeBaseStructure); 
	
}

void BASIC_TIM6_Config(void)
{
	// 开启定时器时钟,即内部时钟 CK_INT=72M
	BASIC_TIM6_APBxClock_FUN(BASIC_TIM6_CLK, ENABLE);
	
	// 基础定时器时钟结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	// TIM6配置1000000/10000=100 10ms  100ms
	TIM_TimeBaseStructure.TIM_Period = 9999;					  			// 自动重装值
	TIM_TimeBaseStructure.TIM_Prescaler = 72 * 10 - 1;					 		  // 预分频系数 (71+1)=72  (72M/s) / 72 = 1M/s -> 1K/s中断    
	TIM_TimeBaseInit(BASIC_TIM6, &TIM_TimeBaseStructure);   // 包装
	
	TIM_ITConfig(BASIC_TIM6,TIM_IT_Update,ENABLE);	  	// 开启溢出中断
	TIM_ClearFlag(BASIC_TIM6, TIM_FLAG_Update);		  	// 清除标志位
	TIM_Cmd(BASIC_TIM6, ENABLE);						// 定时器使能

	// 
	//TIM_Cmd(BASIC_TIM6, DISABLE);						// 定时器使能
}

