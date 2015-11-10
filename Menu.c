
#include <iopwm316.h>
//modbus
#include "mb_m.h"
#include "LCD12864.h"
#include "mbport.h"
#include "Sn74hc573.h"

#include "Menu.h"
#include "io_port.h"

static Page_Union Page_Old;//保存上一次读取的Page
extern unsigned char Time_Enable;
extern unsigned char Time_Count; 

static Page_Union Page_Debug;

//存放Page目录
/*
*获取按键编码值
*
*/
Key_Union Get_Key(void){
  Key_Union Key_Code;
  //按键扫描
  Key_Code.Key_Index=0;
  Sn_Output_KeyCode(0x0e);
  switch(PINC&0xf0){
    case 0x00:Key_Code.Key_Struct.Set=1;
    Key_Code.Key_Struct.Forward=1;
    Key_Code.Key_Struct.Right=1;
    Key_Code.Key_Struct.Feed=1;break;
    case 0x10:Key_Code.Key_Struct.Forward=1;
    Key_Code.Key_Struct.Right=1;
    Key_Code.Key_Struct.Feed=1;break;
    case 0x20:Key_Code.Key_Struct.Set=1;
    Key_Code.Key_Struct.Right=1;
    Key_Code.Key_Struct.Feed=1;break;
    case 0x30:Key_Code.Key_Struct.Right=1;
    Key_Code.Key_Struct.Feed=1;break;
    case 0x40:Key_Code.Key_Struct.Set=1;
    Key_Code.Key_Struct.Forward=1;
    Key_Code.Key_Struct.Feed=1;break;
    case 0x50:Key_Code.Key_Struct.Forward=1;
    Key_Code.Key_Struct.Feed=1;break;
    case 0x60:Key_Code.Key_Struct.Set=1;
    Key_Code.Key_Struct.Feed=1;break;
    case 0x70:Key_Code.Key_Struct.Feed=1;break;
    case 0x80:Key_Code.Key_Struct.Set=1;
    Key_Code.Key_Struct.Forward=1;
    Key_Code.Key_Struct.Right=1;break;
    case 0x90:Key_Code.Key_Struct.Forward=1;
    Key_Code.Key_Struct.Right=1;break;
    case 0xa0:Key_Code.Key_Struct.Set=1;
    Key_Code.Key_Struct.Right=1;break;
    case 0xb0:Key_Code.Key_Struct.Right=1;break;
    case 0xc0:Key_Code.Key_Struct.Set=1;
    Key_Code.Key_Struct.Forward=1;break;
    case 0xd0:Key_Code.Key_Struct.Forward=1;break; 
    case 0xe0:Key_Code.Key_Struct.Set=1;break;//set键按下 
  }
  Sn_Output_KeyCode(0x0d);
  switch(PINC&0xf0){
    case 0x00:Key_Code.Key_Struct.Add=1;
    Key_Code.Key_Struct.Up=1;
    Key_Code.Key_Struct.Travel_Right=1;
    Key_Code.Key_Struct.Current_Add=1;break;
    case 0x10:Key_Code.Key_Struct.Up=1;
    Key_Code.Key_Struct.Travel_Right=1;
    Key_Code.Key_Struct.Current_Add=1;break;
    case 0x20:Key_Code.Key_Struct.Add=1;
    Key_Code.Key_Struct.Travel_Right=1;
    Key_Code.Key_Struct.Current_Add=1;break;
    case 0x30:Key_Code.Key_Struct.Travel_Right=1;
    Key_Code.Key_Struct.Current_Add=1;break;
    case 0x40:Key_Code.Key_Struct.Add=1;
    Key_Code.Key_Struct.Up=1;
    Key_Code.Key_Struct.Current_Add=1;break;
    case 0x50:Key_Code.Key_Struct.Up=1;
    Key_Code.Key_Struct.Current_Add=1;break;
    case 0x60:Key_Code.Key_Struct.Add=1;
    Key_Code.Key_Struct.Current_Add=1;break;
    case 0x70:Key_Code.Key_Struct.Current_Add=1;break;
    case 0x80:Key_Code.Key_Struct.Add=1;
    Key_Code.Key_Struct.Up=1;
    Key_Code.Key_Struct.Travel_Right=1;break;
    case 0x90:Key_Code.Key_Struct.Up=1;
    Key_Code.Key_Struct.Travel_Right=1;break;
    case 0xa0:Key_Code.Key_Struct.Add=1;
    Key_Code.Key_Struct.Travel_Right=1;break;
    case 0xb0:Key_Code.Key_Struct.Travel_Right=1;break;
    case 0xc0:Key_Code.Key_Struct.Add=1;
    Key_Code.Key_Struct.Up=1;break;
    case 0xd0:Key_Code.Key_Struct.Up=1;break; 
    case 0xe0:Key_Code.Key_Struct.Add=1;break;//set键按下
  }
  Sn_Output_KeyCode(0x0b);
  switch(PINC&0xf0){
    case 0x00:Key_Code.Key_Struct.Dec=1;
    Key_Code.Key_Struct.Travel_Left=1;
    Key_Code.Key_Struct.Back=1;
    Key_Code.Key_Struct.Currene_Dec=1;break;
    case 0x10:Key_Code.Key_Struct.Travel_Left=1;
    Key_Code.Key_Struct.Back=1;
    Key_Code.Key_Struct.Currene_Dec=1;break;
    case 0x20:Key_Code.Key_Struct.Dec=1;
    Key_Code.Key_Struct.Back=1;
    Key_Code.Key_Struct.Currene_Dec=1;break;
    case 0x30:Key_Code.Key_Struct.Back=1;
    Key_Code.Key_Struct.Currene_Dec=1;break;
    case 0x40:Key_Code.Key_Struct.Dec=1;
    Key_Code.Key_Struct.Travel_Left=1;
    Key_Code.Key_Struct.Currene_Dec=1;break;
    case 0x50:Key_Code.Key_Struct.Travel_Left=1;
    Key_Code.Key_Struct.Currene_Dec=1;break;
    case 0x60:Key_Code.Key_Struct.Dec=1;
    Key_Code.Key_Struct.Currene_Dec=1;break;
    case 0x70:Key_Code.Key_Struct.Currene_Dec=1;break;
    case 0x80:Key_Code.Key_Struct.Dec=1;
    Key_Code.Key_Struct.Travel_Left=1;
    Key_Code.Key_Struct.Back=1;break;
    case 0x90:Key_Code.Key_Struct.Travel_Left=1;
    Key_Code.Key_Struct.Back=1;break;
    case 0xa0:Key_Code.Key_Struct.Dec=1;
    Key_Code.Key_Struct.Back=1;break;
    case 0xb0:Key_Code.Key_Struct.Back=1;break;
    case 0xc0:Key_Code.Key_Struct.Dec=1;
    Key_Code.Key_Struct.Travel_Left=1;break;
    case 0xd0:Key_Code.Key_Struct.Travel_Left=1;break; 
    case 0xe0:Key_Code.Key_Struct.Dec=1;break;//set键按下
  }
  Sn_Output_KeyCode(0x07);
  switch(PINC&0xf0){
    case 0x80:Key_Code.Key_Struct.Cancel=1;
    Key_Code.Key_Struct.Left=1;
    Key_Code.Key_Struct.Down=1;break;
    case 0x90:Key_Code.Key_Struct.Left=1;
    Key_Code.Key_Struct.Down=1;break;
    case 0xa0:Key_Code.Key_Struct.Cancel=1;
    Key_Code.Key_Struct.Down=1;break;
    case 0xb0:Key_Code.Key_Struct.Down=1;break;
    case 0xc0:Key_Code.Key_Struct.Cancel=1;
    Key_Code.Key_Struct.Left=1;break;
    case 0xd0:Key_Code.Key_Struct.Left=1;break; 
    case 0xe0:Key_Code.Key_Struct.Cancel=1;break;//set键按下   
  }
  Sn_Output_KeyCode(0xff);
  if(GET_START_PIN())Key_Code.Key_Struct.Start=1;
  if(GET_RESET_PIN())Key_Code.Key_Struct.Reset=1;
  if(GET_STOP_PIN())Key_Code.Key_Struct.Stop=1;
  return Key_Code;
}
#ifdef USE_ASCII
/*
*测试操作盒
*
*/
static void Test_Fuction(unsigned long Key){
  Display_String(0,0,"SET:0<:0>:0CAN:0");
  Display_String(0,1,"      ^:0    ]:0");
  Display_String(0,2," [:0<:0 >:0]:_  ");
  Display_String(0,3,"      ^:0    ]:0");
  Display_String(0,4,"FEED:0I+:0I-:0  ");
  Display_String(0,5,"STAR:0SS:0STOP:0");
  Display_String(0,6,"SEND:           ");
  Display_String(0,7,"RECV:           "); 
  
  //按键触发
  if(Key&KEY_SET) 
    Display_Char(32,0,'1');
  else 
    Display_Char(32,0,'0');
  if(Key&KEY_ADD)         
    Display_Char(56,0,'1');
  else
    Display_Char(56,0,'0');
  if(Key&KEY_DEC)       
    Display_Char(80,0,'1');
  else
    Display_Char(80,0,'0');
  if(Key&KEY_CANCEL)     
    Display_Char(120,0,'1');
  else
    Display_Char(120,0,'0');
  if(Key&KEY_FEED)       
    Display_Char(40,4,'1');
  else
    Display_Char(40,4,'0');
  if(Key&KEY_CURRENT_ADD) 
    Display_Char(72,4,'1');
  else
    Display_Char(72,4,'0');
  if(Key&KEY_CURRENT_DEC)
    Display_Char(104,4,'1');
  else
    Display_Char(104,4,'0');
  if(Key&KEY_START)      
    Display_Char(40,5,'1');
  else
    Display_Char(40,5,'0');
  if(Key&KEY_RESET)     
    Display_Char(72,5,'1');
  else
    Display_Char(72,5,'0');
  if(Key&KEY_STOP)      
    Display_Char(120,5,'1');
  else
    Display_Char(120,5,'0');
  if(Key&KEY_UP)        
    Display_Char(120,1,'1');
  else
    Display_Char(120,1,'0');
  if(Key&KEY_DOWN)     
    Display_Char(120,3,'1');
  else
    Display_Char(120,3,'0');
  if(Key&KEY_FORWARD)   
    Display_Char(64,1,'1');
  else
    Display_Char(64,1,'0');
  if(Key&KEY_BACK)      
    Display_Char(64,3,'1');
  else
    Display_Char(64,3,'0');
  if(Key&KEY_LEFT)      
    Display_Char(48,2,'1');
  else
    Display_Char(48,2,'0');
  if(Key&KEY_RIGHT)     
    Display_Char(80,2,'1');
  else
    Display_Char(80,2,'0');
  if(Key&KEY_TRAVELLEFT)
    Display_Char(24,2,'1');
  else
    Display_Char(24,2,'0');
  if(Key&KEY_TRAVELRIGHT)
    Display_Char(104,2,'1');
  else
    Display_Char(104,2,'0');
}
#endif
__flash unsigned char Ch_lib[][24]={
  //板厚
  {0x88,0x00,0x68,0x00,0xFF,0x0F,0x28,0x08,0x40,0x04,0xFE,0x03,
  0x12,0x08,0xF2,0x05,0x12,0x02,0x91,0x05,0x71,0x08,0x00,0x00},/*"板",0*/
  {0x00,0x08,0xFF,0x07,0x01,0x02,0x5F,0x02,0x55,0x02,0x55,0x0A,
  0x55,0x0F,0xD5,0x02,0xD5,0x02,0x5F,0x02,0x01,0x02,0x00,0x00},/*"厚",1*/
  //修补
  {0x10,0x00,0xFC,0x0F,0x03,0x00,0xF8,0x03,0x10,0x08,0x94,0x0A,
  0x8B,0x0A,0x4A,0x09,0x2A,0x05,0x96,0x04,0x10,0x02,0x00,0x00},/*"修",2*/
  {0x84,0x00,0x45,0x00,0xF6,0x0F,0x4C,0x00,0xA0,0x00,0x00,0x00,
  0x00,0x00,0xFF,0x0F,0x10,0x00,0x20,0x00,0xC0,0x00,0x00,0x00},/*"补",3*/
  //头部摆动
  {0x40,0x08,0x48,0x08,0x50,0x04,0x42,0x04,0x44,0x02,0xC0,0x01,
  0x7F,0x00,0x40,0x01,0x40,0x02,0x40,0x04,0x40,0x08,0x00,0x00},/*"头",4*/
  {0x20,0x00,0xAA,0x0F,0xB2,0x04,0xA3,0x04,0xB2,0x04,0xAA,0x0F,
  0x20,0x00,0xFE,0x0F,0x02,0x02,0x32,0x02,0xCE,0x01,0x00,0x00},/*"部",5*/
  {0x84,0x00,0x84,0x08,0xFF,0x0F,0x44,0x00,0x8F,0x04,0xA9,0x06,
  0xAF,0x05,0xF9,0x04,0xAF,0x04,0xA9,0x06,0x8F,0x0C,0x00,0x00},/*"摆",6*/
  {0x10,0x03,0xD2,0x02,0x32,0x02,0x92,0x02,0x10,0x03,0x00,0x08,
  0x08,0x06,0xFF,0x01,0x08,0x08,0x08,0x08,0xF8,0x07,0x00,0x00},/*"动",7*/
  //道
  {0x10,0x08,0x11,0x04,0xF2,0x03,0x00,0x04,0xFA,0x0B,0xAB,0x0A,
  0xAE,0x0A,0xAA,0x0A,0xAA,0x0A,0xAB,0x0A,0xFA,0x0B,0x00,0x00},/*"道",8*/
  //第一点位
  {0x04,0x08,0xD3,0x09,0x52,0x05,0x56,0x03,0x52,0x01,0xF4,0x0F,
  0x53,0x01,0x52,0x01,0x56,0x09,0x72,0x09,0x02,0x07,0x00,0x00},/*"第",9*/
  {0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,
  0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x00,0x00},/*"一",10*/
  {0x00,0x08,0xF0,0x05,0x10,0x01,0x10,0x05,0x10,0x09,0x1F,0x01,
  0x12,0x05,0x12,0x09,0x12,0x01,0xF2,0x05,0x02,0x08,0x00,0x00},/*"点",11*/
  {0x10,0x00,0xFC,0x0F,0x03,0x00,0x08,0x08,0x68,0x08,0x88,0x0B,
  0x09,0x08,0x0A,0x0C,0x08,0x0B,0xE8,0x08,0x08,0x08,0x00,0x00},/*"位",12*/
  //电压流
  {0xFC,0x03,0x24,0x01,0x24,0x01,0x24,0x01,0xFF,0x07,0x24,0x09,
  0x24,0x09,0x24,0x09,0xFC,0x09,0x00,0x08,0x00,0x0E,0x00,0x00},/*"电",13*/
  {0x00,0x08,0xFE,0x07,0x02,0x08,0x42,0x08,0x42,0x08,0x42,0x08,
  0xFA,0x0F,0x42,0x08,0x42,0x09,0x42,0x0A,0x02,0x08,0x00,0x00},/*"压",14*/
  {0x22,0x04,0x44,0x02,0x00,0x08,0x24,0x04,0xB4,0x03,0x2C,0x00,
  0xA5,0x0F,0x26,0x00,0xA4,0x07,0x34,0x08,0x64,0x0E,0x00,0x00},/*"流",15*/
  //长度
  {0x20,0x00,0x20,0x00,0x20,0x00,0xFF,0x0F,0x28,0x04,0x28,0x02,
  0xE4,0x00,0x24,0x01,0x22,0x02,0x22,0x04,0x20,0x04,0x00,0x00},/*"长",16*/
  {0x00,0x08,0xFE,0x07,0x0A,0x00,0x8A,0x08,0xBE,0x09,0xAA,0x0A,
  0xAB,0x04,0xAA,0x04,0xBE,0x0A,0x8A,0x09,0x0A,0x08,0x00,0x00},/*"度",17*/
  //始终端
  {0x88,0x08,0x78,0x05,0x0F,0x02,0xF8,0x0D,0x00,0x00,0xD8,0x0F,
  0x54,0x04,0x53,0x04,0x50,0x04,0xD8,0x0F,0x30,0x00,0x00,0x00},/*"始",18*/
  {0x98,0x04,0xD4,0x04,0xB3,0x02,0x08,0x02,0x48,0x00,0x44,0x02,
  0xAB,0x02,0x92,0x04,0x2A,0x05,0x46,0x08,0x40,0x00,0x00,0x00},/*"终",19*/
  {0xE9,0x04,0x0A,0x05,0xE8,0x02,0x00,0x00,0xAE,0x0F,0xA8,0x00,
  0xA8,0x07,0xEF,0x00,0xA8,0x07,0xA8,0x08,0xAE,0x0F,0x00,0x00},/*"端",20*/
  //返回
  {0x10,0x08,0x11,0x04,0xF2,0x03,0x00,0x06,0xFE,0x09,0x0A,0x08,
  0x2A,0x0A,0x4A,0x09,0x89,0x08,0x49,0x09,0x39,0x0A,0x00,0x00},/*"返",21*/
  {0x00,0x00,0xFE,0x0F,0x02,0x04,0x02,0x04,0xF2,0x04,0x92,0x04,
  0x92,0x04,0xF2,0x04,0x02,0x04,0x02,0x04,0xFE,0x0F,0x00,0x00},/*"回",22*/
  //改
  {0xE2,0x0F,0x22,0x04,0x22,0x02,0x3E,0x01,0x20,0x08,0x10,0x04,
  0xEF,0x02,0x08,0x01,0x88,0x02,0x78,0x04,0x08,0x08,0x00,0x00},/*"改",23*/
  //根
  {0x88,0x00,0x68,0x00,0xFF,0x0F,0x48,0x00,0x00,0x00,0xFF,0x0F,
  0x49,0x04,0xC9,0x01,0x49,0x02,0x7F,0x05,0x80,0x08,0x00,0x00},/*"根",24*/
  //间隙
  {0x00,0x00,0xF9,0x0F,0x02,0x00,0xF8,0x03,0x49,0x02,0x49,0x02,
  0x49,0x02,0x49,0x02,0xF9,0x0B,0x01,0x08,0xFF,0x0F,0x00,0x00},/*"间",25*/
  {0xFE,0x0F,0x02,0x02,0x32,0x02,0xCE,0x01,0x04,0x04,0xFA,0x02,
  0xA8,0x08,0xAF,0x0F,0xA8,0x00,0xFA,0x02,0x04,0x04,0x00,0x00},/*"隙",26*/
  //加减
  {0x08,0x08,0x08,0x06,0xFF,0x01,0x08,0x08,0x08,0x08,0xF8,0x07,
  0x00,0x00,0xFC,0x0F,0x04,0x04,0x04,0x04,0xFC,0x0F,0x00,0x00},/*"加",27*/
  {0x04,0x02,0x08,0x09,0xFC,0x07,0x04,0x00,0xD4,0x03,0x54,0x02,
  0xD4,0x0B,0x04,0x04,0xFF,0x03,0x84,0x05,0x65,0x0E,0x00,0x00},/*"减",28*/
  //启
  {0x00,0x08,0x00,0x06,0xFC,0x01,0xA4,0x0F,0xA4,0x04,0xA5,0x04,
  0xA6,0x04,0xA4,0x04,0xA4,0x04,0xA4,0x04,0xBC,0x0F,0x00,0x00},/*"启",29*/
  //键
  {0x94,0x00,0xF3,0x0F,0x92,0x04,0x64,0x0A,0xDC,0x07,0x88,0x0A,
  0xAA,0x0A,0xFF,0x0F,0xAA,0x0A,0xBE,0x0A,0x08,0x0A,0x00,0x00},/*"键",30*/
  //示教
  {0x10,0x04,0x10,0x02,0x92,0x01,0x12,0x00,0x12,0x08,0xF2,0x0F,
  0x12,0x00,0x12,0x00,0x92,0x00,0x10,0x01,0x10,0x06,0x00,0x00},/*"示",31*/
  {0xA8,0x02,0x6A,0x02,0x3F,0x0A,0xAA,0x0F,0x6C,0x01,0x0A,0x01,
  0x10,0x08,0xEF,0x05,0x08,0x02,0xF8,0x05,0x08,0x08,0x00,0x00},/*"教",32*/
  //模式
  {0x88,0x00,0x68,0x00,0xFF,0x0F,0x48,0x00,0x02,0x0A,0xFA,0x0A,
  0xAF,0x06,0xAA,0x03,0xAF,0x06,0xFA,0x0A,0x02,0x0A,0x00,0x00},/*"模",33*/
  {0x08,0x08,0x48,0x08,0x48,0x08,0xC8,0x07,0x48,0x04,0x48,0x04,
  0x08,0x04,0xFF,0x00,0x08,0x03,0x09,0x04,0x0A,0x0E,0x00,0x00},/*"式",34*/
  //取消
  {0x02,0x02,0xFE,0x03,0x52,0x02,0x52,0x02,0xFE,0x0F,0x02,0x01,
  0x04,0x08,0xFC,0x04,0x04,0x03,0xFC,0x04,0x00,0x08,0x00,0x00},/*"取",35*/
  {0x10,0x04,0x22,0x02,0x04,0x01,0x00,0x00,0xF2,0x0F,0x54,0x01,
  0x50,0x01,0x5F,0x01,0x50,0x01,0x54,0x09,0xF2,0x0F,0x00,0x00},/*"消",36*/
  //确认
  {0x42,0x00,0xF2,0x07,0x2E,0x02,0xE2,0x07,0x00,0x08,0xF4,0x07,
  0x53,0x01,0xF2,0x07,0x5A,0x01,0x56,0x09,0xF0,0x0F,0x00,0x00},/*"确",37*/
  {0x10,0x00,0x11,0x00,0xF2,0x07,0x00,0x02,0x00,0x09,0x00,0x06,
  0xC0,0x01,0x3F,0x00,0xC0,0x01,0x00,0x06,0x00,0x08,0x00,0x00},/*"认",38*/
  //停止
  {0x20,0x00,0x10,0x00,0xFC,0x0F,0x03,0x00,0x82,0x01,0xBA,0x02,
  0xAA,0x0A,0xAB,0x0E,0xAA,0x02,0xBA,0x02,0x82,0x01,0x00,0x00},/*"停",39*/
  {0x00,0x08,0x00,0x08,0xF8,0x0F,0x00,0x08,0x00,0x08,0x00,0x08,
  0xFF,0x0F,0x10,0x08,0x10,0x08,0x10,0x08,0x00,0x08,0x00,0x00},/*"止",40*/
  //数
  {0x48,0x09,0x2A,0x0B,0x98,0x05,0x7F,0x05,0x28,0x0B,0x4A,0x00,
  0x10,0x08,0xEF,0x05,0x08,0x02,0xF8,0x05,0x08,0x08,0x00,0x00},/*"数",41*/
  //速
  {0x11,0x08,0xF2,0x07,0x00,0x08,0x7A,0x0A,0x4A,0x09,0xCA,0x08,
  0xFF,0x0F,0xCA,0x08,0x4A,0x09,0x7A,0x0A,0x02,0x08,0x00,0x00},/*"速",42*/
  //全
  {0x10,0x08,0x10,0x09,0x28,0x09,0x24,0x09,0x22,0x09,0xE1,0x0F,
  0x22,0x09,0x24,0x09,0x28,0x09,0x10,0x09,0x10,0x08,0x00,0x00},/*"全",43*/
  //设置
  {0x10,0x00,0x11,0x00,0xF2,0x07,0x00,0x02,0x50,0x08,0xCF,0x08,
  0x41,0x05,0x41,0x02,0x4F,0x05,0xD0,0x08,0x10,0x08,0x00,0x00},/*"设",44*/
  {0x10,0x08,0x17,0x08,0xD5,0x0F,0x55,0x08,0x57,0x08,0x7D,0x0E,
  0x57,0x08,0x55,0x08,0xD5,0x0F,0x17,0x08,0x10,0x08,0x00,0x00},/*"置",45*/
  //预约有效
  {0x20,0x00,0x2A,0x08,0xF2,0x0F,0x2E,0x00,0x60,0x00,0x00,0x00,
  0xF2,0x09,0x1A,0x04,0xD6,0x03,0x12,0x04,0xF2,0x09,0x00,0x00},/*"预",46*/
  {0x98,0x04,0xD4,0x04,0xB3,0x02,0x88,0x02,0x10,0x00,0x08,0x00,
  0x27,0x00,0xC4,0x00,0x04,0x08,0x04,0x08,0xFC,0x07,0x00,0x00},/*"约",47*/
  {0x44,0x00,0x24,0x00,0xF4,0x0F,0x5C,0x01,0x57,0x01,0x54,0x01,
  0x54,0x01,0x54,0x01,0x54,0x09,0xF4,0x0F,0x04,0x00,0x00,0x00},/*"有",48*/
  {0x44,0x08,0x34,0x04,0x85,0x02,0x06,0x01,0x94,0x02,0x24,0x04,
  0x10,0x08,0xEF,0x04,0x08,0x03,0xF8,0x04,0x08,0x08,0x00,0x00},/*"效",49*/
  //参
  {0x90,0x00,0x54,0x0A,0xB6,0x0A,0x95,0x0A,0x5C,0x0A,0x54,0x09,
  0x34,0x05,0x94,0x04,0x36,0x04,0x54,0x02,0x90,0x00,0x00,0x00},/*"参",50*/
  //上下
  {0x00,0x00,0x00,0x03,0xC0,0x00,0x30,0x00,0x0C,0x00,0x02,0x00,
  0x0C,0x00,0x30,0x00,0xC0,0x00,0x00,0x03,0x00,0x00,0x00,0x00},/*"∧",51*/
  {0x00,0x00,0x0C,0x00,0x30,0x00,0xC0,0x00,0x00,0x03,0x00,0x04,
  0x00,0x03,0xC0,0x00,0x30,0x00,0x0C,0x00,0x00,0x00,0x00,0x00},/*"∨",52*/
  //:
  {0x00,0x00,0x00,0x00,0x30,0x03,0x30,0x03,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*": ",53*/
  //选择
  {0x10,0x08,0x11,0x04,0xF2,0x03,0x00,0x04,0x28,0x0A,0x26,0x09,
  0xE4,0x08,0x3F,0x08,0xE4,0x09,0x24,0x0A,0x20,0x0B,0x00,0x00},/*"选",54*/
  {0x88,0x00,0x88,0x08,0xFF,0x0F,0x48,0x00,0x21,0x02,0xA3,0x02,
  0x95,0x02,0xE9,0x0F,0x95,0x02,0xA3,0x02,0x20,0x02,0x00,0x00},/*"择",55*/
  //主页
  {0x00,0x08,0x88,0x08,0x88,0x08,0x88,0x08,0x89,0x08,0xFA,0x0F,
  0x88,0x08,0x88,0x08,0x88,0x08,0x88,0x08,0x00,0x08,0x00,0x00},/*"主",56*/
  {0x01,0x08,0xF9,0x09,0x09,0x04,0x09,0x04,0x0D,0x02,0xCB,0x01,
  0x09,0x02,0x09,0x02,0x09,0x04,0xF9,0x05,0x01,0x08,0x00,0x00},/*"页",57*/
  //箭头
  {0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x00,0x00,
  0x02,0x02,0x04,0x01,0x88,0x00,0x50,0x00,0x20,0x00,0x00,0x00,},/*"->",58*/
  //焊接中
  {0x78,0x08,0x00,0x06,0xFF,0x01,0x08,0x02,0x04,0x05,0x5F,0x01,
  0x55,0x01,0xD5,0x0F,0x55,0x01,0x5F,0x01,0x00,0x01,0x00,0x00},/*"焊",59*/
  {0x88,0x00,0x88,0x08,0xFF,0x0F,0x48,0x00,0xA4,0x08,0xAC,0x0A,
  0xB5,0x0B,0xE6,0x04,0xB4,0x04,0xAC,0x0B,0xA4,0x08,0x00,0x00},/*"接",60*/
  {0x00,0x00,0xF8,0x01,0x88,0x00,0x88,0x00,0x88,0x00,0xFF,0x0F,
  0x88,0x00,0x88,0x00,0x88,0x00,0xF8,0x01,0x00,0x00,0x00,0x00},/*"中",61*/
  //操作机器人
  {0x12,0x01,0xD2,0x00,0xFE,0x0F,0x91,0x00,0x08,0x08,0x44,0x09,
  0xAB,0x04,0x52,0x05,0x6A,0x02,0x46,0x01,0xC0,0x00,0x00,0x00},/*"移",62*/ 
  {0x02,0x08,0x22,0x09,0x32,0x09,0x2A,0x09,0x26,0x09,0xE2,0x0F,
  0x22,0x09,0x2A,0x09,0x32,0x09,0x62,0x09,0x02,0x08,0x00,0x00},/*"至",63*/
  {0x88,0x00,0x68,0x00,0xFF,0x0F,0x28,0x08,0x40,0x04,0xFE,0x03,
  0x02,0x00,0x02,0x00,0xFE,0x07,0x00,0x08,0x00,0x0E,0x00,0x00},/*"机",64*/
  {0x20,0x01,0x27,0x0F,0xA5,0x0A,0xA5,0x0A,0x67,0x0E,0x38,0x00,
  0x67,0x0E,0xA5,0x0A,0xAD,0x0A,0x37,0x0F,0x20,0x01,0x00,0x00},/*"器",65*/
  {0x00,0x08,0x00,0x04,0x00,0x02,0x80,0x01,0x60,0x00,0x1F,0x00,
  0x60,0x00,0x80,0x01,0x00,0x02,0x00,0x04,0x00,0x08,0x00,0x00},/*"人",66*/
  //MM
  {0xFC,0x03,0x3C,0x00,0xC0,0x03,0x3C,0x00,0xFC,0x03,0x00,0x00,
  0xFC,0x03,0x3C,0x00,0xC0,0x03,0x3C,0x00,0xFC,0x03,0x00,0x00},/*"MM",67*/
  //A_
  {0x00,0x02,0xE0,0x03,0x9C,0x00,0xF0,0x00,0x80,0x03,0x00,0x02,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"A ",68*/
  //V
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x04,0x00,0x7C,0x00,0x80,0x03,0xE0,0x00,0x1C,0x00,0x04,0x00},/*"V ",69*/
  // 
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",70*/
  //.
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x03,0x00,0x00,0x00,0x00},/*".",71*/
  //CM
  {0xF8,0x01,0x04,0x02,0x04,0x02,0x04,0x02,0x0C,0x01,0x00,0x00,
  0xFC,0x03,0x3C,0x00,0xC0,0x03,0x3C,0x00,0xFC,0x03,0x00,0x00},/*"CM",72*/
  // /M
  {0x00,0x04,0x80,0x03,0x60,0x00,0x1C,0x00,0x02,0x00,0x00,0x00,
  0xFC,0x03,0x3C,0x00,0xC0,0x03,0x3C,0x00,0xFC,0x03,0x00,0x00},/*"/M",73*/
  //IN
  {0x04,0x02,0x04,0x02,0xFC,0x03,0x04,0x02,0x04,0x02,0x00,0x00,
  0x04,0x02,0xFC,0x03,0x30,0x02,0xC4,0x00,0xFC,0x03,0x04,0x00},/*"IN",74*/
  //高压输出注意安全
  {0x82,0x0F,0x82,0x00,0xBA,0x00,0xAA,0x0E,0xAA,0x0A,0xAB,0x0A,
  0xAA,0x0A,0xAA,0x0E,0xBA,0x00,0x82,0x08,0x82,0x0F,0x00,0x00},/*"高",75*/
  {0x34,0x01,0x2C,0x01,0xF7,0x0F,0xA4,0x00,0xE8,0x0F,0xA4,0x02,
  0xEA,0x0F,0x09,0x00,0xCA,0x03,0x04,0x08,0xE8,0x0F,0x00,0x00},/*"输",76*/
  {0x80,0x07,0x1E,0x04,0x10,0x04,0x10,0x04,0x10,0x04,0xFF,0x07,
  0x10,0x04,0x10,0x04,0x10,0x04,0x1E,0x04,0x80,0x0F,0x00,0x00},/*"出",77*/
  {0x22,0x04,0x44,0x02,0x00,0x08,0x88,0x08,0x88,0x08,0x89,0x08,
  0xFA,0x0F,0x88,0x08,0x88,0x08,0x88,0x08,0x00,0x08,0x00,0x00},/*"注",78*/
  {0x08,0x08,0x0A,0x06,0xFA,0x00,0xAE,0x06,0xAA,0x08,0xAB,0x09,
  0xAA,0x0A,0xAE,0x08,0xFA,0x0C,0x0A,0x02,0x08,0x0C,0x00,0x00},/*"意",79*/
  {0x2C,0x08,0x24,0x08,0xA4,0x09,0x64,0x05,0x3D,0x05,0x26,0x02,
  0x24,0x02,0x24,0x05,0xE4,0x04,0x24,0x08,0x2C,0x00,0x00,0x00},/*"安",80*/
  //手自
  {0x80,0x00,0x92,0x00,0x92,0x00,0x92,0x08,0x92,0x08,0xFE,0x0F,
  0x91,0x00,0x91,0x00,0x91,0x00,0x91,0x00,0x80,0x00,0x00,0x00},/*"手",81*/
  {0x00,0x00,0xFC,0x0F,0x24,0x09,0x24,0x09,0x26,0x09,0x25,0x09,
  0x24,0x09,0x24,0x09,0x24,0x09,0xFC,0x0F,0x00,0x00,0x00,0x00},/*"自",82*/
  //无
  {0x20,0x08,0x22,0x04,0x22,0x02,0x22,0x01,0xE2,0x00,0x3E,0x00,
  0xE2,0x07,0x22,0x08,0x22,0x08,0x22,0x08,0x20,0x0E,0x00,0x00},/*"无",83*/
  //左右
  {0x04,0x04,0x04,0x02,0x84,0x09,0x74,0x08,0x4F,0x08,0x44,0x08,
  0xC4,0x0F,0x44,0x08,0x44,0x08,0x44,0x08,0x04,0x08,0x00,0x00},/*"左",84*/ 
  {0x04,0x02,0x04,0x01,0x84,0x00,0xE4,0x0F,0x5C,0x04,0x47,0x04,
  0x44,0x04,0x44,0x04,0x44,0x04,0xC4,0x0F,0x04,0x00,0x00,0x00},/*"右",85*/
  //完成
  {0x86,0x08,0x82,0x08,0x92,0x04,0x92,0x03,0x92,0x00,0x93,0x00,
  0x92,0x00,0x92,0x07,0x92,0x08,0x82,0x08,0x86,0x0C,0x00,0x00},/*"完",86*/
  {0x00,0x08,0xFC,0x07,0x24,0x00,0x24,0x02,0xE4,0x0B,0x04,0x04,
  0xFF,0x02,0x04,0x01,0x85,0x02,0x66,0x04,0x04,0x0F,0x00,0x00},/*"成",87*/
  //错误
  {0x98,0x00,0xF7,0x0F,0x94,0x04,0x84,0x02,0x10,0x00,0xD4,0x0F,
  0x5F,0x05,0x54,0x05,0x54,0x05,0x5F,0x05,0xD4,0x0F,0x00,0x00},/*"错",88*/
  {0x22,0x00,0xE4,0x0F,0x00,0x05,0x40,0x01,0x5E,0x09,0x52,0x05,
  0xD2,0x03,0x52,0x05,0x5E,0x09,0x40,0x01,0x00,0x01,0x00,0x00},/*"误",89*/
};
__flash unsigned char Pic_lib[][12]={
  
  {0xF8,0x01,0x04,0x02,0x04,0x02,0x04,0x02,0xF8,0x01,0x00,0x00},/*"0",0*/
  {0x00,0x00,0x08,0x02,0xFC,0x03,0x00,0x02,0x00,0x00,0x00,0x00},/*"1",1*/
  {0x18,0x03,0x84,0x02,0x44,0x02,0x24,0x02,0x18,0x00,0x00,0x00},/*"2",2*/
  {0x08,0x01,0x04,0x02,0x24,0x02,0x24,0x02,0xD8,0x01,0x00,0x00},/*"3",3*/
  {0xC0,0x00,0xB0,0x00,0x88,0x02,0xFC,0x03,0x80,0x02,0x00,0x00},/*"4",4*/
  {0x3C,0x01,0x24,0x02,0x24,0x02,0x24,0x02,0xC4,0x01,0x00,0x00},/*"5",5*/
  {0xF8,0x01,0x24,0x02,0x24,0x02,0x2C,0x02,0xC0,0x01,0x00,0x00},/*"6",6*/
  {0x0C,0x00,0x04,0x00,0xE4,0x03,0x1C,0x00,0x04,0x00,0x00,0x00},/*"7",7*/
  {0xD8,0x01,0x24,0x02,0x24,0x02,0x24,0x02,0xD8,0x01,0x00,0x00},/*"8",8*/
  {0x38,0x00,0x44,0x03,0x44,0x02,0x44,0x02,0xF8,0x01,0x00,0x00},/*"9",9*/
  
  {0x00,0x00,0xFE,0x03,0xFC,0x01,0xF8,0x00,0x70,0x00,0x20,0x00},/*"/>",10*/
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",11*/
  
};
/*
*显示数字 x y显示起始坐标,*p显示数据指针，flag显示间断插入字符
*
*/
void Display_Num(unsigned char *x,unsigned char y,unsigned int *p,unsigned char flag){
  unsigned char i;
  unsigned int data;
  //获取要显示数据
  data=*(p);
  for(i=0;i<3;i++){
    Display_Chinese(x,y,&Pic_lib[data&0x000f][0],DIS_PIC);
    data>>=4;
    if(i==flag){
      *x= *x+6;
    }
  }
}
__flash unsigned char Page_Header[][PAGE_HEADER_LENGTH]={
  {ZHU3,YE4,ZHIZHEN,SHI4,JIAO4,KONGGE}, /*主页示教 */
  {ZHU3,YE4,ZHIZHEN,HAN4,JIE1,KONGGE},  /*主页焊接 */
  {ZHU3,YE4,ZHIZHEN,XIU1,BU3,KONGGE},   /*主页修补 */
  {ZHU3,YE4,ZHIZHEN,CUO4,WU4,KONGGE},   /*主页错误 */
  {SHE4,ZHI4,ZHIZHEN,SHI4,JIAO4,KONGGE},/*设置示教 */
  {SHE4,ZHI4,ZHIZHEN,HAN4,JIE1,KONGGE}, /*设置焊接 */
};
__flash unsigned char Page_Content[][PAGE_CONTENT_LENGTH]={
  //content1 
  {KONGGE,QI3,DONG4,JIAN4,QI3,DONG4,SHI4,JIAO4,KONGGE,KONGGE},  /*  启动键启动示教   */
  {SHE4,ZHI4,JIAN4,SHE4,ZHI4,SHI4,JIAO4,CAN1,SHU4,KONGGE},      /*设置键设置示教参数 */
  {KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE},/*     */
  //content 2
  {BAN3,KONGGE,KONGGE,HOU4,MAOHAO,KONGGE,MM,KONGGE,KONGGE,KONGGE}, /*板厚：??mm */
  {HAN4,JIE1,CHANG2,DU4,MAOHAO,KONGGE,MM,KONGGE,KONGGE,KONGGE}, /*焊接长度：??mm */
  {SHI4,JIAO4,DIAN3,SHU4,MAOHAO,KONGGE,DIAN3,KONGGE,KONGGE,KONGGE},/*示教点数：点 */
  //content 3
  {SHI3,KONGGE,ZHONG1_1,KONGGE,DUAN1,MAOHAO,KONGGE,KONGGE,KONGGE,KONGGE},/*始终端：?? */
  {TOU2,BU4,BAI3,KONGGE,DONG4,MAOHAO,KONGGE,KONGGE,KONGGE,KONGGE}, /*头部摆动:  */
  {DI4,YI1,DIAN3,WEI4,ZHI4,MAOHAO,KONGGE,KONGGE,KONGGE,KONGGE}, /*第一点位置：  */
  //content 4
  {YI2,DONG4,JI1,QI4,REN2,ZHI4_1,KONGGE,KONGGE,KONGGE,KONGGE}, /*移动机器人至  */
  {SHI4,JIAO4,DI4,KONGGE,DIAN3,WEI4,ZHI4,KONGGE,KONGGE,KONGGE},/*示教第？？点位置 */
  {KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE},/*  */
  //content 5
  {KONGGE,KONGGE,KONGGE,SHI4,JIAO4,ZHONG1,KONGGE,KONGGE,KONGGE,KONGGE}, /*示教中  */
  {GAO1,YA1,SHU1,CHU1,ZHU4,YI4,AN1,QUAN2,KONGGE,KONGGE},/*高压输出注意安全 */
  {TING2,ZHI3,JIAN4,TING2,ZHI3,SHI4,JIAO4,KONGGE,KONGGE,KONGGE},/* 停止键停止示教 */
  //content 6
  {KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE}, /*  */
  {QUE4,REN4,SHI4,JIAO4,DIAN3,WEI4,ZHI4,KONGGE,KONGGE,KONGGE},/*确认示教点位置 */
  {KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE},/*  */
  //content 7
  {KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE}, /*  */
  {GEN1,BU4,JIAN1,XI4,MAOHAO,KONGGE,MM,KONGGE,KONGGE,KONGGE},/*根部间隙：MM */
  {KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE},/*  */
  //content 8
  {KONGGE,KONGGE,SHI4,JIAO4,WAN2,CHENG2,KONGGE,KONGGE,KONGGE,KONGGE}, /* 示教完成*/
  {KONGGE,QI3,DONG4,JIAN4,QI3,DONG4,HAN4,JIE1,KONGGE,KONGGE},  /*  启动键启动焊接   */
  {SHE4,ZHI4,JIAN4,SHE4,ZHI4,HAN4,JIE1,CAN1,SHU4,KONGGE},      /*设置键设置焊接 */
  //content 9
  {SHI3,ZHONG1_1,DUAN1,MAOHAO,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE}, /* 始终端 :*/
  {HAN4,DAO4,MAOHAO,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE},  /*  焊道：   */
  {XIU1,BU3,MO2,SHI4,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE},      /*修补模式 */
  //content 10
  {KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE}, /*  */
  {YU4,YUE1,MAOHAO,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE},/*预约：有效 */
  {KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE},/*  */
  //content 11
  {KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE}, /*  */
  {XIU1,BU3,HAN4,JIE1,ZHONG1,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE},/*修补焊接中 */
  {KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE},/*  */
  //content 12
  {DIAN4,LIU2,MAOHAO,KONGGE,A,DIAN4,YA1,MAOHAO,XIAOSHU,V}, /* 电流：A电压：V */
  {HAN4,SU4,MAOHAO,KONGGE,CM,MEI,IN,KONGGE,KONGGE,KONGGE},/*焊速：CM/MIN */
  {HAN4,DAO4,MAOHAO,KONGGE,MEI,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE},/*焊道：*/
   //content 13
  {KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE}, /*  */
  {CUO4,WU4,MAOHAO,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE},/*错误： */
  {KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE},/*  */
};
__flash unsigned char Page_Bottom[][PAGE_BOTTOM_LENGTH]={
  {KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE},/*     */
  {SHE4,ZHI4,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE},/*设置      */
  {XIU1,GAI3,XIANGSHANG,XIANGXIA,MAOHAO,XUAN3,ZE2,KONGGE,FAN3,HUI2}, /*修改 选择 返回*/
  {QUE4,REN4,XIANGSHANG,XIANGXIA,MAOHAO,JIA1,JIAN3,KONGGE,QU3,XIAO1},/*确认 加减 取消*/
  {QUE4,REN4,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,QU3,XIAO1},/*确认      取消*/
  {SHE4,ZHI4,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,FAN3,HUI2}, /*设置        返回*/
  {KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,KONGGE,FAN3,HUI2}, /*设置        返回*/
};
__flash unsigned char Swing[][2]={
  {WU2,KONGGE},/*无 */
  {ZUO3,KONGGE},
  {YOU4,KONGGE},
  {ZUO3,YOU4},
};
/*
*液晶界面选择函数
*
*/
void Menu_Select(unsigned int *p){
  /*定义Page结构体*/
  Page_Union Page;
  Mult_Union Mult;
  unsigned char i,j;
  unsigned char x,data;
  *(p+PAGE_BUF)=Page_Debug.Page;
  /*获取page数据*/
  Page.Page=*(p+PAGE_BUF);
  /*判断Page header是否需要更新 */
  if(Page_Old.Page_Mult.Header!=Page.Page_Mult.Header){
    x=0;
    for(i=0;i<PAGE_HEADER_LENGTH;i++)
      /*显示数据*/
      Display_Chinese(&x,0,&Ch_lib[Page_Header[Page.Page_Mult.Header][i]][0],DIS_CH);
    /*赋予Page header 新值*/
    Page_Old.Page_Mult.Header=Page.Page_Mult.Header;
  }
  /*判断Page content是否需要更新*/
  if(Page_Old.Page_Mult.Content!=Page.Page_Mult.Content){
    for(j=0;j<3;j++){
      x=7;
      for(i=0;i<PAGE_CONTENT_LENGTH;i++){
        /*显示数据*/
        Display_Chinese(&x,j+1,&Ch_lib[Page_Content[Page.Page_Mult.Content*3+j][i]][0],DIS_CH);
      }
    }
    /*赋予Page header 新值*/
    Page_Old.Page_Mult.Content=Page.Page_Mult.Content;
  }
  /*判断Page content是否需要更新*/
  if(Page_Old.Page_Mult.Bottom!=Page.Page_Mult.Bottom){
    x=0;
    for(i=0;i<PAGE_BOTTOM_LENGTH;i++){
      if(i==2) x=35;
      if(i==5) x=XUANZE_X;
      if(i==8) x=QUXIAO_X;
      /*显示数据*/
      Display_Chinese(&x,4,&Ch_lib[Page_Bottom[Page.Page_Mult.Bottom][i]][0],DIS_CH);
    }
    /*如果Bottom 为 确认 则 光标闪烁开启*/
    if(Page.Page_Mult.Bottom == 2){
      Time_Enable=1;
      Time_Count=0;
    }
    else{
      Time_Enable=0;
      Time_Count=0;
    }
    /*赋予Page header 新值*/
    Page_Old.Page_Mult.Bottom=Page.Page_Mult.Bottom;
  }
  /*判断Page mouse是否需要更新*/
  for(i=1;i<4;i++){
    /*如果mouse要显示的位置*/
    x=0;
    if((i==Page.Page_Mult.Mouse)&&(Time_Count<20))  data=JIANTOU;
    else  data=KONG;
    if(Time_Count>40) Time_Count=0;
    /*显示数据*/
    Display_Chinese(&x,i,&Pic_lib[data][0],DIS_PIC);
  }
  /*刷新数据显示*/
  switch(Page.Page_Mult.Content){
    /*板厚 焊接长度 示教点数*/
    case 1:
    /*板厚 焊接长度*/
    for(i=0;i<3;i++){
      x=61;
      Display_Num(&x,i+1,p+PLATE_HIGHT_BUF+i,4); 
    }
    break;
    /*始终端 头部摆动 焊接第一点位置*/
    case 2:
    Mult.Data=*(p+MULT_BUF);
    x=73;
    /*手？自*/
    Display_Chinese(&x,1,&Ch_lib[Mult.Mult_Res.Weld_Start_And_Stop+SHOU3][0],DIS_CH);
    Display_Chinese(&x,1,&Ch_lib[DONG4][0],DIS_CH);
    x=73;
    /*左右 左 右 无*/
    for(i=0;i<2;i++)
      Display_Chinese(&x,2,&Ch_lib[Swing[Mult.Mult_Res.Swing_Mode][i]][0],DIS_CH);
    /*左 右*/
    x=73;
    Display_Chinese(&x,3,&Ch_lib[Mult.Mult_Res.Weld_First_Point+ZUO3][0],DIS_CH);
    break;
    /*根部间隙*/
    case 6:
    x=61;
    Display_Num(&x,2,p+ROOT_GAP_BUF,4); 
    break;
    case 11:
    /*电流 焊速 当前焊道 */
    for(i=0;i<3;i++){
      x=37;
      Display_Num(&x,i+1,p+WELD_CURRENT_BUF+i,4);
    }
    /*电压*/
    x=97;
    Display_Num(&x,1,p+WELD_VOLAGTE_BUF,1);
    /*规定焊道*/
    x=61;
    Display_Num(&x,3,p+WELD_NUM_BUF,4);
    break;
  }
}
