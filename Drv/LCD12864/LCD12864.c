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
   
#define  LCD_LEFT()       Sn_Output_CS(1)
#define  LCD_RIGHT()      Sn_Output_CS(0)

/*
 *��ȡæ״̬����
 *RS:L R\W:H
 *
*/
unsigned char Lcd_GetBusy()
{
  unsigned char Res;
    /**/
    CLR_RS();
    SET_RW();
    Nop();
    Nop();
    Nop();
    SET_E();
    /*����״̬*/
    LCD_DDR=0x00;
    Nop();
    Nop();
    Nop();
    /*��ȡ�˿�״̬*/
    Res=LCD_GETSTATUS_BUSY(LCD_DB_PIN);
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
  
   /*æ���*/
  if(Lcd_GetBusy())
  {/*æ���ӳ�3Fclk*/
    Delay_us(70);
    /*���æ*/
    if(Lcd_GetBusy()){
      /*һֱæ*/
      return Sys_Lcd_Busy;
    }
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
  
   /*æ���*/
  if(Lcd_GetBusy())
  {/*æ���ӳ�3Fclk*/
    Delay_us(70);
    /*���æ*/
    if(Lcd_GetBusy()){
      /*һֱæ*/
      return Sys_Lcd_Busy;
    }
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
        if(error==Sys_Lcd_Busy);
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
  return error;
}



