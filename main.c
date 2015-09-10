
/*********************************************************************/
#include <stdlib.h>
//freertos 
#include "FreeRTOS.h"
#include "task.h"

//modbus
#include "mb_m.h"

//sys配置

#include "io_port.h"
#include "LCD12864.h"
#include "config.h"
#include "Sn74hc573.h"
#include "delay.h"

static Type_Key  Key;

/**********************************全局变量*******************************************/

/********************************程序*************************************************/
//空闲任务钩子函数
void vApplicationIdleHook(void)
{
  
   //喂狗
   
}

/***********************************任务**********************************************/
void UART_Task(void *pvParameters)
{
  portTickType xLastWakeTime;
  // Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount ();
  unsigned char i=0;
  for(;;)
  {     
    i++;
    if(i>9){
      i=0;
    }
   
    eMBMasterPoll(); //调用 MOdbusPOLL
    vTaskDelayUntil(&xLastWakeTime,100); 
  }
}

/******************************************任务***************************************/
void Control_task(void *pvParameters)
{
  Key_Union Key_Code;
  unsigned char *p;
  portTickType xLastWakeTime;
  // Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount ();
  Display_String(0,0,"SET:0<:0>:0Can:0");
  Display_String(0,1,"      ^:0    ]:0");
  Display_String(0,2," [:0<:0 >:0]:_ ");
  Display_String(0,3,"      ^:0    ]:0");
  Display_String(0,4,"FEED:0I+:0I-:0");
  Display_String(0,5,"STAR:0SS:0STOP:0");
  Display_String(0,6,"SEND:");
  Display_String(0,7,"RECV:");
  for(;;)
  {  
    
    unsigned char i;
     eMBMasterReqWriteHoldingRegister(0x01,1,i,10);
    //按键扫描
    Key_Code.Key_Index=0;
    Sn_Output_KeyCode(0x0e);
    switch(PINC&0xf0){
      case 0xe0:Key_Code.Key_Struct.Set=1;break;//set键按下
      case 0xd0:Key_Code.Key_Struct.Forward=1;break;
      case 0xb0:Key_Code.Key_Struct.Right=1;break;
      case 0x70:Key_Code.Key_Struct.Feed=1;break;
    }
    Sn_Output_KeyCode(0x0d);
    switch(PINC&0xf0){
      case 0xe0:Key_Code.Key_Struct.Add=1;break;
      case 0xd0:Key_Code.Key_Struct.Up=1;break;
      case 0xb0:Key_Code.Key_Struct.Travel_Right=1;break;
      case 0x70:Key_Code.Key_Struct.Current_Add=1;break;
    }
    Sn_Output_KeyCode(0x0b);
    switch(PINC&0xf0){
      case 0xe0:Key_Code.Key_Struct.Dec=1;break;
      case 0xd0:Key_Code.Key_Struct.Travel_Left=1;break;
      case 0xb0:Key_Code.Key_Struct.Back=1;break;
      case 0x70:Key_Code.Key_Struct.Currene_Dec=1;break;
    }
    Sn_Output_KeyCode(0x07);
    switch(PINC&0xf0){
      case 0xe0:Key_Code.Key_Struct.Cancel=1;break;
      case 0xd0:Key_Code.Key_Struct.Left=1;break;
      case 0xb0:Key_Code.Key_Struct.Down=1;break;
    }
    
    if(GET_START_PIN())Key_Code.Key_Struct.Start=1;
    if(GET_RESET_PIN())Key_Code.Key_Struct.Reset=1;
    if(GET_STOP_PIN())Key_Code.Key_Struct.Stop=1;
    Key.Trg=Key_Code.Key_Index&(Key_Code.Key_Index^Key.Cont);
    Key.Release=(Key_Code.Key_Index^Key.Trg^Key.Cont);
    Key.Cont=Key_Code.Key_Index;
    vMBMasterGetRTUSndBuf(&p);
    for(i=0;i<(usMBMasterGetPDUSndLength()+3);i++){
     // *(p+i)+=0x30;
    }
    Display_String(40,6,p);
   //vMB
    //按键触发
    if(Key.Trg&KEY_SET)         Display_Char(32,0,'1');
    if(Key.Trg&KEY_ADD)         Display_Char(56,0,'1');
    if(Key.Trg&KEY_DEC)         Display_Char(80,0,'1');
    if(Key.Trg&KEY_CANCEL)      Display_Char(120,0,'1');
    if(Key.Trg&KEY_FEED)        Display_Char(40,4,'1');
    if(Key.Trg&KEY_CURRENT_ADD) Display_Char(72,4,'1');
    if(Key.Trg&KEY_CURRENT_DEC) Display_Char(104,4,'1');
    if(Key.Trg&KEY_START)       Display_Char(40,5,'1');
    if(Key.Trg&KEY_RESET)       Display_Char(72,5,'1');
    if(Key.Trg&KEY_STOP)        Display_Char(120,5,'1');
    if(Key.Trg&KEY_UP)          Display_Char(120,1,'1');
    if(Key.Trg&KEY_DOWN)        Display_Char(120,3,'1');
    if(Key.Trg&KEY_FORWARD)     Display_Char(64,1,'1');
    if(Key.Trg&KEY_BACK)        Display_Char(64,3,'1');
    if(Key.Trg&KEY_LEFT)        Display_Char(48,2,'1');
    if(Key.Trg&KEY_RIGHT)       Display_Char(80,2,'1');
    if(Key.Trg&KEY_TRAVELLEFT)  Display_Char(24,2,'1');
    if(Key.Trg&KEY_TRAVELRIGHT) Display_Char(104,2,'1');
    //按键释放
    if(Key.Release&KEY_SET)         Display_Char(32,0,'0');
    if(Key.Release&KEY_ADD)         Display_Char(56,0,'0');
    if(Key.Release&KEY_DEC)         Display_Char(80,0,'0');
    if(Key.Release&KEY_CANCEL)      Display_Char(120,0,'0');
    if(Key.Release&KEY_FEED)        Display_Char(40,4,'0');
    if(Key.Release&KEY_CURRENT_ADD) Display_Char(72,4,'0');
    if(Key.Release&KEY_CURRENT_DEC) Display_Char(104,4,'0');
    if(Key.Release&KEY_START)       Display_Char(40,5,'0');
    if(Key.Release&KEY_RESET)       Display_Char(72,5,'0');
    if(Key.Release&KEY_STOP)        Display_Char(120,5,'0');
    if(Key.Release&KEY_UP)          Display_Char(120,1,'0');
    if(Key.Release&KEY_DOWN)        Display_Char(120,3,'0');
    if(Key.Release&KEY_FORWARD)     Display_Char(64,1,'0');
    if(Key.Release&KEY_BACK)        Display_Char(64,3,'0');
    if(Key.Release&KEY_LEFT)        Display_Char(48,2,'0');
    if(Key.Release&KEY_RIGHT)       Display_Char(80,2,'0');
    if(Key.Release&KEY_TRAVELLEFT)  Display_Char(24,2,'0');
    if(Key.Release&KEY_TRAVELRIGHT) Display_Char(104,2,'0');
    
    vTaskDelayUntil(&xLastWakeTime,1000);  
  }   
}
/***********************************主函数*******************************************/
int main(void)
{
  //初始化系统
  INIT_IO(); 
  //初始化LCD
  LCD_Init();
  // 初始化Modbus
  eMBMasterInit(MB_RTU,0,MODBUS_BAUDRATE,MB_PAR_NONE);
  eMBMasterEnable();
  //创建任务 
  xTaskCreate(Control_task,"Control",configMINIMAL_STACK_SIZE,NULL,1,NULL);
  //创建任务
  xTaskCreate(UART_Task,"UART",configMINIMAL_STACK_SIZE,NULL,2,NULL);
  //任务调度
  vTaskStartScheduler();
  //永远执行不到这里
  for(;;);
  
}

