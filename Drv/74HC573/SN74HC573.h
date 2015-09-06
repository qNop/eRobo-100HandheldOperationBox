 /*
  *文件名：sn74hc573.h
  *
  *
  */
#ifndef SN74HC573_H_
#define SN74HC573_H_

/*输出KEY高低电平*/


#define CS1       0XBF
#define CS2       0X7F

unsigned char Sn_Get_Data();
void Sn_Output_KeyCode(unsigned char KeyCode);
void Sn_Output_CS(unsigned char bit);

#endif