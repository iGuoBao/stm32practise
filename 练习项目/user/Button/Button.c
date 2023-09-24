#include "Button.h"

#include "LED.h"


void KEY_init(void)
{
	// 定义一个GPIO初始化结构体变量
  GPIO_InitTypeDef GPIO_InitStructure; 
	
	// 使能三个端口的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); 
  
  // 配置KEY0的GPIO参数
  GPIO_InitStructure.GPIO_Pin = KEY0_PIN; 							// 设置引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 			  // 设置为上拉输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	  // 设置速度为50MHz
  GPIO_Init(KEY0_PORT, &GPIO_InitStructure); 					  // 初始化GPIOA
	// GPIO_WriteBit(KEY0_PORT, KEY0_PIN,1);									  // 上拉 则需要输出高电平
  
  // 配置KEY1的GPIO参数，与KEY0类似
  GPIO_InitStructure.GPIO_Pin = KEY1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(KEY1_PORT, &GPIO_InitStructure);
  
  // 配置KEY2的GPIO参数，与KEY0类似
  GPIO_InitStructure.GPIO_Pin = KEY2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(KEY2_PORT, &GPIO_InitStructure);
}


int IsKeyPressed(GPIO_TypeDef * KEY_PORT,uint16_t KEY_PIN)
{
	// 通过判断输出模式 区分不同按钮设计从而正确判断是否按下。
	//
	// 引脚输出模式
	if(GPIO_ReadOutputDataBit(KEY_PORT, KEY_PIN) == 1) 											// 上拉输入模式
	{
		return !GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN); // 返回引脚电平的反值 若按下为1
	}
	else if(GPIO_ReadOutputDataBit(KEY_PORT, KEY_PIN) == 0) 								// 下拉输入模式
	{
		return GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN);  // 返回引脚电平的原值 若按下为1
	}
	return 0;
}
