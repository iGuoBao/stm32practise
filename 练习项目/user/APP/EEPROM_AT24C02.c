#include "EEPROM_AT24C02.h"

void EEPROM_Init()
{
	RCC_APB2PeriphClockCmd(EEPROM_PORT_RCC, ENABLE); 	// 使能GPIOB和相对因复用时钟
	
	// GPIO初始化结构体
	GPIO_InitTypeDef GPIO_InitStructure; 
	// 设置复用引脚
	GPIO_InitStructure.GPIO_Pin = EEPROM_PIN;	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;		 // 设置为复用功能开漏输出模式 硬件i2c只支持复用开漏
	GPIO_Init(EEPROM_PORT,&GPIO_InitStructure);	   // 根据GPIO初始化结构体初始化GPIOB
	
	
}
	