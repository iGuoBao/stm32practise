#ifndef __ANIMATIONS_H__
#define __ANIMATIONS_H__

#include "tftlcd.h"
#include	"ADC.h"

#define voltmeter_window_start_pointX 	1
#define voltmeter_window_start_pointY		1
#define voltmeter_window_width    320
#define voltmeter_window_height   200 


#define voltmeter_chart_start_pointX  	5  + voltmeter_window_start_pointX
#define voltmeter_chart_start_pointY 		10 + voltmeter_window_start_pointY
#define voltmeter_chart_width    				300
#define voltmeter_chart_height    			180
#define voltmeter_chart_line_lengthX		240
#define voltmeter_chart_line_lengthY		150


void draw_voltmeter_window(void);
void draw_voltmeter_chart(void);
void draw_voltmeter_chart_value_time_line(void);

void refresh_voltmeter_chart(void);
void show_voltmeter_chart_value(void);




#endif