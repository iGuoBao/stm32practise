#include "exti.h"


u16 USART1_RX_STA=0;       //����״̬���
u8 USART1_RX_BUF[USART1_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.


static void NVCI_Config()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);							// ������� 2
	
	// �ṹ��ʹ��
	NVIC_InitTypeDef NVIC_InitStructure;
	// EXTI4--KEY0  �ж�����
	NVIC_InitStructure.NVIC_IRQChannel = KEY0_EXTI_IRQ;					// �����ж�Դ EXTI4ͨ��  KEY0_EXTI_IRQ----EXTI0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		// ��ռ���ȼ�1  pree
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					// �����ȼ�1		sub
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							// ʹ��
	NVIC_Init(&NVIC_InitStructure);															// ��װ���
	// EXTI3--KEY1  �ж�����
	NVIC_InitStructure.NVIC_IRQChannel = KEY1_EXTI_IRQ;					// �����ж�Դ EXTI4ͨ��  KEY0_EXTI_IRQ----EXTI0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		// ��ռ���ȼ�1  pree
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					// �����ȼ�1		sub
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							// ʹ��
	NVIC_Init(&NVIC_InitStructure);															// ��װ���
	// EXTI2--KEY2  �ж�����
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_EXTI_IRQ;					// �����ж�Դ EXTI4ͨ��  KEY0_EXTI_IRQ----EXTI0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		// ��ռ���ȼ�1  pree
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					// �����ȼ�1		sub
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							// ʹ��
	NVIC_Init(&NVIC_InitStructure);															// ��װ���
	// EXTI0--WKUP  �ж�����
	NVIC_InitStructure.NVIC_IRQChannel = WKUP_EXTI_IRQ;					// �����ж�Դ EXTI4ͨ��  KEY0_EXTI_IRQ----EXTI0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		// ��ռ���ȼ�1  pree
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					// �����ȼ�1		sub
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							// ʹ��
	NVIC_Init(&NVIC_InitStructure);															// ��װ���
}


void EXTI_Key_Config(void)
{
	RCC_APB2PeriphClockCmd(KEY0_EXTI_RCC,ENABLE);										// ����ʱ�ӿ���
	GPIO_EXTILineConfig(KEY0_EXTI_PORTSOURCE, KEY0_EXTI_PINSOURCE); //ѡ����Ϊ�ⲿ�ж���·  EXTI0 ������ӳ��
	NVCI_Config();		// NVCI����
	
	// EXTI�ṹ��
	EXTI_InitTypeDef EXTI_InitStructure;
	// ���� EXTI4
	GPIO_EXTILineConfig(KEY0_EXTI_PORTSOURCE, KEY0_EXTI_PINSOURCE); // EXTI0 ������ӳ��
	EXTI_InitStructure.EXTI_Line = KEY0_EXTI_LINE;									// KEY0 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;							// EXTI0 Ϊ�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;					// �½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;												// ʹ��
	EXTI_Init(&EXTI_InitStructure);																	// ��װ���
	// ���� EXTI3
	GPIO_EXTILineConfig(KEY1_EXTI_PORTSOURCE, KEY1_EXTI_PINSOURCE); // EXTI0 ������ӳ��
	EXTI_InitStructure.EXTI_Line = KEY1_EXTI_LINE;									// KEY0 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;							// EXTI0 Ϊ�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;					// �½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;												// ʹ��
	EXTI_Init(&EXTI_InitStructure);																	// ��װ���
	// ���� EXTI2
	GPIO_EXTILineConfig(KEY2_EXTI_PORTSOURCE, KEY2_EXTI_PINSOURCE); // EXTI0 ������ӳ��
	EXTI_InitStructure.EXTI_Line = KEY2_EXTI_LINE;									// KEY0 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;							// EXTI0 Ϊ�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;					// �½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;												// ʹ��
	EXTI_Init(&EXTI_InitStructure);																	// ��װ���
	// ���� EXTI0
	GPIO_EXTILineConfig(WKUP_EXTI_PORTSOURCE, WKUP_EXTI_PINSOURCE); // EXTI0 ������ӳ��
	EXTI_InitStructure.EXTI_Line = WKUP_EXTI_LINE;										// KEY0 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;							// EXTI0 Ϊ�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;					// �����ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;												// ʹ��
	EXTI_Init(&EXTI_InitStructure);																	// ��װ���
}	

void EXTI_USART1_Config(void)
{
	NVCI_Config();		// NVCI����
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);// �²⣺ �����ж� ��������ж�
}





void KEY0_IRQHandler(void)	// �ж�
{
	if (EXTI_GetITStatus(KEY0_EXTI_LINE) != RESET)			 //ȷ���Ƿ������ EXTI Line �ж�
	{
		if(IsKeyPressed(KEY0_PORT,KEY0_PIN))
		{
			GPIO_WriteBit(LED1_PORT, LED1_PIN, !GPIO_ReadOutputDataBit(LED1_PORT, LED1_PIN));		// ȡ��
		}
		//����жϱ�־λ
		EXTI_ClearITPendingBit(KEY0_EXTI_LINE);
	}
}

<<<<<<< HEAD

void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 r;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
	{
		if (USART_ReceiveData(USART1) == 1)
		{
			GPIO_WriteBit(LED0_PORT, LED0_PIN, !GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN));		// ȡ��
		}
	} 
} 	

 


=======
void KEY1_IRQHandler(void)
{
		if (EXTI_GetITStatus(KEY1_EXTI_LINE) != RESET)			 //ȷ���Ƿ������ EXTI Line �ж�
	{
		if(IsKeyPressed(KEY1_PORT,KEY1_PIN))
		{
			Beep_On();
			delay_ms(200);
			Beep_Off();
			GPIO_SetBits(LED0_PORT, LED0_PIN);
			GPIO_SetBits(LED1_PORT, LED1_PIN);
		}
			//����жϱ�־λ
			EXTI_ClearITPendingBit(KEY1_EXTI_LINE);
	}
}

void KEY2_IRQHandler(void)
{
		if (EXTI_GetITStatus(KEY2_EXTI_LINE) != RESET)			 //ȷ���Ƿ������ EXTI Line �ж�
	{
		if(IsKeyPressed(KEY2_PORT,KEY2_PIN))
		{
			GPIO_WriteBit(LED0_PORT, LED0_PIN, !GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN));		// ȡ��
		}
		//����жϱ�־λ
		EXTI_ClearITPendingBit(KEY2_EXTI_LINE);
	}
}

void WKUP_IRQHandler(void)
{

		if (EXTI_GetITStatus(WKUP_EXTI_LINE) != RESET)			 //ȷ���Ƿ������ EXTI Line �ж�
	{

			Beep_On();
			delay_ms(200);
			Beep_Off();
			GPIO_ResetBits(LED0_PORT, LED0_PIN);
			GPIO_ResetBits(LED1_PORT, LED1_PIN);

		//����жϱ�־λ
		EXTI_ClearITPendingBit(WKUP_EXTI_LINE);
	}
}
>>>>>>> main
