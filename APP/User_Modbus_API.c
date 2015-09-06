

#include "User_Modbus_API.h"

#include "mb.h"
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
eMBErrorCode eMBRegCoilsCB( UCHAR           *pucRegBuffer, 
                            USHORT          usAddress    , 
                            USHORT          usNCoils     ,
                            eMBRegisterMode eMode        )
{  
 /*  eMBErrorCode eStatus=MB_ENOERR;
   unsigned int m_data,mm_data;
   unsigned char i;
     
    if((usAddress>=Coil_START_ADDR)&&((usAddress+usNCoils-1)<=Coil_END_ADDR))
    {
        switch(eMode)
        {
              
            case MB_REG_READ:             
                 m_data=Modbus_Weld_Data.Weld.Coil;
                 m_data=m_data<<(Coil_END_ADDR-(usAddress+usNCoils-1));
                 m_data=m_data>>((Coil_END_ADDR-usNCoils));
                 *pucRegBuffer=(unsigned char)m_data;
                 if(usNCoils>=8)
                 {
                    pucRegBuffer++;
                    *pucRegBuffer=(unsigned char)(m_data>>8);
                 }
                 break;
            case MB_REG_WRITE:
                 if(usNCoils==1)//写单个线圈
                 {
                     if(*pucRegBuffer==COIL_ON)//打开单个线圈
                     {
                         switch(usAddress-1)
                         {    
                              //启动焊接
                              case COIL_WELD                  :
                                   START_WELD(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //设置为划擦起弧
                              case COIL_STRIKING_WAY          :
                                   SCRATCH(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //设置为正极性//
                              case COIL_POLARITY_WELDING      :
                                   POSITIVE_POLARITY(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //设置为平特性// 
                              case COIL_CHARATERISTIC_WELDING :
                                   VOLTAGE_CHARATERISTIC_WELDING(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //停止触发//
                              case COIL_TRIGGER               :
                                   START_TRIGGER(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //清空其它未使用位//
                              default: Modbus_Weld_Data.Weld.Coil &=0x1F;
                                   break;
                          }
                       }
                     else//关闭单个线圈
                     {
                             switch(usAddress-1)
                         {    
                              //停止焊接//
                              case COIL_WELD                  :
                                   STOP_WELD(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //设置为回抽起弧//
                              case COIL_STRIKING_WAY          :
                                   PUMPBACK(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //设置为反极性//
                              case COIL_POLARITY_WELDING      :
                                   REVERSE_POLARITY(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //设置为降特性// 
                              case COIL_CHARATERISTIC_WELDING :
                                   CURRENT_CHARATERISTIC_WELDING(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //触发电源//
                              case COIL_TRIGGER               :
                                   STOP_TRIGGER(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //清空其它未使用位//
                              default: Modbus_Weld_Data.Weld.Coil &=0x1F;
                                   break;
                          }
                     
                       }
                   }
                 else//写多个线圈
                 {
                     m_data=*pucRegBuffer;
                     pucRegBuffer++;
                     m_data|=((*pucRegBuffer)<<8);
                     m_data<<=(usAddress-1);
                     //Modbus_Weld_Data.Weld.Coil|=m_data;
                     mm_data=Modbus_Weld_Data.Weld.Coil;
                     for(i=usAddress;i<(usNCoils+usAddress);i++)
                     {
                        if((m_data>>i)!=(mm_data>>i))
                        {
                                
                        
                        }
                     }
                   }
                 break;
            default :;break;
        }
    }
    else
      eStatus=MB_ENOREG;
    return eStatus;*/
  
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
eMBErrorCode    eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress,
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
eMBErrorCode eMBRegHoldingCB(UCHAR           *pucRegBuffer , 
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


