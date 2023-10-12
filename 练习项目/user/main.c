#include "stm32f10x.h"         

// 用户外设
#include "LED.h"
#include "Button.h"
#include "beep.h"
#include "EEPROM_AT24C02.h"
#include "tftlcd.h"
#include "animations.h"

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
	//LED_init();						
	//JLED_init();
	//KEY_init();
	//Beep_Init(PWM);
	//EEPROM_Init();
	ADCx_GPIO_Init();
	
	delay_Config();					// systick
	EXTI_Key_Config();		// 中断设置
	EXTI_USART1_Config(115200);
	ADCx_Mode_Config();
	TFTLCD_Init();
	// RTC_Init();
	// I2C_Config(EEPROM_I2Cx_Write_ADDRESS);

	LCD_Clear(BLACK);
	draw_voltmeter_window();
	draw_voltmeter_chart();
	draw_voltmeter_chart_value_time_line();
	
	while(1)
	{
		//printf("data=%d\r\n",123);
			refresh_voltmeter_chart();
			show_voltmeter_chart_value();
		
	}
}


