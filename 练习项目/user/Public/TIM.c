#include "TIM.h"

void BASIC_TIM3_Config(void)
{
	if (1){
		// 开时钟
		BASIC_TIM4_APBxClock_FUN(BASIC_TIM4_CLK, ENABLE);	
		
		// 基础定时器时钟结构体
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		// TIM3配置
		TIM_TimeBaseStructure.TIM_Period = 0;												// 刚好数1us
		TIM_TimeBaseStructure.TIM_Prescaler = 71;										//  1M
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// 向上计数
		TIM_TimeBaseInit(BASIC_TIM4, &TIM_TimeBaseStructure); 
		
		TIM_Cmd(Beep_PWM_TIMx, ENABLE);	// 使能
	}
	

}

void BASIC_TIM4_Config(void)
{
		// 开时钟
	BASIC_TIM4_APBxClock_FUN(BASIC_TIM4_CLK, ENABLE);	
	
		// 基础定时器时钟结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	// TIM4配置
	TIM_TimeBaseStructure.TIM_Period = 0;												// 刚好数1us
	TIM_TimeBaseStructure.TIM_Prescaler = 71;										//  1M
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 向上计数
	TIM_TimeBaseInit(BASIC_TIM4, &TIM_TimeBaseStructure); 
	
	TIM_Cmd(Beep_PWM_TIMx, ENABLE);	// 使能
	
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
	// TIM6配置
	TIM_TimeBaseStructure.TIM_Period = 9999;					  			// 自动重装值
	TIM_TimeBaseStructure.TIM_Prescaler = 71;					 		  // 预分频系数 (71+1)=72  (72M/s) / 72 = 1M/s -> 1K/s中断    
	TIM_TimeBaseInit(BASIC_TIM6, &TIM_TimeBaseStructure);   // 包装
	
	TIM_ClearFlag(BASIC_TIM6, TIM_FLAG_Update);		  	  // 清除标志位
	TIM_Cmd(BASIC_TIM6, ENABLE);										  // 定时器使能

}

