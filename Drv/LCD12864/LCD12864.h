 /*
  *文件名：lcd12864.h
  *液晶型号：深圳富创LG128642-FFDWH6V-NT,
  *液晶内部驱动器：NT7108C
  */

#ifndef LCD12864_H_
#define LCD12864_H_

#define TRUE                       1
#define FALSE                      0

#define LCD_DISPLAY_ON            0X3F
#define LCD_DISPLAY_OFF           0X3E

#define LCD_SETPAGE(X)          ( 0XB8 | X )
#define LCD_SETADDRESS(Y)       ( 0X40 | Y )
#define LCD_DISPLAYSTARTLINE(Z) ( 0XC0 | Z )
    
#define LCD_DB_PIN               PINB
#define LCD_DDR                  DDRB

#define LCD_GETSTATUS_BUSY(STATUS)      ((STATUS & 0X80) ? 1 : 0)
#define LCD_GETSTATUS_ONOFF(STATUS)     ((STATUS & 0X20) ? 0 : 1)
#define LCD_GETSTATUS_REST(STATUS)      ((STATUS & 0X10) ? 1 : 0)


#endif 