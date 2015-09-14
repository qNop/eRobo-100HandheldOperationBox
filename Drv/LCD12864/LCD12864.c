/*
 *ENcycle Tmin 1000ns 
 *ENHigh  Tmin  450ns 
 *ENLow   Tmin  450ns
 *        Tasu  140ns
 *        Tdsu  200ns
 *        Tbusy 1<Fclk<3
 *Fclk  Tmin 2.5us Tmax 20us
 */
#include <iopwm316.h>
#include "LCD12864.h"
#include "SN74HC573.h"
#include "IO_PORT.h"
#include "delay.h"

#define  SET_RS()         SETPIN(PORT_LCD_RS,LCD_RS)
#define  CLR_RS()         CLRPIN(PORT_LCD_RS,LCD_RS)

#define  SET_RW()         SETPIN(PORT_LCD_RW,LCD_RW)
#define  CLR_RW()         CLRPIN(PORT_LCD_RW,LCD_RW)

#define  SET_E()          SETPIN(PORT_LCD_E,LCD_E)
#define  CLR_E()          CLRPIN(PORT_LCD_E,LCD_E)
   
#define  LCD_LEFT()       SET_LCD_CS2(),CLEAR_LCD_CS1()
#define  LCD_RIGHT()      SET_LCD_CS1(),CLEAR_LCD_CS2()


//*******************************************************************
// ����ASCII�ֿ�8��*8�� ������ȡģ��
//*******************************************************************

__flash unsigned char ASC_8[]={
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 	//" "=20H
    0x00,0x06,0x5F,0x5F,0x06,0x00,0x00,0x00, 	//"!"=21H
    0x00,0x00,0x07,0x00,0x07,0x00,0x00,0x00, 	//"""=22H 
    0x00,0x14,0x7f,0x14,0x7f,0x14,0x00,0x00, 	//"#"=23H 
    0x00,0x24,0x2a,0x7f,0x2a,0x12,0x00,0x00,	//"$"=24H 
    0x00,0x23,0x13,0x08,0x64,0x62,0x00,0x00, 	//"%"=25H 
    0x00,0x36,0x49,0x55,0x22,0x50,0x00,0x00, 	//"&"=26H 
    0x00,0x00,0x05,0x03,0x00,0x00,0x00,0x00, 	//"'"=27H
    0x00,0x1C,0x3E,0x63,0x41,0x00,0x00,0x00, 	//"("=28H
    0x00,0x41,0x63,0x3E,0x1C,0x00,0x00,0x00, 	//")"=29H
    0x00,0x14,0x08,0x3e,0x08,0x14,0x00,0x00, 	//"*"=2AH 
    0x00,0x08,0x08,0x3e,0x08,0x08,0x00,0x00, 	//"+"=2BH 
    0x80,0xE0,0x60,0x00,0x00,0x00,0x00,0x00, 	//","=2CH
    0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x00,	//"-"=2DH
    0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00,	//"."=2EH
    0x00,0x20,0x10,0x08,0x04,0x02,0x00,0x00, 	//"/"=2FH
    0x3E,0x7F,0x71,0x59,0x4D,0x7F,0x3E,0x00,    //"0"=30H
    0x00,0x42,0x7F,0x7F,0x40,0x00,0x00,0x00,	//"1"=31H
    0x62,0x73,0x59,0x49,0x4F,0x46,0x00,0x00,	//"2"=32H
    0x22,0x63,0x49,0x49,0x7F,0x36,0x00,0x00,	//"3"=33H 
    0x1C,0x1E,0x13,0x51,0x7F,0x7F,0x50,0x00,	//"4"=34H 
    0x27,0x67,0x45,0x45,0x7D,0x39,0x00,0x00,	//"5"=35H
    0x3C,0x7E,0x4B,0x49,0x79,0x30,0x00,0x00,	//"6"=36H
    0x03,0x03,0x71,0x79,0x0F,0x07,0x00,0x00,	//"7"=37H 
    0x36,0x7F,0x49,0x49,0x7F,0x36,0x00,0x00,	//"8"=38H
    0x26,0x6F,0x49,0x49,0x7F,0x3E,0x00,0x00,	//"9"=39H
    0x00,0x00,0x66,0x66,0x00,0x00,0x00,0x00,	//":"=3AH
    0x00,0x00,0x56,0x36,0x00,0x00,0x00,0x00, 	//";"=3BH         
    0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00, 	//"<"=3CH         
    0x00,0x14,0x14,0x14,0x14,0x14,0x00,0x00, 	//"="=3DH        
    0x00,0x00,0x41,0x22,0x14,0x08,0x00,0x00, 	//">"=3EH        
    0x00,0x02,0x01,0x51,0x09,0x06,0x00,0x00, 	//"?"=3FH        
    0x00,0x32,0x49,0x79,0x41,0x3e,0x00,0x00, 	//"@"=40H      
    0x7C,0x7E,0x13,0x13,0x7E,0x7C,0x00,0x00,	//"A"=41H 
    0x41,0x7F,0x7F,0x49,0x49,0x7F,0x36,0x00,	//"B"=42H
    0x1C,0x3E,0x63,0x41,0x41,0x63,0x22,0x00,	//"C"=43H 
    0x41,0x7F,0x7F,0x41,0x63,0x3E,0x1C,0x00,	//"D"=44H
    0x41,0x7F,0x7F,0x49,0x49,0x63,0x63,0x00,	//"E"=45H 
    0x41,0x7F,0x7F,0x49,0x1D,0x01,0x03,0x00,	//"F"=46H
    0x1C,0x3E,0x63,0x41,0x51,0x73,0x72,0x00,	//"G"=47H
    0x7F,0x7F,0x08,0x08,0x7F,0x7F,0x00,0x00,	//"H"=48H
    0x00,0x41,0x7F,0x7F,0x41,0x00,0x00,0x00,	//"I"=49H
    0x61,0x41,0x41,0x7F,0x7F,0x01,0x00,0x00,	//"J"=4AH
    0x7F,0x7F,0x1C,0x36,0x63,0x41,0x00,0x00,	//"K"=4BH
    0x41,0x7F,0x7F,0x41,0x40,0x60,0x70,0x00,	//"L"=4CH
    0x7F,0x7F,0x06,0x1C,0x06,0x7F,0x7F,0x00,	//"M"=4DH
    0x7F,0x7F,0x06,0x0C,0x18,0x7F,0x7F,0x00,	//"N"=4EH
    0x1C,0x3E,0x63,0x41,0x63,0x3E,0x1C,0x00,	//"O"=4FH
    0x41,0x7F,0x7F,0x09,0x09,0x0F,0x06,0x00,	//"P"=50H
    0x1C,0x7E,0x63,0x51,0x63,0x3E,0x5C,0x00,	//"Q"=51H
    0x41,0x7F,0x7F,0x09,0x19,0x7F,0x66,0x00,	//"R"=52H 
    0x26,0x6F,0x4D,0x59,0x73,0x32,0x00,0x00,	//"S"=53H
    0x03,0x41,0x7F,0x7F,0x41,0x03,0x00,0x00,	//"T"=54H 
    0x7F,0x7F,0x40,0x40,0x7F,0x7F,0x00,0x00,	//"U"=55H
    0x07,0x1F,0x78,0x40,0x78,0x1F,0x07,0x00,	//"V"=56H
    0x7F,0x7F,0x30,0x1C,0x30,0x7F,0x7F,0x00,	//"W"=57H
    0x41,0x63,0x3E,0x08,0x3E,0x63,0x41,0x00,	//"X"=58H
    0x07,0x4F,0x78,0x78,0x4F,0x07,0x00,0x00,	//"Y"=59H 
    0x43,0x61,0x71,0x59,0x4D,0x47,0x63,0x00,	//"Z"=5AH 
    0x00,0x00,0x7f,0x41,0x41,0x00,0x00,0x00, 	//"["=5BH 
    0x00,0x02,0x04,0x08,0x10,0x20,0x00,0x00, 	//"\"=5CH 
    0x00,0x00,0x41,0x41,0x7f,0x00,0x00,0x00, 	//"]"=5DH 
    0x00,0x04,0x02,0x01,0x02,0x04,0x00,0x00, 	//"^"=5EH 
    0x00,0x40,0x40,0x40,0x40,0x40,0x00,0x00, 	//"_"=5FH 
    0x00,0x01,0x02,0x04,0x00,0x00,0x00,0x00, 	//"`"=60H       
    0x20,0x54,0x54,0x54,0x38,0x78,0x40,0x00,	//"a"=61H
    0x7F,0x7F,0x48,0x44,0x44,0x7C,0x38,0x00,	//"b"=62H
    0x38,0x7C,0x44,0x44,0x6C,0x28,0x00,0x00,	//"c"=63H
    0x30,0x78,0x48,0x49,0x3F,0x7F,0x40,0x00,	//"d"=64H
    0x38,0x7C,0x54,0x54,0x5C,0x18,0x00,0x00,	//"e"=65H
    0x48,0x7E,0x7F,0x49,0x03,0x02,0x00,0x00,	//"f"=66H
    0x98,0xBC,0xA4,0xA4,0xF8,0x7C,0x04,0x00,	//"g"=67H
    0x41,0x7F,0x7F,0x08,0x04,0x7C,0x78,0x00,	//"h"=68H
    0x00,0x44,0x7D,0x7D,0x40,0x00,0x00,0x00,	//"i"=69H
    0x20,0x60,0x40,0x44,0x7D,0x3D,0x00,0x00,	//"j"=6AH 
    0x41,0x7F,0x7F,0x10,0x38,0x6C,0x44,0x00,	//"k"=6BH
    0x00,0x41,0x7F,0x7F,0x40,0x00,0x00,0x00,	//"l"=6CH
    0x7C,0x7C,0x18,0x38,0x18,0x7C,0x7C,0x00,	//"m"=6DH
    0x7C,0x7C,0x04,0x04,0x7C,0x78,0x00,0x00,	//"n"=6EH
    0x38,0x7C,0x44,0x44,0x7C,0x38,0x00,0x00,	//"o"=6FH
    0x84,0xFC,0xF8,0xA4,0x24,0x3C,0x18,0x00,	//"p"=70H
    0x0C,0x1E,0x1E,0x92,0xFE,0xFE,0x92,0x00,	//"q"=71H
    0x44,0x7C,0x78,0x4C,0x04,0x1C,0x18,0x00,	//"r"=72H
    0x48,0x5C,0x54,0x54,0x74,0x24,0x00,0x00,	//"s"=73H
    0x00,0x04,0x3E,0x7F,0x44,0x24,0x00,0x00,	//"t"=74H
    0x3C,0x7C,0x40,0x40,0x3C,0x7C,0x40,0x00,	//"u"=75H
    0x1C,0x3C,0x60,0x60,0x3C,0x1C,0x00,0x00,	//"v"=76H
    0x3C,0x7C,0x70,0x38,0x70,0x7C,0x3C,0x00,	//"w"=77H
    0x44,0x6C,0x38,0x10,0x38,0x6C,0x44,0x00,	//"x"=78H
    0x9C,0xBC,0xA0,0xA0,0xFC,0x7C,0x00,0x00,	//"y"=79H
    0x44,0x64,0x74,0x5C,0x4C,0x44,0x00,0x00,	//"z"=7AH
    0x00,0x00,0x08,0x36,0x41,0x00,0x00,0x00, 	//"{"=7BH 
    0x00,0x00,0x00,0x77,0x00,0x00,0x00,0x00, 	//"|"=7CH 
    0x00,0x00,0x41,0x36,0x08,0x00,0x00,0x00, 	//"}"=7DH 
    0x00,0x02,0x01,0x02,0x04,0x02,0x00,0x00, 	//"~"=7EH 
    0x00,0xff,0xff,0xff,0xff,0xff,0x00,0x00 	//" "=7FH 
};

/*
 *��ȡæ״̬����
 *RS:L R\W:H
 *
*/
unsigned char Lcd_GetBusy()
{
  unsigned char Res=0;
    /*����״̬*/
    LCD_DDR=0x00;
    /**/
    CLR_RS();
    SET_RW();
    Nop();
    Nop();
    Nop();
    SET_E();
    Nop();
    Nop();
    Nop();
    /*��ȡ�˿�״̬*/
    while(0x80 & LCD_DB_PIN){
      Res++;
      if(Res>100){
        break;
      }
    }
    if(Res>100){
      Res=1;
    }
    else
      Res=0;
    /*�ָ�Ϊ���״̬*/
    CLR_E();
    LCD_DDR=0XFF;
    return Res; 
}
/*
 *д����
 *RS:L R\W:L E:H
 *
 */
Sys_Error Write_Cmd(unsigned char Cmd){
  
    /*���æ*/
    if(Lcd_GetBusy()){
      /*һֱæ*/
      return Sys_Lcd_Busy;
    }
  CLR_RS();
  CLR_RW();
  CLR_E();
  Nop();
  Nop();
  OUTPUT_LCD_DB(Cmd);
  Nop();
  Nop();
  SET_E();
  Delay_us(1);
  CLR_E();
  return Sys_No_Error;
}
/*
 *д����
 *RS:H R\W:L E:H
 *
 */
Sys_Error Write_Data(unsigned char Data){
  
    /*���æ*/
    if(Lcd_GetBusy()){
      /*һֱæ*/
      return Sys_Lcd_Busy;
    }
  SET_RS();
  CLR_RW();
  CLR_E();
  Nop();
  Nop();
  OUTPUT_LCD_DB(Data);
  Nop();
  Nop();
  SET_E();
  Delay_us(1);
  CLR_E();
  return Sys_No_Error;
}

/*
 *�趨��ʾ����
 *
 */
Sys_Error Set_Cursor(unsigned char x,unsigned char y){
  Sys_Error error;
  error = Sys_No_Error;
  /*�����*/
  if(y<LCD_LEFT_MAX)
    /*�����Ƭѡ*/
    LCD_LEFT();
  else
    /*Ƭѡ�Ұ���*/
    LCD_RIGHT();
  error=Write_Cmd(LCD_SETPAGE(x));
  if(error==Sys_Lcd_Busy)
    return error;
  error=Write_Cmd(LCD_SETADDRESS(y));
  return error;
  
}
/*
 *��������
 *
 */
Sys_Error Clr_LCD(void){
  Sys_Error error;
  unsigned char x,y;
  for(x=0;x<8;x++){
    for(y=0;y<128;y++){
      error=Set_Cursor(x,y);
        if(error==Sys_Lcd_Busy)
          return error;
      error=Write_Data(0x00);
        if(error==Sys_Lcd_Busy)
          return error;
    }
  }
  return error;
  
}
/*
 *��ʼ��Һ��
 *
 */
Sys_Error LCD_Init(void){
  Sys_Error error;
  LCD_LEFT();
  error=Write_Cmd(LCD_DISPLAYSTARTLINE(0));
  error=Write_Cmd(LCD_DISPLAY_ON);
  LCD_RIGHT();
  error=Write_Cmd(LCD_DISPLAYSTARTLINE(0));
  error=Write_Cmd(LCD_DISPLAY_ON);
  error=Clr_LCD();
  
  return error;
}
/*
 *Һ����ʾ�����ַ�
 *
 */
Sys_Error Display_Char(unsigned char x,unsigned char y,unsigned char Char){
  Sys_Error error;
  unsigned char width;
  for(width=0;width<8;width++){
    Set_Cursor(y,x+width);
    Write_Data(ASC_8[(Char-32)*8+width]);
  }
  return error;
}

/*
 *Һ����ʾ�ַ���
 *
 */
Sys_Error Display_String(unsigned char x,unsigned char y,unsigned char *pString){
  Sys_Error error;
  /*�ַ�����β\0*/
  while(*pString!='\0'){
    Display_Char(x,y,*pString);
    pString++;
    x+=8;
  }
  return error;
}

