
/*********************************************************************/
#include <stdlib.h>
//freertos 
#include "FreeRTOS.h"
#include "task.h"

//modbus
#include "mb.h"


//sys����
#include "config.h"
#include "io_port.h"

/**********************************ȫ�ֱ���*******************************************/

/********************************����*************************************************/
//���������Ӻ���
void vApplicationIdleHook(void)
{
    eMBPoll(); //���� MOdbusPOLL
}

/***********************************����**********************************************/
void UART_Task(void *pvParameters)
{
   
   portTickType xLastWakeTime;
   // Initialise the xLastWakeTime variable with the current time.
   xLastWakeTime = xTaskGetTickCount ();
     for(;;)
     {  
             
     }
     
}

/******************************************����***************************************/
void Control_task(void *pvParameters)
{
   portTickType xLastWakeTime;
   // Initialise the xLastWakeTime variable with the current time.
   xLastWakeTime = xTaskGetTickCount ();
   for(;;)
   {    
     //�ȴ����Ӷ��� ֱ�����Ӷ�����Ч �൱��Ѹ�ٹ����������
       
   }
     
}
/***********************************������*******************************************/
int main(void)
{

  //��ʼ��ϵͳ
  INIT_IO(); 
 // ��ʼ��Modbus
  eMBInit(MB_RTU,MODBUS_ADDR,0,MODBUS_BAUDRATE,MB_PAR_NONE);
  eMBEnable();
  //�������� 
  xTaskCreate(Control_task,"Control",configMINIMAL_STACK_SIZE,NULL,2,NULL);
  //��������
  xTaskCreate(UART_Task,"UART",configMINIMAL_STACK_SIZE,NULL,1,NULL);
  //�������
  vTaskStartScheduler();
  //��Զִ�в�������
  for(;;);

}

