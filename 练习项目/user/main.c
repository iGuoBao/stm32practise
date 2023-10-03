#include "stm32f10x.h"         

// 用户外设
#include "LED.h"
#include "Button.h"
#include "beep.h"
#include "EEPROM_AT24C02.h"
#include "tftlcd.h"

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
	//LED_init();						
	//JLED_init();
	//KEY_init();
	//Beep_Init(PWM);
	//EEPROM_Init();
	
	delay_init();					// systick
	EXTI_Key_Config();		// 中断设置
	EXTI_USART1_Config(115200);
	
	TFTLCD_Init();
		printf("TFTLCD_Init();");
	// 外设初始化 结束
	
	
	// I2C_Config(EEPROM_I2Cx_Write_ADDRESS);

	LCD_Clear(LGRAY);
	LCD_Fill(1,1,320,40,LGRAYBLUE);
	
	FRONT_COLOR=BLACK;
	u8 str[] = "SO EASY" ;
	LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,str);
	LCD_Fill(30,150,60,180,GRAY);

	LCD_Set_Window(1,200,200,200);
	
	
	
	while(1)
	{
		//printf("data=%d\r\n",123);
		
		for(int i=0;i<=8;i++)
		{
			delay_ms(30);
			printf("number %d - %u\r\n",i,I2C_EEPROM_ByteRead(i));
		}
		
		break;	
	}
}


