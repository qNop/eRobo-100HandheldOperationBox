#include <iopwm316.h>
#include "SN74HC573.h"
#include "IO_PORT.h"
#include "delay.h"

static unsigned char Sn74hc573_Data;
 
unsigned char Sn_Get_Data()
{
    return Sn74hc573_Data;
}

void Sn_Output_KeyCode(unsigned char KeyCode)
{
  /*存储相应状态*/
  Sn74hc573_Data = (KeyCode<<2);
  /*LE输出高电平*/
  /*数据*/
  OUTPUT_LCD_DB(Sn74hc573_Data);
  /*置位LE*/
  SET_LE();
  Delay_us(1);
  CLEAR_LE();

}
