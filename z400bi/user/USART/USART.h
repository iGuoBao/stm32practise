#ifndef __USART_H__
#define __USART_H__

#include "stm32f10x.h"
#include "stdio.h" // ��׼��

#define BUFFER_SIZE		128	// �������ֽ�����  	

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


// ����֡�ṹ��
typedef struct {
    u8 SOI;        // ��ʼλ��־��START OF INFORMATION��
    u8 VER;        // ͨ��Э��汾��
    u8 ADR;        // ��ͬ�����豸�Ĳ�ͬ��ַ������1��254��0��255������
    u8 CID1;       // �豸��ʶ��(�豸��������)
    u8 CID2;       // ������Ϣ�����Ʊ�ʶ�루���ݻ�������������
                        // ��Ӧ��Ϣ��������RTN
    u16 LENGTH;    // INFO�ֽڳ��ȣ�����LENID��LCHKSUM��
    u16 LENGTH_LENID;    
    u16 INFO[4095 -1];       // ������Ϣ������������ϢCOMMAND_INFO
                        // Ӧ����Ϣ��Ӧ��������ϢDATA_INFO
    u16 CHKSUM;    // У�����
    u8 EOI;        // �����루END OF INFORMATION�� (CR: 0x0D)
} ProtocolFrame_3phase_voltage;

typedef struct {
    u8 SOI;      // ��ʼλ��־��START OF INFORMATION�� 7EH	81H
    u8 ADR;      // ģ���ַ���� 
    u8 CMD;      // �����ʶ�루���ݻ�������������
    u8 LEN;      // ������Ϣ����
    u8 DATAINFO[30];      //������Ϣ������������ϢCOMMAND INFO
                          //Ӧ����Ϣ��Ӧ��������ϢDATA INFO    
        
    u16 CHKSUM;           // У�����

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