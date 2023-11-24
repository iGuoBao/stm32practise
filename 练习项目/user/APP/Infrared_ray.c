#include "infrared_ray.h"


u8 Infrared_ray_Receive_Data_Index;
int Infrared_ray_Receive_Data[300];


u8 Infrared_ray_synchronous_Receive_flag = 0;  // ͬ����־ ��ͬ���� 1, ��ʱ �����  0
u8 Infrared_ray_first_receive_flag; 
u8 Infrared_ray_Receive_over_flag = 0;	// ��ʱ��־  
u8 Infrared_ray_Receive_flag;		// ͨ������󱻸�ֵ1  ͨ��getGPIO��ƽ���

u32 Infrared_ray_timeus_up, Infrared_ray_timeus_down;


/// @brief ��������,100us���; �½��ز���
void Infrared_ray_init()
{
	RCC_APB2PeriphClockCmd(Infrared_ray_Receive_RCC, ENABLE); // GPIO����ʱ��	
	RCC_APB1PeriphClockCmd(infrared_ray_TIMx_RCC, ENABLE);	  // ��ʱ��ʱ��
	
	//IO�ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	//�������IO����
	GPIO_InitStructure.GPIO_Pin = Infrared_ray_Receive_PIN;  		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ; 	//��������
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 	//����
	GPIO_Init(Infrared_ray_Receive_PORT, &GPIO_InitStructure);
	
	// ͼ���� ������  ӦдTIM�� 72M
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	// TIM4���� 100us  		
	TIM_TimeBaseStructure.TIM_Prescaler = 100 - 1;   
	TIM_TimeBaseStructure.TIM_Period = 71;  
    TIM_TimeBaseInit(infrared_ray_TIMx, &TIM_TimeBaseStructure);

	TIM_ITConfig(infrared_ray_TIMx,TIM_IT_Update,ENABLE);	  	// ��������ж�
	TIM_ClearFlag(infrared_ray_TIMx, TIM_FLAG_Update);		  	  // �����־λ
	TIM_Cmd(infrared_ray_TIMx, ENABLE);	// ʹ��

	//---
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	TIM_ICInitStructure.TIM_Channel = infrared_ray_TIMx_Channel;
	// TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;		// �����½��ز���
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;		// �½��ز���
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	// ֱ������Դ
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;			    // Ԥ��Ƶ1  1m
	TIM_ICInit(infrared_ray_TIMx, &TIM_ICInitStructure);

	TIM_ITConfig(infrared_ray_TIMx, TIM_IT_CC4, ENABLE);// ʹ��TIM4�����ж�
}

// ���� ����32λ���� �����ֽ�
void printf_Infrared_ray_Receive_Data_Decode()
{
	u8 index32 = 0;
	printf("\r\n");
	for (int i = 1; i <= 4; i++)
	{
		u8 temp_byte = 0x00;
		//ÿ8λλȨ��� ��װ�ֽ� ��16���ƴ�ӡ
		for (int j = 1; j <= 8; j++)
		{
			u8 temp_reveive_data = Infrared_ray_Receive_Data[index32];
			if(temp_reveive_data >= 10 && temp_reveive_data <= 15) // 1125us  100us
			{
				Infrared_ray_Receive_Data[index32] = 0;
			}
			else if(temp_reveive_data >= 19 && temp_reveive_data <= 25) // 2250us  100us
			{
				Infrared_ray_Receive_Data[index32] = 1;
			}

			temp_byte = temp_byte + ((Infrared_ray_Receive_Data[index32]) << (8 - j));
			index32++;
		}
		printf("%2x ",temp_byte);
		//printf("%d ",Infrared_ray_Receive_Data[i - 1]); //*100us
	}
}

Infrared_ray_Data_Struct Decode_Infrared_ray_Receive_Data()
{
	u32 temp_byte = 0x00;
	Infrared_ray_Data_Struct Infrared_ray_Data_Struct_temp;
	for (int i = 0; i < 32; i++)
	{
		u8 temp_reveive_data = Infrared_ray_Receive_Data[i];
		if(temp_reveive_data >= 10 && temp_reveive_data <= 15) // 1125us  100us
		{
			Infrared_ray_Receive_Data[i] = 0;
		}
		else if(temp_reveive_data >= 19 && temp_reveive_data <= 25) // 2250us  100us
		{
			Infrared_ray_Receive_Data[i] = 1;
		}
		temp_byte = temp_byte + ((Infrared_ray_Receive_Data[i]) << (31 - i));
	}
	// = ���λ8λ��
	Infrared_ray_Data_Struct_temp.addr   = (temp_byte >> 24) & 0xFF;
	Infrared_ray_Data_Struct_temp.addr_f = (temp_byte >> 16) & 0xFF;
	Infrared_ray_Data_Struct_temp.data   = (temp_byte >> 8) & 0xFF;
	Infrared_ray_Data_Struct_temp.data_f = temp_byte & 0xFF;


	return Infrared_ray_Data_Struct_temp;
}
