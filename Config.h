/*
ϵͳ��飺
���ߣ�������
ʱ�䣺20140320
�汾��V1.00   ������ ����Ϊ���ԣ�ż��Ϊ��ʽ��  
С�� �汾�������ã�
����ϵͳ��FreeRTOS v7.1.1
ʹ��ϵͳ��Դ��ADC --->
+--  ADC6  PORTB_5 -->����ʱ��
+--  ADC7  PORTB_6 -->��������
+--  ADC8  PORTC_4 -->��ѹ����
+--  ADC9  PORTC_5 -->��������
+--  ADC10 PORTC_6 -->��ѹ����
Total--->5 IO
DAC --->
+--  DAC   PORTC_7 -->��˿�ٶȸ���  
Total--->1 IO
��������--->
���Ƽ�---->
+--  INPUT PORTC_2 -->ֹͣ��
+--  INPUT PORTC_3 -->������
+--  INPUT PORTB_0 -->��˿��
+--  INPUT PORTB_1 -->��˿��
˿��ѡ��--->
+--  INPUT PORTD_1 -->2.4
+--  INPUT PORTD_0 -->3.2
+--  INPUT PORTC_0 -->4.0
+--  INPUT PORTC_1 -->4.8
���ܼ�---->
+--  INPUT PORTB_7 -->�𻡷�ʽ
+--  INPUT PORTD_5 -->���Ӽ���
+--  INPUT PORTD_7 -->����ѡ��
Total--->11 IO
�������--->
+-- OUTPUT PORTD_2 -->�ջ��ź�
+-- OUTPUT PORTD_3 -->�����ɹ�
+-- OUTPUT PORTD_4 -->����˿
+-- OUTPUT PORTD_6 -->��Դ����
+-- OUTPUT PORTB_2 -->�����ƶ�
+-- OUTPUT PORTB_3 -->��˿����
+-- OUTPUT PORTB_4 -->��˿�ƶ�
Total--->7 IO
ALL Used --->5+1+11+7=24 IO  
Rest --->24-24=0     IO
//�����ڼ佫 ����˿   PORTD_4 -->PORTD_1
//                  �����ɹ� PORTD_3 -->PORTD_0 
//                   TXD -->PORTD_3
//                  RXD -->PORTD_4
//
//                   ˿��ѡ��ֻ���� 4.0-4.8����

��ʱ��1����ϵͳ����
UART����ͨ��
��ʱ��0�������ڳ�ʱ
���Ź�

*/

#ifndef CONFIG_H
#define CONFIG_H

//�������汾��ȷ���������
#define CODE_VER                               100//1.00��

#define ENABLE_BIT_DEFINITIONS

//#define DEBUG

#include "iopwm316.h"


#define  CPU_CLK         16000000

typedef struct{
  unsigned int Weld_Start_And_Stop:1;//����ʼ�ն�
  unsigned int Weld_First_Point:1;    //���ӵ�һ��
  unsigned int Swing_Mode:2;          //�ڶ���ʽ
  unsigned int Reservation_Action:1;  //ԤԼ��Ч
  unsigned int Rst:11;
}Mult_Res_Struct; 

typedef union{
  unsigned int Data;
  Mult_Res_Struct Mult_Res;
}Mult_Union;

typedef struct{
  unsigned int Header:4;   //��ʾ��ͬҳ��
  unsigned int Content:7;  //��ʾ��ͬҳ����
  unsigned int Bottom:3;   //��ʾ��ͬҳ��
  unsigned int Mouse:2;    //Ϊ0 ������α� 1�� ��ʾ��1λ�� 2����ʾ��2λ�� 3����ʾ��3λ��
}Page_Struct;
typedef union{
  unsigned int Page;
  Page_Struct Page_Mult;
}Page_Union;
/*
typedef struct{
unsigned long Key;               //����ֵ4
unsigned int Error;               //������6
Mul_Res_Struct Mult;              //8
unsigned int Teach_Point_Num;     //ʾ�̵���10
unsigned int Root_Gap;              //������϶12
unsigned int Plate_Hight;           //���14
unsigned int Weld_Length;           //���ӳ� 16
Page_Struct Page;                   //18
unsigned char Current_Weld_Num;           //��ǰ�����20
unsigned char Set_Weld_Num;
unsigned int Weld_Current;          //���ӵ���22
unsigned int Weld_Volagte;          //���ӵ�ѹ24
unsigned int Weld_Speed;            //�����ٶ�26
unsigned int Swing_Frq;             //�ڶ�Ƶ��28
unsigned int Swing_Wide;            // �ڶ�����30
unsigned int Stay_Time;             // ��ͣ��ʱ��32
}Reg_Union;
typedef union{
unsigned int Reg_Buf[16];//34λͨ������
Reg_Union Reg;
}MB_HoldReg_Union;*/
#define KEY_LOW_BUF             0
#define KEY_HIGH_BUF            1
#define ERROR_BUF               2
#define MULT_BUF                3
#define ROOT_GAP_BUF            4   //������϶12
#define PLATE_HIGHT_BUF         5  //���14
#define WELD_LENGTH_BUF         6   //���ӳ� 16
#define TEACH_POINT_BUF         7
#define PAGE_BUF                8
#define WELD_NUM_BUF            9
#define WELD_CURRENT_BUF       10   //���ӵ���22 ������ѹ ����׼���õ� FFFF������F ����ʮ����
#define WELD_SPEED_BUF         11   //�����ٶ�26
#define WELD_CURRENT_NUM_BUF   12
#define WELD_VOLAGTE_BUF       13   //���ӵ�ѹ24
#define SWING_FRQ_BUF          14   //�ڶ�Ƶ��28
#define SWING_WIDE_BUF         15   // �ڶ�����30
#define STAY_TIME_BUF          16   // ��ͣ��ʱ��32


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

/*ϵͳ��������*/
typedef struct
{
  unsigned long Sys_Modbus_Error:1;//MODBUS����
  unsigned long Sys_Weld_Error:1;
  //Ҳ��Ӧ���м���
  unsigned long Sys_Lcd_Busy:1;
  unsigned long Sys_Rst:28;
  
}Sys_Error;

/*PID����*/
/*
typedef struct
{


}*/


#define  REVPIN(PORT, PIN)           (PORT ^=  (1<<(PIN)))                                 //��תPORT��PINλ
#define  SETPIN(PORT, PIN)           (PORT |=  (1<<(PIN)))                                 //PORT��PINλ = 1
#define  CLRPIN(PORT, PIN)           (PORT &= ~(1<<(PIN)))                                 //PORT��PINλ = 0
#define  GETPIN(PORT, PIN)           (PORT &   (1<<(PIN)))                                 //��PORT��PINλֵ
#define  OUTPIN(PORT, PIN, VALUE)    ((VALUE) ? (SETPIN(PORT, PIN)) : (CLRPIN(PORT, PIN)))


/*modbus define here*/

#define MODBUS_ADDR                         0x01

/*�����ʵ�ѡ�� 16M���� U2X=0 ����������� MODBUS �����С��2% �Ƽ�ѡ�� 4800 9600 19200 38400 76800*/
#define MODBUS_BAUDRATE                     38400

#define MB_TIMER_PRESCALER                (1024)   //��Ƶ

#define MB_TIMER_FREQUENCY                (16)        //ϵͳʱ��16M

#define MB_KEY_RES                              10
#define MB_CURRENT_PAGE                         12

/*����״̬*/
#define  WELD_STATUS_IDLE                       0 //����̬
#define  WELD_STATUS_FEED                       1 //��˿̬
#define  WELD_STATUS_BACK                       2 //��˿̬
#define  WELD_STATUS_TOUCH                      3 //�Ӵ�״̬

#define  WELD_STATUS_START                      1 //����̬
#define  WELD_STATUS_SLOW_SEND                  2 //����˿̬
#define  WELD_STATUS_PUMPBACK                   3 //�س�̬
#define  WELD_STATUS_ARC_SUCCESS                4 //�����ɹ�̬
#define  WELD_STATUS_WELDING                    5 //������̬
#define  WELD_STATUS_STOP                       6 //�ϻ�̬ 
#define  WELD_STATUS_ARC_STOP                   7 //�ջ�̬
#define  WELD_STATUS_BURNBACK                   8 //����̬

#endif