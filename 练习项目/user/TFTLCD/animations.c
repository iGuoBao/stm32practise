#include "animations.h"
// 1.2KB   x,y

// 线段长度为x轴长度

int arr_coordinate_X_memory_write_index = 0;
u8 chart_overflow = 0;
u16 arr_coordinate_X_memory[voltmeter_chart_line_lengthX ], \
		arr_coordinate_Y_memory[voltmeter_chart_line_lengthX ], \
		chart_origin_pointX, \
		chart_origin_pointY, \
		chart_TEMP_pointX, \
		chart_TEMP_pointY, \
		value_line_start_pointX = (voltmeter_chart_start_pointX + (voltmeter_chart_width/7)), \
		value_line_start_pointY = (voltmeter_chart_start_pointY + (voltmeter_chart_height/7)), \
		value_line_end_pointX, \
		value_line_end_pointY;

void draw_voltmeter_window(void)
{
	LCD_Fill(voltmeter_window_start_pointX,
					 voltmeter_window_start_pointY,
					 voltmeter_window_width,
					 voltmeter_window_height,
					 BLACK);
}
void draw_voltmeter_chart(void)
{
	LCD_Fill(voltmeter_chart_start_pointX,
				   voltmeter_chart_start_pointX,
				   voltmeter_chart_width,
				   voltmeter_chart_height,
				   BLACK);
}

void draw_voltmeter_chart_value_time_line(void)
{
	value_line_end_pointX = value_line_start_pointX;
	value_line_end_pointY = (voltmeter_chart_start_pointY + voltmeter_chart_line_lengthY);
	LCD_DrawLine_Color(value_line_start_pointX,value_line_start_pointY,value_line_end_pointX,value_line_end_pointY,YELLOW);
	
	chart_origin_pointX = value_line_end_pointX;
	chart_origin_pointY = value_line_end_pointY;
	
	value_line_end_pointX = (chart_origin_pointX + voltmeter_chart_line_lengthX);
	value_line_end_pointY = value_line_end_pointY;
	LCD_DrawLine_Color(chart_origin_pointX,chart_origin_pointY,value_line_end_pointX,value_line_end_pointY,YELLOW);
}


void refresh_voltmeter_chart(void)
{
	ADC_Cmd(ADCx,ENABLE);
	//int refresh_skip_distance;
	if(!chart_overflow){
		if(arr_coordinate_X_memory_write_index == 0)
		{
			// bug chart_TEMP_pointXY ??????????????  ????????????? ??????
			chart_TEMP_pointX = chart_origin_pointX + 1;
			chart_TEMP_pointY = (1 - (GetValue()/3.3)) * (voltmeter_chart_line_lengthY - 27) + value_line_start_pointY;  // ?????? -27
			arr_coordinate_X_memory[0] = chart_TEMP_pointX;
			arr_coordinate_Y_memory[0] = chart_TEMP_pointY;
			arr_coordinate_X_memory_write_index = 1;
		}
		else if (arr_coordinate_X_memory_write_index < voltmeter_chart_line_lengthX -2 )	// ?????? ?????
		{
			// bug chart_TEMP_pointXY ??????????????  ????????????? ??????
			chart_TEMP_pointX = chart_TEMP_pointX + 1;
			chart_TEMP_pointY = (1 - (GetValue()/3.3)) * (voltmeter_chart_line_lengthY - 27) + value_line_start_pointY;  // ??????  -27
			arr_coordinate_X_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointX;
			arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointY;
			
			LCD_DrawLine_Color(arr_coordinate_X_memory[arr_coordinate_X_memory_write_index-1],arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index-1],chart_TEMP_pointX,chart_TEMP_pointY,RED);
			arr_coordinate_X_memory_write_index = arr_coordinate_X_memory_write_index + 1;
		}
		else if(arr_coordinate_X_memory_write_index == voltmeter_chart_line_lengthX -2)
		{

			chart_TEMP_pointX = chart_TEMP_pointX + 1;
			chart_TEMP_pointY = (1 - (GetValue()/3.3)) * (voltmeter_chart_line_lengthY - 27) + value_line_start_pointY;  // ?????? -27
			arr_coordinate_X_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointX;
			arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointY;
			
			LCD_DrawLine_Color(arr_coordinate_X_memory[arr_coordinate_X_memory_write_index-1],arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index-1],chart_TEMP_pointX,chart_TEMP_pointY,RED);
			
			chart_overflow = 1;		
			arr_coordinate_X_memory_write_index = 0;	
			
		} 
	}
	else
	{
		chart_TEMP_pointX = value_line_end_pointX + 1;	
		chart_TEMP_pointY = (1 - (GetValue()/3.3)) * (voltmeter_chart_line_lengthY - 27) + value_line_start_pointY;  // ?????? -27
		arr_coordinate_X_memory[voltmeter_chart_line_lengthX - 1] = chart_TEMP_pointX;
		arr_coordinate_Y_memory[voltmeter_chart_line_lengthX - 1] = chart_TEMP_pointY;
		
		for(int i = 1; i < voltmeter_chart_line_lengthX - 1; i = i + 1)
		{
			LCD_DrawLine_Color(arr_coordinate_X_memory[i-1], arr_coordinate_Y_memory[i-1],arr_coordinate_X_memory[i], arr_coordinate_Y_memory[i],BLACK); 		// ????
			LCD_DrawLine_Color(arr_coordinate_X_memory[i-1], arr_coordinate_Y_memory[i],arr_coordinate_X_memory[i], arr_coordinate_Y_memory[i+1],RED); 			// ????
			arr_coordinate_Y_memory[i-1] = arr_coordinate_Y_memory[i];
		}
			arr_coordinate_Y_memory[voltmeter_chart_line_lengthX - 2] = arr_coordinate_Y_memory[voltmeter_chart_line_lengthX - 1];
	}
}

void show_voltmeter_chart_value(void) {
    float value = GetValue();

    // ????????????С??????
    int intValue = (int)value;
    int decimalPart = (int)((value - intValue) * 100);  // ???豣????λС??

    // ???????????С?????????????????
    char show_value_char[20];
    snprintf(show_value_char, sizeof(show_value_char), "%d.%02d", intValue, decimalPart);

    //printf("data=%f\r\n", value);
    LCD_ShowString(value_line_start_pointX, value_line_start_pointY-16, 100, 16, 16, (u8*)show_value_char);
}

