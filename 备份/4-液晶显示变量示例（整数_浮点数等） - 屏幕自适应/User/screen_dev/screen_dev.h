#ifndef _SCREEB_DEV_H
#define _SCREEB_DEV_H

#include "stm32f4xx.h"
#include <stdio.h>
#include "./font/fonts.h"

typedef struct _tFont sFONT;
/** 
  * @brief �����������ṹ��
  */
typedef struct
{
  /*���ݴ�������������*/
  uint16_t					tp_max_width;				//�������ֵ��һ��Ϊ��ʾ���ĸ�
  uint16_t					tp_max_height;			//�������ֵ��һ��Ϊ��ʾ���Ŀ�
  uint16_t					config_reg_addr;  	//��ͬ���͵Ĵ���ic���üĴ�����ַ���ܲ�ͬ
	uint16_t					ic_id;							//����оƬid
	const uint8_t*		config_talbe;				//���������ñ�
	uint8_t						config_talbe_len;		//���������ñ��С
	const char*				device_name;				//����������
}TOUCH_PARAM_TypeDef;


/** 
  * @brief ��ʾ������
  */
typedef struct
{
  /*������ʾ����������*/
  uint16_t 		dp_max_width;  	//��ʾ��Ӳ���߶����ֵ
  uint16_t 		dp_max_height;  //��ʾ��Ӳ��������ֵ
  uint16_t		device_id;			//��ʾ���豸id
	uint8_t			LCD_SCAN_MODE;	//��ʾ��ɨ��ģʽ����Ӧ������.c�ļ���������
	uint16_t		LCD_X_LENGTH;		//��ʾ����ǰ��ʾ��x�᳤��
	uint16_t		LCD_Y_LENGTH;		//��ʾ����ǰ��ʾ��y�᳤��
	const char* device_name;		//��ʾ������
	const char*	size_info;			//��ʾ���ߴ�
}DISP_PARAM_TypeDef;


/** 
  * @brief ��ʾ�������ӿ�
  */
typedef struct
{
void 										 (*xx_send_cmd)									(uint16_t usCmd);
void 										 (*xx_write_data)								(uint16_t usData);
uint16_t 								 (*xx_read_data)								(void);
void										 (*xx_init_func)								(void);
uint32_t								 (*xx_Read_Chipid)							(void);
void                     (*xx_Rst)											(void);
void                     (*xx_BackLed_Control)					(FunctionalState enumState);
void                     (*xx_GramScan)									(uint8_t ucOtion);
void                     (*xx_OpenWindow)								(uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight );
void                     (*xx_Clear)										(uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight );
void                     (*xx_SetPointPixel)						(uint16_t usX, uint16_t usY );
uint16_t                 (*xx_GetPointPixel)						(uint16_t usX , uint16_t usY );
void                     (*xx_DrawLine)									(uint16_t usX1, uint16_t usY1, uint16_t usX2, uint16_t usY2 );
void                     (*xx_DrawRectangle)						(uint16_t usX_Start, uint16_t usY_Start, uint16_t usWidth, uint16_t usHeight,uint8_t ucFilled );
void                     (*xx_DrawCircle)								(uint16_t usX_Center, uint16_t usY_Center, uint16_t usRadius, uint8_t ucFilled );
void                     (*xx_DispChar_EN)							(uint16_t usX, uint16_t usY, const char cChar );
void                     (*xx_DispStringLine_EN)				(uint16_t line, char * pStr );
void                     (*xx_DispString_EN)						(uint16_t usX, uint16_t usY, char * pStr );
void 										 (*xx_DispString_EN_YDir)				(uint16_t usX,uint16_t usY ,  char * pStr );
void                     (*xx_DispChar_CH)							(uint16_t usX, uint16_t usY, uint16_t usChar );
void                     (*xx_DispString_CH)						(uint16_t usX, uint16_t usY,  char * pStr );
void                     (*xx_DispString_EN_CH)					(uint16_t usX, uint16_t usY,  char * pStr );
void 										 (*xx_DispStringLine_EN_CH)			(uint16_t line, char * pStr );
void 										 (*xx_DispString_EN_CH_YDir)		(uint16_t usX,uint16_t usY , char * pStr );
void 										 (*xx_SetFont)									(sFONT *fonts);
sFONT* 										(*xx_GetFont)									(void);
void 										 (*xx_ClearLine)								(uint16_t Line);
void 										 (*xx_SetBackColor)							(uint16_t Color);
void 										 (*xx_SetTextColor)							(uint16_t Color);
void 										 (*xx_SetColors)								(uint16_t TextColor, uint16_t BackColor);
void 										 (*xx_GetColors)								(uint16_t *TextColor, uint16_t *BackColor);
void 										 (*xx_DrawLineCircle)						(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint8_t thick );
void 										 (*xx_DisplayStringEx)					(uint16_t x,uint16_t y,uint16_t Font_width,	uint16_t Font_Height,	uint8_t *ptr,	uint16_t DrawModel);//�³�Ա2020.7.16 add by jc
void 										 (*xx_DisplayStringEx_YDir)			(uint16_t x,uint16_t y,uint16_t Font_width,	uint16_t Font_Height,	uint8_t *ptr,	uint16_t DrawModel);//�³�Ա2020.7.16 add by jc
}DISP_DRIVE_PARAM_TypeDef;


/** 
  * @brief ������ʾ�豸����
  */
typedef struct
{
	TOUCH_PARAM_TypeDef					*my_touchpanel;	//�����������ṹ��
	DISP_PARAM_TypeDef					*my_display;		//��ʾ�������ṹ��
	DISP_DRIVE_PARAM_TypeDef 		*my_disp_driver;//��ʾ�������ӿ�
}DEVICE_PARAM_TypeDef;


/** 
  * @brief ��������LCD�豸���ڸ��Ե������ж��塣
  */
extern DISP_DRIVE_PARAM_TypeDef NT35510_DP_Driver;
extern DISP_PARAM_TypeDef NT35510_DP_Desc;

extern DISP_DRIVE_PARAM_TypeDef ILI9806G_DP_Driver;
extern DISP_PARAM_TypeDef ILI9806G_DP_Desc;

extern DEVICE_PARAM_TypeDef *LCD;

void LCD_Device_Init(DEVICE_PARAM_TypeDef* p);
#endif
