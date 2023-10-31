#ifndef __BEEP_H__
#define __BEEP_H__

#include "stm32f10x.h"

#include "SysTick.h"
#include "TIM.h"

// Beep PB8
#define Beep_PORT 					GPIOB
#define Beep_PIN 						GPIO_Pin_8
#define Beep_PORT_RCC				RCC_APB2Periph_GPIOB
#define Beep_PWM_PORT_RCC		(Beep_PORT_RCC|RCC_APB2Periph_AFIO)
#define Beep_PWM_TIMx				TIM4
#define Beep_PWM_CCRx 			CCR3				// TIM4 CH3 PB8
#define Beep_PWM_OCxInit 		TIM_OC3Init	// 初始化
#define Beep_PWM_OCxPreloadConfig 			TIM_OC3PreloadConfig	// 通道重载配置函数



// 关于初始化时 用到的mode
typedef enum {
  Normal,
  PWM,
	DOWN,
}Beep_Mode;


/*
// 音乐机编码
typedef enum {
    CL = 262, DL = 294, EL = 330, FL = 349, GL = 392, AL = 440, BL = 494,
    CM = 523, DM = 587, EM = 659, FM = 698, GM = 784, AM = 880, BM = 988,
    CH = 1046, DH = 1175, EH = 1319, FH = 1397, GH = 1568, AH = 1760, BH = 1976
} Beep_Music_Note;
*/


typedef enum {
		NO,
    CL,
    DL,
    EL,
    FL,
    GL,
    AL,
    BL,

    CM,
    DM,
    EM,
    FM,
    GM,
    AM,
    BM,

    CH,
    DH,
    EH,
    FH,
    GH,
    AH,
    BH
} Beep_Music_Note;


typedef enum {
    VOLUME1, VOLUME2, VOLUME3, VOLUME4
} Beep_Music_Volume;

typedef enum {
    B12, B1, B2, B3 
} Beep_Music_Duration;
//

void Beep_Init(Beep_Mode mode);
void Beep_On(void);
void Beep_Off(void);
void Beep_Test(void);

void Set_Beep_PWM_Pulse(int Num);
void Set_Beep_PWM_HZ(int Num);


// 编码函数
// 11111111  1111    1111
// note			 volume	 duration
u8 Beep_Usart_encode(Beep_Music_Note note, Beep_Music_Volume volume, Beep_Music_Duration duration);
// 解码函数
void Beep_Usart_decode(u8 encoded, Beep_Music_Note *note, Beep_Music_Volume *volume, Beep_Music_Duration *duration);
void Beep_Music_Do(Beep_Music_Note key,Beep_Music_Volume,Beep_Music_Duration);
void Beep_Music();
#endif