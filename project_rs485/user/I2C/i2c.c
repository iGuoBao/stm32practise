#include "i2c.h"

/*ͨѶ�ȴ���ʱʱ��*/
#define I2CT_FLAG_TIMEOUT ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))

u8 pBuffer[128];

void I2C_Config(u16 address)
{
	RCC_APB1PeriphClockCmd(I2Cx_CLK, ENABLE); //ʹ��I2C1ʱ��

	// I2C�ṹ��
	I2C_InitTypeDef I2C_InitStructure;
	// I2C--1 ����
	I2C_DeInit(I2Cx);
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C; 						// ����ΪIICģʽ
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_16_9; // ����ռ�ձ�Ϊ16/9
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; //ָ��7λ��ַ
	I2C_InitStructure.I2C_OwnAddress1 = address; 					// ���õ�ַ
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable; 					// ʹ��ACK�ź�
	I2C_InitStructure.I2C_ClockSpeed = 400000; 						// ����ʱ��Ƶ��Ϊ400KHz
	I2C_Init(I2Cx, &I2C_InitStructure); 									// ����IIC��ʼ���ṹ���ʼ��IIC1

	I2C_Cmd(I2Cx, ENABLE); //ʹ��IIC1����

}

// EEPROM_AT24C02


// ���ֽ�
void I2C_EEPROM_Write_Byte(uint16_t addr, uint8_t data)
{
	// ��ʼλ
	I2C_GenerateSTART(I2Cx,ENABLE);
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT));
		
	// ѡ���豸 ��֪ģʽѡ��
	I2C_Send7bitAddress(I2Cx,EEPROM_I2Cx_Write_ADDRESS,I2C_Direction_Transmitter); // ����
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));	

	// ���ݵ�ַ �������д��
	I2C_SendData(I2Cx,(addr & 0x00FF));  // 8bit
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2Cx,data); 						 // 8bit
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	//ֹͣ
	I2C_GenerateSTOP(I2Cx,ENABLE);
	
}




u8 I2C_EEPROM_ByteRead(uint8_t ReadAddr)
{
	u8 tem;
	// ��ʼλ
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	// ѡ���豸 ��֪ģʽѡ��
	I2C_Send7bitAddress(I2Cx, EEPROM_I2Cx_Read_ADDRESS, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	// ����Ҫ��ȡ���ݵĵ�ַ
	I2C_SendData(I2Cx, ReadAddr);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	// ���·�����ʼ�ź� ��ʼλ
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	/*�ݷ��ʹӻ��豸��ַ����ѡͨ*/
	I2C_Send7bitAddress(I2Cx, EEPROM_I2Cx_Read_ADDRESS, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)); 
	tem = I2C_ReceiveData(I2Cx);
	
	I2C_AcknowledgeConfig(I2Cx, DISABLE); 		// �ر�Ӧ��

	I2C_GenerateSTOP(I2Cx, ENABLE);
	return tem;
}
