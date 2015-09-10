

#include "User_Modbus_API.h"

#include "mb.h"
#include "mb_m.h"
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
eMBErrorCode eMBMasterRegCoilsCB( UCHAR           *pucRegBuffer, 
                            USHORT          usAddress    , 
                            USHORT          usNCoils     ,
                            eMBRegisterMode eMode        )
{  
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
  * @brief  ���ּĴ��������������ּĴ����ɶ����ɶ���д
  * @param  pucRegBuffer  ������ʱ--��������ָ�룬д����ʱ--��������ָ��
  *         usAddress     �Ĵ�����ʼ��ַ
  *         usNRegs       �Ĵ�������
  *         eMode         ������ʽ��������д
  * @retval eStatus       �Ĵ���״̬
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


