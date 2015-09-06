/*底层调用*/
#include "iopwm316.h"
/*文件内调用*/
#include "ADC.h"
/*全局调用*/
#include "Config.h"

/*ADC初始化*/
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
/*使能ADC转换*/
Sys_Error Enable_Conv_ADC(unsigned char CHANNEL)
{
    CLEAR_ADC_FLAG();
    ENABLE_ADC();
    ENABLE_ADC_IT();
    ENABLE_ADC_AUTO();
    START_CONV_CHANNEL(CHANNEL);
    return Sys_No_Error;
}
/*失能ADC转换*/
Sys_Error Disable_Conv_ADC(void)
{

    DISABLE_ADC();
    DISABLE_ADC_IT();
    CLEAR_ADC_FLAG();
    DISABLE_ADC_AUTO();
    return Sys_No_Error;
    
}

