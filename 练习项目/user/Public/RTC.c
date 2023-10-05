#include "RTC.h"

#define SECONDS_PER_DAY 86400
#define SECONDS_PER_HOUR 3600
#define SECONDS_PER_MINUTE 60

void RTC_Init()
{
	printf("RTC_Init=%d\r\n",1);
	// 注意 RTC使用的RTCCLK时钟源，APB使用的是PCLK1时钟源。两者不一定一样。
	// 使能PWR功耗时钟  BKP后备寄存器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP,ENABLE);
	
	if (BKP_ReadBackupRegister(BKP_DR1) == 0x0825)	// 已初始化
	{
		printf("Rif=%d\r\n",1);
		RTC_WaitForSynchro();			 				// 等待最近一次对 RTC 寄存器的写操作完成
		RTC_ITConfig(RTC_IT_SEC, ENABLE); // 使能 RTC 秒中断
		RTC_WaitForLastTask();				 		// 等待最近一次对 RTC 寄存器的写操作完成
	}
	else 	// 没初始化过，对其功能进行初始化
	{
		printf("Rif=%d\r\n",0);
		BKP_DeInit();
		
		// 可用宏定义以后决定时钟源
		RCC_LSICmd(ENABLE);				// 内部低速时钟 启动  40khz
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);   // 设置RTC时钟源为LSI
		RCC_RTCCLKCmd(ENABLE);		// RTC时钟使能
		RTC_WaitForLastTask(); 
		RTC_WaitForSynchro(); 						// 等待 RTC 寄存器同步
		RTC_WaitForLastTask();						// 等待最近一次对 RTC 寄存器的写操作完成
		
		
		RTC_EnterConfigMode();						// 允许配置
		RTC_SetPrescaler(9999); 						// 设置 RTC 预分频的值  40k/40k = 1

		//RTC_WaitForLastTask(); 						// ----死循环    等待最近一次对 RTC 寄存器的写操作完成

		RTC_SetCounter(1696478761); // 设置一下时间 unix时间戳 2023-10-05 12:06:01
		RTC_ExitConfigMode(); 						// 退出配置模式
		

		BKP_WriteBackupRegister(BKP_DR1, 0x0825); //向指定的后备寄存器中写入用户程序数据
		RTC_ITConfig(RTC_IT_SEC, ENABLE); // 使能 RTC 秒中断
	}
	
}




// 检查是否为闰年
int isLeapYear(int year)
{
    if (year % 4 != 0) {
        return 0;
    } else if (year % 100 != 0) {
        return 1;
    } else if (year % 400 != 0) {
        return 0;
    } else {
        return 1;
    }
}

// 获取每个月的天数
int getDaysInMonth(int month, int year)
{
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year) && month == 2) {
        return 29;
    }
    return daysInMonth[month - 1];
}

void UnixtimeToTime(u32 timestamp, int* year, int* month, int* day, int* hour, int* minute, int* second)
{
    *second = timestamp % SECONDS_PER_MINUTE;
    timestamp /= SECONDS_PER_MINUTE;
    *minute = timestamp % SECONDS_PER_MINUTE;
    timestamp /= SECONDS_PER_MINUTE;
    *hour = timestamp % SECONDS_PER_HOUR;
    timestamp /= SECONDS_PER_HOUR;

    unsigned int years = timestamp / (SECONDS_PER_DAY * (isLeapYear(*year) ? 366 : 365));
    timestamp -= years * (SECONDS_PER_DAY * (isLeapYear(*year) ? 366 : 365));
    
    *year = years + 1970;

    *month = 1;
    while (timestamp >= getDaysInMonth(*month, *year) * SECONDS_PER_DAY) {
        timestamp -= getDaysInMonth(*month, *year) * SECONDS_PER_DAY;
        (*month)++;
    }

    *day = timestamp / SECONDS_PER_DAY + 1; // +1 because day of the month starts from 1
}

void showTimeToScreen()
{
	#include "animations.h"
	int year;int month; int day; int hour; int minute;int second;
	u8 showRTCString[7];
	UnixtimeToTime(RTC_GetCounter(),&year,&month,&day,&hour,&minute,&second);
	sprintf(showRTCString, "%d年%d月%d日", year, month,day);
	LCD_ShowString(30,300,100,16,16,showRTCString);
	
}