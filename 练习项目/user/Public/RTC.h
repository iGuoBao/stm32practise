#ifndef __RTC_H__
#define __RTC_H__

#include "stm32f10x.h"
#include "exti.h"


void RTC_Init();

void UnixtimeToTime(u32 timestamp, int* year, int* month, int* day, int* hour, int* minute, int* second);
void showTimeToScreen();

#endif