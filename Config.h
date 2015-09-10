/*
系统简介：
作者：陈世豪
时间：20140320
版本：V1.00   （整数 奇数为测试，偶数为正式版  
小数 版本号升级用）
操作系统：FreeRTOS v7.1.1
使用系统资源：ADC --->
+--  ADC6  PORTB_5 -->回烧时间
+--  ADC7  PORTB_6 -->电流反馈
+--  ADC8  PORTC_4 -->电压反馈
+--  ADC9  PORTC_5 -->电流给定
+--  ADC10 PORTC_6 -->电压给定
Total--->5 IO
DAC --->
+--  DAC   PORTC_7 -->送丝速度给定  
Total--->1 IO
按键配置--->
控制键---->
+--  INPUT PORTC_2 -->停止键
+--  INPUT PORTC_3 -->启动键
+--  INPUT PORTB_0 -->退丝键
+--  INPUT PORTB_1 -->送丝键
丝径选择--->
+--  INPUT PORTD_1 -->2.4
+--  INPUT PORTD_0 -->3.2
+--  INPUT PORTC_0 -->4.0
+--  INPUT PORTC_1 -->4.8
功能键---->
+--  INPUT PORTB_7 -->起弧方式
+--  INPUT PORTD_5 -->焊接极性
+--  INPUT PORTD_7 -->特性选择
Total--->11 IO
控制输出--->
+-- OUTPUT PORTD_2 -->收弧信号
+-- OUTPUT PORTD_3 -->引弧成功
+-- OUTPUT PORTD_4 -->慢送丝
+-- OUTPUT PORTD_6 -->电源触发
+-- OUTPUT PORTB_2 -->行走制动
+-- OUTPUT PORTB_3 -->送丝换向
+-- OUTPUT PORTB_4 -->送丝制动
Total--->7 IO
ALL Used --->5+1+11+7=24 IO  
Rest --->24-24=0     IO
//调试期间将 慢送丝   PORTD_4 -->PORTD_1
//                  引弧成功 PORTD_3 -->PORTD_0 
//                   TXD -->PORTD_3
//                  RXD -->PORTD_4
//
//                   丝径选择只保留 4.0-4.8两档

定时器1用作系统调度
UART用作通信
定时器0用作串口超时
看门狗

*/

#ifndef CONFIG_H
#define CONFIG_H

//定义程序版本，确定程序代码
#define CODE_VER                               100//1.00版

#define ENABLE_BIT_DEFINITIONS

#define DEBUG

#include "iopwm316.h"

typedef union{
  unsigned long Key_Index;
  struct{
    unsigned int Set:1;
    unsigned int Add:1;
    unsigned int Dec:1;
    unsigned int Cancel:1;
    unsigned int Feed:1;
    unsigned int Current_Add:1;
    unsigned int Currene_Dec:1;
    unsigned int Start:1;
    
    unsigned int Reset:1;
    unsigned int Stop:1;  
    
    unsigned int Up:1;
    unsigned int Down:1;
    unsigned int Forward:1;
    unsigned int Back:1;
    unsigned int Left:1;
    unsigned int Right:1;
    unsigned int Travel_Left:1;
    unsigned int Travel_Right:1;
    
    unsigned int Rest:14;
  }Key_Struct;
}Key_Union;

typedef struct{
  unsigned long Trg;
  unsigned long Cont;
  unsigned long Release;
}Type_Key;

#define KEY_SET                    0X001
#define KEY_ADD                    0X002
#define KEY_DEC                    0X004
#define KEY_CANCEL                 0X008
#define KEY_FEED                   0X010
#define KEY_CURRENT_ADD            0X020
#define KEY_CURRENT_DEC            0X040
#define KEY_START                  0X080
#define KEY_RESET                  0X100
#define KEY_STOP                   0X200
#define KEY_UP                     0X400
#define KEY_DOWN                   0X800
#define KEY_FORWARD                0X01000
#define KEY_BACK                   0X02000
#define KEY_LEFT                   0X04000
#define KEY_RIGHT                  0X08000
#define KEY_TRAVELLEFT             0X010000
#define KEY_TRAVELRIGHT            0X020000
/*系统错误类型*/
typedef enum
{
  Sys_No_Error,//无错误
  Sys_Modbus_Error,
  //应该有几种
  
  Sys_Weld_Error,
  //也是应该有几种
  Sys_Lcd_Busy,
  
}Sys_Error;
/*PID定义*/
/*
typedef struct
{


}*/


#define  REVPIN(PORT, PIN)           (PORT ^=  (1<<(PIN)))                                 //翻转PORT口PIN位
#define  SETPIN(PORT, PIN)           (PORT |=  (1<<(PIN)))                                 //PORT口PIN位 = 1
#define  CLRPIN(PORT, PIN)           (PORT &= ~(1<<(PIN)))                                 //PORT口PIN位 = 0
#define  GETPIN(PORT, PIN)           (PORT &   (1<<(PIN)))                                 //读PORT口PIN位值
#define  OUTPIN(PORT, PIN, VALUE)    ((VALUE) ? (SETPIN(PORT, PIN)) : (CLRPIN(PORT, PIN)))


/*modbus define here*/

#define MODBUS_ADDR                         0x01

/*波特率的选择 16M晶振 U2X=0 的情况下满足 MODBUS 误差率小于2% 推荐选用 4800 9600 19200 38400 76800*/
#define MODBUS_BAUDRATE                     19200

#define MB_TIMER_PRESCALER                (1024)   //分频

#define MB_TIMER_FREQUENCY                (16)        //系统时钟16M

/*焊接状态*/
#define  WELD_STATUS_IDLE                       0 //空闲态
#define  WELD_STATUS_FEED                       1 //送丝态
#define  WELD_STATUS_BACK                       2 //退丝态
#define  WELD_STATUS_TOUCH                      3 //接触状态

#define  WELD_STATUS_START                      1 //启动态
#define  WELD_STATUS_SLOW_SEND                  2 //慢送丝态
#define  WELD_STATUS_PUMPBACK                   3 //回抽态
#define  WELD_STATUS_ARC_SUCCESS                4 //引弧成功态
#define  WELD_STATUS_WELDING                    5 //焊接中态
#define  WELD_STATUS_STOP                       6 //断弧态 
#define  WELD_STATUS_ARC_STOP                   7 //收弧态
#define  WELD_STATUS_BURNBACK                   8 //回烧态

#endif