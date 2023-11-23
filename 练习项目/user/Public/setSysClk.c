#include "setSysClk.h"

// 时钟源设置为 默认外部高速振荡器
int setSysClkHSE()
{
	RCC_DeInit();								// 将外设 RCC 寄存器重设为缺省值
	RCC_HSEConfig(RCC_HSE_ON); 	// HSE晶振 启动
	
	// 设置频率
	RCC_HCLKConfig(RCC_SYSCLK_Div1); 
	RCC_PCLK1Config(RCC_HCLK_Div2); 
	RCC_PCLK2Config(RCC_HCLK_Div1);
	
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);  //72M
	RCC_PLLCmd(ENABLE);
	
	// while可能一直循环 
	// while(RCC_WaitForHSEStartUp() != SUCCESS){}		// 如果没稳定就一直等待
	// for (int i = 0; i < 10 && RCC_WaitForHSEStartUp() != SUCCESS; i++){}		//检测稳定 最多10次
	if(RCC_WaitForHSEStartUp() != SUCCESS) return 0;
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while(RCC_GetSYSCLKSource()!=0x08);
	
	return 1;
}
int setSysClkHSI()
{
	RCC_DeInit();
	// 设置内部高速
	// 时间不够
	
	
	return 1;
}