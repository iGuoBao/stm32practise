#include "EEPROM_AT24C02.h"

void EEPROM_Init()
{
	RCC_APB2PeriphClockCmd(EEPROM_PORT_RCC, ENABLE); 	// ʹ��GPIOB���������ʱ��
	
	// GPIO��ʼ���ṹ��
	GPIO_InitTypeDef GPIO_InitStructure; 
	// ���ø�������
	GPIO_InitStructure.GPIO_Pin = EEPROM_PIN;	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;		 // ����Ϊ���ù��ܿ�©���ģʽ Ӳ��i2cֻ֧�ָ��ÿ�©
	GPIO_Init(EEPROM_PORT,&GPIO_InitStructure);	   // ����GPIO��ʼ���ṹ���ʼ��GPIOB
	
	
}
	