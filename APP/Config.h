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

#include "iopwm316.h"

/*ϵͳ��������*/
typedef enum
{
    Sys_No_Error,//�޴���
    Sys_Modbus_Error,
    //Ӧ���м���
    
    Sys_Weld_Error,
    //Ҳ��Ӧ���м���
    
    
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
#define MODBUS_BAUDRATE                     115200

  #define MB_TIMER_PRESCALER                (1024)   //��Ƶ

  #define MB_TIMER_FREQUENCY                (16)        //ϵͳʱ��16M
  #if  MODBUS_BAUDRATE>=19200
        #define usTim1Timerout50us           35
  #else       
        #define usTim1Timerout50us          7*110000/MODBUS_BAUDRATE//((7*220000) / (2*MODBUS_BAUDRATE))
  #endif
  #define usTimerOCRADelta      (255-(unsigned char)(usTim1Timerout50us*MB_TIMER_FREQUENCY*50/MB_TIMER_PRESCALER))

                          
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