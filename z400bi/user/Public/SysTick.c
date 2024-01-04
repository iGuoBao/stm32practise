#include "SysTick.h"


void delay_Config(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
}

void delay_us(u32 nus)
{     
    u32 temp;   
    SysTick->LOAD = nus * 9; // 72MHz / 8 = 9MHz
    SysTick->VAL=0x00; // 清空计数器
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; // 开始倒数
    do
    {
        temp=SysTick->CTRL;
    }
    while((temp&0x01)&&!(temp&(1<<16))); // 等待时间到达   
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; // 关闭计数器
    SysTick->VAL =0X00; // 清空计数器
}

void delay_ms(u16 nms)
{     
    u32 temp;   
    SysTick->LOAD = nms * 9000; // 72MHz / 8 = 9MHz
    SysTick->VAL=0x00; // 清空计数器
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; // 开始倒数
    do
    {
        temp=SysTick->CTRL;
    }
    while((temp&0x01)&&!(temp&(1<<16))); // 等待时间到达   
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; // 关闭计数器
    SysTick->VAL =0X00; // 清空计数器
}
