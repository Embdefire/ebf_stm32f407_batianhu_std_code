/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ���ݴ�����-��������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h"  

#include "screen_dev.h"

#include "./touch/gt9xx.h"
#include "./lcd/bsp_nt35510_lcd.h"
#include "./LCD_4_5/lcd/bsp_ili9806g_lcd.h"

#include "./touch/palette.h"


/* ʵ����һ����ʾ���豸,���豸����ʾ���ԡ��������ԡ���ʾ����ʵ���� */
DEVICE_PARAM_TypeDef NT35510 = 
{
	.my_touchpanel = &GT917S_TP_Desc,
	.my_display = &NT35510_DP_Desc,
	.my_disp_driver = &NT35510_DP_Driver,
};

DEVICE_PARAM_TypeDef ILI9806G = 
{
	.my_touchpanel = &GT5688_TP_Desc,
	.my_display = &ILI9806G_DP_Desc,
	.my_disp_driver = &ILI9806G_DP_Driver,
};
/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main ( void )
{
	LED_GPIO_Config();

	Debug_USART_Config();	

	
	//����0��3��5��6 ģʽ�ʺϴ���������ʾ���֣�
	//���Ƽ�ʹ������ģʽ��ʾ����	����ģʽ��ʾ���ֻ��о���Ч��			
	//���� 6 ģʽΪ�󲿷�Һ�����̵�Ĭ����ʾ����  

	/* �ȳ�ʼ���������������������Һ����ɨ�跽�����ƥ��Ĵ������� */
	/* ÿ���޸�Һ��ɨ�跽���Ӧ���µ���һ��GTP_Init_Panel�������´������� */
	/* ��ʼ����ɺ󣬻᷵�ص�ǰ����оƬ���ͣ���������ʹ�ö�Ӧ����ʾ������ */
	switch ( GTP_Init_Panel())
	{
		case GT5688:
		{
			LCD = &ILI9806G;
		}break;
		case GT917S:
		{
			LCD = &NT35510;
		}break;
		default:
		{
			LCD = &ILI9806G;
		}break;
	};
	
	/* ��ʼ����ʾ�� */
	LCD->my_disp_driver->xx_init_func();
	printf("\r\n ********** ����������� *********** \r\n"); 
	printf("\r\n ��������ʾ�����������Ķ������е�readme.txt�ļ�˵��������Ҫ���FLASH��ˢ��ģ����\r\n"); 
 
	//���ƴ����������
	Palette_Init();
    
	while ( 1 )
	{
	}
	
	
}





/*********************************************END OF FILE**********************/

