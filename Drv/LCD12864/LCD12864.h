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

#define LCD_SETPAGE(X)          ( 0XB8 | X )
#define LCD_SETADDRESS(Y)       ( 0X40 | Y )
#define LCD_DISPLAYSTARTLINE(Z) ( 0XC0 | Z )

#define LCD_LEFT_MAX             0X40
#define LCD_RIGHT_MAX            0X80
    
#define LCD_DB_PIN               PINB
#define LCD_DDR                  DDRB
    
#define  LCD_LEFT()       SET_LCD_CS2(),CLEAR_LCD_CS1()
#define  LCD_RIGHT()      SET_LCD_CS1(),CLEAR_LCD_CS2()

#define LCD_GETSTATUS_BUSY(STATUS)      ((STATUS & 0X80) ? 1 : 0)
#define LCD_GETSTATUS_ONOFF(STATUS)     ((STATUS & 0X20) ? 0 : 1)
#define LCD_GETSTATUS_REST(STATUS)      ((STATUS & 0X10) ? 1 : 0)

void LCD_Init(void);
//清屏时间为23ms
void Clr_LCD(void);
void Set_Cursor(unsigned char x,unsigned char y);
void Write_Data(unsigned char Data);
void Write_Cmd(unsigned char Cmd);
#ifdef USE_ASCII
void Display_Char(unsigned char x,unsigned char y,unsigned char Char);
void Display_String(unsigned char x,unsigned char y,unsigned char *pString);
#endif
void Display_Logo(unsigned char y);
void Display_Chinese(unsigned char *x,unsigned char y,\
                     unsigned char __flash *Ch,unsigned char width);
#endif 