#include "exti.h"

extern float  ADC_ConvertedValue; // from ADC
extern u8 music_station;

extern u8 Infrared_ray_Receive_over_flag, Infrared_ray_Receive_flag, Infrared_ray_synchronous_Receive_flag;
extern u8 Infrared_ray_Receive_Data_Index;
extern int Infrared_ray_Receive_Data[];
extern u32 Infrared_ray_timeus_up, Infrared_ray_timeus_down;


// 突然意识到  虽然很好对照优先级，但是后续不方便，还是需要写到各个的NVCI下
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
	NVIC_Init(&NVIC_InitStructure);															
	// EXTI2--KEY2
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_EXTI_IRQ;					
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
	NVIC_Init(&NVIC_InitStructure);															
	// EXTI0--WKUP
	NVIC_InitStructure.NVIC_IRQChannel = WKUP_EXTI_IRQ;					
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
	NVIC_Init(&NVIC_InitStructure);		
	//USART
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
	// TIM6
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;						//定时器中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;				//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	
	// ADC PA1
	NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQ;							//定时器中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;				//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	
	// IR LED
	//NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;   //打开全局中断 !< External Line[9:5] Interrupts 
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级为0
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 	 //响应优先级为1
	//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   //使能
	//NVIC_Init(&NVIC_InitStructure);
	// TIM4
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;						//定时器中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;				//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	

}

void EXTI_Key_Config(void)
{
	RCC_APB2PeriphClockCmd(KEY0_EXTI_RCC,ENABLE);										
	GPIO_EXTILineConfig(KEY0_EXTI_PORTSOURCE, KEY0_EXTI_PINSOURCE); 
	NVCI_Config();																
}	

void EXTI_USART1_Config(u32 b)
{
	USART1_Init(b);
	NVCI_Config();		// NVCI
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

// 中断函数定义

void EXTI3_IRQHandler(void)
{
	/*
	if (EXTI_GetITStatus(KEY1_EXTI_LINE) != RESET)			
	{
		if(IsKeyPressed(KEY1_PORT,KEY1_PIN))
		{
			Beep_Init(PWM);
			ToggleLED(1);
			delay_ms(1000);
			ToggleLED(1);
			Beep_Init(DOWN);
		}
		EXTI_ClearITPendingBit(KEY1_EXTI_LINE);
	}
	*/
	
}

void USART1_IRQHandler(void)                
{
	if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)
	{
		//USART_ReceiveData(USART1);
		//buffer[writeIndex++] = USART_ReceiveData(USART1);		// 将数据存储到缓冲区
		if(USART_ReceiveData(USART1) == 1)
		{
			float value = GetValue();

			int intValue = (int)value;
			int decimalPart = (int)((value - intValue) * 100); 

			printf("data=%f\r\n", value);
			ADC_Cmd(ADCx,DISABLE);
			ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);		
		}
		
  	USART_ClearITPendingBit(USART1, USART_IT_RXNE); // 清除中断标志位
		//if(writeIndex >=128) writeIndex = 0;
	}
} 	

void KEY0_IRQHandler(void)	
{
	if (EXTI_GetITStatus(KEY0_EXTI_LINE) != RESET)		
	{
		EXTI_ClearITPendingBit(KEY0_EXTI_LINE);
		if(IsKeyPressed(KEY0_PORT,KEY0_PIN))
		{
			
		}
	}
}

void KEY2_IRQHandler(void)
{
	if (EXTI_GetITStatus(KEY2_EXTI_LINE) != RESET)			
	{
		EXTI_ClearITPendingBit(KEY2_EXTI_LINE);
		if(IsKeyPressed(KEY2_PORT,KEY2_PIN))
		{


		}
	}
}

void WKUP_IRQHandler(void)
{

	if (EXTI_GetITStatus(WKUP_EXTI_LINE) != RESET)		
	{
		
	}
	EXTI_ClearITPendingBit(WKUP_EXTI_LINE);
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //检查TIM6更新中断发生与否
  {
		show_voltmeter_chart_value();
		if(ADC_GetSoftwareStartConvStatus(ADC1)==ENABLE)
		{
			ADC_Cmd(ADCx,DISABLE);
		}
		else if(ADC_GetSoftwareStartConvStatus(ADC1)==DISABLE)
		{
			ADC_Cmd(ADCx,ENABLE);
		}
	}
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //清除TIMx更新中断标志 
}

void TIM4_IRQHandler(void)
{
	// tim4 溢出中断
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) 
    {
		/*
		// 引脚上升沿 
		if (Infrared_ray_Receive_flag)
		{
			printf("up\r\n");
			Infrared_ray_timeus_down++;
		}
		
		// 引脚下降沿  开始数up
		else if (!Infrared_ray_Receive_flag)
		*/

		// debug 上升沿后读取 一直是0 所以flag恒定0 暂时不能优化
		Infrared_ray_timeus_up++;

		if (Infrared_ray_timeus_up > 1000 && Infrared_ray_Receive_over_flag)  // 100ms	 1s = 10000 *100us 
		{
			printf("100ms time out\r\n");
			Infrared_ray_Receive_over_flag = 0; 
			Infrared_ray_Receive_Data_Index = 0;

			Infrared_ray_Data_Struct Infrared_ray_Data = Decode_Infrared_ray_Receive_Data();
			printf("Infrared_ray_Data=%2x\r\n", Infrared_ray_Data.data);
		}
	  	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //清除TIMx更新中断标志
    }

	// tim4 通道4捕获中断
	if(TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)
	{
		// 读取通道4 gpio电平  改变上升沿下降沿flag ==0
		Infrared_ray_Receive_flag = GPIO_ReadInputDataBit(Infrared_ray_Receive_PORT, Infrared_ray_Receive_PIN);

		// 之前没开始接受的话 下降沿  溢出中断开启开始接收 接受位-置1
		if (!Infrared_ray_Receive_flag && !Infrared_ray_Receive_over_flag)
		{
			Infrared_ray_timeus_up = 0;
			//Infrared_ray_timeus_down = 0;
			Infrared_ray_synchronous_Receive_flag = 0;
			Infrared_ray_Receive_Data_Index = 0;
			Infrared_ray_Receive_over_flag = 1; 
		}
		// 开始接受
		else if (!Infrared_ray_Receive_flag && Infrared_ray_Receive_over_flag) 
		{
			// 同步过
			
			if (Infrared_ray_synchronous_Receive_flag)
			{
				Infrared_ray_Receive_Data[Infrared_ray_Receive_Data_Index++] = Infrared_ray_timeus_up;
				Infrared_ray_timeus_up = 0;
				/*
				if(Infrared_ray_timeus_up >= 10 && Infrared_ray_timeus_up <= 15) // 1125us  100us
				{
					//逻辑0 数据存放到Infrared_ray_Receive_Data[]数组
					Infrared_ray_Receive_Data[Infrared_ray_Receive_Data_Index++] = 7;
				}
				else if(Infrared_ray_timeus_up >=18 && Infrared_ray_timeus_up <= 24)	// 2250us
				{
					//逻辑1 数据存放到Infrared_ray_Receive_Data[]数组
					Infrared_ray_Receive_Data[Infrared_ray_Receive_Data_Index++] = 8;
				}
				//清空时间记时 错误的数据
				Infrared_ray_timeus_up = 0;
				//Infrared_ray_timeus_down = 0;
				*/
			}
			// 没同步
			else
			{
				if(Infrared_ray_timeus_up >= 126 && Infrared_ray_timeus_down <= 138) // 同步 13.5
				{
					Infrared_ray_synchronous_Receive_flag = 1;
					Infrared_ray_Receive_over_flag = 1;
					Infrared_ray_timeus_up = 0;
					//Infrared_ray_timeus_down = 0;
					Infrared_ray_Receive_Data_Index = 0;
				}
			}
		}
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);
	}
}

void TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //检查TIM6更新中断发生与否
  {
		show_voltmeter_chart_value();
		if(ADC_GetSoftwareStartConvStatus(ADC1)==ENABLE)
		{
			ADC_Cmd(ADCx,DISABLE);
		}
		else if(ADC_GetSoftwareStartConvStatus(ADC1)==DISABLE)
		{
			ADC_Cmd(ADCx,ENABLE);
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

// RTC 计时器
void RTC_IRQHandler(void)
{
	showTimeToScreen();
}


