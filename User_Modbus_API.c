

#include "User_Modbus_API.h"

#include "mb.h"
#include "mb_m.h"
#include "mbutils.h"
#include "Config.h"

//static unsigned long Key;

/*******************************************************************************
  * @brief  线圈寄存器处理函数，线圈寄存器可读，可读可写
  * @param  pucRegBuffer  读操作---返回数据指针，写操作--返回数据指针
  *         usAddress     寄存器起始地址
  *         usNRegs       寄存器长度
  *         eMode         操作方式，读或者写
  * @retval eStatus       寄存器状态
  ******************************************************************************/


/******************************************************************************* 
  * @brief  输入寄存器处理函数，输入寄存器可读，但不可写。
  * @param  pucRegBuffer  返回数据指针
  *         usAddress     寄存器起始地址
  *         usNRegs       寄存器长度
  * @retval eStatus       寄存器状态
  *******************************************************************************/


/*******************************************************************************
  * @brief  保持寄存器处理函数，保持寄存器可读，可读可写
  * @param  pucRegBuffer  读操作时--返回数据指针，写操作时--输入数据指针
  *         usAddress     寄存器起始地址
  *         usNRegs       寄存器长度
  *         eMode         操作方式，读或者写
  * @retval eStatus       寄存器状态
  ******************************************************************************/
eMBErrorCode eMBMasterRegHoldingCB(UCHAR           *pucRegBuffer , 
                             USHORT          usAddress     , 
                             USHORT          usNRegs       ,
                             eMBRegisterMode eMode         )
{
   eMBErrorCode eStatus=MB_ENOERR;
   unsigned char i;     
   if(( usAddress + usNRegs )<= 16 )
   {
      usAddress-=1;
      usNRegs+=usAddress;
      usNRegs<<=1;
      switch(eMode)
      {
        /*读保持寄存器*/
        case MB_REG_READ:
          
          for(i=usAddress*2;i<usNRegs;i++)
          {
            
          
          }
          break;
        /*写保持寄存器*/
        case MB_REG_WRITE:
          for(i=usAddress*2;i<usNRegs;i++)
          {
              
          
          }
          break;
        default:;break;
        }
   }
   else
     eStatus=MB_ENOREG;
   return eStatus;
}


