
/*********************************************************************/
#include <stdlib.h>
//freertos 
#include "FreeRTOS.h"
#include "task.h"

//modbus
#include "mb.h"


//sys配置

#include "io_port.h"
#include "LCD12864.h"
#include "config.h"
#include "Sn74hc573.h"
#include "delay.h"

/**********************************全局变量*******************************************/

/********************************程序*************************************************/
//空闲任务钩子函数
void vApplicationIdleHook(void)
{
   // eMBPoll(); //调用 MOdbusPOLL
}

/***********************************任务**********************************************/
void UART_Task(void *pvParameters)
{
   
   portTickType xLastWakeTime;
   // Initialise the xLastWakeTime variable with the current time.
   xLastWakeTime = xTaskGetTickCount ();
     for(;;)
     {  
             vTaskDelayUntil(&xLastWakeTime,100); 
     }
     
}

/******************************************任务***************************************/
void Control_task(void *pvParameters)
{
  unsigned char p[20]; 
  portTickType xLastWakeTime;
   // Initialise the xLastWakeTime variable with the current time.
   xLastWakeTime = xTaskGetTickCount ();
   for(;;)
   {    
     
     switch(p[0]){
       case 0:Sn_Output_CS(1);
       p[0]=1;break;
       case 1:       
       Sn_Output_CS(0);
       p[0]=0;break;
     }
     p[16]=p[20]+p[19];
     vTaskDelayUntil(&xLastWakeTime,1000);  
   }   
}
/***********************************主函数*******************************************/
int main(void)
{
  //初始化系统
  INIT_IO(); 
  //初始化LCD
  if(LCD_Init()!=Sys_No_Error){
    SETPIN(PORT_LE,LE);
  }
 // 初始化Modbus
  eMBInit(MB_RTU,MODBUS_ADDR,0,MODBUS_BAUDRATE,MB_PAR_NONE);
  eMBEnable();
  //创建任务 
  xTaskCreate(Control_task,"Control",configMINIMAL_STACK_SIZE,NULL,1,NULL);
  //创建任务
  xTaskCreate(UART_Task,"UART",configMINIMAL_STACK_SIZE,NULL,2,NULL);
  //任务调度
  vTaskStartScheduler();
  //永远执行不到这里
  for(;;);

}

