#ifndef __EXTI_H__
#define __EXTI_H__

#include "stm32f10x.h"

#include "Button.h"
#include "LED.h"
#include "beep.h"

#include "SysTick.h"



// KEY0 �ж϶���
#define KEY0_EXTI_PORT 					KEY0_PORT
#define KEY0_EXTI_PIN 					KEY0_PIN
#define KEY0_EXTI_PORTSOURCE 		KEY0_PORTSOURCE		// ��button.h ����  �ж�Դ������ӳ����
#define KEY0_EXTI_PINSOURCE  		KEY0_PINSOURCE
#define KEY0_EXTI_LINE 					EXTI_Line4				// EXTIͨ��ѡ�� 4
#define KEY0_EXTI_IRQ 					EXTI4_IRQn				// �жϺ�  	NVIC��
#define KEY0_IRQHandler 				EXTI4_IRQHandler	// �жϺ�����

// KEY1 �ж϶���
#define KEY1_EXTI_PORT 					KEY1_PORT
#define KEY1_EXTI_PIN 					KEY1_PIN
#define KEY1_EXTI_PORTSOURCE 		KEY1_PORTSOURCE		
#define KEY1_EXTI_PINSOURCE  		KEY1_PINSOURCE
#define KEY1_EXTI_LINE 					EXTI_Line3				
#define KEY1_EXTI_IRQ 					EXTI3_IRQn				
#define KEY1_IRQHandler 				EXTI3_IRQHandler	

// KEY2 �ж϶���
#define KEY2_EXTI_PORT 					KEY2_PORT
#define KEY2_EXTI_PIN 					KEY2_PIN
#define KEY2_EXTI_PORTSOURCE 		KEY2_PORTSOURCE		
#define KEY2_EXTI_PINSOURCE  		KEY2_PINSOURCE
#define KEY2_EXTI_LINE 					EXTI_Line2				
#define KEY2_EXTI_IRQ 					EXTI2_IRQn				
#define KEY2_IRQHandler 				EXTI2_IRQHandler	

// WKUP �ж϶���
#define WKUP_EXTI_PORT 					WKUP_PORT
#define WKUP_EXTI_PIN 					WKUP_PIN
#define WKUP_EXTI_PORTSOURCE 		WKUP_PORTSOURCE		
#define WKUP_EXTI_PINSOURCE  		WKUP_PINSOURCE
#define WKUP_EXTI_LINE 					EXTI_Line0				
#define WKUP_EXTI_IRQ 					EXTI0_IRQn				
#define WKUP_IRQHandler 				EXTI0_IRQHandler	


static void  NVCI_Config();

void EXTI_Key_Config(void);
void EXTI_USART1_Config(void);

<<<<<<< HEAD

// KEY0 �жϺ���
void KEY0_IRQHandler(void);						
void USART1_IRQHandler(void);

=======
void KEY0_IRQHandler(void);						// KEY0 �жϺ���
void KEY1_IRQHandler(void);	
void KEY2_IRQHandler(void);	
void WKUP_IRQHandler(void);	
>>>>>>> main

#endif