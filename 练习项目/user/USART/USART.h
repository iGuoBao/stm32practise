#ifndef __USART_H__
#define __USART_H__

#include "stm32f10x.h"
#include "stdio.h" // 标准库

#define BUFFER_SIZE		128	// 最大接受字节数量  	

//---------USART1----------
#define USART_TX_CLK  					( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 )
#define USART_TX_Port  					GPIOA
#define USART_TX_PIN 					GPIO_Pin_9
#define USART_RX_CLK  					( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 )
#define USART_RX_Port  					GPIOA
#define USART_RX_PIN 					GPIO_Pin_10	
//---------USART2----------
// RS485 RE-PD7  PA2-USART2_TX  PA3/USART2_RX
#define USART2_TX_CLK  						RCC_APB2Periph_GPIOA
#define USART2_TX_CLK2 						RCC_APB1Periph_USART2 //RCC_APB1PeriphClockCmd  RCC_APB2Periph_AFIO
#define USART2_TX_Port  					GPIOA
#define USART2_TX_PIN 						GPIO_Pin_2
#define USART2_RX_CLK  						RCC_APB2Periph_GPIOA
#define USART2_RX_Port  					GPIOA
#define USART2_RX_PIN 						GPIO_Pin_3	
#define USART2_RS485_RE_CLK  		  RCC_APB2Periph_GPIOD
#define USART2_RS485_RE_CLK2 			RCC_APB1Periph_USART2 
#define USART2_RS485_RE_Port  		GPIOD
#define USART2_RS485_RE_PIN 			GPIO_Pin_7

extern u8 RS485_send_cmd_flag;
extern u8 read_3phase_voltage_send_flag;
extern u8 DCFU02_send_flag;
extern u8 LYTHR30EN_send_flag;

//extern u8 read_3phase_voltage[];	
//extern u8 read_DCFU02[];	
//extern u8 read_LYTHR30EN[];
extern u8 ask_BIBD180[];
extern u8 send_addr1_ON_BIBD180[];
//extern u8 send_addr2_ON_BIBD180[];
//extern u8 send_addr3_ON_BIBD180[];
extern u8 send_addr1_OFF_BIBD180[];
//extern u8 send_addr2_OFF_BIBD180[];
//extern u8 send_addr3_OFF_BIBD180[];


// 定义帧结构体
typedef struct {
    u8 SOI;        // 起始位标志（START OF INFORMATION）
    u8 VER;        // 通信协议版本号
    u8 ADR;        // 对同类型设备的不同地址描述（1－254，0、255保留）
    u8 CID1;       // 设备标识码(设备类型描述)
    u8 CID2;       // 命令信息：控制标识码（数据或动作类型描述）
                        // 响应信息：返回码RTN
    u16 LENGTH;    // INFO字节长度（包括LENID和LCHKSUM）
    u16 LENGTH_LENID;    
    u16 INFO[4095 -1];       // 命令信息：控制数据信息COMMAND_INFO
                        // 应答信息：应答数据信息DATA_INFO
    u16 CHKSUM;    // 校验和码
    u8 EOI;        // 结束码（END OF INFORMATION） (CR: 0x0D)
} ProtocolFrame_3phase_voltage;

typedef struct {
    u8 SOI;      // 起始位标志（START OF INFORMATION） 7EH	81H
    u8 ADR;      // 模块地址描述 
    u8 CMD;      // 命令标识码（数据或动作类型描述）
    u8 LEN;      // 数据信息长度
    u8 DATAINFO[30];      //命令信息：控制数据信息COMMAND INFO
                          //应答信息：应答数据信息DATA INFO    
        
    u16 CHKSUM;           // 校验和码

} ProtocolFrame_DCFU02;


typedef struct {
    u8 ADD;      
    u8 CMD;      
    u8 LEN;      
    u8 DATA[5];      
    u8 HCRC;
    u8 LCRC;                
} ProtocolFrame_LYTHR30EN;



void USARTn_Init(u8 number,u32 bound);
void RS485_ENABLE(u8 work_station);
void RS485_send_data(u8 buf);
void RS485_send_cmd(u8* buf,u8 len);

void f_ProtocolFrame_3phase_voltage(ProtocolFrame_3phase_voltage* frame, u8* buf);
void f_ProtocolFrame_DCFU02(ProtocolFrame_DCFU02* frame, u8* buf);
void f_ProtocolFrame_LYTHR30EN(ProtocolFrame_LYTHR30EN* frame, u8* buf);


#endif