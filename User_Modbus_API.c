

#include "User_Modbus_API.h"

#include "mb.h"
#include "mb_m.h"
#include "mbutils.h"
#include "Config.h"

//static unsigned long Key;

/*******************************************************************************
  * @brief  ��Ȧ�Ĵ�������������Ȧ�Ĵ����ɶ����ɶ���д
  * @param  pucRegBuffer  ������---��������ָ�룬д����--��������ָ��
  *         usAddress     �Ĵ�����ʼ��ַ
  *         usNRegs       �Ĵ�������
  *         eMode         ������ʽ��������д
  * @retval eStatus       �Ĵ���״̬
  ******************************************************************************/


/******************************************************************************* 
  * @brief  ����Ĵ���������������Ĵ����ɶ���������д��
  * @param  pucRegBuffer  ��������ָ��
  *         usAddress     �Ĵ�����ʼ��ַ
  *         usNRegs       �Ĵ�������
  * @retval eStatus       �Ĵ���״̬
  *******************************************************************************/


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


