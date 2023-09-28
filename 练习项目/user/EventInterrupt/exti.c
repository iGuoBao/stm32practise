#include "exti.h"

static void NVCI_Config()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);							// 配置组别 2
	
	// 结构体使用
	NVIC_InitTypeDef NVIC_InitStructure;
	// EXTI0--KEY0  中断配置
	NVIC_InitStructure.NVIC_IRQChannel = KEY0_EXTI_IRQ;					// 配置中断源 EXTI4通道  KEY0_EXTI_IRQ----EXTI0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		// 抢占优先级1  pree
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					// 子优先级1		sub
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							// 使能
	NVIC_Init(&NVIC_InitStructure);															// 包装完毕
}

void EXTI_Key_Config(void)
{
	RCC_APB2PeriphClockCmd(KEY0_EXTI_RCC,ENABLE);	// 复用时钟开启
	GPIO_EXTILineConfig(KEY0_EXTI_PORTSOURCE, KEY0_EXTI_PINSOURCE); //选择作为外部中断线路  EXTI0 与引脚映射
	NVCI_Config();		// NVCI配置
	
	// EXTI结构体
	EXTI_InitTypeDef EXTI_InitStructure;
	// 配置 EXTI0
	GPIO_EXTILineConfig(KEY0_EXTI_PORTSOURCE, KEY0_EXTI_PINSOURCE); // EXTI0 与引脚映射
	EXTI_InitStructure.EXTI_Line = KEY0_EXTI_LINE;									// KEY0 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;							// EXTI0 为中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;					// 上升下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;												// 使能
	EXTI_Init(&EXTI_InitStructure);																	// 包装完毕
}	
	


void KEY0_IRQHandler(void)	// 中断
{
	if (EXTI_GetITStatus(KEY0_EXTI_LINE) != RESET)			 //确保是否产生了 EXTI Line 中断
	{
		if(IsKeyPressed(KEY0_PORT,KEY0_PIN))
		{
			GPIO_WriteBit(LED0_PORT, LED0_PIN, !GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN));		// 取反
			delay_ms(1000);
			GPIO_WriteBit(LED0_PORT, LED0_PIN, !GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN));		// 取反
		}
		//清除中断标志位
		EXTI_ClearITPendingBit(KEY0_EXTI_LINE);
	}
}