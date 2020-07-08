/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   �����ǻ������ݶ�ȡ
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
#include "./i2c/i2c.h"
#include "./mpu6050/mpu6050.h"


//�����Ƿ�ʹ��LCD������ʾ������Ҫ�Ļ��������ע�͵�����
#define USE_LCD_DISPLAY

#ifdef USE_LCD_DISPLAY
 #include "./lcd/bsp_ili9806g_lcd.h"
#endif

/*���������*/
uint32_t Task_Delay[NumOfTask]={0};

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	
	short Acel[3];
	short Gyro[3];
	float Temp;
	
	SysTick_Init();
	
  LED_GPIO_Config();
	
	
#ifdef USE_LCD_DISPLAY	
		 /*��ʼ��Һ����*/
	ILI9806G_Init ();         //LCD ��ʼ��
	
	//����0��3��5��6 ģʽ�ʺϴ���������ʾ���֣�
	//���Ƽ�ʹ������ģʽ��ʾ����	����ģʽ��ʾ���ֻ��о���Ч��			
	//���� 6 ģʽΪ�󲿷�Һ�����̵�Ĭ����ʾ����  
  ILI9806G_GramScan ( 6 );

#endif
	
	
  /*��ʼ��USART1*/
  Debug_USART_Config(); 
		
	//��ʼ�� I2C
	I2cMaster_Init(); 

	printf("\r\n ��ӭʹ��Ұ��  STM32 F407 �����塣\r\n");		 

	printf("\r\n ����һ��I2C����(AT24C02)��д�������� \r\n");

 	 	//MPU6050��ʼ��
	MPU6050_Init();
	
	//���MPU6050
	if (MPU6050ReadID() == 1)
	{	
		while(1)
		{
			if(Task_Delay[0]==TASK_ENABLE)
			{
				LED2_TOGGLE;
				Task_Delay[0]=1000;
			}
			
			if(Task_Delay[1]==0)
			{
				MPU6050ReadAcc(Acel);
				printf("���ٶȣ�%8d%8d%8d",Acel[0],Acel[1],Acel[2]);
				MPU6050ReadGyro(Gyro);
				printf("    ������%8d%8d%8d",Gyro[0],Gyro[1],Gyro[2]);
				MPU6050_ReturnTemp(&Temp);
				printf("    �¶�%8.2f\r\n",Temp);				
				
				
				#ifdef USE_LCD_DISPLAY	
					{
						char cStr [ 70 ];
						sprintf ( cStr, "Acc  :%6d%6d%6d",Acel[0],Acel[1],Acel[2] );	//���ٶ�ԭʼ����


						ILI9806G_DispStringLine_EN(LINE(7),cStr);			

						sprintf ( cStr, "Gyro :%6d%6d%6d",Gyro[0],Gyro[1],Gyro[2] );	//��ԭʼ����

						ILI9806G_DispStringLine_EN(LINE(8),cStr);			

						sprintf ( cStr, "Tem  :%6.2f",Temp );	//�¶�ֵ
						ILI9806G_DispStringLine_EN(LINE(9),cStr);			

					}
				#endif
				
				Task_Delay[1]=500; //����һ�����ݣ��ɸ����Լ���������߲���Ƶ�ʣ���100ms����һ��
				
			}

			//*************************************	��������������ĸ�ʽ************************************//
	//		if(Task_Delay[i]==0)
	//		{
	//			Task(i);
	//			Task_Delay[i]=;
	//		}

		}

	}
	else
	{
			printf("\r\nû�м�⵽MPU6050��������\r\n");
			LED_RED; 
			#ifdef USE_LCD_DISPLAY			
				/*����������ɫ������ı�����ɫ*/
				LCD_SetColors(BLUE,BLACK);	

				ILI9806G_DispStringLine_EN(LINE(4),"No MPU6050 detected! ");			//Ұ���Դ���16*24��ʾ
				ILI9806G_DispStringLine_EN(LINE(5),"Please check the hardware connection! ");			//Ұ���Դ���16*24��ʾ

			#endif
		while(1);	
	}


}




/*********************************************END OF FILE**********************/

