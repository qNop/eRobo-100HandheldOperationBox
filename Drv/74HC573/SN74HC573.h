 /*
  *�ļ�����sn74hc573.h
  *
  *
  */
#ifndef SN74HC573_H_
#define SN74HC573_H_

/*���KEY�ߵ͵�ƽ*/


#define CS1       0XF2
#define CS2       0XF1

unsigned char Sn_Get_Data();
void Sn_Output_KeyCode(unsigned char KeyCode);
void Sn_Output_CS(unsigned char bit);

#endif