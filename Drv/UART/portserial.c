
/**/

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mb_m.h"
#include "mbrtu.h"
#include "mbport.h"

#define UART_DR             UDR 
#define USART_RX_ENABLE()   SETPIN(UCSRB, RXCIE0)
#define USART_RX_DISABLE()  CLRPIN(UCSRB, RXCIE0)
#define USART_TX_ENABLE()   SETPIN(UCSRB, UDRIE0)
#define USART_TX_DISABLE()  CLRPIN(UCSRB, UDRIE0)

/* ----------------------- Start implementation -----------------------------*/
void vMBMasterPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    ENTER_CRITICAL_SECTION();
    if( xRxEnable ){
        USART_RX_ENABLE();
    }
    else{
       USART_RX_DISABLE();   
    }
    if( xTxEnable ){
       USART_TX_ENABLE();
    }
    else{
       USART_TX_DISABLE();
    }
    EXIT_CRITICAL_SECTION();
}

BOOL xMBMasterPortSerialInit( UCHAR ucPort, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
    BOOL  bInitialized = TRUE;
  //  UCSRA |=(1<<U2X0);
    UCSRB=0x00;
    UCSRC |= (1<<UCSZ01)|(1<<UCSZ00); //8λ����λ+1λֹͣλ
    UBRR= (CPU_CLK/MODBUS_BAUDRATE/16-1);
    UCSRB |= (1<<RXEN0)|(1<<TXEN0);  //�����ͺͽ���
    
    return bInitialized;
}
//����
BOOL xMBMasterPortSerialPutByte( CHAR ucByte )
{
   while (!( UCSRA & (1<<UDRE0)));
    UART_DR = ucByte;
   return TRUE;
}
//����
BOOL xMBMasterPortSerialGetByte( CHAR * pucByte )
{
  *pucByte = (CHAR)(UART_DR);
  return TRUE;
}


//�����ж��ӳ���  

__interrupt void RXC_isr( void )
{
    pxMBMasterFrameCBByteReceived();
}  


//�����ж��ӳ���  
__interrupt void TX_isr( void )
{
  
    pxMBMasterFrameCBTransmitterEmpty();
} 

void EnterCriticalSection( void )
{
  CLRPIN(SREG, 7); //�����ж�
  
}

void ExitCriticalSection( void )
{
  SETPIN(SREG, 7);//�����ж�
}
