#include "animations.h"
// 1.2KB   x,y
u16 arr_coordinate_X_memory[voltmeter_chart_line_lengthX];
u16 arr_coordinate_Y_memory[voltmeter_chart_line_lengthY];
int arr_coordinate_X_memory_write_index = 0;

u16 chart_origin_pointX;
u16 chart_origin_pointY;
u16 chart_TEMP_pointX;
u16 chart_TEMP_pointY;
u16 value_line_start_pointX = (voltmeter_chart_start_pointX + (voltmeter_chart_width/7));
u16 value_line_start_pointY = (voltmeter_chart_start_pointY + (voltmeter_chart_height/7));
u16 value_line_end_pointX;
u16 value_line_end_pointY;

u8 chart_overflow = 0;


void draw_voltmeter_window(void)
{
	LCD_Fill(voltmeter_window_start_pointX,
					 voltmeter_window_start_pointY,
					 voltmeter_window_width,
					 voltmeter_window_height,
					 LIGHTGRAY);
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
	if(!chart_overflow){
		// 第一次
		if(arr_coordinate_X_memory_write_index == 0)
		{
			chart_TEMP_pointX = chart_origin_pointX;
			chart_TEMP_pointY = (1 - (GetValue()/3.3)) * (voltmeter_chart_line_lengthY) + (voltmeter_chart_height/7) + 10;  // 临时解决(voltmeter_chart_height/7)+ 10
			arr_coordinate_X_memory[0] = chart_TEMP_pointX;
			arr_coordinate_Y_memory[0] = chart_TEMP_pointY;
			
			arr_coordinate_X_memory_write_index = 1;
		}
		// 没满格前
		else if (arr_coordinate_X_memory_write_index < voltmeter_chart_line_lengthX-1)	// 坐标轴 宽度长
		{
			chart_TEMP_pointX = chart_TEMP_pointX + 1;
			chart_TEMP_pointY = (1 - (GetValue()/3.3)) * voltmeter_chart_line_lengthY + (voltmeter_chart_height/7)+ 10;  // 临时解决(voltmeter_chart_height/7)+ 10
			arr_coordinate_X_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointX;
			arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointY;
			
			LCD_DrawLine_Color(arr_coordinate_X_memory[arr_coordinate_X_memory_write_index-1],arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index-1],chart_TEMP_pointX,chart_TEMP_pointY,RED);
			arr_coordinate_X_memory_write_index++;
		}
		else if(arr_coordinate_X_memory_write_index == voltmeter_chart_line_lengthX -1)
		{
			chart_TEMP_pointX = chart_TEMP_pointX + 1;
			chart_TEMP_pointY = (1 - (GetValue()/3.3)) * voltmeter_chart_line_lengthY + (voltmeter_chart_height/7)+ 10;  // 临时解决(voltmeter_chart_height/7)+ 10
			arr_coordinate_X_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointX;
			arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointY;
			
			LCD_DrawLine_Color(arr_coordinate_X_memory[arr_coordinate_X_memory_write_index-1],arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index-1],chart_TEMP_pointX,chart_TEMP_pointY,RED);
			
			chart_overflow = 1;
			arr_coordinate_X_memory_write_index = 0;
			
		} 
	}
	else
	{
		LCD_Fill(value_line_start_pointX + 1 ,
				   value_line_start_pointY,
				   value_line_end_pointX,
				   value_line_end_pointY - 1,
				   BLACK);
		chart_overflow = 0;
	}
	
	
	/*
	失败失败
	
	else
	{
		delay_ms(1000);

		//printf("1(%u16)(%u16)\r\n",arr_coordinate_X_memory[1],arr_coordinate_Y_memory[1]);

		//printf("T(%u16)(%u16)\r\n",arr_coordinate_X_memory[voltmeter_chart_line_lengthX],arr_coordinate_Y_memory[voltmeter_chart_line_lengthX]);
		for(u16 i=0;i<voltmeter_chart_line_lengthX-1;i++)
		{
			// 以前的点去除
			LCD_DrawLine_Color(arr_coordinate_X_memory[i],arr_coordinate_Y_memory[i],
													arr_coordinate_X_memory[i+1],arr_coordinate_Y_memory[i+1],BLACK);
			
			arr_coordinate_X_memory[i] = arr_coordinate_X_memory[i + 1];
			arr_coordinate_Y_memory[i] = arr_coordinate_Y_memory[i + 1];
			if(!i)
			{
				LCD_DrawLine_Color(arr_coordinate_X_memory[i-1],arr_coordinate_Y_memory[i-1],
													arr_coordinate_X_memory[i],arr_coordinate_Y_memory[i],RED);
			}
		}
		chart_TEMP_pointX = voltmeter_chart_line_lengthX;
		chart_TEMP_pointY = (1 - (GetValue()/3.3)) * voltmeter_chart_line_lengthY + (voltmeter_chart_height/7)+ 10;  // 临时解决(voltmeter_chart_height/7)+ 10
		arr_coordinate_X_memory[voltmeter_chart_line_lengthX] = chart_TEMP_pointX;
		arr_coordinate_Y_memory[voltmeter_chart_line_lengthX] = chart_TEMP_pointY;
		LCD_DrawLine_Color(arr_coordinate_X_memory[voltmeter_chart_line_lengthX-1],arr_coordinate_Y_memory[voltmeter_chart_line_lengthX-1],
													arr_coordinate_X_memory[voltmeter_chart_line_lengthX],arr_coordinate_Y_memory[voltmeter_chart_line_lengthX],RED);
	}
	
	
	
	*/
	/*
	理想最优解 失败  还需要时间
	// 满格后
	else
	{
		// 左回移旧数据
		for(u16 i=0;i<=voltmeter_chart_line_lengthX - 1;i++)	// 固定次数 旧数据
		{
			if(arr_coordinate_X_memory_write_index == voltmeter_chart_line_lengthX)
			{
				// 以前的点去除
				LCD_DrawFRONT_COLOR(arr_coordinate_X_memory[arr_coordinate_X_memory_write_index],arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index],BLACK);
				LCD_DrawLine_Color(arr_coordinate_X_memory[arr_coordinate_X_memory_write_index],
													arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index],
													arr_coordinate_X_memory[0],
													arr_coordinate_Y_memory[0],
													RED);
				arr_coordinate_X_memory_write_index = 0;
			}
			else 
			{
				arr_coordinate_X_memory_write_index++;
				// 以前的点去除
				LCD_DrawFRONT_COLOR(arr_coordinate_X_memory[arr_coordinate_X_memory_write_index],arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index],BLACK);
				LCD_DrawLine_Color(arr_coordinate_X_memory[arr_coordinate_X_memory_write_index],
													arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index],
													arr_coordinate_X_memory[arr_coordinate_X_memory_write_index+1],
													arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index+1],
													RED);
			}
		}
		// 新数据
		chart_TEMP_pointX = voltmeter_chart_line_lengthX;
		chart_TEMP_pointY = (1 - (GetValue()/3.3)) * voltmeter_chart_line_lengthY + (voltmeter_chart_height/7)+ 10;  // 临时解决(voltmeter_chart_height/7)+ 10
		arr_coordinate_X_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointX;
		arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointY;
		
		if(arr_coordinate_X_memory_write_index == 0)
		{
			LCD_DrawLine_Color(arr_coordinate_X_memory[voltmeter_chart_line_lengthX-1],arr_coordinate_Y_memory[voltmeter_chart_line_lengthX-1],chart_TEMP_pointX,chart_TEMP_pointY,RED);
		}
		LCD_DrawLine_Color(arr_coordinate_X_memory[arr_coordinate_X_memory_write_index-1],arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index-1],chart_TEMP_pointX,chart_TEMP_pointY,RED);
	}
	*/
}


