#include "animations.h"
// 1.2KB   x,y

u16 arr_coordinate_X_memory[voltmeter_chart_line_lengthX ]; // 实际最优解-2 (-1下标 -1坐标轴)
u16 arr_coordinate_Y_memory[voltmeter_chart_line_lengthX ];
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

/*
	@brief：用于电压表动图刷新
	@param：用于描述函数的参数，包括参数名和描述。
	@note：			自己写着玩的
		可优化空间非常大
		通用性：
			移植有问题。如果放中断里就不行；同样的刷新电压表，他的显示是正常的。
			例如界面的更新。关于像素点生成，原生成思路是把数据一像素一像素的x轴间隔距离生成;此函数以写死，不能调整像素间生成的点间距。
			总之屎山一样，慢慢改吧。
		性能优化点：
			用了数组存储点的位置。由于现在是直接调用画点的形式(动态刷新)，因此数组空间不大，是否可以通过访问一列一列的显示器显存的数据来静态刷新。
			画线的动态形式生成消耗了大部分资源。 新数据用画线，旧数据应当遍历相对因区域的像素点，然后复制黏贴一样移动。
			

	@warning：关于chart_TEMP_point点生成。在if的每个分钟都用到了  但是不能提前，会出现新的点只在第一列刷新而不前进的问题。(从逻辑上理不清原因)
*/
void refresh_voltmeter_chart(void)
{
	// ADC_Cmd(ADCx,ENABLE);  // ADC跟着刷新走  耗资源
	//int refresh_skip_distance;
	if(!chart_overflow){
		// 第一次 		/**/ /**/ /**/ /**/ /**/ /**/ 
		if(arr_coordinate_X_memory_write_index == 0)
		{
			// bug chart_TEMP_pointXY 两个的计算不能提前  一提前就没有曲线 原地刷新
			chart_TEMP_pointX = chart_origin_pointX + 1;
			chart_TEMP_pointY = (1 - (GetValue()/3.3)) * (voltmeter_chart_line_lengthY - 27) + value_line_start_pointY;  // 临时解决 -27
			arr_coordinate_X_memory[0] = chart_TEMP_pointX;
			arr_coordinate_Y_memory[0] = chart_TEMP_pointY;
			arr_coordinate_X_memory_write_index = 1;
		}
		// 没满格前的操作
		else if (arr_coordinate_X_memory_write_index < voltmeter_chart_line_lengthX -2 )	// 坐标轴 宽度长
		{
			// bug chart_TEMP_pointXY 两个的计算不能提前  一提前就没有曲线 原地刷新
			chart_TEMP_pointX = chart_TEMP_pointX + 1;
			chart_TEMP_pointY = (1 - (GetValue()/3.3)) * (voltmeter_chart_line_lengthY - 27) + value_line_start_pointY;  // 临时解决  -27
			arr_coordinate_X_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointX;
			arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointY;
			
			LCD_DrawLine_Color(arr_coordinate_X_memory[arr_coordinate_X_memory_write_index-1],arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index-1],chart_TEMP_pointX,chart_TEMP_pointY,RED);
			arr_coordinate_X_memory_write_index = arr_coordinate_X_memory_write_index + 1;
		}
		// 满前的一步
		else if(arr_coordinate_X_memory_write_index == voltmeter_chart_line_lengthX -2)
		{
			// bug chart_TEMP_pointXY 两个的计算不能提前  一提前就没有曲线 原地刷新
			chart_TEMP_pointX = chart_TEMP_pointX + 1;
			chart_TEMP_pointY = (1 - (GetValue()/3.3)) * (voltmeter_chart_line_lengthY - 27) + value_line_start_pointY;  // 临时解决 -27
			arr_coordinate_X_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointX;
			arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointY;
			
			//画线
			LCD_DrawLine_Color(arr_coordinate_X_memory[arr_coordinate_X_memory_write_index-1],arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index-1],chart_TEMP_pointX,chart_TEMP_pointY,RED);
			
			chart_overflow = 1;		//画满了 开始左移 动画
			arr_coordinate_X_memory_write_index = 0;	// 可忽略 读写位置为0
			
		} 
	}
	else
	{
		// bug chart_TEMP_pointXY 两个的计算不能提前  一提前就没有曲线 原地刷新
		chart_TEMP_pointX = value_line_end_pointX + 1;	
		chart_TEMP_pointY = (1 - (GetValue()/3.3)) * (voltmeter_chart_line_lengthY - 27) + value_line_start_pointY;  // 临时解决 -27
		arr_coordinate_X_memory[voltmeter_chart_line_lengthX - 1] = chart_TEMP_pointX;
		arr_coordinate_Y_memory[voltmeter_chart_line_lengthX - 1] = chart_TEMP_pointY;
		
		for(int i = 1; i < voltmeter_chart_line_lengthX - 1; i = i + 1)
		{
			// 图形左移  通过改变相对因的y轴坐标
			LCD_DrawLine_Color(arr_coordinate_X_memory[i-1], arr_coordinate_Y_memory[i-1],arr_coordinate_X_memory[i], arr_coordinate_Y_memory[i],BLACK); 		// 消除
			LCD_DrawLine_Color(arr_coordinate_X_memory[i-1], arr_coordinate_Y_memory[i],arr_coordinate_X_memory[i], arr_coordinate_Y_memory[i+1],RED); 			// 画线
			// 数组数据左移
			arr_coordinate_Y_memory[i-1] = arr_coordinate_Y_memory[i];
		}
			// 最后新数据左移  不写上面是防溢出
			arr_coordinate_Y_memory[voltmeter_chart_line_lengthX - 2] = arr_coordinate_Y_memory[voltmeter_chart_line_lengthX - 1];
	}
	
	/*
	保留
	暴力刷新  但是又准又细又快
	else
	{
		LCD_Fill(value_line_start_pointX + 1 ,
				   value_line_start_pointY,
				   value_line_end_pointX,
				   value_line_end_pointY - 1,
				   BLACK);
		chart_overflow = 0;
	}
	*/
	
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

void show_voltmeter_chart_value(void) 
{
    float value = GetValue();

    // 提取整数部分和小数部分
    int intValue = (int)value;
    int decimalPart = (int)((value - intValue) * 100);  // 假设保留两位小数

    // 将整数部分和小数部分转换为字符数组
    char show_value_char[20];
    snprintf(show_value_char, sizeof(show_value_char), "%d.%02d", intValue, decimalPart);
    LCD_ShowString(value_line_start_pointX, value_line_start_pointY-16, 100, 16, 16, (u8*)show_value_char);
}

