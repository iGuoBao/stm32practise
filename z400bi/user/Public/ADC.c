#include "ADC.h"

float ADC_ConvertedValue;

void ADCx_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// �� ADC IO �˿�ʱ��
	ADC_GPIO_APB_FUN(ADC_GPIO_RCC, ENABLE);
	// ���� ADC IO ����ģʽ
	GPIO_InitStructure.GPIO_Pin = ADC_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		// ����Ϊģ������
	GPIO_Init(ADC_GPIO_PORT, &GPIO_InitStructure);

}

void ADCx_Mode_Config(void)
{
	ADCx_GPIO_Init();	// from adc.c
	
	ADC_APB_FUN ( ADC_RCC, ENABLE );	// �� ADC ʱ��
	
	ADC_InitTypeDef ADC_InitStructure;
	// ADC1 ģʽ����		
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;									// ����ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ;  										// ��ֹɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 									// ����ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // �ر��ⲿ����ת��  ͨ���������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;							// ת������Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;															// ת��ͨ�� 1 ��
	ADC_Init(ADCx, &ADC_InitStructure);
	
	// ����ʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);		// ���� ADC ʱ�ӣΪP CLK2 �� 8 ��Ƶ���� 9MHz
	// ���ù���
	ADC_RegularChannelConfig(ADCx,ADC_CHANNEL,1,ADC_SampleTime_55Cycles5);	// ���� ADC ͨ��ת��˳��Ϊ 1����һ��ת��������ʱ��Ϊ 55.5 ��ʱ������   
	// �����ж�
	ADC_ITConfig(ADCx, ADC_IT_EOC, ENABLE);		// ADC ת�����������жϣ����жϷ�������ж�ȡת��ֵ

	
	// ���� ADC ������ʼת��
	ADC_Cmd(ADCx, ENABLE);


	// (����)(����)(����)(����)(����)(����)(����)(����)(����)(����)(����)(����)
	// ��ʼ�� ADC У׼�Ĵ�����������ת STM32F103��ָ���� (����)(����)(����)(����)
	// (����)(����)(����)(����)(����)(����)(����)(����)(����)(����)(����)(����)
	ADC_ResetCalibration(ADCx);	// ����ָ���� ADC ��У׼�Ĵ���
	// �ȴ�У׼�Ĵ�����ʼ�����
	while (ADC_GetResetCalibrationStatus(ADCx));
	// ADC ��ʼУ׼
	ADC_StartCalibration(ADCx);
	// �ȴ�У׼���
	while (ADC_GetCalibrationStatus(ADCx));
	// ����û�в����ⲿ����������ʹ��������� ADC ת��
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);
 }
float GetValue()
{
	return ADC_ConvertedValue;
}