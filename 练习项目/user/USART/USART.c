#include "USART.h"


u8 buffer[BUFFER_SIZE];
u8 writeIndex = 0;

u8 RS485_send_cmd_flag = 0;



//------------------

u8 read_3phase_voltage[]={
	0x7E,0x31,0x30,0x30,0x31,0x33,0x30,0x34,0x30,0x30,0x30,0x30,0x30,0x46,0x44,0x42,0x37,0x0D
	};	

u8 read_DCFU02[]={
	0x7E,0x42,0x20,0x00,0xff,0x9e
};

//------------------





int fputc(int ch,FILE *p)  //函数默认的，在使用printf函数时自动调用
{
	USART_SendData(USART1,(u8)ch);	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	//USART_SendData(USART2,(u8)ch);	
	//while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	return ch;
}


void USARTn_Init(u8 number,u32 bound)
{
	//USART_DeInit(USART1);
	//USART_DeInit(USART2);
	
	// 串口1
	if(number == 1)
	{
		RCC_APB2PeriphClockCmd(USART_TX_CLK,ENABLE);


		// GPIO结构体
		GPIO_InitTypeDef GPIO_InitStructure;
		// 串口输出
		GPIO_InitStructure.GPIO_Pin = USART_TX_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	    			// 复用推挽输出
		GPIO_Init(USART_TX_Port,&GPIO_InitStructure);  			
		// 串口输入
		GPIO_InitStructure.GPIO_Pin = USART_RX_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  // 浮空输入
		GPIO_Init(USART_RX_Port,&GPIO_InitStructure); 
		
		
		// USART结构体
		USART_InitTypeDef USART_InitStructure;
		// 串口1
		USART_InitStructure.USART_BaudRate = bound;								 	//波特率设置
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;			//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;					//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//收发模式
		USART_Init(USART1, &USART_InitStructure);			// 包装完毕


		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);// 开启中断
		USART_Cmd(USART1, ENABLE); 									  //使能串口1 
		USART_ClearFlag(USART1, USART_FLAG_TC);				// 清除 USARTx 的待处理标志位
		
	}
	else if(number == 2)
	{

		RCC_APB1PeriphClockCmd(USART2_TX_CLK2,ENABLE);
		RCC_APB2PeriphClockCmd(USART2_TX_CLK,ENABLE);
		RCC_APB2PeriphClockCmd(USART2_RS485_RE_CLK,ENABLE);
		
		// GPIO结构体
		GPIO_InitTypeDef GPIO_InitStructure;
		// 串口输出
		GPIO_InitStructure.GPIO_Pin = USART2_TX_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	    			// 复用推挽输出
		GPIO_Init(USART2_TX_Port,&GPIO_InitStructure);  			
		// 串口输入
		GPIO_InitStructure.GPIO_Pin = USART2_RX_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  // 浮空输入
		GPIO_Init(USART2_RX_Port,&GPIO_InitStructure); 
		// RE输出  使能
		GPIO_InitStructure.GPIO_Pin = USART2_RS485_RE_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	    			// 推挽输出
		GPIO_Init(USART2_RS485_RE_Port,&GPIO_InitStructure);  
		
	
		// USART结构体
		USART_InitTypeDef USART_InitStructure;
		// 串口2
		USART_InitStructure.USART_BaudRate = bound;						//波特率设置
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;			//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;				//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//收发模式
		USART_Init(USART2, &USART_InitStructure); 

		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);// 开启中断
		USART_Cmd(USART2, ENABLE); 				  // 使能串口2
		USART_ClearFlag(USART2, USART_FLAG_TC);	  // 清除 USARTx 的待处理标志位
	}
}

void RS485_ENABLE(u8 work_station)
{
	if (work_station) GPIO_SetBits(USART2_RS485_RE_Port, USART2_RS485_RE_PIN);
	else GPIO_ResetBits(USART2_RS485_RE_Port, USART2_RS485_RE_PIN);
}
void RS485_send_data(u8 data)
{
	USART_SendData(USART2,data);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
}

void RS485_send_cmd(u8* buf,u8 len)
{
	u8 i;
	for(i=0;i<len;i++)
	{
		u8 data_temp = buf[i];
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET);
		USART_SendData(USART2, data_temp);
	}
}


u8 hexToAsciiU8(u8 hexValue) 
{
	u8 temp;
    if (hexValue >= 0 && hexValue <= 9) 
	{
        return hexValue + 0x30;  // 将0-9的十六进制数转换为对应的ASCII数字
    } 
	else if (hexValue >= 10 && hexValue <= 15)
	{
    	return hexValue + 0x37;  // 将A-F的十六进制数转换为对应的ASCII数字
    } 
	else if (hexValue >= 17 && hexValue <= 22) 
	{
        return hexValue + 0x57;  // 将a-f的十六进制数转换为对应的ASCII数字
    } 
	else 
	{
        return 0;  // 非法输入
    }
}

u8 asciiU8ToHex(u8 asciiNum) {
    // 将ASCII格式的数字转换为十六进制
    u8 hexValue = 0;
    if (asciiNum >= 0x30 && asciiNum <= 0x39) 
	{
        hexValue = asciiNum - 0x30;  // 将0-9的ASCII数字转换为对应的十六进制数
    } else if (asciiNum >= 0x41 && asciiNum <= 0x46) 
	{
        hexValue = asciiNum - 0x37;  // 将A-F的ASCII数字转换为对应的十六进制数
    } else if (asciiNum >= 0x61 && asciiNum <= 0x66) 
	{
        hexValue = asciiNum - 0x57;  // 将a-f的ASCII数字转换为对应的十六进制数
    } else 
	{
        return 0;
    }
	return hexValue;
}



// 根据接收的数组 组进结构体
void f_ProtocolFrame_3phase_voltage(ProtocolFrame_3phase_voltage* frame, u8* buf)
{
	u8 i = 0,LENID;
	frame->SOI = buf[i++]; // SOI和EOI是以16进制解释16进制传输
	frame->VER = (asciiU8ToHex(buf[i++]) << 4) + asciiU8ToHex(buf[i++]); // 一字节数据 转 ASCII分两字节传输
	frame->ADR = (asciiU8ToHex(buf[i++]) << 4) + asciiU8ToHex(buf[i++]);
	frame->CID1 = (asciiU8ToHex(buf[i++]) << 4) + asciiU8ToHex(buf[i++]);
	frame->CID2 = (asciiU8ToHex(buf[i++]) << 4) + asciiU8ToHex(buf[i++]);
	frame->LENGTH = (asciiU8ToHex(buf[i++]) << 12) + (asciiU8ToHex(buf[i++]) << 8) + (asciiU8ToHex(buf[i++]) << 4) + asciiU8ToHex(buf[i++]);
	frame->LENGTH_LENID = (frame->LENGTH & 0x0FFF);		// LENID = 取frame->LENGTH后12位

	for (int index = 0; index < (frame->LENGTH_LENID); index++)
	{
		frame->INFO[index] = (asciiU8ToHex(buf[i++]) << 4) + asciiU8ToHex(buf[i++]);
	}
	//frame->INFO = buf[i++];
	frame->CHKSUM = buf[i++];
	frame->EOI = buf[i++];	// SOI和EOI是以16进制解释16进制传输
}

void f_ProtocolFrame_DCFU02(ProtocolFrame_DCFU02* frame, u8* buf)
{
	u8 i = 0;
	frame->SOI = buf[i++]; 
	frame->ADR = buf[i++]; 
	frame->CMD = buf[i++]; 
	frame->LEN = buf[i++]; 
	
	for (int index = 0; index < frame->LEN; index++)
	{
		frame->DATAINFO[index] = buf[i++];

	}
	frame->CHKSUM = buf[i++]; 
}