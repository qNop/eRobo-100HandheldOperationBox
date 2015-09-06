#include <iopwm316.h>
#include "SN74HC573.h"
#include "IO_PORT.h"
#include <intrinsics.h>

static unsigned char Sn74hc573_Data;
 
unsigned char Sn_Get_Data()
{
    return Sn74hc573_Data;
}

void Sn_Output_KeyCode(unsigned char KeyCode)
{
  unsigned char temp;
  temp = GET_LCD_DB();
  /*�洢��Ӧ״̬*/
  Sn74hc573_Data |= (KeyCode<<2);
  /*LE����ߵ�ƽ*/
  SET_LE();
  /*����*/
  OUTPUT_LCD_DB(Sn74hc573_Data);
  /*�������*/
  CLEAR_LE();
  /*�ӳ�*/
  __no_operation();
  __no_operation();
  /*��λLE*/
  SET_LE();
  /**/
  OUTPUT_LCD_DB(temp);
}

void Sn_Output_CS(unsigned char bit)
{
  unsigned char temp;
  temp = GET_LCD_DB();
  /*LCDƬѡ��벿�� CS1 0 CS2 1*/
  if(bit){
     /*�洢��Ӧ״̬*/
    Sn74hc573_Data |= CS1; 
  }
  /*LCDƬѡ�Ұ벿�� CS1 1 CS2 0*/
  else{
    Sn74hc573_Data |= CS2;
  }
  /*LE����ߵ�ƽ*/
  SET_LE();
  /*����*/
  OUTPUT_LCD_DB(Sn74hc573_Data);
  /*�������*/
  CLEAR_LE();
  __no_operation();
  __no_operation();
  /*��λLE*/
  SET_LE();
  /**/
  OUTPUT_LCD_DB(temp);
}