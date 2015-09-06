
#include "port.h"
#include "mb.h"
#include "mbport.h"
#include "mbrtu.h"

/* ----------------------- Defines ------------------------------------------*/

#define TIMER_ENABLE()      SETPIN(TIMSK0, TOIE0);
#define TIMER_DISABLE()     CLRPIN(TIMSK0, TOIE0);

/* ----------------------- Static variables ---------------------------------*/
//static USHORT   usTimerOCRADelta;


void prvvTIMERExpiredISR( void )
{
   xMBRTUTimerT35Expired();
}


/* ----------------------- Start implementation -----------------------------*/
BOOL xMBPortTimersInit( void ) 
{
  //  usTimerOCRADelta =
  //    (65535 - (MB_TIMER_FREQUENCY * 50 * usTim1Timerout50us / 1024));
    TCCR0A = 0x00;
    TCCR0B = 0x00;
    SETPIN(SREG, 7);                       //ʹ��ȫ����
    vMBPortTimersDisable();
    return TRUE;
}


void vMBPortTimersEnable(){
   
    SETPIN(TIMSK0, TOIE0);               //ʹ��T1����ж�
    TCNT0=(unsigned char)(usTimerOCRADelta);
    SETPIN(TCCR0B, CS02);                  //��ʼ����
    SETPIN(TCCR0B, CS00);
}

 void vMBPortTimersDisable(  )
{
    /* Disable the timer. */
    CLRPIN(TCCR0B, CS02);                 //�رռ���
    CLRPIN(TCCR0B, CS01);
    CLRPIN(TCCR0B, CS00);
    CLRPIN(TIMSK0, TOIE0); 
}

//��ʱ��T1����жϷ������
//#pragma vector = TIMER0_OVF_vect
__interrupt void Timer0Isr( void ){
   TCNT0 =(unsigned char)(usTimerOCRADelta);
   prvvTIMERExpiredISR();
}
