

#include "User_Modbus_API.h"

#include "mb.h"
#include "mb_m.h"
#include "mbutils.h"
#include "Config.h"

extern unsigned int *pModbus_Reg;
/*******************************************************************************
  * @brief  ���ּĴ��������������ּĴ����ɶ����ɶ���д
  * @param  pucRegBuffer  ������ʱ--��������ָ�룬д����ʱ--��������ָ��
  *         usAddress     �Ĵ�����ʼ��ַ
  *         usNRegs       �Ĵ�������
  *         eMode         ������ʽ��������д
  * @retval eStatus       �Ĵ���״̬
  ******************************************************************************/
eMBErrorCode eMBMasterRegHoldingCB(UCHAR     *pucRegBuffer , 
                             USHORT          usAddress     , 
                             USHORT          usNRegs       ,
                             eMBRegisterMode eMode         )
{
   eMBErrorCode eStatus=MB_ENOERR;
   unsigned char i;     
   if(( usAddress + usNRegs )<= 255 )
   {  usNRegs+=2;
      switch(eMode)
      {
        /*�����ּĴ���*/
        case MB_REG_READ:
          for(i=2;i<usNRegs;i++)
          {
            //  *(pModbus_Reg+i)=*pucRegBuffer;
            //  pucRegBuffer++;
            //  (*(pModbus_Reg+i))<<=8;
            //  *(pModbus_Reg+i)|=*pucRegBuffer;
            //  pucRegBuffer++;
          }
          break;
        /*д���ּĴ���
        case MB_REG_WRITE:
          for(i=usAddress*2;i<usNRegs;i++)
          {
              
          
          }
          break;*/
        default:;break;
        }
   }
   else
     eStatus=MB_ENOREG;
   return eStatus;
}


