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

//#define DEBUG

#include "iopwm316.h"


#define  CPU_CLK         16000000

typedef struct{
  unsigned int Weld_Start_And_Stop:1;//焊接始终端
  unsigned int Weld_First_Point:1;    //焊接第一点
  unsigned int Swing_Mode:2;          //摆动方式
  unsigned int Reservation_Action:1;  //预约有效
  unsigned int Rst:11;
}Mult_Res_Struct; 

typedef union{
  unsigned int Data;
  Mult_Res_Struct Mult_Res;
}Mult_Union;

typedef struct{
  unsigned int Header:4;   //显示不同页首
  unsigned int Content:7;  //显示不同页内容
  unsigned int Bottom:3;   //显示不同页底
  unsigned int Mouse:2;    //为0 则清除游标 1则 显示在1位置 2则显示在2位置 3则显示在3位置
}Page_Struct;
typedef union{
  unsigned int Page;
  Page_Struct Page_Mult;
}Page_Union;
/*
typedef struct{
unsigned long Key;               //按键值4
unsigned int Error;               //错误编号6
Mul_Res_Struct Mult;              //8
unsigned int Teach_Point_Num;     //示教点数10
unsigned int Root_Gap;              //根部间隙12
unsigned int Plate_Hight;           //板厚14
unsigned int Weld_Length;           //焊接长 16
Page_Struct Page;                   //18
unsigned char Current_Weld_Num;           //当前焊缝号20
unsigned char Set_Weld_Num;
unsigned int Weld_Current;          //焊接电流22
unsigned int Weld_Volagte;          //焊接电压24
unsigned int Weld_Speed;            //焊接速度26
unsigned int Swing_Frq;             //摆动频率28
unsigned int Swing_Wide;            // 摆动幅度30
unsigned int Stay_Time;             // 左停留时间32
}Reg_Union;
typedef union{
unsigned int Reg_Buf[16];//34位通信数组
Reg_Union Reg;
}MB_HoldReg_Union;*/
#define KEY_LOW_BUF             0
#define KEY_HIGH_BUF            1
#define ERROR_BUF               2
#define MULT_BUF                3
#define ROOT_GAP_BUF            4   //根部间隙12
#define PLATE_HIGHT_BUF         5  //板厚14
#define WELD_LENGTH_BUF         6   //焊接长 16
#define TEACH_POINT_BUF         7
#define PAGE_BUF                8
#define WELD_NUM_BUF            9
#define WELD_CURRENT_BUF       10   //焊接电流22 电流电压 都是准备好的 FFFF后三个F 代表十进制
#define WELD_SPEED_BUF         11   //焊接速度26
#define WELD_CURRENT_NUM_BUF   12
#define WELD_VOLAGTE_BUF       13   //焊接电压24
#define SWING_FRQ_BUF          14   //摆动频率28
#define SWING_WIDE_BUF         15   // 摆动幅度30
#define STAY_TIME_BUF          16   // 左停留时间32


typedef union{
  unsigned long Key_Index;
  struct{
    unsigned long Set:1;
    unsigned long Add:1;
    unsigned long Dec:1;
    unsigned long Cancel:1;
    
    unsigned long Travel_Left:1;
    unsigned long Travel_Right:1;
    unsigned long Left:1;
    unsigned long Right:1;
    
    unsigned long Forward:1;
    unsigned long Back:1;
    unsigned long Up:1;
    unsigned long Down:1;
    
    unsigned long Feed:1;
    unsigned long Current_Add:1;
    unsigned long Currene_Dec:1;
    unsigned long Start:1;
    
    unsigned long Reset:1;
    unsigned long Stop:1;  
    
    unsigned long Rest:14;
  }Key_Struct;
}Key_Union;

typedef struct{
  unsigned long Trg;
  unsigned long Cont;
  unsigned long Release;
}Type_Key;


#define KEY_SET                    0X000001
#define KEY_ADD                    0X000002
#define KEY_DEC                    0X000004
#define KEY_CANCEL                 0X000008
#define KEY_TRAVELLEFT             0X000010
#define KEY_TRAVELRIGHT            0X000020
#define KEY_LEFT                   0X000040
#define KEY_RIGHT                  0X000080
#define KEY_UP                     0X000400
#define KEY_DOWN                   0X000800
#define KEY_FORWARD                0X000100
#define KEY_BACK                   0X000200
#define KEY_FEED                   0X001000
#define KEY_CURRENT_ADD            0X002000
#define KEY_CURRENT_DEC            0X004000
#define KEY_START                  0X008000  
#define KEY_RESET                  0X010000
#define KEY_STOP                   0X020000

/*系统错误类型*/
typedef struct
{
  unsigned long Sys_Modbus_Error:1;//MODBUS错误
  unsigned long Sys_Weld_Error:1;
  //也是应该有几种
  unsigned long Sys_Lcd_Busy:1;
  unsigned long Sys_Rst:28;
  
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
#define MODBUS_BAUDRATE                     38400

#define MB_TIMER_PRESCALER                (1024)   //分频

#define MB_TIMER_FREQUENCY                (16)        //系统时钟16M

#define MB_KEY_RES                              10
#define MB_CURRENT_PAGE                         12

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