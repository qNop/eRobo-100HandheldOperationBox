
/*********************************************************************/
#include <stdlib.h>
//freertos 
#include "FreeRTOS.h"
#include "task.h"

//modbus
#include "mb_m.h"
#include "mbport.h"
//sys配置

#include "io_port.h"
#include "LCD12864.h"
#include "config.h"

#include "delay.h"
#include "menu.h"

eMBMasterErrorEventType MB_Error;
static  Type_Key  Key;
unsigned int Modbus_Reg[17];
unsigned int *pModbus_Reg;
unsigned char Time_Enable=0;
unsigned char Time_Count=0;

/**********************************全局变量*******************************************/

/********************************程序*************************************************/
//空闲任务钩子函数
void vApplicationIdleHook(void)
{ 
   //喂狗
  Menu_Select(pModbus_Reg);
}

/***********************************任务**********************************************/
void Modbus_Task(void *pvParameters)
{
static  portTickType Display_xLastWakeTime;
  
  Display_xLastWakeTime = xTaskGetTickCount();
 
  for(;;)
  {     
    eMBMasterPoll(); //调用 MOdbusPOLL
    //显示任务周期为200ms
    vTaskDelayUntil(&Display_xLastWakeTime,3); 
  }
}

/******************************************任务***************************************/
void Control_task(void *pvParameters)
{
  Key_Union Key_Code;
  eMBMasterEventType    eEvent;
  portTickType Control_xLastWakeTime;
  Control_xLastWakeTime = xTaskGetTickCount();
  pModbus_Reg=&Modbus_Reg[0];//获取mobus寄存器指针
  for(;;)
  { 
    //光标闪烁计时器
    if(Time_Enable)
      Time_Count++;
    //获取按键值  
    Key_Code=Get_Key();
    //按键值处理
    Key.Trg=Key_Code.Key_Index&(Key_Code.Key_Index^Key.Cont);
    Key.Release=(Key_Code.Key_Index^Key.Trg^Key.Cont);
    Key.Cont=Key_Code.Key_Index;
    //MODBUS发送器状态
    xMBMasterPortEventGet( &eEvent );
    //如果发送处于预备状态则进入发送状态
    if(eEvent == EV_MASTER_READY){
      //按键触发 发送触发值
      *pModbus_Reg=Key_Code.Key_Index;//存储按键高位
      Key_Code.Key_Index>>=8;
      *(pModbus_Reg+1)=Key_Code.Key_Index;//存储按键低位
      if(Key.Trg){
        eMBMasterReqWriteMultipleHoldingRegister(MODBUS_ADDR,MB_KEY_RES,2,\
          pModbus_Reg,10);
      }
      else if(Key.Release){//按键释放发送按键释放值
        eMBMasterReqWriteMultipleHoldingRegister(MODBUS_ADDR,MB_KEY_RES,2,\
          pModbus_Reg,10);
      }
      else{//无按键按下则发送寄存器查询代码
        
        eMBMasterReqReadHoldingRegister(MODBUS_ADDR,MB_CURRENT_PAGE,15,10);
      }
    }
    //该任务周期为40ms
    vTaskDelayUntil(&Control_xLastWakeTime,30);  
  }   
}
/***********************************主函数*******************************************/
int main(void)
{
  //初始化系统
  INIT_IO(); 
  //初始化LCD
  LCD_Init();
  //显示公司logo
  Display_Logo(2);
  //清除显示屏
  Clr_LCD();
  //初始化Modbus
  eMBMasterInit(MB_RTU,0,MODBUS_BAUDRATE,MB_PAR_NONE);
  //使能Modbus
  eMBMasterEnable();
  //发送主机处于待机状态
  xMBMasterPortEventPost(EV_MASTER_READY);
  //创建任务 
  xTaskCreate(Control_task,"Control",configMINIMAL_STACK_SIZE,NULL,2,NULL);
  //创建任务
  xTaskCreate(Modbus_Task,"Modbus",configMINIMAL_STACK_SIZE,NULL,1,NULL);
  //任务调度
  vTaskStartScheduler();
  //永远执行不到这里
  for(;;);
  
}

