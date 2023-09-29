#include "TIM.h"

#include "beep.h"
#include "exti.h"

extern int Reques_Ms;

void BASIC_TIM6_Config(void)
{
	// 开启定时器时钟,即内部时钟 CK_INT=72M
	BASIC_TIM6_APBxClock_FUN(BASIC_TIM6_CLK, ENABLE);
	
	// 基础定时器时钟结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	// TIM6配置
	TIM_TimeBaseStructure.TIM_Period = 1024;					// 自动重装值
	TIM_TimeBaseStructure.TIM_Prescaler = 71;					// 预分频系数 (71+1)=72  (72M/s) / 72 = 1M/s -> 1K/s中断    
	TIM_TimeBaseInit(BASIC_TIM6, &TIM_TimeBaseStructure); 
	
	TIM_ITConfig(BASIC_TIM6,TIM_IT_Update,ENABLE);		// 开启中断
	//TIM_ClearFlag(BASIC_TIM6, TIM_FLAG_Update);			// 清除标志位
	//TIM_Cmd(BASIC_TIM6, ENABLE);										// 定时器使能

}



void DelayMs(int Ms)
{
	Reques_Ms = Ms;
	TIM_ClearFlag(BASIC_TIM6, TIM_FLAG_Update);				// 清除标志位
	TIM_Cmd(BASIC_TIM6, ENABLE);											// 定时器使能
}