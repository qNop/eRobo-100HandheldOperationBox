/*�ײ����*/
#include "iopwm316.h"
/*�ļ��ڵ���*/
#include "ADC.h"
/*ȫ�ֵ���*/
#include "Config.h"

/*ADC��ʼ��*/
void INIT_ADC(void)                            
{
    DISABLE_ADC();               
    RIGHT_ADJUST_ADC_INPUT();    
    ENABLE_ADC_HIGH_SPEED_MODE();
    ENABLE_VCC_VREF();           
    CLEAR_ADC_FLAG();            
    DISABLE_ADC_IT();            
    SET_PRESCALER(ADC_PRESCALER_32);           
}
/*ʹ��ADCת��*/
Sys_Error Enable_Conv_ADC(unsigned char CHANNEL)
{
    CLEAR_ADC_FLAG();
    ENABLE_ADC();
    ENABLE_ADC_IT();
    ENABLE_ADC_AUTO();
    START_CONV_CHANNEL(CHANNEL);
    return Sys_No_Error;
}
/*ʧ��ADCת��*/
Sys_Error Disable_Conv_ADC(void)
{

    DISABLE_ADC();
    DISABLE_ADC_IT();
    CLEAR_ADC_FLAG();
    DISABLE_ADC_AUTO();
    return Sys_No_Error;
    
}

