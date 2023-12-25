#ifndef __NTC_H__
#define __NTC_H__

#include "math.h"
#include "stm32f10x.h"
#include "NTC.h"
#include "ADC.h"






void NTC_Init(void);
float get_NTC_value(void);
	

#endif