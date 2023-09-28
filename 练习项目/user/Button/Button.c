#include "Button.h"

#include "exti.h"
#include "LED.h"
#include "SysTick.h"

void KEY_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 	// GPIO结构体
	EXTI_InitTypeDef EXTI_InitStructure;	// EXTI结构体
	
  RCC_APB2PeriphClockCmd(KEY0_EXTI_RCC|KEY1_EXTI_RCC|KEY2_EXTI_RCC|WKUP_EXTI_RCC, ENABLE); // 使能端口的时钟
  
  // 配置KEY0的GPIO参数
  GPIO_InitStructure.GPIO_Pin = KEY0_PIN; 							// 设置引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 			  // 设置为上拉输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	  // 设置速度为50MHz
  GPIO_Init(KEY0_PORT, &GPIO_InitStructure); 					  // 初始化GPIOA
	GPIO_WriteBit(KEY0_PORT, KEY0_PIN,1);									// 上拉 则需要输出高电平
  // EXTI4
	GPIO_EXTILineConfig(KEY0_EXTI_PORTSOURCE, KEY0_EXTI_PINSOURCE); 
	EXTI_InitStructure.EXTI_Line = KEY0_EXTI_LINE;									
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;							
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;					
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;												
	EXTI_Init(&EXTI_InitStructure);	
	
	
  // 配置KEY1的GPIO参数，与KEY0类似
  GPIO_InitStructure.GPIO_Pin = KEY1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(KEY1_PORT, &GPIO_InitStructure);
	GPIO_WriteBit(KEY1_PORT, KEY1_PIN,1);									  // 上拉 则需要输出高电平
  // EXTI3
	GPIO_EXTILineConfig(KEY1_EXTI_PORTSOURCE, KEY1_EXTI_PINSOURCE); 
	EXTI_InitStructure.EXTI_Line = KEY1_EXTI_LINE;									
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;							
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;					
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;											
	EXTI_Init(&EXTI_InitStructure);	
	
	
  // 配置KEY2的GPIO参数，与KEY0类似
  GPIO_InitStructure.GPIO_Pin = KEY2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(KEY2_PORT, &GPIO_InitStructure);
	GPIO_WriteBit(KEY2_PORT, KEY2_PIN,1);									  // 上拉 则需要输出高电平
	// EXTI2
	GPIO_EXTILineConfig(KEY2_EXTI_PORTSOURCE, KEY2_EXTI_PINSOURCE); 
	EXTI_InitStructure.EXTI_Line = KEY2_EXTI_LINE;								
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;						
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;				
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;											
	EXTI_Init(&EXTI_InitStructure);		
	
	
	  // 配置WKUP的GPIO参数，与KEY0类似
  GPIO_InitStructure.GPIO_Pin = WKUP_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;						// 下拉输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(WKUP_PORT, &GPIO_InitStructure);
	//-----GPIO_WriteBit(WKUP_PORT, WKUP_PIN,0);									  // 下拉 则需要输出低电平						
	// EXTI0
	GPIO_EXTILineConfig(WKUP_EXTI_PORTSOURCE, WKUP_EXTI_PINSOURCE);
	EXTI_InitStructure.EXTI_Line = WKUP_EXTI_LINE;										
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;							
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;				
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;											
	EXTI_Init(&EXTI_InitStructure);
}




int IsKeyPressed(GPIO_TypeDef * KEY_PORT,uint16_t KEY_PIN)
{
	// 通过判断输出模式 区分不同按钮设计从而正确判断是否按下。
	//
	// 引脚输出模式
	if(GPIO_ReadOutputDataBit(KEY_PORT, KEY_PIN) == 1){
		delay_ms(15);										// 去抖
		if(GPIO_ReadOutputDataBit(KEY_PORT, KEY_PIN) == 1)			
		{
			return !GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN); // 返回引脚电平的反值 若按下为1
		}
		else if(GPIO_ReadOutputDataBit(KEY_PORT, KEY_PIN) == 0) 								// 下拉输入模式
		{
			return GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN);  // 返回引脚电平的原值 若按下为1
		}
	}
	return 0;
}
