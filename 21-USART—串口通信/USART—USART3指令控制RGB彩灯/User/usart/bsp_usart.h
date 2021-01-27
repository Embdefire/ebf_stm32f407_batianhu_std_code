#ifndef __USART_H
#define	__USART_H

#include "stm32f4xx.h"
#include <stdio.h>


//���Ŷ���
/*******************************************************/
#define USARTx                             USART3

/* ��ͬ�Ĵ��ڹ��ص����߲�һ����ʱ��ʹ�ܺ���Ҳ��һ������ֲʱҪע�� 
 * ����1��6��      RCC_APB2PeriphClockCmd
 * ����2/3/4/5/7�� RCC_APB1PeriphClockCmd
 */
#define USARTx_CLK                         RCC_APB1Periph_USART3
#define USARTx_CLOCKCMD                    RCC_APB1PeriphClockCmd
#define USARTx_BAUDRATE                    115200  //���ڲ�����

#define USARTx_RX_GPIO_PORT                GPIOB
#define USARTx_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define USARTx_RX_PIN                      GPIO_Pin_11
#define USARTx_RX_AF                       GPIO_AF_USART3
#define USARTx_RX_SOURCE                   GPIO_PinSource11

#define USARTx_TX_GPIO_PORT                GPIOB
#define USARTx_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define USARTx_TX_PIN                      GPIO_Pin_10
#define USARTx_TX_AF                       GPIO_AF_USART3
#define USARTx_TX_SOURCE                   GPIO_PinSource10

/************************************************************/

void USARTx_Config(void);

#endif /* __USART_H */
