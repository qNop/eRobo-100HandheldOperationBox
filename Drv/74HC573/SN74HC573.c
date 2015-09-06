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
  /*存储相应状态*/
  Sn74hc573_Data |= (KeyCode<<2);
  /*LE输出高电平*/
  SET_LE();
  /*数据*/
  OUTPUT_LCD_DB(Sn74hc573_Data);
  /*输出数据*/
  CLEAR_LE();
  /*延迟*/
  __no_operation();
  __no_operation();
  /*置位LE*/
  SET_LE();
  /**/
  OUTPUT_LCD_DB(temp);
}

void Sn_Output_CS(unsigned char bit)
{
  unsigned char temp;
  temp = GET_LCD_DB();
  /*LCD片选左半部分 CS1 0 CS2 1*/
  if(bit){
     /*存储相应状态*/
    Sn74hc573_Data |= CS1; 
  }
  /*LCD片选右半部分 CS1 1 CS2 0*/
  else{
    Sn74hc573_Data |= CS2;
  }
  /*LE输出高电平*/
  SET_LE();
  /*数据*/
  OUTPUT_LCD_DB(Sn74hc573_Data);
  /*输出数据*/
  CLEAR_LE();
  __no_operation();
  __no_operation();
  /*置位LE*/
  SET_LE();
  /**/
  OUTPUT_LCD_DB(temp);
}
