#include "i2c.h"

/*通讯等待超时时间*/
#define I2CT_FLAG_TIMEOUT ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))

u8 pBuffer[128];

void I2C_Config(u16 address)
{
	RCC_APB1PeriphClockCmd(I2Cx_CLK, ENABLE); //使能I2C1时钟

	// I2C结构体
	I2C_InitTypeDef I2C_InitStructure;
	// I2C--1 设置
	I2C_DeInit(I2Cx);
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C; 						// 设置为IIC模式
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_16_9; // 设置占空比为16/9
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; //指定7位地址
	I2C_InitStructure.I2C_OwnAddress1 = address; 					// 设置地址
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable; 					// 使能ACK信号
	I2C_InitStructure.I2C_ClockSpeed = 400000; 						// 设置时钟频率为400KHz
	I2C_Init(I2Cx, &I2C_InitStructure); 									// 根据IIC初始化结构体初始化IIC1

	I2C_Cmd(I2Cx, ENABLE); //使能IIC1外设

}

// EEPROM_AT24C02


// 单字节
void I2C_EEPROM_Write_Byte(uint16_t addr, uint8_t data)
{
	// 开始位
	I2C_GenerateSTART(I2Cx,ENABLE);
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT));
		
	// 选择设备 告知模式选择
	I2C_Send7bitAddress(I2Cx,EEPROM_I2Cx_Write_ADDRESS,I2C_Direction_Transmitter); // 方向
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));	

	// 数据地址 先清空再写入
	I2C_SendData(I2Cx,(addr & 0x00FF));  // 8bit
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2Cx,data); 						 // 8bit
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	//停止
	I2C_GenerateSTOP(I2Cx,ENABLE);
	
}




u8 I2C_EEPROM_ByteRead(uint8_t ReadAddr)
{
	u8 tem;
	// 开始位
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	// 选择设备 告知模式选择
	I2C_Send7bitAddress(I2Cx, EEPROM_I2Cx_Read_ADDRESS, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	// 发送要读取数据的地址
	I2C_SendData(I2Cx, ReadAddr);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	// 重新发送起始信号 开始位
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	/*⑤发送从机设备地址，读选通*/
	I2C_Send7bitAddress(I2Cx, EEPROM_I2Cx_Read_ADDRESS, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)); 
	tem = I2C_ReceiveData(I2Cx);
	
	I2C_AcknowledgeConfig(I2Cx, DISABLE); 		// 关闭应答

	I2C_GenerateSTOP(I2Cx, ENABLE);
	return tem;
}
