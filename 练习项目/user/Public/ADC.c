#include "ADC.h"

float ADC_ConvertedValue;

void ADCx_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// 打开 ADC IO 端口时钟
	ADC_GPIO_APB_FUN(ADC_GPIO_RCC, ENABLE);
	// 配置 ADC IO 引脚模式
	GPIO_InitStructure.GPIO_Pin = ADC_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		// 必须为模拟输入
	GPIO_Init(ADC_GPIO_PORT, &GPIO_InitStructure);

}

void ADCx_Mode_Config(void)
{
	ADC_APB_FUN ( ADC_RCC, ENABLE );	// 打开 ADC 时钟
	
	ADC_InitTypeDef ADC_InitStructure;
	// ADC1 模式配置		
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;									// 独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ;  										// 禁止扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 									// 连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 关闭外部触发转换  通常都用软件
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;							// 转换结果右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;															// 转换通道 1 个
	ADC_Init(ADCx, &ADC_InitStructure);
	
	// 配置时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);		// 配置 ADC 时钟Ｎ狿 CLK2 的 8 分频，即 9MHz
	// 配置规则
	ADC_RegularChannelConfig(ADCx,ADC_CHANNEL,1,ADC_SampleTime_55Cycles5);	// 配置 ADC 通道转换顺序为 1，第一个转换，采样时间为 55.5 个时钟周期   
	// 配置中断
	ADC_ITConfig(ADCx, ADC_IT_EOC, ENABLE);		// ADC 转换结束产生中断，在中断服务程序中读取转换值

	
	// 开启 ADC ，并开始转换
	ADC_Cmd(ADCx, ENABLE);


	// (点赞)(点赞)(点赞)(点赞)(点赞)(点赞)(点赞)(点赞)(点赞)(点赞)(点赞)(点赞)
	// 初始化 ADC 校准寄存器零死角玩转 STM32F103—指南者 (点赞)(点赞)(点赞)(点赞)
	// (点赞)(点赞)(点赞)(点赞)(点赞)(点赞)(点赞)(点赞)(点赞)(点赞)(点赞)(点赞)
	ADC_ResetCalibration(ADCx);	// 重置指定的 ADC 的校准寄存器
	// 等待校准寄存器初始化完成
	while (ADC_GetResetCalibrationStatus(ADCx));
	// ADC 开始校准
	ADC_StartCalibration(ADCx);
	// 等待校准完成
	while (ADC_GetCalibrationStatus(ADCx));
	// 由于没有采用外部触发，所以使用软件触发 ADC 转换
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);
 }
float GetValue()
{
	return ADC_ConvertedValue;
}