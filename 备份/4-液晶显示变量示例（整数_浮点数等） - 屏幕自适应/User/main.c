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
#include <stdio.h>
#include <string.h>

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
//	ILI9806G_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* ��������ʾȫ�� */

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
	static uint8_t testIntCNT = 0;	
	static double testFloatCNT = 0;	
	char dispBuff[100];
	char *pStr = 0;
	
	testIntCNT++;	
	testFloatCNT += 0.1;
	
	LCD->my_disp_driver->xx_SetFont(&Font16x32);	
	LCD->my_disp_driver->xx_SetColors(RED,BLACK);
	

	/********��ʾ����ʾ��*******/
	/*ʹ��c��׼��ѱ���ת�����ַ���*/
	sprintf(dispBuff,"��ʾ���ͱ����� %d ",testIntCNT);
  LCD->my_disp_driver->xx_ClearLine(LINE(5));	/* ����������� */
	
	/*Ȼ����ʾ���ַ������ɣ���������Ҳ����������*/
	ILI9806G_DispStringLine_EN_CH(LINE(5),dispBuff);
	
	
	/*ʹ��c��׼��ѱ���ת�����ַ���*/
	sprintf(dispBuff,"��ʾ�����ͱ����� %f ",testFloatCNT);
  LCD->my_disp_driver->xx_ClearLine(LINE(6));	/* ����������� */
	
	/*Ȼ����ʾ���ַ������ɣ���������Ҳ����������*/
	LCD->my_disp_driver->xx_DispStringLine_EN_CH(LINE(6),dispBuff);


	/*ʹ��c��׼��ѱ���ת�����ַ���*/
	sprintf(dispBuff,"������(����2λС��)�� %.2f ",testFloatCNT);
  LCD->my_disp_driver->xx_ClearLine(LINE(7));	/* ����������� */
	
	/*Ȼ����ʾ���ַ������ɣ���������Ҳ����������*/
	LCD->my_disp_driver->xx_DispStringLine_EN_CH(LINE(7),dispBuff);
	
	/********������ʾʾ��*******/
	LCD->my_disp_driver->xx_SetTextColor(GREEN);

	pStr = "����2��Ӣ�Ŀո�ʾ��";
	//ʹ�� %*c ���ַ���ǰ����ָ��������Ӣ�Ŀո�
	sprintf(dispBuff,"%*c%s",2,' ',pStr);
	
	LCD->my_disp_driver->xx_ClearLine(LINE(9));												// ����������� 
	LCD->my_disp_driver->xx_DispStringLine_EN_CH(LINE(9),dispBuff);//��ʾ��ʽ������ַ���

	LCD->my_disp_driver->xx_DispStringLine_EN_CH(LINE(11),"��Ӣ��24x32����ʾ����");
	LCD->my_disp_driver->xx_SetFont(&Font24x48);	
	pStr = "ABCDEF";
	//����ʱ��Ҫ����Ŀո���� = (Һ�����/���������� - �ַ�������)/2
	sprintf(dispBuff,"%*c%s",((LCD->my_display->LCD_X_LENGTH/(((sFONT *)LCD->my_disp_driver->xx_GetFont())->Width))-strlen(pStr))/2,' ',pStr);
 
	LCD->my_disp_driver->xx_ClearLine(LINE(8));													// ����������� 
	LCD->my_disp_driver->xx_DispStringLine_EN_CH(LINE(8),dispBuff);//��ʾ��ʽ������ַ���
	
	LCD->my_disp_driver->xx_SetFont(&Font16x32);	
	pStr = "���ľ���ʾ��";
	//����ʱ��Ҫ����Ŀո���� = (Һ�����/������ - �ַ�������)/2
	//strlen���㳤��ʱ��һ�����ĵ���2���ֽڣ���2��Ӣ���ַ������Ҳ������Ӣ�Ŀո�
	//������(WIDTH_CH_CHAR/2)������������
	sprintf(dispBuff,"%*c%s",(LCD->my_display->LCD_X_LENGTH/(WIDTH_CH_CHAR/2)-strlen(pStr))/2,' ',pStr);
	
	LCD->my_disp_driver->xx_ClearLine(LINE(15));													// ����������� 
	LCD->my_disp_driver->xx_DispStringLine_EN_CH(LINE(15),dispBuff);	//��ʾ��ʽ������ַ���
	
	
	pStr = "��Ӣ�ľ���ʾ��ABCDEFG";
	//����ʱ��Ҫ����Ŀո���� = (Һ�����/������ - �ַ�������)/2
	//strlen���㳤��ʱ��һ�����ĵ���2���ֽڣ���2��Ӣ���ַ������Ҳ������Ӣ�Ŀո�
	//������(WIDTH_CH_CHAR/2)������������
	sprintf(dispBuff,"%*c%s",(LCD->my_display->LCD_X_LENGTH/(WIDTH_CH_CHAR/2)-strlen(pStr))/2,' ',pStr);
 
	LCD->my_disp_driver->xx_ClearLine(LINE(16));												// ����������� 
	LCD->my_disp_driver->xx_DispStringLine_EN_CH(LINE(16),dispBuff);//��ʾ��ʽ������ַ���
	
	Delay(0x4ffffff);
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

