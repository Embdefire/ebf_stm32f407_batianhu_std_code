/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   Һ����ʾ����
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
#include "./lcd4_5/bsp_ili9806g_lcd.h"
#include "./lcd4_3/bsp_nt35510_lcd.h"

#include "./screen_dev/screen_dev.h"

static void LCD_Test(void);	
static void Delay ( __IO uint32_t nCount );

void Printf_Charater(void)   ;

/* ʵ���������豸��������δ�õ���ֻ��ʼ������ */
TOUCH_PARAM_TypeDef	GT5688 = 
{
	.device_name = "GT5688",
};

TOUCH_PARAM_TypeDef	GT917S = 
{
	.device_name = "GT917S",
};
/* ʵ����һ����ʾ���豸,���豸����ʾ���ԡ��������ԡ���ʾ����ʵ���� */
DEVICE_PARAM_TypeDef NT35510 = 
{
	.my_touchpanel = &GT917S,
	.my_display = &NT35510_DP_Desc,
	.my_disp_driver = &NT35510_DP_Driver,
};

DEVICE_PARAM_TypeDef ILI9806G = 
{
	.my_touchpanel = &GT5688,
	.my_display = &ILI9806G_DP_Desc,
	.my_disp_driver = &ILI9806G_DP_Driver,
};

DEVICE_PARAM_TypeDef *LCD;

int main(void)
{	
	//LCD ��ʼ��
	LCD = &ILI9806G;
	LCD->my_disp_driver->xx_init_func();
	int Chipid = LCD->my_disp_driver->xx_Read_Chipid();    
	switch ( Chipid )
	{
		case 0x9806:
		{
			LCD = &ILI9806G;
		}break;
		case 0:
		{
			LCD = &NT35510;
		}break;
		default:
		{
			LCD = &NT35510;
		}break;
	};

	LCD->my_disp_driver->xx_init_func();     

	/* USART config */
	Debug_USART_Config();		

	
	printf("\r\n ********** Һ����������ʾ�����ֿ����ⲿFLASH��*********** \r\n"); 
	printf("\r\n ��������ʾ�����������Ķ������е�readme.txt�ļ�˵��������Ҫ���FLASH��ˢ��ģ����\r\n"); 

 //����0��3��5��6 ģʽ�ʺϴ���������ʾ���֣�
 //���Ƽ�ʹ������ģʽ��ʾ����	����ģʽ��ʾ���ֻ��о���Ч��			
 //���� 6 ģʽΪ�󲿷�Һ�����̵�Ĭ����ʾ����  
//	ILI9806G_GramScan ( 6 );
	
	Printf_Charater();
	
	while ( 1 )
	{
		LCD_Test();
	}
	
	
}



/*���ڲ��Ը���Һ���ĺ���*/
void LCD_Test(void)
{
	/*��ʾ��ʾ����*/
	static uint8_t testCNT = 0;	
	char dispBuff[100];
	
	testCNT++;	
	
	LCD->my_disp_driver->xx_SetFont(&Font16x32);
	LCD->my_disp_driver->xx_SetColors(RED,BLACK);

  LCD->my_disp_driver->xx_Clear(0,0,LCD->my_display->LCD_X_LENGTH,LCD->my_display->LCD_Y_LENGTH);	/* ��������ʾȫ�� */
	/********��ʾ�ַ���ʾ��*******/ 
	sprintf(dispBuff,"Ұ��%s��LCD������",LCD->my_display->size_info);
  LCD->my_disp_driver->xx_DispStringLine_EN_CH(LINE(0),dispBuff);
	sprintf(dispBuff,"�ֱ��ʣ�%dx%d px",LCD->my_display->dp_max_height,LCD->my_display->dp_max_width);
  LCD->my_disp_driver->xx_DispStringLine_EN_CH(LINE(2),dispBuff);
	sprintf(dispBuff,"%sҺ������",LCD->my_display->device_name);
  LCD->my_disp_driver->xx_DispStringLine_EN_CH(LINE(3),dispBuff);
	sprintf(dispBuff,"%s����������",LCD->my_touchpanel->device_name);
  LCD->my_disp_driver->xx_DispStringLine_EN_CH(LINE(4),dispBuff);

	/********��ʾ����ʾ��*******/
	LCD->my_disp_driver->xx_SetTextColor(GREEN);

	/*ʹ��c��׼��ѱ���ת�����ַ���*/
	sprintf(dispBuff,"��ʾ�������� : %d ",testCNT);
  LCD->my_disp_driver->xx_ClearLine(LINE(7));	/* ����������� */
	
	/*Ȼ����ʾ���ַ������ɣ���������Ҳ����������*/
	LCD->my_disp_driver->xx_DispStringLine_EN(LINE(7),dispBuff);

	/*******��ʾͼ��ʾ��******/
  /* ��ֱ�� */
  
  LCD->my_disp_driver->xx_ClearLine(LINE(7));/* ����������� */
	LCD->my_disp_driver->xx_SetTextColor(BLUE);

  LCD->my_disp_driver->xx_DispStringLine_EN_CH(LINE(7),"��ֱ��:");
  
	LCD->my_disp_driver->xx_SetTextColor(RED);
  LCD->my_disp_driver->xx_DrawLine(50,270,420,275);  
  LCD->my_disp_driver->xx_DrawLine(50,300,420,375);
  
	LCD->my_disp_driver->xx_SetTextColor(GREEN);
  LCD->my_disp_driver->xx_DrawLine(50,370,420,475);  
  LCD->my_disp_driver->xx_DrawLine(50,400,420,475);
	
	LCD->my_disp_driver->xx_SetTextColor(BLUE);
  LCD->my_disp_driver->xx_DrawLine(50,420,420,325);  
  LCD->my_disp_driver->xx_DrawLine(50,450,420,395);
  
  Delay(0x2FFFFFF);
  
  LCD->my_disp_driver->xx_Clear(0,32*7,LCD->my_display->LCD_X_LENGTH,LCD->my_display->LCD_Y_LENGTH-32*7);	/* ��������ʾȫ�� */
  
  
  /*������*/

  LCD->my_disp_driver->xx_ClearLine(LINE(7));	/* ����������� */
	LCD->my_disp_driver->xx_SetTextColor(BLUE);

  LCD->my_disp_driver->xx_DispStringLine_EN_CH(LINE(7),"������:");

	LCD->my_disp_driver->xx_SetTextColor(RED);
  LCD->my_disp_driver->xx_DrawRectangle(50,300,200,100,1);
	
	LCD->my_disp_driver->xx_SetTextColor(GREEN);
  LCD->my_disp_driver->xx_DrawRectangle(100,300,200,120,0);
	
	LCD->my_disp_driver->xx_SetTextColor(BLUE);
  LCD->my_disp_driver->xx_DrawRectangle(250,300,200,150,1);
  
  
  Delay(0x2FFFFFF);
	
	LCD->my_disp_driver->xx_Clear(0,32*7,LCD->my_display->LCD_X_LENGTH,LCD->my_display->LCD_Y_LENGTH-32*7);	/* ��������ʾȫ�� */

  /* ��Բ */
  LCD->my_disp_driver->xx_ClearLine(LINE(7));	/* ����������� */
	LCD->my_disp_driver->xx_SetTextColor(BLUE);
	
  LCD->my_disp_driver->xx_DispStringLine_EN_CH(LINE(7),"��Բ:");

	LCD->my_disp_driver->xx_SetTextColor(RED);
	LCD->my_disp_driver->xx_DrawCircle(150,400,60,1);

	LCD->my_disp_driver->xx_SetTextColor(GREEN);
	LCD->my_disp_driver->xx_DrawCircle(250,400,60,0);

	LCD->my_disp_driver->xx_SetTextColor(BLUE);
	LCD->my_disp_driver->xx_DrawCircle(350,400,60,1);

  Delay(0x2FFFFFF);
  
  LCD->my_disp_driver->xx_Clear(0,32*7,LCD->my_display->LCD_X_LENGTH,LCD->my_display->LCD_Y_LENGTH-32*7);	/* ��������ʾȫ�� */

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



/*"��"�ַ�����ģ16x16 */ 	  
unsigned char charater_matrix[] =    
{ /*"��",0*/
0x01,0x00,0x21,0x08,0x11,0x08,0x09,0x10,0x09,0x20,0x01,0x00,0x7F,0xF8,0x00,	0x08,
0x00,0x08,0x00,0x08,0x3F,0xF8,0x00,0x08,0x00,0x08,0x00,0x08,0x7F,0xF8,0x00,0x08,
};   

   
  
/**
  * @brief  ʹ�ô�������λ����ӡ��ģ
	*					��ʾ��ģ��ʾԭ��
  * @retval ��
  */
void Printf_Charater(void)   
{   
	int i,j;   
	unsigned char kk; 
  
	/*i�����м���*/
  for ( i=0;i<16;i++)   
	{   
		/*j����һ�ֽ������ݵ���λ����*/
		/*һ�����صĵ�һ���ֽ�*/
    for(j=0; j<8; j++)   
    {      
			/*һ������λһ������λ�ش���*/
      kk = charater_matrix[2*i] << j ;  //����Jλ          
			if( kk & 0x80)     
			{   
				printf("*"); //������λΪ1�����*�ţ���ʾ�ʼ�
			}   
			else  
			{   
				printf(" "); //������λΪ0������ո񣬱�ʾ�հ�  
			}   
    }   
		/*һ�����صĵڶ����ֽ�*/
    for(j=0; j<8; j++)   
		{              
      kk = charater_matrix[2*i+1] << j ;  //����Jλ   
       
			if( kk & 0x80)         
			{   
				printf("*"); //������λΪ1�����*�ţ���ʾ�ʼ�   
			}   
			else  
			{   
				printf(" "); //������λΪ0������ո񣬱�ʾ�հ� 
			}   
		} 			
    printf("\n");    //�����һ�����أ����� 
	}   
	printf("\n\n"); 		//һ����������
}   


/*********************************************END OF FILE**********************/

