

#include "User_Modbus_API.h"

#include "mb.h"
#include "mbutils.h"
#include "Config.h"


/*******************************************************************************
  * @brief  ��Ȧ�Ĵ�������������Ȧ�Ĵ����ɶ����ɶ���д
  * @param  pucRegBuffer  ������---��������ָ�룬д����--��������ָ��
  *         usAddress     �Ĵ�����ʼ��ַ
  *         usNRegs       �Ĵ�������
  *         eMode         ������ʽ��������д
  * @retval eStatus       �Ĵ���״̬
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
                 if(usNCoils==1)//д������Ȧ
                 {
                     if(*pucRegBuffer==COIL_ON)//�򿪵�����Ȧ
                     {
                         switch(usAddress-1)
                         {    
                              //��������
                              case COIL_WELD                  :
                                   START_WELD(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //����Ϊ������
                              case COIL_STRIKING_WAY          :
                                   SCRATCH(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //����Ϊ������//
                              case COIL_POLARITY_WELDING      :
                                   POSITIVE_POLARITY(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //����Ϊƽ����// 
                              case COIL_CHARATERISTIC_WELDING :
                                   VOLTAGE_CHARATERISTIC_WELDING(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //ֹͣ����//
                              case COIL_TRIGGER               :
                                   START_TRIGGER(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //�������δʹ��λ//
                              default: Modbus_Weld_Data.Weld.Coil &=0x1F;
                                   break;
                          }
                       }
                     else//�رյ�����Ȧ
                     {
                             switch(usAddress-1)
                         {    
                              //ֹͣ����//
                              case COIL_WELD                  :
                                   STOP_WELD(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //����Ϊ�س���//
                              case COIL_STRIKING_WAY          :
                                   PUMPBACK(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //����Ϊ������//
                              case COIL_POLARITY_WELDING      :
                                   REVERSE_POLARITY(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //����Ϊ������// 
                              case COIL_CHARATERISTIC_WELDING :
                                   CURRENT_CHARATERISTIC_WELDING(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //������Դ//
                              case COIL_TRIGGER               :
                                   STOP_TRIGGER(Modbus_Weld_Data.Weld.Coil);
                                   break;
                              //�������δʹ��λ//
                              default: Modbus_Weld_Data.Weld.Coil &=0x1F;
                                   break;
                          }
                     
                       }
                   }
                 else//д�����Ȧ
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
  
  //����״̬
  eMBErrorCode    eStatus = MB_ENOERR;
  //�Ĵ�������
  int    iNCoils = (int)usNCoils;
  //�Ĵ���ƫ����
  unsigned int         usBitOffset;

  //���Ĵ����Ƿ���ָ����Χ��
  if( (usAddress + usNCoils) <= 16 )
  {
          
    //����Ĵ���ƫ����
    usBitOffset = ( unsigned int )( usAddress  );
    switch ( eMode ){
      case MB_REG_READ:                  //������
        while( iNCoils > 0 ){
          
        }
      break;

      case MB_REG_WRITE:                //д����
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
  * @brief  ����Ĵ���������������Ĵ����ɶ���������д��
  * @param  pucRegBuffer  ��������ָ��
  *         usAddress     �Ĵ�����ʼ��ַ
  *         usNRegs       �Ĵ�������
  * @retval eStatus       �Ĵ���״̬
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
  * @brief  ���ּĴ��������������ּĴ����ɶ����ɶ���д
  * @param  pucRegBuffer  ������ʱ--��������ָ�룬д����ʱ--��������ָ��
  *         usAddress     �Ĵ�����ʼ��ַ
  *         usNRegs       �Ĵ�������
  *         eMode         ������ʽ��������д
  * @retval eStatus       �Ĵ���״̬
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
        /*�����ּĴ���*/
        case MB_REG_READ:
          
          for(i=usAddress*2;i<usNRegs;i++)
          {
            
          
          }
          break;
        /*д���ּĴ���*/
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


