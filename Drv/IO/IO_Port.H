
#ifndef IO_PORT_H
#define IO_PORT_H

/*LCD_PWM*/
#define  LCD_PWM                     0
#define  PIN_LCD_PWM                 PIND
#define  DDR_LCD_PWM                 DDRD   
 
/*LCD_LE*/
#define  LE                          0
#define  PORT_LE                     PORTC
#define  DDR_LE                      DDRC

#define  SET_LE()                   (PORT_LE |= (1<<(LE)))  
#define  CLEAR_LE()                 (PORT_LE &= ~(1<<(LE)))

/*LCD_RW*/
#define  LCD_RW                      1
#define  PORT_LCD_RW                 PORTD
#define  DDR_LCD_RW                  DDRD

#define  SET_LCD_RW()                (PORT_LCD_RW |= (1<<(LCD_RW)))  
#define  CLEAR_LCD_RW()              (PORT_LCD_RW &= ~(1<<(LCD_RW)))

/*LCD_RS*/
#define  LCD_RS                       2
#define  PORT_LCD_RS                  PORTD
#define  DDR_LCD_RS                   DDRD

#define  SET_LCD_RS()                (PORT_LCD_RS |= (1<<(LCD_RS)))  
#define  CLEAR_LCD_RS()              (PORT_LCD_RS &= ~(1<<(LCD_RS)))

/*LCD_E*/
#define  LCD_E                        1
#define  PORT_LCD_E                   PORTC
#define  DDR_LCD_E                    DDRC

#define  SET_LCD_E()                 (PORT_LCD_E |= (1<<(LCD_E)))  
#define  CLEAR_LCD_E()               (PORT_LCD_E &= ~(1<<(LCD_E)))

/*LCD_DB*/
#define  PORT_LCD_DB                  PORTB
#define  DDR_LCD_DB                   DDRB

#define  SET_LCD_DB(data)             (PORT_LCD_DB = data) 

/*UART TXD*/
#define  TXD                          3
#define  PORT_TXD                     PORTD
#define  DDR_TXD                      DDRD

/*UART RXD*/
#define  RXD                          4
#define  PIN_RXD                      PIND
#define  DDR_RXD                      DDRD
/*KEY_4*/
#define  KEY_4                          4
#define  PIN_KEY_4                    PINC
#define  DDR_KEY_4                    DDRC
/*KEY_5*/
#define  KEY_5                          5
#define  PIN_KEY_5                    PINC
#define  DDR_KEY_5                    DDRC
/*KEY_6*/
#define  KEY_6                          6
#define  PIN_KEY_6                    PINC
#define  DDR_KEY_6                    DDRC
/*KEY_7*/
#define  KEY_7                          7
#define  PIN_KEY_7                    PINC
#define  DDR_KEY_7                    DDRC

#define  GET_KEY_CODE()               PINC & 0xf0

/*START*/
#define  START                        5
#define  PIN_START                    PIND
#define  DDR_START                    DDRD
/*START*/
#define  RESET                        6
#define  PIN_RESET                    PIND
#define  DDR_RESET                    DDRD
/*STOP*/
#define  STOP                         7
#define  PIN_STOP                     PIND
#define  DDR_STOP                     DDRD

/*Io define here*/
#define  GET_PORT_STATUS(PIN_X,PIN)   PIN_X&(1<<(PIN))

#define  CONFIG_PORT_IN(DDR,PIN)      DDR &=~(1<<(PIN)) 

#define  CONFIG_PORT_OUT(DDR,PIN)     DDR |= (1<<(PIN))
/*获取启动引脚电平  常闭态 高电平为有效*/
#define  GET_START_PIN()      ((START_PIN&(1<<START))?1:0)
/*获取送丝引脚电平  常闭态 高电平为有效*/
#define  GET_RESET_PIN()       ((RESET_PIN&(1<<RESET))?1:0)
/*获取停止引脚电平  常开态 低电平为有效*/
#define  GET_STOP_PIN()       ((STOP_PIN&(1<<STOP))?1:0)

void INIT_IO(void);   /*io初始化*/

#endif