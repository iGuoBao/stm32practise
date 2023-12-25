#ifndef __RTC_H__
#define __RTC_H__

#include "stm32f10x.h"
#include "exti.h"


//ʱ��ṹ��
typedef struct 
{
	u8 hour;
	u8 min;
	u8 sec;	
	
	//������������
	u16 w_year;
	u8  w_month;
	u8  w_date;
	u8  week;		 
}_calendar;					 
extern _calendar calendar;	//�����ṹ��

u8 RTC_Init(void);        //��ʼ��RTC,����0,ʧ��;1,�ɹ�;
u8 Is_Leap_Year(u16 year);//ƽ��,�����ж�
u8 RTC_Alarm_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);
u8 RTC_Get(void);         //����ʱ��   
u8 RTC_Get_Week(u16 year,u8 month,u8 day);
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);//����ʱ��	

// �ɰ� ����
// void UnixtimeToTime(u32 timestamp, int* year, int* month, int* day, int* hour, int* minute, int* second);
void showTimeToScreen();		// δ֪bug

void showLastDownloadTimeToScreen();

#endif