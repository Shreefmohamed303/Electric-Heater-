#ifndef GPIO_H_
#define GPIO_H_

#include "Std_Types.h"
#include <xc.h>
/*-------------------------- Important Defines -------------------------------*/
/* 1. GPIO Pins */
// PORTA pins consist of 6 pins from PA0-->PA5
#define GPIOA_PIN_0              0
#define GPIOA_PIN_1              1
#define GPIOA_PIN_2              2
#define GPIOA_PIN_3              3
#define GPIOA_PIN_4              4
#define GPIOA_PIN_5              5

// PORTB pins pins consist of 8 pins from PB0-->PB7
#define GPIOB_PIN_0              0
#define GPIOB_PIN_1              1
#define GPIOB_PIN_2              2
#define GPIOB_PIN_3              3
#define GPIOB_PIN_4              4
#define GPIOB_PIN_5              5
#define GPIOB_PIN_6              6
#define GPIOB_PIN_7              7

// PORTC pins pins consist of 8 pins from PC0-->PC7
#define GPIOC_PIN_0              0
#define GPIOC_PIN_1              1
#define GPIOC_PIN_2              2
#define GPIOC_PIN_3              3
#define GPIOC_PIN_4              4
#define GPIOC_PIN_5              5
#define GPIOC_PIN_6              6
#define GPIOC_PIN_7              7

// PORTD pins pins consist of 8 pins from PD0-->PD7
#define GPIOD_PIN_0              0
#define GPIOD_PIN_1              1
#define GPIOD_PIN_2              2
#define GPIOD_PIN_3              3
#define GPIOD_PIN_4              4
#define GPIOD_PIN_5              5
#define GPIOD_PIN_6              6
#define GPIOD_PIN_7              7

// PORTE pins pins consist of 3 pins from PE0-->PE2
#define GPIOE_PIN_0              0
#define GPIOE_PIN_1              1
#define GPIOE_PIN_2              2

/* 2. Register Definitions*/

// PORTA 
#define GPIO_PORTA_DATA         PORTA 
#define GPIO_PORTA_DIRECTION    TRISA
// PORTB 
#define GPIO_PORTB_DATA         PORTB 
#define GPIO_PORTB_DIRECTION    TRISB
// PORTC 
#define GPIO_PORTC_DATA         PORTC 
#define GPIO_PORTC_DIRECTION    TRISC
// PORTD 
#define GPIO_PORTD_DATA         PORTD 
#define GPIO_PORTD_DIRECTION    TRISD
// PORTE 
#define GPIO_PORTE_DATA         PORTE 
#define GPIO_PORTE_DIRECTION    TRISE

/* 3. GPIO Direction Setting*/
#define GPIO_OUT                0u 
#define GPIO_IN                 1u

/*-------------------------------- MACROS ------------------------------------*/

//Configuration for ALL GPIO_PORT pins 
#define GPIO_InitPort(GPIO_PORT_DIRECTION,DIRECTION)    ((GPIO_PORT_DIRECTION)= (DIRECTION)?(~GPIO_OUT):(GPIO_OUT))
#define GPIO_WritePort(GPIO_PORT_DATA,DATA)             ((GPIO_PORT_DATA)=(DATA))
#define GPIO_ReadPort (GPIO_PORT_DATA,DATA)             (GPIO_PORT_DATA)

//Configuration for specific pin in GPIO_PORT
#define GPIO_InitPin(GPIO_PORT_DIRECTION,PIN,DIRECTION) (DIRECTION)? (GPIO_PORT_DIRECTION |= (1<<PIN)) : (GPIO_PORT_DIRECTION &= ~(1<<PIN)) 
#define GPIO_WritePin(GPIO_PORT_DATA,PIN,DATA)          (DATA)?(GPIO_PORT_DATA |= (1<<PIN)) : (GPIO_PORT_DATA &= ~(1<<PIN))
#define GPIO_ReadPin(GPIO_PORT_DATA,PIN)                ((GPIO_PORT_DATA & (1<<PIN)) >> PIN)
#define GPIO_TogglePin(GPIO_PORT_DATA,PIN)              (GPIO_PORT_DATA^=(1<<PIN))
#endif
