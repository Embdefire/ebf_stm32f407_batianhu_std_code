/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   SRAMӦ������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h"  
#include "./sram/sram.h"
#include "./lcd/bsp_ili9806g_lcd.h"
#include "./touch/gt9xx.h"
#include "./touch/palette.h"

static void LCD_Test(void);	
static void Delay ( __IO uint32_t nCount );
void Printf_Charater(void)   ;


/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main ( void )
{
    LED_GPIO_Config();
	ILI9806G_Init ();         //LCD ��ʼ��

	Debug_USART_Config();		
	
    /* ��ʼ�������� */
    GTP_Init_Panel(); 
	
    
    /*���û��庯��*/
//	Palette_Init();
    
	while ( 1 )
	{
		//LCD_Test();
	}
	
	
}




/*���ڲ��Ը���Һ���ĺ���*/
void LCD_Test(void)
{
	/*��ʾ��ʾ����*/
	static uint8_t testCNT = 0;	
	char dispBuff[100];
	
	testCNT++;	
	
	LCD_SetFont(&Font24x32);
	LCD_SetColors(RED,BLACK);

  ILI9806G_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* ��������ʾȫ�� */
	/********��ʾ�ַ���ʾ��*******/
  ILI9806G_DispStringLine_EN(LINE(0),"BH 4.5 inch LCD para:");
  ILI9806G_DispStringLine_EN(LINE(1),"Image resolution:480x854 px");
  ILI9806G_DispStringLine_EN(LINE(2),"ILI9806G LCD driver");
  ILI9806G_DispStringLine_EN(LINE(3),"GT5688 Touch Pad driver");
  
	/********��ʾ����ʾ��*******/
	LCD_SetFont(&Font24x32);
	LCD_SetTextColor(GREEN);

	/*ʹ��c��׼��ѱ���ת�����ַ���*/
	sprintf(dispBuff,"Count : %d ",testCNT);
  ILI9806G_ClearLine(LINE(4));	/* ����������� */
	
	/*Ȼ����ʾ���ַ������ɣ���������Ҳ����������*/
	ILI9806G_DispStringLine_EN(LINE(4),dispBuff);

	/*******��ʾͼ��ʾ��******/
	LCD_SetFont(&Font24x32);
  /* ��ֱ�� */
  
  ILI9806G_ClearLine(LINE(4));/* ����������� */
	LCD_SetTextColor(BLUE);

  ILI9806G_DispStringLine_EN(LINE(4),"Draw line:");
  
	LCD_SetTextColor(RED);
  ILI9806G_DrawLine(50,170,850,175);  
  ILI9806G_DrawLine(50,200,850,275);
  
	LCD_SetTextColor(GREEN);
  ILI9806G_DrawLine(50,270,850,375);  
  ILI9806G_DrawLine(50,300,850,475);
	
	LCD_SetTextColor(BLUE);
  ILI9806G_DrawLine(50,320,850,225);  
  ILI9806G_DrawLine(50,400,850,395);
  
  Delay(0x2FFFFFF);
  
  ILI9806G_Clear(0,16*8,LCD_X_LENGTH,LCD_Y_LENGTH-16*8);	/* ��������ʾȫ�� */
  
  
  /*������*/

  ILI9806G_ClearLine(LINE(4));	/* ����������� */
	LCD_SetTextColor(BLUE);

  ILI9806G_DispStringLine_EN(LINE(4),"Draw Rect:");

	LCD_SetTextColor(RED);
  ILI9806G_DrawRectangle(50,200,200,100,1);
	
	LCD_SetTextColor(GREEN);
  ILI9806G_DrawRectangle(100,200,200,150,1);
	
	LCD_SetTextColor(BLUE);
  ILI9806G_DrawRectangle(250,200,200,200,1);
  
  
  Delay(0x2FFFFFF);
	
	ILI9806G_Clear(0,16*8,LCD_X_LENGTH,LCD_Y_LENGTH-16*8);	/* ��������ʾȫ�� */

  /* ��Բ */
  ILI9806G_ClearLine(LINE(4));	/* ����������� */
	LCD_SetTextColor(BLUE);
	
  ILI9806G_DispStringLine_EN(LINE(4),"Draw Cir:");

    LCD_SetTextColor(RED);
    ILI9806G_DrawCircle(150,300,100,1);

    LCD_SetTextColor(GREEN);
    ILI9806G_DrawCircle(250,300,100,1);

    LCD_SetTextColor(BLUE);
    ILI9806G_DrawCircle(350,300,100,1);

  Delay(0x2FFFFFF);
  
  ILI9806G_Clear(0,16*8,LCD_X_LENGTH,LCD_Y_LENGTH-16*8);	/* ��������ʾȫ�� */

}


/**
  * @brief  ����ʱ����
  * @param  nCount ����ʱ����ֵ
  * @retval ��
  */	
static void Delay ( __IO uint32_t nCount )
{
  for ( ; nCount != 0; nCount -- );
	
}
/*********************************************END OF FILE**********************/

