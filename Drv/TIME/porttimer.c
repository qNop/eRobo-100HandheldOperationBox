
#include "port.h"
#include "mb.h"
#include "mb_m.h"
#include "mbport.h"
#include "mbrtu.h"


/* ----------------------- Defines ------------------------------------------*/

#define TIMER_ENABLE()      SETPIN(TIMSK0, TOIE0);
#define TIMER_DISABLE()     CLRPIN(TIMSK0, TOIE0);

/* ----------------------- Static variables ---------------------------------*/
//static USHORT   usTimerOCRADelta;
//static USHORT usT35TimeOut50us;
static unsigned char TimeOver_Count=0;
static USHORT   usTimerOCRADelta;

#define Timer_Reload             255-160;

void prvvTIMERExpiredISR( void )
{
   pxMBMasterPortCBTimerExpired();
}


/* ----------------------- Start implementation -----------------------------*/
BOOL xMBMasterPortTimersInit( USHORT usTimeOut50us ) 
{
  //  usTimerOCRADelta =
  //    (65535 - (MB_TIMER_FREQUENCY * 50 * usTim1Timerout50us / 1024));
    usTimerOCRADelta =
     (255-(unsigned char)(usTimeOut50us*MB_TIMER_FREQUENCY*50/MB_TIMER_PRESCALER));
    TCCR0A = 0x00;
    TCCR0B = 0x00;
    SETPIN(SREG, 7);                       //ʹ��ȫ����
    vMBMasterPortTimersDisable();
    return TRUE;
}

void vMBMasterPortTimersT35Enable()
{
    SETPIN(TIMSK0, TOIE0);               //ʹ��T1����ж�
    TCNT0=(usTimerOCRADelta);
    SETPIN(TCCR0B, CS02);                  //��ʼ����
    SETPIN(TCCR0B, CS00);
    TimeOver_Count=0;
}

void vMBMasterPortTimersConvertDelayEnable()
{
    SETPIN(TIMSK0, TOIE0);               //ʹ��T1����ж�
    TCNT0=Timer_Reload;             //10ms��ʱ
    SETPIN(TCCR0B, CS02);                  //��ʼ����
    SETPIN(TCCR0B, CS00);
    TimeOver_Count=MB_MASTER_DELAY_MS_CONVERT/10;
}

void vMBMasterPortTimersRespondTimeoutEnable()
{
    SETPIN(TIMSK0, TOIE0);               //ʹ��T1����ж�
    TCNT0=Timer_Reload;          //10ms��ʱ
    SETPIN(TCCR0B, CS02);                  //��ʼ����
    SETPIN(TCCR0B, CS00);
    TimeOver_Count=MB_MASTER_TIMEOUT_MS_RESPOND/10;
}

void vMBMasterPortTimersDisable()
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
   TCNT0 =Timer_Reload;
   if(TimeOver_Count!=0)
      TimeOver_Count--;
   else
      prvvTIMERExpiredISR();
}
