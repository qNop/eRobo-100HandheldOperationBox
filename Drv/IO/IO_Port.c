
/*
      �˿ڳ�ʼ��
      
*/
#include "IO_PORT.h"
 
#include "iopwm316.h"
#include "Config.h"


void INIT_IO(void)

{
   /*lcd������������Ϊ����˿�*/
    OUTPUT_LCD_DB(0XFF);
    DDRB = 0XFF;
   /*LCD_PWM�˿�����Ϊ���״̬*/
    CONFIG_PORT_OUT(DDR_LCD_PWM,LCD_PWM);
    CLRPIN(PORT_LCD_PWM,LCD_PWM);
      /*LCD_RW�˿�����Ϊ���״̬*/
    CONFIG_PORT_OUT(DDR_LCD_RW,LCD_RW);
      /*LCD_RS�˿�����Ϊ���״̬*/
    CONFIG_PORT_OUT(DDR_LCD_RS,LCD_RS);
      /*LCD_E�˿�����Ϊ���״̬*/
    CONFIG_PORT_OUT(DDR_LCD_E,LCD_E);
    /*573LE�˿�����Ϊ���״̬*/
    CONFIG_PORT_OUT(DDR_LE,LE);
    /*����573LE�˿�Ϊ�ߵ�ƽ*/
    CLRPIN(PORT_LE,LE);
   /*�����˿���������״̬*/
    CONFIG_PORT_IN(DDR_START,START);
   /*��λ�˿���������״̬*/
    CONFIG_PORT_IN(DDR_RESET,RESET);
   /*ֹͣ�˿���������״̬*/ 
    CONFIG_PORT_IN(DDR_STOP,STOP);
   /*KEY_4�˿���������״̬*/ 
    CONFIG_PORT_IN(DDR_KEY_4,KEY_4);
    /*KEY_5�˿���������״̬*/ 
    CONFIG_PORT_IN(DDR_KEY_5,KEY_5);
    /*KEY_6�˿���������״̬*/ 
    CONFIG_PORT_IN(DDR_KEY_6,KEY_6);
    /*KEY_7�˿���������״̬*/ 
    CONFIG_PORT_IN(DDR_KEY_7,KEY_7);
   /*UART TXD*/
    CONFIG_PORT_OUT(DDR_TXD,TXD);
   /*UART RXD*/
    CONFIG_PORT_IN(DDR_RXD,RXD);  
    SETPIN(PORT_RXD,RXD);
}