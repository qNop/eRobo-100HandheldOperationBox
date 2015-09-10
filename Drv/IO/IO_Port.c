
/*
      端口初始化
      
*/
#include "IO_PORT.h"
 
#include "iopwm316.h"
#include "Config.h"


void INIT_IO(void)

{
   /*lcd数据总线配置为输出端口*/
    OUTPUT_LCD_DB(0XFF);
    DDRB = 0XFF;
   /*LCD_PWM端口配置为输出状态*/
    CONFIG_PORT_OUT(DDR_LCD_PWM,LCD_PWM);
    CLRPIN(PORT_LCD_PWM,LCD_PWM);
      /*LCD_RW端口配置为输出状态*/
    CONFIG_PORT_OUT(DDR_LCD_RW,LCD_RW);
      /*LCD_RS端口配置为输出状态*/
    CONFIG_PORT_OUT(DDR_LCD_RS,LCD_RS);
      /*LCD_E端口配置为输出状态*/
    CONFIG_PORT_OUT(DDR_LCD_E,LCD_E);
    /*573LE端口配置为输出状态*/
    CONFIG_PORT_OUT(DDR_LE,LE);
    /*设置573LE端口为高电平*/
    CLRPIN(PORT_LE,LE);
   /*启动端口配置输入状态*/
    CONFIG_PORT_IN(DDR_START,START);
   /*复位端口配置输入状态*/
    CONFIG_PORT_IN(DDR_RESET,RESET);
   /*停止端口配置输入状态*/ 
    CONFIG_PORT_IN(DDR_STOP,STOP);
   /*KEY_4端口配置输入状态*/ 
    CONFIG_PORT_IN(DDR_KEY_4,KEY_4);
    /*KEY_5端口配置输入状态*/ 
    CONFIG_PORT_IN(DDR_KEY_5,KEY_5);
    /*KEY_6端口配置输入状态*/ 
    CONFIG_PORT_IN(DDR_KEY_6,KEY_6);
    /*KEY_7端口配置输入状态*/ 
    CONFIG_PORT_IN(DDR_KEY_7,KEY_7);
   /*UART TXD*/
    CONFIG_PORT_OUT(DDR_TXD,TXD);
   /*UART RXD*/
    CONFIG_PORT_IN(DDR_RXD,RXD);  
    SETPIN(PORT_RXD,RXD);
}