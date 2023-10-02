#ifndef __EEPROM_AT24C02_H__
#define __EEPROM_AT24C02_H__

#include "stm32f10x.h"
#include "i2c.h"


/*
	AT24C02
	数据地址长度	 8位
	页长度 				 8字节

*/


// SCL PB6
#define EEPROM_SCL_PIN				GPIO_Pin_6
// SDA PB7
#define EEPROM_SDA_PIN				GPIO_Pin_7
#define EEPROM_PORT						GPIOB
#define EEPROM_PIN					  EEPROM_SCL_PIN | EEPROM_SDA_PIN
#define EEPROM_PORT_RCC				RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO

void EEPROM_Init(void);

#endif