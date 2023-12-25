#include "beep.h"

#include <stdio.h>
u8 music_station=1;
int noteFrequencies[] = {
    0,262, 294, 330, 349, 392, 440, 494,
    523, 587, 659, 698, 784, 880, 988,
    1046, 1175, 1319, 1397, 1568, 1760, 1976
};

int DurationNum[] = {
		306, 612, 1224, 1836 
};


void Beep_Init(Beep_Mode mode)
{
	if(mode == 0)
	{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(Beep_PORT_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = Beep_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
	else if(mode == 1)
	{
		// GPIO结构体
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(Beep_PWM_PORT_RCC, ENABLE); // 复用时钟
		GPIO_InitStructure.GPIO_Pin = Beep_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		BASIC_TIM4_Config();
		
		TIM_OCInitTypeDef TIM_OCInitStructure;
		// TIM4 CH3
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能
		TIM_OCInitStructure.TIM_Pulse = 30;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 	
		Beep_PWM_OCxInit(Beep_PWM_TIMx, &TIM_OCInitStructure);				//使能通道和预装载
		Beep_PWM_OCxPreloadConfig(Beep_PWM_TIMx, TIM_OCPreload_Enable);
		music_station = 1;
	}
	else
	{
    RCC_APB2PeriphClockCmd(Beep_PORT_RCC, DISABLE);
		TIM_Cmd(Beep_PWM_TIMx, DISABLE);	// 使能
		music_station = 0;
	}
}

void Beep_On(void)
{
    GPIO_SetBits(Beep_PORT,Beep_PIN);
}

void Beep_Off(void)
{
    GPIO_ResetBits(Beep_PORT,Beep_PIN);
}

void Beep_Test(void)
{
	Beep_On();
	delay_ms(200);
	Beep_Off();
}
void Set_Beep_PWM_Pulse(int Num)
{
		TIM_OCInitTypeDef TIM_OCInitStructure;
		// TIM4 CH3
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能
		TIM_OCInitStructure.TIM_Pulse = Num;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 	
		Beep_PWM_OCxInit(Beep_PWM_TIMx, &TIM_OCInitStructure);				//使能通道和预装载
		Beep_PWM_OCxPreloadConfig(Beep_PWM_TIMx, TIM_OCPreload_Enable);
		
		TIM_Cmd(Beep_PWM_TIMx, ENABLE);	// 使能
}

void Set_Beep_PWM_HZ(int Num)
{
	SetBASIC_TIM4_Hz(Num);
}

// 编码函数
// 11111111  1111    1111
// note			 volume	 duration
u8 Beep_Usart_encode(Beep_Music_Note note, Beep_Music_Volume volume, Beep_Music_Duration duration) {
    return (note << 8) | (volume << 4) | duration;		
}

// 解码函数
void Beep_Usart_decode(u8 encoded, Beep_Music_Note *note, Beep_Music_Volume *volume, Beep_Music_Duration *duration) {
    *note = (Beep_Music_Note)(encoded >> 8);
    *volume = (Beep_Music_Volume)((encoded >> 4) & 0x0F);
    *duration = (Beep_Music_Duration)(encoded & 0x0F);
		
}


// 音乐机工作
void Beep_Music_Do(Beep_Music_Note key, Beep_Music_Volume volume, Beep_Music_Duration duration)
{    
		if(music_station){
			Set_Beep_PWM_HZ(noteFrequencies[key]);
			delay_ms(DurationNum[duration]);
			Set_Beep_PWM_HZ(0);
		}
}


void Beep_Music()
{
	if(music_station==1){
	// 国际歌
	Beep_Music_Do(GM, VOLUME1, B1);

	Beep_Music_Do(CH, VOLUME1, B1);
	Beep_Music_Do(CH, VOLUME1, B12);
	Beep_Music_Do(BM, VOLUME1, B12);
	Beep_Music_Do(DH, VOLUME1, B12);
	Beep_Music_Do(CH, VOLUME1, B12);
	Beep_Music_Do(GM, VOLUME1, B12);
	Beep_Music_Do(EM, VOLUME1, B12);

	Beep_Music_Do(AM, VOLUME1, B2);
	Beep_Music_Do(FM, VOLUME1, B1);
	Beep_Music_Do(0, VOLUME1, B12); 
	Beep_Music_Do(AM, VOLUME1, B12);

	Beep_Music_Do(DH, VOLUME1, B1);
	Beep_Music_Do(CH, VOLUME1, B1);
	Beep_Music_Do(BM, VOLUME1, B12);
	Beep_Music_Do(AM, VOLUME1, B12);
	Beep_Music_Do(GM, VOLUME1, B12);
	Beep_Music_Do(FM, VOLUME1, B12);

	Beep_Music_Do(EM,VOLUME1,B2);
	Beep_Music_Do(EM,VOLUME1,B1);
	Beep_Music_Do(GM,VOLUME1,B1);

	Beep_Music_Do(CH,VOLUME1,B1);
	Beep_Music_Do(BM,VOLUME1,B1);
	Beep_Music_Do(DH,VOLUME1,B12);
	Beep_Music_Do(CH,VOLUME1,B12);
	Beep_Music_Do(GM,VOLUME1,B12);
	Beep_Music_Do(EM,VOLUME1,B12);

	Beep_Music_Do(AM,VOLUME1,B2);
	Beep_Music_Do(FM,VOLUME1,B12);
	Beep_Music_Do(AM,VOLUME1,B12);
	Beep_Music_Do(DH,VOLUME1,B12);
	Beep_Music_Do(CH,VOLUME1,B12);

	Beep_Music_Do(BM,VOLUME1,B1);
	Beep_Music_Do(DH,VOLUME1,B1);
	Beep_Music_Do(FH,VOLUME1,B1);
	Beep_Music_Do(BM,VOLUME1,B1);

	Beep_Music_Do(CH,VOLUME1,B2);
	Beep_Music_Do(CH,VOLUME1,B12);
	Beep_Music_Do(0,VOLUME1,B12);
	Beep_Music_Do(EH,VOLUME1,B12);
	Beep_Music_Do(DH,VOLUME1,B12);

	Beep_Music_Do(BM,VOLUME1,B2);
	Beep_Music_Do(AM,VOLUME1,B12);
	Beep_Music_Do(BM,VOLUME1,B12);
	Beep_Music_Do(CH,VOLUME1,B12);
	Beep_Music_Do(AM,VOLUME1,B12);

	Beep_Music_Do(BM,VOLUME1,B2);
	Beep_Music_Do(GM,VOLUME1,B12);
	Beep_Music_Do(GM,VOLUME1,B12);
	Beep_Music_Do(FM,VOLUME1,B12);
	Beep_Music_Do(GM,VOLUME1,B12);

	Beep_Music_Do(AM,VOLUME1,B1);
	Beep_Music_Do(AM,VOLUME1,B1);
	Beep_Music_Do(DH,VOLUME1,B1);
	Beep_Music_Do(CH,VOLUME1,B1);

	Beep_Music_Do(BM,VOLUME1,B2);
	Beep_Music_Do(BM,VOLUME1,B12);
	Beep_Music_Do(0,VOLUME1,B12);
	Beep_Music_Do(DH,VOLUME1,B1);

	Beep_Music_Do(DH,VOLUME1,B1);
	Beep_Music_Do(BM,VOLUME1,B1);
	Beep_Music_Do(GM,VOLUME1,B12);
	Beep_Music_Do(GM,VOLUME1,B12);
	Beep_Music_Do(FM,VOLUME1,B12);
	Beep_Music_Do(GM,VOLUME1,B12);

	Beep_Music_Do(EH,VOLUME1,B2);
	Beep_Music_Do(CH,VOLUME1,B12);
	Beep_Music_Do(AM,VOLUME1,B12);
	Beep_Music_Do(BM,VOLUME1,B12);
	Beep_Music_Do(CH,VOLUME1,B12);

	Beep_Music_Do(BM,VOLUME1,B1);
	Beep_Music_Do(DH,VOLUME1,B1);
	Beep_Music_Do(CH,VOLUME1,B1);
	Beep_Music_Do(AM,VOLUME1,B1);

	Beep_Music_Do(GM,VOLUME1,B2);
	Beep_Music_Do(GM,VOLUME1,B12);
	Beep_Music_Do(0,VOLUME1,B12);
	Beep_Music_Do(EH,VOLUME1,B12);
	Beep_Music_Do(DH,VOLUME1,B12);

	Beep_Music_Do(CH,VOLUME1,B2);
	Beep_Music_Do(GM,VOLUME1,B1);
	Beep_Music_Do(EM,VOLUME1,B1);

	Beep_Music_Do(AM,VOLUME1,B2);
	Beep_Music_Do(FM,VOLUME1,B12);
	Beep_Music_Do(0,VOLUME1,B12);
	Beep_Music_Do(DH,VOLUME1,B12);
	Beep_Music_Do(CH,VOLUME1,B12);

	Beep_Music_Do(BH,VOLUME1,B2);
	Beep_Music_Do(AM,VOLUME1,B1);
	Beep_Music_Do(GM,VOLUME1,B1);

	Beep_Music_Do(GM,VOLUME1,B2);
	Beep_Music_Do(GM,VOLUME1,B12);
	Beep_Music_Do(0,VOLUME1,B12);
	Beep_Music_Do(GM,VOLUME1,B1);

	Beep_Music_Do(EH,VOLUME1,B2);
	Beep_Music_Do(DH,VOLUME1,B1);
	Beep_Music_Do(GM,VOLUME1,B1);

	Beep_Music_Do(CH,VOLUME1,B2);
	Beep_Music_Do(BM,VOLUME1,B1);
	Beep_Music_Do(BM,VOLUME1,B1);

	Beep_Music_Do(AM,VOLUME1,B1);
	Beep_Music_Do(GM,VOLUME1,B1);
	Beep_Music_Do(AM,VOLUME1,B1);
	Beep_Music_Do(DH,VOLUME1,B1);

	Beep_Music_Do(DH,VOLUME1,B2);
	Beep_Music_Do(DH,VOLUME1,B12);
	Beep_Music_Do(0,VOLUME1,B12);
	Beep_Music_Do(EH,VOLUME1,B12);
	Beep_Music_Do(DH,VOLUME1,B12);

	Beep_Music_Do(CH,VOLUME1,B2);
	Beep_Music_Do(GM,VOLUME1,B1);
	Beep_Music_Do(EM,VOLUME1,B1);

	Beep_Music_Do(AM,VOLUME1,B2);
	Beep_Music_Do(FM,VOLUME1,B12);
	Beep_Music_Do(0,VOLUME1,B12);
	Beep_Music_Do(DH,VOLUME1,B12);
	Beep_Music_Do(CH,VOLUME1,B12);

	Beep_Music_Do(BM,VOLUME1,B2);
	Beep_Music_Do(AM,VOLUME1,B1);
	Beep_Music_Do(EM,VOLUME1,B1);

	Beep_Music_Do(EH,VOLUME1,B2);
	Beep_Music_Do(EH,VOLUME1,B2);
}
}
