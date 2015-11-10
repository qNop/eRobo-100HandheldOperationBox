
/*********************************************************************/
#include <stdlib.h>
//freertos 
#include "FreeRTOS.h"
#include "task.h"

//modbus
#include "mb_m.h"
#include "mbport.h"
//sys����

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

/**********************************ȫ�ֱ���*******************************************/

/********************************����*************************************************/
//���������Ӻ���
void vApplicationIdleHook(void)
{ 
   //ι��
  Menu_Select(pModbus_Reg);
}

/***********************************����**********************************************/
void Modbus_Task(void *pvParameters)
{
static  portTickType Display_xLastWakeTime;
  
  Display_xLastWakeTime = xTaskGetTickCount();
 
  for(;;)
  {     
    eMBMasterPoll(); //���� MOdbusPOLL
    //��ʾ��������Ϊ200ms
    vTaskDelayUntil(&Display_xLastWakeTime,3); 
  }
}

/******************************************����***************************************/
void Control_task(void *pvParameters)
{
  Key_Union Key_Code;
  eMBMasterEventType    eEvent;
  portTickType Control_xLastWakeTime;
  Control_xLastWakeTime = xTaskGetTickCount();
  pModbus_Reg=&Modbus_Reg[0];//��ȡmobus�Ĵ���ָ��
  for(;;)
  { 
    //�����˸��ʱ��
    if(Time_Enable)
      Time_Count++;
    //��ȡ����ֵ  
    Key_Code=Get_Key();
    //����ֵ����
    Key.Trg=Key_Code.Key_Index&(Key_Code.Key_Index^Key.Cont);
    Key.Release=(Key_Code.Key_Index^Key.Trg^Key.Cont);
    Key.Cont=Key_Code.Key_Index;
    //MODBUS������״̬
    xMBMasterPortEventGet( &eEvent );
    //������ʹ���Ԥ��״̬����뷢��״̬
    if(eEvent == EV_MASTER_READY){
      //�������� ���ʹ���ֵ
      *pModbus_Reg=Key_Code.Key_Index;//�洢������λ
      Key_Code.Key_Index>>=8;
      *(pModbus_Reg+1)=Key_Code.Key_Index;//�洢������λ
      if(Key.Trg){
        eMBMasterReqWriteMultipleHoldingRegister(MODBUS_ADDR,MB_KEY_RES,2,\
          pModbus_Reg,10);
      }
      else if(Key.Release){//�����ͷŷ��Ͱ����ͷ�ֵ
        eMBMasterReqWriteMultipleHoldingRegister(MODBUS_ADDR,MB_KEY_RES,2,\
          pModbus_Reg,10);
      }
      else{//�ް����������ͼĴ�����ѯ����
        
        eMBMasterReqReadHoldingRegister(MODBUS_ADDR,MB_CURRENT_PAGE,15,10);
      }
    }
    //����������Ϊ40ms
    vTaskDelayUntil(&Control_xLastWakeTime,30);  
  }   
}
/***********************************������*******************************************/
int main(void)
{
  //��ʼ��ϵͳ
  INIT_IO(); 
  //��ʼ��LCD
  LCD_Init();
  //��ʾ��˾logo
  Display_Logo(2);
  //�����ʾ��
  Clr_LCD();
  //��ʼ��Modbus
  eMBMasterInit(MB_RTU,0,MODBUS_BAUDRATE,MB_PAR_NONE);
  //ʹ��Modbus
  eMBMasterEnable();
  //�����������ڴ���״̬
  xMBMasterPortEventPost(EV_MASTER_READY);
  //�������� 
  xTaskCreate(Control_task,"Control",configMINIMAL_STACK_SIZE,NULL,2,NULL);
  //��������
  xTaskCreate(Modbus_Task,"Modbus",configMINIMAL_STACK_SIZE,NULL,1,NULL);
  //�������
  vTaskStartScheduler();
  //��Զִ�в�������
  for(;;);
  
}

