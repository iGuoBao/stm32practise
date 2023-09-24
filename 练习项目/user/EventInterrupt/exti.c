#include "exti.h"
#include "Button.h"
#include "LED.h"

void EXTI_Key_Config(void)
{
	
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	// 选择作为外部中断线路
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4); // EXTI0 与引脚映射
	

	// EXTI0--KEY0  中断配置

	//EXTI4 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//EXTI4中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器		
	
	
	
	
	// 配置 EXTI0
	// GPIO_EXTILineConfig(KEY0_EXTI_PORTSOURCE, KEY0_EXTI_PINSOURCE); // EXTI0 与引脚映射
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;									    // KEY0 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;							// EXTI0 为中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;					// 下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;												// 使能
	EXTI_Init(&EXTI_InitStructure);																	// 包装完毕
}	
	





void EXTI4_IRQHandler(void)	// 中断
{
	
	//GPIO_WriteBit(LED0_PORT, LED0_PIN, !GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN));		// 取反

	// 中断进不去
	if (EXTI_GetITStatus(EXTI_Line4) != RESET) //确保是否产生了 EXTI Line 中断
	{
		if(IsKeyPressed(KEY0_PORT,KEY0_PIN))
		{
			GPIO_WriteBit(LED0_PORT, LED0_PIN, !GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN));		// 取反
		}
		
		//清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}