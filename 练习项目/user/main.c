#include "stm32f10x.h"         

// 用户外设
#include "LED.h"
#include "Button.h"
//#include "RTC.h"
//#include "beep.h"
//#include "EEPROM_AT24C02.h"
#include "adc_temp.h"
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
	
	BASIC_TIM4_Config();


	//------ app
	extern u8 buffer[BUFFER_SIZE];
	extern u8 writeIndex;

	extern u8 work_status;		// 0  1=auto
	extern u8 fun_work_status;		// 0  1=on
	extern u8 bidi_work_status;		// 0  1=on

	int temp;
	u8 adc_step = 0;
	u8 fake_temperature = 0;

	u8 bidi_step = 0;

	u8 adc_step2 = 0;
	//------ app

	
	TFTLCD_Init();
	LCD_Clear(GREEN);
	void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);//显示字符串


	while(1)
	{
		LCD_ShowString(10,10,140,20,16,"temperature");
		char show_temp[16];
		float floatNum = temp / 100.0;
   		sprintf(show_temp, "%.2f", floatNum);
		LCD_ShowString(100,10,40,20,16,show_temp);
		
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





		if (bidi_step++ == 100){
			bidi_step = 0;
			//RS485_send_cmd(ask_BIBD180,9);
			//u8 addr = buffer[1];	
		}
/*
		for(int i=0;i<9;i++){
				printf("%02X ",buffer[i]);
		}
*/
		printf("\r\n");
		temp=Get_Temperture();
		if(temp<0)
		{
			temp=-temp;
			printf("temp -");
		}
		else
		{
			printf("temp +");
		}
		printf("%d \r\n",temp);
		printf("%.2f C\r\n",(float)temp/100);
		delay_ms(100);
		//TIM_SetCompare2(TIM3,90);
	}	
}


