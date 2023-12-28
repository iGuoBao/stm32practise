#include "exti.h"

extern float  ADC_ConvertedValue; // from ADC


extern u8 buffer[BUFFER_SIZE];
extern u8 writeIndex;
extern u8 TIM4_100ms_step;

u8 work_status = 0;		// 0  1=auto
u8 fun_work_status = 0;		// 0  1=on
 u8 bidi_work_status;		// 0  1=on

//ProtocolFrame_3phase_voltage frame;

// 突然意识到  虽然很好对照优先级，但是后续不方便，还是需要写到各个的NVCI下
static void NVCI_Config()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);							

	NVIC_InitTypeDef NVIC_InitStructure;
	// EXTI4--KEY0 
	NVIC_InitStructure.NVIC_IRQChannel = KEY0_EXTI_IRQ;					
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
	NVIC_Init(&NVIC_InitStructure);														
	// EXTI3--KEY1
	NVIC_InitStructure.NVIC_IRQChannel = KEY1_EXTI_IRQ;				
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
	NVIC_Init(&NVIC_InitStructure);															
	// EXTI2--KEY2
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_EXTI_IRQ;					
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
	NVIC_Init(&NVIC_InitStructure);															
	// EXTI0--WKUP
	NVIC_InitStructure.NVIC_IRQChannel = WKUP_EXTI_IRQ;					
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
	NVIC_Init(&NVIC_InitStructure);		
	// USART
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
	// USART2
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
	//RTC
	/*
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;		//RTC全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;	//先占优先级1位,从优先级3位
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;	//先占优先级0位,从优先级4位
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//使能该通道中断
	NVIC_Init(&NVIC_InitStructure);		//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	*/
	// TIM4
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;		//RTC全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	//先占优先级1位,从优先级3位
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	//先占优先级0位,从优先级4位
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//使能该通道中断
	NVIC_Init(&NVIC_InitStructure);		//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

void EXTI_Key_Config(void)
{
	RCC_APB2PeriphClockCmd(KEY0_EXTI_RCC,ENABLE);										
	GPIO_EXTILineConfig(KEY0_EXTI_PORTSOURCE, KEY0_EXTI_PINSOURCE); 
	NVCI_Config();																
}	

void EXTI_USARTn_Config(u8 number,u32 b)
{
	USARTn_Init(number,b);
}

void USART1_IRQHandler(void)                
{
	if (USART_GetFlagStatus(USART1, USART_IT_RXNE) != RESET)
	{
		buffer[writeIndex] = USART_ReceiveData(USART1);		// 将数据存储到缓冲区
		
		writeIndex++;
		USART_ClearITPendingBit(USART1, USART_IT_RXNE); // 清除中断标志位
	}
} 	
void USART2_IRQHandler(void)                
{
	if (USART_GetFlagStatus(USART2, USART_IT_RXNE) != RESET)
	{
		buffer[writeIndex] = USART_ReceiveData(USART2);		// 将数据存储到缓冲区
		
		writeIndex++;
		USART_ClearITPendingBit(USART2, USART_IT_RXNE); // 清除中断标志位
	}
} 	


void KEY0_IRQHandler(void)	
{
	if (EXTI_GetITStatus(KEY0_EXTI_LINE) != RESET)		
	{
		if (IsKeyPressed(KEY0_PORT,KEY0_PIN))
		{

			work_status = !work_status;
			/*
			writeIndex = 0;
			ProtocolFrame_LYTHR30EN frame;
			f_ProtocolFrame_LYTHR30EN(&frame,buffer);
			printf("\n");
			//printf("t=%d.%d C\n", (buffer[3] * 256 + buffer[4]) / 10 , buffer[4] % 10);
			//printf("s=%d.%d V\n", (buffer[5] * 256 + buffer[6]) / 10 , buffer[6] % 10);
			//printf("t=%d.%d C\n", (frame.DATA[0] * 256 + frame.DATA[1]) / 10, frame.DATA[1] % 10);
			*/
		}
	}
	EXTI_ClearITPendingBit(KEY0_EXTI_LINE);
}

void KEY1_IRQHandler(void)
{
	if (EXTI_GetITStatus(KEY1_EXTI_LINE) != RESET && IsKeyPressed(KEY1_PORT,KEY1_PIN))			
	{
		if (IsKeyPressed(KEY1_PORT,KEY1_PIN))
		{
			bidi_work_status = 2;
			if (work_status == 0) fun_work_status = 0;


			//writeIndex = 0;
			//TIM4_100ms_step = 0;
			//TIM_SetCounter(TIM4,0);
			//RS485_send_cmd(read_3phase_voltage,18);
			//RS485_send_cmd(read_DCFU02,6);
			//RS485_send_cmd(read_LYTHR30EN,9);
			//TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
			
			//RS485_send_cmd_flag = 1;
		}
		
	}
	EXTI_ClearITPendingBit(KEY1_EXTI_LINE);
}

void KEY2_IRQHandler(void)
{
	if (EXTI_GetITStatus(KEY2_EXTI_LINE) != RESET)			
	{
		if (IsKeyPressed(KEY2_PORT,KEY2_PIN))
		{
			if (bidi_work_status == 0)
			{
				RS485_send_cmd(send_addr1_ON_BIBD180,9);
				bidi_work_status = 1;
			}
			else
			{
				RS485_send_cmd(send_addr1_OFF_BIBD180,9);
				bidi_work_status = 0;
			}
			
				/*
				// key2 debug
				// 把数组放进buffer 01  03  04  00  FA  01  F8  DA  10
				buffer[0] = 0x01;
				buffer[1] = 0x03;
				buffer[2] = 0x04;
				buffer[3] = 0x00;
				buffer[4] = 0xFA;
				buffer[5] = 0x01;
				buffer[6] = 0xF8;
				buffer[7] = 0xDA;
				buffer[8] = 0x10;
				*/

			
		}
		EXTI_ClearITPendingBit(KEY2_EXTI_LINE);
	}
	
}

void WKUP_IRQHandler(void)
{
	if (EXTI_GetITStatus(WKUP_EXTI_LINE) != RESET)		
	{
		//DO
		bidi_work_status = 2;
		if (work_status == 0) fun_work_status = 1;

		EXTI_ClearITPendingBit(WKUP_EXTI_LINE);
	}
}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) 
  	{
		TIM4_100ms_step++;
		if (TIM4_100ms_step>5 && RS485_send_cmd_flag)
		{
			// 超时错误 500ms延时或没有收到正确停止位0x0D
			printf("no echo\r\n");

			TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
			TIM4_100ms_step = 0;
		}
	}
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //清除TIMx更新中断标志 
}





/*
// RTC 秒中断
void RTC_IRQHandler(void)
{
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
	{
		printf("RTC Time:%d-%d-%d %d:%d:%d\r\n",
		calendar.w_year,
		calendar.w_month,
		calendar.w_date,
		calendar.hour,
		calendar.min,
		calendar.sec);//输出闹铃时间	

		RTC_Get();//更新时间  

		RTC_ClearITPendingBit(RTC_IT_SEC);
	}

	
}*/

