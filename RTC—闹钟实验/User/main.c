/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   RTC����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
#include "stm32f4xx.h"
#include "./led/bsp_led.h" 
#include "./usart/bsp_debug_usart.h"
#include "./RTC/bsp_rtc.h"
#include "./beep/bsp_beep.h"

#ifdef USE_LCD_DISPLAY
	#include "./lcd/bsp_ili9806g_lcd.h"
#endif

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{  
	/* ��ʼ��LED */
	LED_GPIO_Config();
	BEEP_GPIO_Config();

	/* ��ʼ�����Դ��ڣ�һ��Ϊ����1 */
	Debug_USART_Config();
	printf("\n\r����һ��RTC����ʵ�� \r\n");

#ifdef USE_LCD_DISPLAY	
	/*=========================Һ����ʼ����ʼ===============================*/
	ILI9806G_Init ();         //LCD ��ʼ��

	//����0��3��5��6 ģʽ�ʺϴ���������ʾ���֣�
	//���Ƽ�ʹ������ģʽ��ʾ����	����ģʽ��ʾ���ֻ��о���Ч��			
	//���� 6 ģʽΪ�󲿷�Һ�����̵�Ĭ����ʾ����  
  ILI9806G_GramScan ( 6 );
  /*=========================Һ����ʼ������===============================*/
#endif	
	/*
	 * ���������ù�RTCʱ��֮��������ݼĴ���0д��һ�����������
	 * ����ÿ�γ����������е�ʱ���ͨ����ⱸ�ݼĴ���0��ֵ���ж�
	 * RTC �Ƿ��Ѿ����ù���������ù��Ǿͼ������У����û�����ù�
	 * �ͳ�ʼ��RTC������RTC��ʱ�䡣
	 */
  
  /* RTC���ã�ѡ��ʱ��Դ������RTC_CLK�ķ�Ƶϵ�� */
  RTC_CLK_Config();
   
  if (RTC_ReadBackupRegister(RTC_BKP_DRX) != 0xf)//RTC_BKP_DATA
  {		
		/* �������� */
		RTC_AlarmSet();
		
    /* ����ʱ������� */
		RTC_TimeAndDate_Set();
		

  }
  else
  {
    /* ����Ƿ��Դ��λ */
    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
    {
      printf("\r\n ������Դ��λ....\r\n");
    }
    /* ����Ƿ��ⲿ��λ */
    else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
    {
      printf("\r\n �����ⲿ��λ....\r\n");
    }

    printf("\r\n ����Ҫ��������RTC....\r\n");
    
    /* ʹ�� PWR ʱ�� */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    /* PWR_CR:DBF��1��ʹ��RTC��RTC���ݼĴ����ͱ���SRAM�ķ��� */
    PWR_BackupAccessCmd(ENABLE);
    /* �ȴ� RTC APB �Ĵ���ͬ�� */
    RTC_WaitForSynchro();

    /* ���RTC�жϱ�־λ */
    RTC_ClearFlag(RTC_FLAG_ALRAF);
    /* ��� EXTI Line 17 ����λ (�ڲ����ӵ�RTC Alarm) */
    EXTI_ClearITPendingBit(EXTI_Line17);		
  } 
	
	/* ��ʾʱ������� */
	RTC_TimeAndDate_Show();
}


/**********************************END OF FILE*************************************/
