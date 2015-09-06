
#ifndef ADC_H
#define ADC_H

//使能ADC
#define ENABLE_ADC()                         (ADCSRA |= (1<<ADEN))
     
#define RIGHT_ADJUST_ADC_INPUT()             (ADMUX  &= ~(1<<ADLAR))
#define LEFT_ADJUST_ADC_INPUT()              (ADMUX  |=  (1<<ADLAR))
      
#define ENABLE_ADC_HIGH_SPEED_MODE()         (ADCSRB |=  (1<<ADHSM))
#define DISABLE_ADC_HIGH_SPEED_MODE()        (ADCSRB &= ~(1<<ADHSM))
      
#define ENABLE_INTERNAL_VREF()               (ADMUX  |=  ((1<<REFS1)|(1<<REFS0)) )
#define ENABLE_EXTERNAL_VREF()               (ADMUX  &= ~((1<<REFS1)|(1<<REFS0)) )
#define ENABLE_VCC_VREF()                    (ADMUX  &= ~(1<<REFS1),\
                                               ADMUX  |=  (1<<REFS0))     
#define ENABLE_ADC_IT()                      (ADCSRA |=  (1<<ADIE) )
#define DISABLE_ADC_IT()                     (ADCSRA &= ~(1<<ADIE) )
#define CLEAR_ADC_FLAG()                     (ADCSRA &= ~(1<<ADIF) )
      

#define ADC_PRESCALER_2                         1
#define ADC_PRESCALER_4                         2
#define ADC_PRESCALER_8                         3
#define ADC_PRESCALER_16                        4
#define ADC_PRESCALER_32                        5
#define ADC_PRESCALER_64                        6
#define ADC_PRESCALER_128                       7

#define SET_PRESCALER(PRESCALER)             (ADCSRA &= ~((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)),\
                                              ADCSRA |=  (PRESCALER) )
      
#define CLEAR_ADC_MUX()                      (ADMUX  &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0)) )
#define SELECT_ADC_CHANNEL(CHANNEL)          (CLEAR_ADC_MUX(),ADMUX |= (CHANNEL))
      
#define START_CONV()                          (ADCSRA |= (1<<ADSC) )
#define START_CONV_CHANNEL(CHANNEL)           (SELECT_ADC_CHANNEL(CHANNEL),START_CONV())
#define START_AMPLIFIED_CONV()                (ADCSRB |= (1<<ADASCR) )
#define STOP_AMPLIFIED_CONV()                 (ADCSRB &= ~(1<<ADASCR) )
#define START_AMPLIFIED_CONV_CHANNEL(CHANNEL) (SELECT_ADC_CHANNEL(CHANNEL),STOP_AMPLIFIED_CONV() )
         
#define START_CONV_IDLE()                    (SMCR   |=  (1<<SM0)|(1<<SE) )
#define START_CONV_IDLE_CHANNEL(CHANNEL)     (SELECT_ADC_CHANNEL(CHANNEL),START_CONV_IDLE() )
#define CLEAR_SLEEP_MODE()                   (SMCR   &= ~(1<<SM0)|(1<<SE) )
        
#define ADC_GET_8_BITS_RESULT(ADC_DATA)       (ADC_DATA=ADCH)
#define ADC_GET_10_BITS_RESULT(ADC_DATA)      (ADC_DATA=ADCH,ADC_DATA<<=8,ADC_DATA|=ADCL)
      
#define DISABLE_ADC()                        (ADCSRA &= ~(1<<ADEN))
      
#define IS_ADC_CONV_FINISHED()               ((ADCSRA &  (1<<ADIF)) ? TRUE : FALSE)
#define IS_ADC_CONV_NOT_FINISHED()           ((ADCSRA | ~(1<<ADIF)) ? TRUE : FALSE)


#define ENABLE_ADC_AUTO()                    (ADCSRA |=(1<<ADATE))
#define DISABLE_ADC_AUTO()                   (ADCSRA &=~(1<<ADATE))


/*信号采集通道*/
#define  BURN_BACK_TIME_CHANNEL                6
#define  CURRENT_FEEDBACK_CHANNEL              7   
#define  VOLTAGE_FEEDBACK_CHANNEL              8
#define  CURRENT_SET_CHANNEL                   9
#define  VOLTAGE_SET_CHANNEL                   10

void INIT_ADC(void) ;
  

#endif  
