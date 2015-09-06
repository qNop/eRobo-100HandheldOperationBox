
/*********************************************************************/
#include <stdlib.h>
//freertos 
#include "FreeRTOS.h"
#include "task.h"

//modbus
#include "mb.h"


//sys配置
#include "config.h"
#include "io_port.h"

/**********************************全局变量*******************************************/

/********************************程序*************************************************/
//空闲任务钩子函数
void vApplicationIdleHook(void)
{
    eMBPoll(); //调用 MOdbusPOLL
}

/***********************************任务**********************************************/
void UART_Task(void *pvParameters)
{
   
   portTickType xLastWakeTime;
   // Initialise the xLastWakeTime variable with the current time.
   xLastWakeTime = xTaskGetTickCount ();
     for(;;)
     {  
             
     }
     
}

/******************************************任务***************************************/
void Control_task(void *pvParameters)
{
   portTickType xLastWakeTime;
   // Initialise the xLastWakeTime variable with the current time.
   xLastWakeTime = xTaskGetTickCount ();
   for(;;)
   {    
     //等待焊接队列 直到焊接队列有效 相当于迅速挂起控制任务
       
   }
     
}
/***********************************主函数*******************************************/
int main(void)
{

  //初始化系统
  INIT_IO(); 
 // 初始化Modbus
  eMBInit(MB_RTU,MODBUS_ADDR,0,MODBUS_BAUDRATE,MB_PAR_NONE);
  eMBEnable();
  //创建任务 
  xTaskCreate(Control_task,"Control",configMINIMAL_STACK_SIZE,NULL,2,NULL);
  //创建任务
  xTaskCreate(UART_Task,"UART",configMINIMAL_STACK_SIZE,NULL,1,NULL);
  //任务调度
  vTaskStartScheduler();
  //永远执行不到这里
  for(;;);

}

