#include "stm32f10x.h"         

// 用户外设
#include "LED.h"
#include "Button.h"
#include "beep.h"
#include "EEPROM_AT24C02.h"

// 公共
#include "SysTick.h"		// 滴答 以后不会使用这种
#include "setSysClk.h"	// 72M

// 中断
#include "exti.h"

// 协议
#include "i2c.h"
#include "USART.h"

int main(void)
{	
	uint8_t eedata;
	setSysClkHSE();				
	
	// 外设初始化 开始
	LED_init();						
	JLED_init();
	KEY_init();
	Beep_Init(PWM);
	EEPROM_Init();
	// 外设初始化 结束

	delay_init();					// systick
	EXTI_Key_Config();		// 中断设置
	EXTI_USART1_Config(115200);
	I2C_Config(EEPROM_I2Cx_Write_ADDRESS);
	I2C_EEPROM_Write_Byte(1, 0x05);

	while(1)
	{
		//printf("data=%d\r\n",123);
		
		for(int i=0;i<=127;i++)
		{
			delay_ms(30);
			printf("number %d - %u\r\n",i,I2C_EEPROM_ByteRead(i));
		}
		
		
	}
}


