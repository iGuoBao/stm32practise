#ifndef __I2C_H__
#define __I2C_H__

#include "stm32f10x.h"
#include "EEPROM_AT24C02.h"
#include "USART.h"



#define I2Cx 												I2C1 										// 使用I2C1外设
#define I2Cx_CLK 										RCC_APB1Periph_I2C1 	  // I2C1时钟
#define I2Cx_PORT										EEPROM_PORT 					  // 使用GPIOB端口


#define I2Cx_ADDRESS								0x01	// 主机地址
#define EEPROM_I2Cx_Read_ADDRESS		0xA0 	// 1010 000(0/1) r=0xA0   w=0xA1
#define EEPROM_I2Cx_Write_ADDRESS		0xA1 	// 1010 000(0/1) r=0xA0   w=0xA1




void I2C_Config(u16 address);

void I2C_EEPROM_Write_Byte(uint16_t addr, uint8_t data);
u8 I2C_EEPROM_ByteRead(uint8_t ReadAddr);


#endif