#ifndef __BSD_TFTLCD_H
#define __BSD_TFTLCD_H 	   


#define LCD_GPIO_RCC		(	RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOG)

// 混合
// GPIO-D组   1  DATA线组
#define LCD_GPIO_GROUP1_PORT  GPIOD
#define LCD_GPIO_GROUP1_PINS  (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15)

// GPIO-E组   2	 DATA线组
#define LCD_GPIO_GROUP2_PORT  GPIOE
#define LCD_GPIO_GROUP2_PINS  (GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)

// GPIO-G组   3		A10
#define LCD_GPIO_GROUP3_PORT  GPIOG
#define LCD_GPIO_GROUP3_PINS  (GPIO_Pin_0|GPIO_Pin_12)

// GPIO-B组   4		背光 PB0
#define LCD_GPIO_GROUP4_PORT  GPIOB
#define LCD_GPIO_GROUP4_PINS  (GPIO_Pin_0)

/*
// XX  5		X
#define LCD_GPIO_GROUP5_PORT  XX
#define LCD_GPIO_GROUP5_PINS  XX
*/

#define LCD_BL 		PB0  //背光
#define T_SCK			PB1
#define T_MOSI  	PF9
#define T_MISO 	 	PB2
#define T_CS   	 	PF11
#define T_PEN   	PF10

#define FSMC_NWE	PD5
#define FSMC_NE4  PG12
#define FSMC_A10  PG0
#define FSMC_NOE  PD4

#define FSMC_D0		PD14
#define FSMC_D1		PD15
#define FSMC_D2		PD0
#define FSMC_D3		PD1
#define FSMC_D4		PE7
#define FSMC_D5		PE8
#define FSMC_D6		PE9
#define FSMC_D7		PE10
#define FSMC_D8		PE11
#define FSMC_D9		PE12
#define FSMC_D10	PE13
#define FSMC_D11	PE14
#define FSMC_D12	PE15
#define FSMC_D13	PD8
#define FSMC_D14	PD9
#define FSMC_D15	PD10


#endif
