 /*
  *文件名：lcd12864.h
  *液晶型号：深圳富创LG128642-FFDWH6V-NT,
  *液晶内部驱动器：NT7108C
  */

#ifndef LCD12864_H_
#define LCD12864_H_

#include "Config.h"

#define TRUE                       1
#define FALSE                      0

#define LCD_DISPLAY_ON            0X3F
#define LCD_DISPLAY_OFF           0X3E

#define LCD_SETPAGE(X)          (( 0X07 & X )| 0XB8 )
#define LCD_SETADDRESS(Y)       (( 0X3F & Y )| 0X40 )
#define LCD_DISPLAYSTARTLINE(Z) ( 0XC0 | Z )

#define LCD_LEFT_MAX             0X40
#define LCD_RIGHT_MAX            0X80
    
#define LCD_DB_PIN               PINB
#define LCD_DDR                  DDRB

#define LCD_GETSTATUS_BUSY(STATUS)      ((STATUS & 0X80) ? 1 : 0)
#define LCD_GETSTATUS_ONOFF(STATUS)     ((STATUS & 0X20) ? 0 : 1)
#define LCD_GETSTATUS_REST(STATUS)      ((STATUS & 0X10) ? 1 : 0)

Sys_Error LCD_Init(void);
Sys_Error Clr_LCD(void);
Sys_Error Set_Cursor(unsigned char x,unsigned char y);
Sys_Error Write_Data(unsigned char Data);
Sys_Error Write_Cmd(unsigned char Cmd);

#endif 