#include "exti.h"

extern float  ADC_ConvertedValue; // from ADC

extern u8 read_3phase_voltage[];  
extern u8 buffer[BUFFER_SIZE];
extern u8 writeIndex;

extern u8 TIM6_100ms_step;


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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
	// TIM6
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;						//定时器中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;			//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	

	
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


// 中断函数定义

void USART1_IRQHandler(void)                
{
	if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)
	{
		//USART_ReceiveData(USART1);
		//buffer[writeIndex++] = USART_ReceiveData(USART1);		// 将数据存储到缓冲区
		if(USART_ReceiveData(USART1) == 1)
		{
			ToggleLED(0);
		}
  	USART_ClearITPendingBit(USART1, USART_IT_RXNE); // 清除中断标志位
		//if(writeIndex >=128) writeIndex = 0;
	}
} 	
void USART2_IRQHandler(void)                
{
	if (USART_GetFlagStatus(USART2, USART_IT_RXNE) != RESET)
	{
		// 接收usart2数据
		buffer[writeIndex++] = USART_ReceiveData(USART2);		// 将数据存储到缓冲区
		if(writeIndex >=128) writeIndex = 0;
		printf("%c",writeIndex);
		// 按照协议 返回数据长度30
		if (writeIndex == 30 - 1)
		{
			// 打印这30个数据
			for (int i = 0; i < 30; i++)
			{
				printf("%c", buffer[i]);
			}
			writeIndex = 0;
		}
		USART_ClearITPendingBit(USART2, USART_IT_RXNE); // 清除中断标志位
	}
} 	


void KEY0_IRQHandler(void)	
{
	if (EXTI_GetITStatus(KEY0_EXTI_LINE) != RESET)		
	{
		if(IsKeyPressed(KEY0_PORT,KEY0_PIN))
		{
			
		}
		EXTI_ClearITPendingBit(KEY0_EXTI_LINE);
	}
}

void KEY1_IRQHandler(void)
{
	if (EXTI_GetITStatus(KEY1_EXTI_LINE) != RESET && IsKeyPressed(KEY1_PORT,KEY1_PIN))			
	{
		printf("KEY1 PUSH\r\n");
		TIM6_100ms_step = 0;
		TIM_SetCounter(TIM6,0);
		TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
		TIM_Cmd(TIM6,ENABLE);

		//send read_3phase_voltage数组 用usart2
		RS485_send_cmd(read_3phase_voltage,18);


		EXTI_ClearITPendingBit(KEY1_EXTI_LINE);
	}
}

void KEY2_IRQHandler(void)
{
	if (EXTI_GetITStatus(KEY2_EXTI_LINE) != RESET)			
	{
		if(IsKeyPressed(KEY2_PORT,KEY2_PIN))
		{
			NVIC_SetPendingIRQ(USART2_IRQn);
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

void TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //检查TIM6更新中断发生与否
  	{
		TIM6_100ms_step++;
		if (TIM6_100ms_step>=5)
		{
			//erro no echo
			printf("no echo\r\n");
			TIM_Cmd(TIM6,DISABLE);
			TIM6_100ms_step = 0;
		}
	}
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //清除TIMx更新中断标志 
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


// RTC 秒中断
void RTC_IRQHandler(void)
{
	showTimeToScreen();
	
}