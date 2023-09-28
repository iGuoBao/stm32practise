#include "exti.h"


u16 USART1_RX_STA=0;       
u8 USART1_RX_BUF[USART1_REC_LEN];     


static void NVCI_Config()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);							
	

	NVIC_InitTypeDef NVIC_InitStructure;
	// EXTI4--KEY0 
	NVIC_InitStructure.NVIC_IRQChannel = KEY0_EXTI_IRQ;					
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
	NVIC_Init(&NVIC_InitStructure);														
	// EXTI3--KEY1
	NVIC_InitStructure.NVIC_IRQChannel = KEY1_EXTI_IRQ;				
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
	NVIC_Init(&NVIC_InitStructure);															
	// EXTI2--KEY2
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_EXTI_IRQ;					
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
	NVIC_Init(&NVIC_InitStructure);															
	// EXTI0--WKUP
	NVIC_InitStructure.NVIC_IRQChannel = WKUP_EXTI_IRQ;					
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
	NVIC_Init(&NVIC_InitStructure);															
}



void EXTI_Key_Config(void)
{
	RCC_APB2PeriphClockCmd(KEY0_EXTI_RCC,ENABLE);										
	GPIO_EXTILineConfig(KEY0_EXTI_PORTSOURCE, KEY0_EXTI_PINSOURCE); 
	NVCI_Config();		
																
}	

void EXTI_USART1_Config(void)
{
	NVCI_Config();		// NVCI
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}


// 中断函数定义

void USART1_IRQHandler(void)                
{
	u8 r;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
	{
		if (USART_ReceiveData(USART1) == 1)
		{
			GPIO_WriteBit(LED0_PORT, LED0_PIN, !GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN));	
		}
	} 
} 	


void KEY0_IRQHandler(void)	
{
	if (EXTI_GetITStatus(KEY0_EXTI_LINE) != RESET)		
	{
		if(IsKeyPressed(KEY0_PORT,KEY0_PIN))
		{
			GPIO_WriteBit(LED1_PORT, LED1_PIN, !GPIO_ReadOutputDataBit(LED1_PORT, LED1_PIN));
		}

		EXTI_ClearITPendingBit(KEY0_EXTI_LINE);
	}
}

void KEY1_IRQHandler(void)
{
		if (EXTI_GetITStatus(KEY1_EXTI_LINE) != RESET)			
	{
		if(IsKeyPressed(KEY1_PORT,KEY1_PIN))
		{
			Beep_On();
			delay_ms(200);
			Beep_Off();
			GPIO_SetBits(LED0_PORT, LED0_PIN);
			GPIO_SetBits(LED1_PORT, LED1_PIN);
		}
		
			EXTI_ClearITPendingBit(KEY1_EXTI_LINE);
	}
}

void KEY2_IRQHandler(void)
{
		if (EXTI_GetITStatus(KEY2_EXTI_LINE) != RESET)			
	{
		if(IsKeyPressed(KEY2_PORT,KEY2_PIN))
		{
			GPIO_WriteBit(LED0_PORT, LED0_PIN, !GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN));		
		}
	
		EXTI_ClearITPendingBit(KEY2_EXTI_LINE);
	}
}

void WKUP_IRQHandler(void)
{

		if (EXTI_GetITStatus(WKUP_EXTI_LINE) != RESET)		
	{

			Beep_On();
			delay_ms(200);
			Beep_Off();
			GPIO_ResetBits(LED0_PORT, LED0_PIN);
			GPIO_ResetBits(LED1_PORT, LED1_PIN);

	
		EXTI_ClearITPendingBit(WKUP_EXTI_LINE);
	}
}

