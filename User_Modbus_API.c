

#include "User_Modbus_API.h"

#include "mb.h"
#include "mb_m.h"
#include "mbutils.h"
#include "Config.h"


/*******************************************************************************
  * @brief  线圈寄存器处理函数，线圈寄存器可读，可读可写
  * @param  pucRegBuffer  读操作---返回数据指针，写操作--返回数据指针
  *         usAddress     寄存器起始地址
  *         usNRegs       寄存器长度
  *         eMode         操作方式，读或者写
  * @retval eStatus       寄存器状态
  ******************************************************************************/
eMBErrorCode eMBMasterRegCoilsCB( UCHAR           *pucRegBuffer, 
                            USHORT          usAddress    , 
                            USHORT          usNCoils     ,
                            eMBRegisterMode eMode        )
{  
  //错误状态
  eMBErrorCode    eStatus = MB_ENOERR;
  //寄存器个数
  int    iNCoils = (int)usNCoils;
  //寄存器偏移量
  unsigned int         usBitOffset;

  //检查寄存器是否在指定范围内
  if( (usAddress + usNCoils) <= 16 )
  {
          
    //计算寄存器偏移量
    usBitOffset = ( unsigned int )( usAddress  );
    switch ( eMode ){
      case MB_REG_READ:                  //读操作
        while( iNCoils > 0 ){
          
        }
      break;

      case MB_REG_WRITE:                //写操作
        while( iNCoils > 0 ){
       
        }
       break;
     }
  }
  else{
    eStatus = MB_ENOREG;
  }
  return eStatus;
}

/******************************************************************************* 
  * @brief  输入寄存器处理函数，输入寄存器可读，但不可写。
  * @param  pucRegBuffer  返回数据指针
  *         usAddress     寄存器起始地址
  *         usNRegs       寄存器长度
  * @retval eStatus       寄存器状态
  *******************************************************************************/
eMBErrorCode    eMBMasterRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress,
                               USHORT usNRegs )
{
   eMBErrorCode eStatus=MB_ENOERR;
   unsigned char i;
  if( ( usAddress + usNRegs )<= 16 )   
   {   
     usAddress-=1;
     usNRegs+=usAddress;
     usNRegs<<=1;
      for(i=usAddress*2;i<usNRegs;i++)
      {
          
          
      }
   }
   else
      eStatus=MB_ENOREG;
   return eStatus;
}

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


