#include "DAC.h"

#include "iopwm316.h"

void INIT_DAC(void)                            
{ 
  
   ENABLE_DAC_OUTPUT();    
   RIGHT_ADJUST_DAC_INPUT();
   DISABLE_DAC();
}

