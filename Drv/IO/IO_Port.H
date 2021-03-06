
#ifndef IO_PORT_H
#define IO_PORT_H

/*LCD_PWM*/
#define  LCD_PWM                     0
#define  PORT_LCD_PWM                PORTD
#define  DDR_LCD_PWM                 DDRD   
 
/*LCD_LE*/
#define  LE                          0
#define  PORT_LE                     PORTC
#define  DDR_LE                      DDRC

#define  SET_LE()                   (PORT_LE |= 0X01)  
#define  CLEAR_LE()                 (PORT_LE &= 0XFE)

/*LCD_RW*/
#define  LCD_RW                      1
#define  PORT_LCD_RW                 PORTD
#define  DDR_LCD_RW                  DDRD

#define  SET_LCD_RW()                (PORT_LCD_RW |= 0X02)  
#define  CLEAR_LCD_RW()              (PORT_LCD_RW &= 0XFD)

/*LCD_RS*/
#define  LCD_RS                       2
#define  PORT_LCD_RS                  PORTD
#define  DDR_LCD_RS                   DDRD

#define  SET_LCD_RS()                (PORT_LCD_RS |= 0X04)  
#define  CLEAR_LCD_RS()              (PORT_LCD_RS &= 0XFB)

/*LCD_E*/
#define  LCD_E                        1
#define  PORT_LCD_E                   PORTC
#define  DDR_LCD_E                    DDRC

#define  SET_LCD_E()                 (PORT_LCD_E |= 0X02)  
#define  CLEAR_LCD_E()               (PORT_LCD_E &= 0XFD)

/*LCD_DB*/
#define  OUTPUT_LCD_DB(db)           ( PORTB = db )
#define  GET_LCD_DB()                 PORTB

#define  SET_LCD_DB(data)             (PORT_LCD_DB = data) 

/*LCD CS1*/
#define  LCD_CS1                       3
#define  PORT_LCD_CS1                  PORTC
#define  DDR_LCD_CS1                   DDRC

#define  SET_LCD_CS1()                 (PORT_LCD_CS1 |= 0X08)  
#define  CLEAR_LCD_CS1()               (PORT_LCD_CS1 &= 0XF7)

/*LCD CS2*/
#define  LCD_CS2                       2
#define  PORT_LCD_CS2                  PORTC
#define  DDR_LCD_CS2                   DDRC

#define  SET_LCD_CS2()                 (PORT_LCD_CS2 |= 0X04)  
#define  CLEAR_LCD_CS2()               (PORT_LCD_CS2 &= 0XFB)

/*UART TXD*/
#define  TXD                          3
#define  PORT_TXD                     PORTD
#define  DDR_TXD                      DDRD

/*UART RXD*/
#define  RXD                          4
#define  PIN_RXD                      PIND
#define  DDR_RXD                      DDRD
#define  PORT_RXD                     PORTD
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
#define  GET_START_PIN()      ((PIN_START&(1<<START))?0:1)
/*获取送丝引脚电平  常闭态 高电平为有效*/
#define  GET_RESET_PIN()      ((PIN_RESET&(1<<RESET))?0:1)
/*获取停止引脚电平  常开态 低电平为有效*/
#define  GET_STOP_PIN()       ((PIN_STOP&(1<<STOP))?0:1)

void INIT_IO(void);   /*io初始化*/

#endif