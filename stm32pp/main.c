#include "stm32f10x.h"

void SystemInit(void);
void delay(int i);

void SystemInit(void)
{
	/* 开始文件汇编 Reset_Handler复位后执行 有这个函数 为防止报错需申明函数*/
}

void delay(int i)
{
	while(i--);
}
int main(void)
{
	/* RCC使能 外设时钟 GPIOB GPIOE */
	RCC_APB2ENR |= (1<<3);
	RCC_APB2ENR |= (1<<6);
	
	/* 高位为1 输出低电平 灯亮 */
	GPIOB_BSRR |= (1 << (16+5));
	GPIOE_BSRR |= (1 << (16+5));
	/* 引脚设置 推挽输出 最高2MHz */
	GPIOB_CRL |= (2 << 4*5);
	GPIOE_CRL |= (2 << 4*5);
	while(1){
	delay(0xFFFFF);
	GPIOB_BSRR |= (1 << (16+5));
	GPIOE_BSRR |= (1 << (16+5));
	delay(0xFFFFF);
	GPIOB_BSRR |= (1 << (5));
	GPIOE_BSRR |= (1 << (5));
	}
}
