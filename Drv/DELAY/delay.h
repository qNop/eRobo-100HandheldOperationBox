
#ifndef DELAY_H_
#define DELAY_H_

#include <intrinsics.h>
#include "config.h"

#define  Delay_us(x)     __delay_cycles(16* x)
#define  Delay_ms(x)     __delay_cycles(16000*x)
/*nopָ��Ϊ65ns*/
#define  Nop()           __no_operation()
#endif