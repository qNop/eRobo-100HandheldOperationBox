 /*
  *文件名：lcd12864.h
  *液晶型号：深圳富创LG128642-FFDWH6V-NT,
  *液晶内部驱动器：NT7108C
  */

#ifndef MENU_H_
#define MENU_H_

#include "Config.h"

//页首定义
#define HOME_TEACH_PAGE         1
#define HOME_WELD_PAGE          2
#define HOME_REPAIR_WELD_PAGE   3
#define HOME_ALARM_PAGE         4
#define SET_TECH_PAGE           5
#define SET_WELD_PAGE           6
    
#define DIS_PIC     6
#define DIS_CH      12
#define DIS_WORD    24
#define DIS_STRING  60
    
#define QUXIAO_X    104
#define XUANZE_X    67
    
#define PAGE_HEADER_LENGTH   6  
#define PAGE_CONTENT_LENGTH  10
#define PAGE_BOTTOM_LENGTH  10

//板厚
#define  BAN3       0 
#define  HOU4       1 
//修补
#define  XIU1       2
#define  BU3        3 
//头部摆动
#define  TOU2       4
#define  BU4        5
#define  BAI3       6 
#define  DONG4      7
//道
#define  DAO4       8
//第一点位
#define  DI4        9
#define  YI1        10
#define  DIAN3      11
#define  WEI4       12 
//电压流
#define  DIAN4      13
#define  YA1        14
#define  LIU2       15
//长度
#define  CHANG2     16
#define  DU4        17
//始终端
#define  SHI3       18
#define  ZHONG1_1   19    
#define  DUAN1      20  
//返回
#define  FAN3       21
#define  HUI2       22
//改
#define  GAI3       23
//根
#define  GEN1       24
//间隙
#define  JIAN1      25
#define  XI4        26
//加减
#define  JIA1       27
#define  JIAN3      28
//启
#define  QI3        29
//键
#define  JIAN4      30
//示教
#define  SHI4       31 
#define  JIAO4      32
//模式
#define  MO2        33
#define  SHI4_1     34   
//取消
#define  QU3        35 
#define  XIAO1      36 
//确认
#define  QUE4       37 
#define  REN4       38
//停止
#define  TING2      39
#define  ZHI3       40 
//数
#define  SHU4       41
//速
#define  SU4        42
    //全
#define  QUAN2       43

//设置
#define  SHE4       44
#define  ZHI4       45
//预约有效
#define  YU4        46 
#define  YUE1       47 
#define  YOU3       48  
#define  XIAO4      49 
//参
#define  CAN1         50
//上下
#define  XIANGSHANG   51   
#define  XIANGXIA     52
//: 
#define  MAOHAO    53
//选择
#define  XUAN3      54
#define  ZE2        55 
//主页
#define  ZHU3       56 
#define  YE4        57
//箭头
#define  ZHIZHEN    58
//焊接中
#define  HAN4       59
#define  JIE1       60
#define  ZHONG1     61
//操作机器人
#define  YI2        62
#define  ZHI4_1     63
#define  JI1        64
#define  QI4        65 
#define  REN2       66
//MM     
#define  MM         67
//A   
#define  A           68
//V
#define  V           69
#define  KONGGE      70  
#define  XIAOSHU     71
    
#define  CM          72
#define  MEI         73
#define  IN          74
//高压输出注意安全
#define  GAO1        75
#define  SHU1        76
#define  CHU1        77
#define  ZHU4        78
#define  YI4         79
#define  AN1         80

//手
#define  SHOU3       81
#define  ZI4         82
//无
#define  WU2         83 
#define  ZUO3        84
#define  YOU4        85
#define  WAN2        86
#define  CHENG2      87
//错误
#define  CUO4        88
#define  WU4         89

#define  JIANTOU     10
#define  KONG        11


Key_Union Get_Key(void);
void Menu_Select(unsigned int *p);

#endif