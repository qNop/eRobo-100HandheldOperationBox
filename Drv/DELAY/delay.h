
#ifndef DELAY_H_
#define DELAY_H_

#include <intrinsics.h>

#define  CPU_CLK         16000000
#define  Delay_us(x)     __delay_cycles(16* x)
#define  Delay_ms(x)     __delay_cycles(16000*x)
/*nopÖ¸ÁîÎª65ns*/
#define  Nop()           __no_operation()
#endif