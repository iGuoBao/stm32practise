#include "LED.h"

// 板载用户LED 两个
void LEDinit()
{
	// 结构体 GPIO_InitS
	GPIO_InitTypeDef GPIO_InitS;
	
	// 使对应 RCC时钟外设 使能
	RCC_APB2PeriphClockCmd(LED0_PORT_RCC|LED1_PORT_RCC,ENABLE);
	
	// 结构体使用  先LED0设置
	GPIO_InitS.GPIO_Pin=LED0_PIN; 						// 选择LED0对应IO口
	GPIO_InitS.GPIO_Mode=GPIO_Mode_Out_PP;	 	// 推挽模式
	GPIO_InitS.GPIO_Speed=GPIO_Speed_50MHz;	  // 速度最高50MHz
	GPIO_Init(LED0_PORT,&GPIO_InitS); 	 			// 打包初始化LED0
	GPIO_ResetBits(LED0_PORT,LED0_PIN);   			// ResetLED0方法 低电平  开发板上低电平 高低电压  点亮
		
	// 同样的办法 结构体使用  设置LED1
	GPIO_InitS.GPIO_Pin=LED1_PIN; 						// 选择对应IO口
	GPIO_InitS.GPIO_Mode=GPIO_Mode_Out_PP;	 	
	GPIO_InitS.GPIO_Speed=GPIO_Speed_50MHz;	  
	GPIO_Init(LED1_PORT,&GPIO_InitS); 	 			// 打包初始化LED0
	GPIO_ResetBits(LED1_PORT,LED1_PIN); 	
}

// GPIO 使用跳线驱动板载LED J排 8个
void JLEDinit()
{
	// 结构体 GPIO_InitS
	GPIO_InitTypeDef GPIO_InitS;
	
	// 使对应 RCC时钟外设 使能
	RCC_APB2PeriphClockCmd(JLED1_PORT_RCC|JLED2_PORT_RCC|JLED3_PORT_RCC|JLED4_PORT_RCC|JLED5_PORT_RCC|JLED6_PORT_RCC|JLED7_PORT_RCC|JLED8_PORT_RCC,ENABLE);
	
	// 结构体使用 JLED1
	GPIO_InitS.GPIO_Pin=JLED1_PIN; 						// 选择LED0对应IO口
	GPIO_InitS.GPIO_Mode=GPIO_Mode_Out_PP;	 	// 推挽模式
	GPIO_InitS.GPIO_Speed=GPIO_Speed_50MHz;	  // 速度最高50MHz
	GPIO_Init(JLED1_PORT,&GPIO_InitS); 	 			// 打包初始化LED
	GPIO_ResetBits(JLED1_PORT,JLED1_PIN);   	// ResetLED方法 低电平  开发板上低电平 高低电压  点亮
	
	// 结构体使用 JLED2
	GPIO_InitS.GPIO_Pin=JLED2_PIN; 						
	GPIO_InitS.GPIO_Mode=GPIO_Mode_Out_PP;	 	
	GPIO_InitS.GPIO_Speed=GPIO_Speed_50MHz;	  
	GPIO_Init(JLED2_PORT,&GPIO_InitS); 	 			
	GPIO_ResetBits(JLED2_PORT,JLED2_PIN);   			
	
	// 结构体使用 JLED3
	GPIO_InitS.GPIO_Pin=JLED3_PIN; 						
	GPIO_InitS.GPIO_Mode=GPIO_Mode_Out_PP;	 	
	GPIO_InitS.GPIO_Speed=GPIO_Speed_50MHz;	  
	GPIO_Init(JLED3_PORT,&GPIO_InitS); 	 			
	GPIO_ResetBits(JLED3_PORT,JLED3_PIN);   		

	// 结构体使用 JLED4
	GPIO_InitS.GPIO_Pin=JLED4_PIN; 						
	GPIO_InitS.GPIO_Mode=GPIO_Mode_Out_PP;	 	
	GPIO_InitS.GPIO_Speed=GPIO_Speed_50MHz;	  
	GPIO_Init(JLED4_PORT,&GPIO_InitS); 	 			
	GPIO_ResetBits(JLED4_PORT,JLED4_PIN);   
	
	// 结构体使用 JLED5
	GPIO_InitS.GPIO_Pin=JLED5_PIN; 						
	GPIO_InitS.GPIO_Mode=GPIO_Mode_Out_PP;	 	
	GPIO_InitS.GPIO_Speed=GPIO_Speed_50MHz;	  
	GPIO_Init(JLED5_PORT,&GPIO_InitS); 	 			
	GPIO_ResetBits(JLED5_PORT,JLED5_PIN);   
	
	// 结构体使用 JLED6
	GPIO_InitS.GPIO_Pin=JLED6_PIN; 						
	GPIO_InitS.GPIO_Mode=GPIO_Mode_Out_PP;	 	
	GPIO_InitS.GPIO_Speed=GPIO_Speed_50MHz;	  
	GPIO_Init(JLED6_PORT,&GPIO_InitS); 	 			
	GPIO_ResetBits(JLED6_PORT,JLED6_PIN);   
	
	// 结构体使用 JLED7
	GPIO_InitS.GPIO_Pin=JLED7_PIN; 						
	GPIO_InitS.GPIO_Mode=GPIO_Mode_Out_PP;	 	
	GPIO_InitS.GPIO_Speed=GPIO_Speed_50MHz;	  
	GPIO_Init(JLED7_PORT,&GPIO_InitS); 	 			
	GPIO_ResetBits(JLED7_PORT,JLED7_PIN);   
	
	// 结构体使用 JLED8
	GPIO_InitS.GPIO_Pin=JLED8_PIN; 						
	GPIO_InitS.GPIO_Mode=GPIO_Mode_Out_PP;	 	
	GPIO_InitS.GPIO_Speed=GPIO_Speed_50MHz;	  
	GPIO_Init(JLED8_PORT,&GPIO_InitS); 	 			
	GPIO_ResetBits(JLED8_PORT,JLED8_PIN);   
}



