
#include <iopwm316.h>
#include "LCD12864.h"
#include "SN74HC573.h"
#include <intrinsics.h>
#include "IO_PORT.h"
#include "Config.h"


#define  SET_RS()         SETPIN(PORT_LCD_RS,LCD_RS)
#define  CLR_RS()         CLRPIN(PORT_LCD_RS,LCD_RS)

#define  SET_RW()         SETPIN(PORT_LCD_RW,LCD_RW)
#define  CLR_RW()         CLRPIN(PORT_LCD_RW,LCD_RW)

#define  SET_E()         SETPIN(PORT_LCD_E,LCD_E)
#define  CLR_E()         CLRPIN(PORT_LCD_E,LCD_E)

unsigned char Lcd_GetBusy()
{
  unsigned char res;
    /**/
    CLR_RS();
    SET_RW();
    SET_E();
    /*ÊäÈë×´Ì¬*/
    LCD_DDR=0x00;
    __no_operation();
    __no_operation();
    __no_operation();
    /*»ñÈ¡¶Ë¿Ú×´Ì¬*/
    res=LCD_GETSTATUS_BUSY(LCD_DB_PIN);
    /*»Ö¸´ÎªÊä³ö×´Ì¬*/
    LCD_DDR=0XFF;
    CLR_E();
    return res; 
}


