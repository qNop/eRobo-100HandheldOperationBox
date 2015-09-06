
#ifndef DAC_H
#define DAC_H

//失/使能DAC
#define ENABLE_DAC()                         (DACON |= (1<<DAEN))
#define DISABLE_DAC()                        (DACON &= ~(1<<DAEN))
//对齐
#define RIGHT_ADJUST_DAC_INPUT()             (DACON  &= ~(1<<DALA))
#define LEFT_ADJUST_DAC_INPUT()              (DACON  |=  (1<<DALA))
//DAC输出控
#define ENABLE_DAC_OUTPUT()                  (DACON  |=  (1<<DAOE))
#define DISABLE_DAC_OUTPUT()                 (DACON  &= ~(1<<DAOE))
//DAC输出
#define SET_DAC_8_BITS(DAC_IN)               (DACH = (unsigned char)(DAC_IN))
#define SET_DAC_10_BITS(DAC_IN)              (DACL = (unsigned char)(DAC_IN), \
                                              DACH = (unsigned char)(DAC_IN>>8))
/*
//基准源选取
#define ENABLE_INTERNAL_VREF()               (ADMUX  |=  ((1<<REFS1)|(1<<REFS0)))
#define ENABLE_EXTERNAL_VREF()               (ADMUX  &= ~((1<<REFS1)|(1<<REFS0)))
#define ENABLE_VCC_VREF()                    (ADMUX  &= ~(1<<REFS1); \
                                              ADMUX |= (1<<REFS0);)*/

void INIT_DAC(void);

#endif