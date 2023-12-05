#include "exti.h"

extern float  ADC_ConvertedValue; // from ADC


extern u8 buffer[BUFFER_SIZE];
extern u8 writeIndex;
extern u8 TIM4_100ms_step;


ProtocolFrame_3phase_voltage frame;

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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
	NVIC_Init(&NVIC_InitStructure);		
	// USART
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
	// USART2
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	

	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;		//RTC全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;	//先占优先级1位,从优先级3位
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;	//先占优先级0位,从优先级4位
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

		

  		USART_ClearITPendingBit(USART1, USART_IT_RXNE); // 清除中断标志位

	}
} 	
void USART2_IRQHandler(void)                
{
	if (USART_GetFlagStatus(USART2, USART_IT_RXNE) != RESET)
	{
		buffer[writeIndex] = USART_ReceiveData(USART2);		// 将数据存储到缓冲区
		
		// 接到停止位   
		if (buffer[writeIndex] == 0x0D && writeIndex >= 1)
		//if (writeIndex == 36 -1)
		{
			//封装数据
			RS485_send_cmd_flag = 0;
			
			//ProtocolFrame_DCFU02 frame;
			f_ProtocolFrame_3phase_voltage(frame,buffer);


			// 清除缓冲区
			for(u8 i = 0;i < writeIndex;i++)
			{
				buffer[i] = 0;
			}
			writeIndex = 0;

			// 6
			printf("%2x %2x %2x %2x %2x %2x", 
				frame.SOI,
				frame.VER,
				frame.ADR,
				frame.CID1,
				frame.CID2,
				frame.LENGTH_LENID
				);
			printf("\n");


		}
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
			for (u8 i = 0;i < writeIndex;i++)
			{
				printf("%x", buffer[i]);
				buffer[i] = 0;
			}
			writeIndex = 0;
			printf("\n");
			
		}
		EXTI_ClearITPendingBit(KEY0_EXTI_LINE);
	}
}

void KEY1_IRQHandler(void)
{
	if (EXTI_GetITStatus(KEY1_EXTI_LINE) != RESET && IsKeyPressed(KEY1_PORT,KEY1_PIN))			
	{
		if (IsKeyPressed(KEY1_PORT,KEY1_PIN))
		{
			writeIndex = 0;
			TIM4_100ms_step = 0;
			TIM_SetCounter(TIM4,0);
			TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
			TIM_Cmd(TIM4,ENABLE);


			RS485_send_cmd(read_3phase_voltage,18);
			//RS485_send_cmd(read_DCFU02,6);

			RS485_send_cmd_flag = 1;

			
		}
		EXTI_ClearITPendingBit(KEY1_EXTI_LINE);
	}
}

void KEY2_IRQHandler(void)
{
	if (EXTI_GetITStatus(KEY2_EXTI_LINE) != RESET)			
	{
		if (IsKeyPressed(KEY2_PORT,KEY2_PIN))
		{
			for (u8 i = 0;i < writeIndex;i++)
			{
				printf("%x ", buffer[i]);
				buffer[i] = 0;
			}
			writeIndex = 0;
			printf("\n");
		}
		EXTI_ClearITPendingBit(KEY2_EXTI_LINE);

	}
}

void WKUP_IRQHandler(void)
{

	if (EXTI_GetITStatus(WKUP_EXTI_LINE) != RESET)		
	{
		//DO

		
		EXTI_ClearITPendingBit(WKUP_EXTI_LINE);
	}

}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) 
  	{
		TIM4_100ms_step++;
		
		if (TIM4_100ms_step>=5 && RS485_send_cmd_flag)
		{
			// 超时错误 500ms延时或没有收到正确停止位0x0D
			printf("no echo\r\n");

			TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
			TIM_Cmd(TIM4,DISABLE);
			TIM4_100ms_step = 0;
		}
		
	}
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //清除TIMx更新中断标志 
}


void ADC_IRQHandler(void)
{
	if (ADC_GetITStatus(ADCx,ADC_IT_EOC)==SET)
	{
		u16 temp;
		// 读取 ADC 的转换值
		temp = ADC_GetConversionValue(ADCx);
		ADC_ConvertedValue = (float)temp / 4096 * 3.3;  // 2^12  3.3参考电压
		
		ADC_ClearITPendingBit(ADCx,ADC_IT_EOC);
	
		ADC_Cmd(ADCx,DISABLE);
		ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
	}

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

