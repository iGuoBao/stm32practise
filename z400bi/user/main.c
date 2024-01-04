#include "stm32f10x.h"         

// 用户外设
#include "LED.h"
#include "Button.h"
//#include "RTC.h"
//#include "beep.h"
//#include "EEPROM_AT24C02.h"
#include "adc_temp.h"
#include "dac.h"
#include "tftlcd.h"
//#include "animations.h"

// 公共
#include "SysTick.h"		// 滴答 以后不会使用这种
#include "setSysClk.h"	// 72M

// 中断
#include "exti.h"

// 协议
//#include "i2c.h"
#include "USART.h"

int main(void)
{	
	setSysClkHSE();		
	LED_init();	
	JLED_init();					
	KEY_init();
	ADC_Temp_Init();
	delay_Config();					// systick
	
	EXTI_Key_Config();		
	EXTI_USARTn_Config(1,9600);delay_ms(50);printf("usart1_init\r\n");	
	EXTI_USARTn_Config(2,9600);RS485_ENABLE(1);delay_ms(50);printf("usart2_init\r\n");	
	
	DAC1_Init();
	BASIC_TIM4_Config();


	//------ app
	extern u16 dac_value;

	extern u8 buffer[BUFFER_SIZE];
	extern u8 writeIndex;

	extern u8 work_status;		// 0  1=auto
	extern u8 fun_work_status;		// 0  1=on
	extern u8 bidi_work_status;		// 0  1=on

	int temp;
	u8 adc_step = 0;
	extern u8 fake_temperature;

	u8 bidi_step = 0;

	u8 adc_step2 = 0;

	float linearInterpolation(float input);
	//------ app

	
	TFTLCD_Init();
	LCD_Clear(GREEN);
	void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);//显示字符串


	while(1)
	{
		//TIM_SetCompare2(TIM3,90);
		
		LCD_ShowString(10,10,140,20,16,"temperature");
		LCD_ShowString(200,10,140,20,16,"fake_temp");
		char show_temp[16];
		float floatNum = Get_Temperture() / 100.0;
   		sprintf(show_temp, "%.2f", floatNum);
		LCD_ShowString(100,10,40,20,16,show_temp);

		char show_fake_temp[16];
		sprintf(show_fake_temp, "%d", fake_temperature);
		LCD_ShowString(290,10,40,20,16,show_fake_temp);
		
		LCD_ShowString(10,70,140,20,16,"addr 1");

		if (work_status == 0)
		{
			LCD_ShowString(10,30,140,20,16,"common Mode");
			// from keyup key1
			if (fun_work_status == 0)
			{
				LCD_ShowString(10,50,140,20,16,"fun off");
				SetJLED(6,0);
			}
			else
			{
				LCD_ShowString(10,50,140,20,16,"fun  on");
				SetJLED(6,1);
			}

			// 分闸
			if (bidi_work_status == 0) 
			{
				LCD_ShowString(10,50,140,20,16,"fun off");
				LCD_ShowString(10,90,140,20,16,"bidi  off");
				SetJLED(6,0);
				bidi_work_status = 0;
			}
			// 合闸
			else if (bidi_work_status == 1)
			{
				LCD_ShowString(10,50,140,20,16,"fun  on");
				LCD_ShowString(10,90,140,20,16,"bidi   on");
				SetJLED(6,1);
			}
			// 手动介入模式
			else
			{
				
			}
		}
		else
		{
			LCD_ShowString(10,30,140,20,16,"auto Mode");

			// 1300 == 13.00 C
			//高于温度设置
			if (temp >= 1300){
				LCD_ShowString(10,50,140,20,16,"fun  on");
				SetJLED(6,1);
			}
			else{
				LCD_ShowString(10,50,140,20,16,"fun off");
				SetJLED(6,0);
			}
		}



		LCD_ShowString(10,110,140,20,16,"dac value");
		char char_dac_value[16];
		sprintf(char_dac_value, "%d", dac_value);
		LCD_ShowString(90,110,140,20,16,char_dac_value);
		
		// 线性插值
		if (fake_temperature >= 25 && fake_temperature <= 80)
		{
			// 线性插值 输入25-80 输出 1.0-3.3
			float set_dac_value = linearInterpolation(fake_temperature);
			DAC_SetChannel1Data(DAC_Align_12b_R, set_dac_value/3.3 * 4096 );			// from 3.3v 4096
		}
		else if (fake_temperature >= 0)
		{
			DAC_SetChannel1Data(DAC_Align_12b_R, 1.0/3.3 * 4096);			// 1v from 3.3v 4096
		}

		
		

		delay_ms(100);
		
	}	
}


float linearInterpolation(float input) {
    float output;
    if (input >= 25 && input <= 80) {
        output = 1.0 + (input - 25) * (3.3 - 1.0) / (80 - 25);
    } else {
        output = -1; // 输入值不在范围内
    }
    return output;
}