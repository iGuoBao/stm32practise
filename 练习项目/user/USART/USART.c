#include "USART.h"


uint8_t buffer[BUFFER_SIZE];
uint16_t writeIndex = 0;

int fputc(int ch,FILE *p)  //函数默认的，在使用printf函数时自动调用
{
	USART_SendData(USART1,(u8)ch);	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}


void USARTn_Init(u8 number,u32 bound)
{
	USART_DeInit(USART1);
	USART_DeInit(USART2);
	
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
		USART_Cmd(USART1, ENABLE); 									  //使能串口1 
		USART_ClearFlag(USART1, USART_FLAG_TC);				// 清除 USARTx 的待处理标志位
		
	}
	else if(number == 2)
	{
		RCC_APB1PeriphClockCmd(USART2_TX_CLK2,ENABLE);
		RCC_APB1PeriphClockCmd(USART2_RS485_RE_CLK2,ENABLE);
		RCC_APB2PeriphClockCmd(USART2_TX_CLK,ENABLE);
		RCC_APB2PeriphClockCmd(USART2_RS485_RE_CLK,ENABLE);
		printf("clk");
		
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
		// RE输出
		GPIO_InitStructure.GPIO_Pin = USART2_RS485_RE_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	    			// 推挽输出
		GPIO_Init(USART2_RS485_RE_Port,&GPIO_InitStructure);  
		
		printf("gpio");
		
		// USART结构体
		USART_InitTypeDef USART_InitStructure;
		// 串口2
		USART_InitStructure.USART_BaudRate = bound;								 	//波特率设置
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;			//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;					//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//收发模式
		USART_Init(USART2, &USART_InitStructure);			// 包装完毕
		USART_Cmd(USART2, ENABLE); 									  //使能串口2
		USART_ClearFlag(USART2, USART_FLAG_TC);				// 清除 USARTx 的待处理标志位
		
	}
	
}

void RS485_ENABLE()
{
	GPIO_SetBits(USART2_RS485_RE_Port, USART2_RS485_RE_PIN);
}

void sendString(char* str)
{
    while(*str)
    {
        // 等待发送数据寄存器为空
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

        // 发送一个字符
        USART_SendData(USART1, *str);

        // 移动到下一个字符
        str++;
    }
}
u8 getDate()
{
	return buffer[writeIndex];
}
