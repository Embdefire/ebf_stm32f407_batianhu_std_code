#include "./screen_dev/screen_dev.h"

void LCD_Device_Init(DEVICE_PARAM_TypeDef* p)
{
	
	//������飬ֻ������0-7
	if(p->my_display->LCD_SCAN_MODE >7 )
		return;
	
	//����ģʽ����XY��������ؿ��
	if(p->my_display->LCD_SCAN_MODE%2 == 0)	
	{
		//0 2 4 6ģʽ��X�������ؿ��Ϊ480��Y����Ϊ854
		p->my_display->LCD_X_LENGTH = p->my_display->dp_max_width;
		p->my_display->LCD_Y_LENGTH =	p->my_display->dp_max_height;
	}
	else				
	{
		//1 3 5 7ģʽ��X�������ؿ��Ϊ854��Y����Ϊ480
		p->my_display->LCD_X_LENGTH = p->my_display->dp_max_height;
		p->my_display->LCD_Y_LENGTH =	p->my_display->dp_max_width; 
	}
}



