#include "animations.h"
// 1.2KB   x,y

u16 arr_coordinate_X_memory[voltmeter_chart_line_lengthX ]; // ʵ�����Ž�-2 (-1�±� -1������)
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
	@brief�����ڵ�ѹ����ͼˢ��
	@param���������������Ĳ�����������������������
	@note��			�Լ�д�����
		���Ż��ռ�ǳ���
		ͨ���ԣ�
			��ֲ�����⡣������ж���Ͳ��У�ͬ����ˢ�µ�ѹ����������ʾ�������ġ�
			�������ĸ��¡��������ص����ɣ�ԭ����˼·�ǰ�����һ����һ���ص�x������������;�˺�����д�������ܵ������ؼ����ɵĵ��ࡣ
			��֮ʺɽһ���������İɡ�
		�����Ż��㣺
			��������洢���λ�á�����������ֱ�ӵ��û������ʽ(��̬ˢ��)���������ռ䲻���Ƿ����ͨ������һ��һ�е���ʾ���Դ����������̬ˢ�¡�
			���ߵĶ�̬��ʽ���������˴󲿷���Դ�� �������û��ߣ�������Ӧ�������������������ص㣬Ȼ�������һ���ƶ���
			

	@warning������chart_TEMP_point�����ɡ���if��ÿ�����Ӷ��õ���  ���ǲ�����ǰ��������µĵ�ֻ�ڵ�һ��ˢ�¶���ǰ�������⡣(���߼���������ԭ��)
*/
void refresh_voltmeter_chart(void)
{
	// ADC_Cmd(ADCx,ENABLE);  // ADC����ˢ����  ����Դ
	//int refresh_skip_distance;
	if(!chart_overflow){
		// ��һ�� 		/**/ /**/ /**/ /**/ /**/ /**/ 
		if(arr_coordinate_X_memory_write_index == 0)
		{
			// bug chart_TEMP_pointXY �����ļ��㲻����ǰ  һ��ǰ��û������ ԭ��ˢ��
			chart_TEMP_pointX = chart_origin_pointX + 1;
			chart_TEMP_pointY = (1 - (GetValue()/3.3)) * (voltmeter_chart_line_lengthY - 27) + value_line_start_pointY;  // ��ʱ��� -27
			arr_coordinate_X_memory[0] = chart_TEMP_pointX;
			arr_coordinate_Y_memory[0] = chart_TEMP_pointY;
			arr_coordinate_X_memory_write_index = 1;
		}
		// û����ǰ�Ĳ���
		else if (arr_coordinate_X_memory_write_index < voltmeter_chart_line_lengthX -2 )	// ������ ���ȳ�
		{
			// bug chart_TEMP_pointXY �����ļ��㲻����ǰ  һ��ǰ��û������ ԭ��ˢ��
			chart_TEMP_pointX = chart_TEMP_pointX + 1;
			chart_TEMP_pointY = (1 - (GetValue()/3.3)) * (voltmeter_chart_line_lengthY - 27) + value_line_start_pointY;  // ��ʱ���  -27
			arr_coordinate_X_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointX;
			arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointY;
			
			LCD_DrawLine_Color(arr_coordinate_X_memory[arr_coordinate_X_memory_write_index-1],arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index-1],chart_TEMP_pointX,chart_TEMP_pointY,RED);
			arr_coordinate_X_memory_write_index = arr_coordinate_X_memory_write_index + 1;
		}
		// ��ǰ��һ��
		else if(arr_coordinate_X_memory_write_index == voltmeter_chart_line_lengthX -2)
		{
			// bug chart_TEMP_pointXY �����ļ��㲻����ǰ  һ��ǰ��û������ ԭ��ˢ��
			chart_TEMP_pointX = chart_TEMP_pointX + 1;
			chart_TEMP_pointY = (1 - (GetValue()/3.3)) * (voltmeter_chart_line_lengthY - 27) + value_line_start_pointY;  // ��ʱ��� -27
			arr_coordinate_X_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointX;
			arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index] = chart_TEMP_pointY;
			
			//����
			LCD_DrawLine_Color(arr_coordinate_X_memory[arr_coordinate_X_memory_write_index-1],arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index-1],chart_TEMP_pointX,chart_TEMP_pointY,RED);
			
			chart_overflow = 1;		//������ ��ʼ���� ����
			arr_coordinate_X_memory_write_index = 0;	// �ɺ��� ��дλ��Ϊ0
			
		} 
	}
	else
	{
		// bug chart_TEMP_pointXY �����ļ��㲻����ǰ  һ��ǰ��û������ ԭ��ˢ��
		chart_TEMP_pointX = value_line_end_pointX + 1;	
		chart_TEMP_pointY = (1 - (GetValue()/3.3)) * (voltmeter_chart_line_lengthY - 27) + value_line_start_pointY;  // ��ʱ��� -27
		arr_coordinate_X_memory[voltmeter_chart_line_lengthX - 1] = chart_TEMP_pointX;
		arr_coordinate_Y_memory[voltmeter_chart_line_lengthX - 1] = chart_TEMP_pointY;
		
		for(int i = 1; i < voltmeter_chart_line_lengthX - 1; i = i + 1)
		{
			// ͼ������  ͨ���ı�������y������
			LCD_DrawLine_Color(arr_coordinate_X_memory[i-1], arr_coordinate_Y_memory[i-1],arr_coordinate_X_memory[i], arr_coordinate_Y_memory[i],BLACK); 		// ����
			LCD_DrawLine_Color(arr_coordinate_X_memory[i-1], arr_coordinate_Y_memory[i],arr_coordinate_X_memory[i], arr_coordinate_Y_memory[i+1],RED); 			// ����
			// ������������
			arr_coordinate_Y_memory[i-1] = arr_coordinate_Y_memory[i];
		}
			// �������������  ��д�����Ƿ����
			arr_coordinate_Y_memory[voltmeter_chart_line_lengthX - 2] = arr_coordinate_Y_memory[voltmeter_chart_line_lengthX - 1];
	}
	
	/*
	����
	����ˢ��  ������׼��ϸ�ֿ�
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
	ʧ��ʧ��
	
	else
	{
		delay_ms(1000);

		//printf("1(%u16)(%u16)\r\n",arr_coordinate_X_memory[1],arr_coordinate_Y_memory[1]);

		//printf("T(%u16)(%u16)\r\n",arr_coordinate_X_memory[voltmeter_chart_line_lengthX],arr_coordinate_Y_memory[voltmeter_chart_line_lengthX]);
		for(u16 i=0;i<voltmeter_chart_line_lengthX-1;i++)
		{
			// ��ǰ�ĵ�ȥ��
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
		chart_TEMP_pointY = (1 - (GetValue()/3.3)) * voltmeter_chart_line_lengthY + (voltmeter_chart_height/7)+ 10;  // ��ʱ���(voltmeter_chart_height/7)+ 10
		arr_coordinate_X_memory[voltmeter_chart_line_lengthX] = chart_TEMP_pointX;
		arr_coordinate_Y_memory[voltmeter_chart_line_lengthX] = chart_TEMP_pointY;
		LCD_DrawLine_Color(arr_coordinate_X_memory[voltmeter_chart_line_lengthX-1],arr_coordinate_Y_memory[voltmeter_chart_line_lengthX-1],
													arr_coordinate_X_memory[voltmeter_chart_line_lengthX],arr_coordinate_Y_memory[voltmeter_chart_line_lengthX],RED);
	}
	
	
	
	*/
	/*
	�������Ž� ʧ��  ����Ҫʱ��
	// �����
	else
	{
		// ����ƾ�����
		for(u16 i=0;i<=voltmeter_chart_line_lengthX - 1;i++)	// �̶����� ������
		{
			if(arr_coordinate_X_memory_write_index == voltmeter_chart_line_lengthX)
			{
				// ��ǰ�ĵ�ȥ��
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
				// ��ǰ�ĵ�ȥ��
				LCD_DrawFRONT_COLOR(arr_coordinate_X_memory[arr_coordinate_X_memory_write_index],arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index],BLACK);
				LCD_DrawLine_Color(arr_coordinate_X_memory[arr_coordinate_X_memory_write_index],
													arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index],
													arr_coordinate_X_memory[arr_coordinate_X_memory_write_index+1],
													arr_coordinate_Y_memory[arr_coordinate_X_memory_write_index+1],
													RED);
			}
		}
		// ������
		chart_TEMP_pointX = voltmeter_chart_line_lengthX;
		chart_TEMP_pointY = (1 - (GetValue()/3.3)) * voltmeter_chart_line_lengthY + (voltmeter_chart_height/7)+ 10;  // ��ʱ���(voltmeter_chart_height/7)+ 10
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

void show_voltmeter_chart_value(void) {
    float value = GetValue();

    // ��ȡ�������ֺ�С������
    int intValue = (int)value;
    int decimalPart = (int)((value - intValue) * 100);  // ���豣����λС��

    // ���������ֺ�С������ת��Ϊ�ַ�����
    char show_value_char[20];
    snprintf(show_value_char, sizeof(show_value_char), "%d.%02d", intValue, decimalPart);

    printf("data=%f\r\n", value);
    LCD_ShowString(value_line_start_pointX, value_line_start_pointY-16, 100, 16, 16, (u8*)show_value_char);
}

