 /********************************************************************************
 * Module : Port
 *
 * File Name : port.h
 *
 * Description : Header File for Digital Devices Connections with Microcontroller
 *
 * Author : Shreef Mohamed
 *
 * Created on: July 4, 2020
 *
 ********************************************************************************/
#ifndef PORT_H
#define PORT_H

#include"GPIO.h"
#include"SSD.h"
/*-------------------------- Important Defines -------------------------------*/

// 1. Electric Heater PIN Connection
#define HEATER_PORT_DIRECTION               GPIO_PORTC_DIRECTION
#define HEATER_PORT_DATA                    GPIO_PORTC_DATA
#define HEATER_PIN                          GPIOC_PIN_5

// 2. Cooler Fan PIN Connection
#define COOLER_PORT_DIRECTION               GPIO_PORTC_DIRECTION
#define COOLER_PORT_DATA                    GPIO_PORTC_DATA
#define COOLER_PIN                          GPIOC_PIN_2

// 3. UP Button PIN 
#define UP_BUTTON_PORT_DIRECTION            GPIO_PORTB_DIRECTION
#define UP_BUTTON_PORT_DATA                 GPIO_PORTB_DATA
#define UP_BUTTON_PIN                       GPIOB_PIN_2

// 3. Down Button PIN 
#define DOWN_BUTTON_PORT_DIRECTION          GPIO_PORTB_DIRECTION
#define DOWN_BUTTON_PORT_DATA               GPIO_PORTB_DATA
#define DOWN_BUTTON_PIN                     GPIOB_PIN_1

// 4. ON/OFF Button PIN 
#define ON_OFF_BUTTON_PORT_DIRECTION        GPIO_PORTB_DIRECTION
#define ON_OFF_BUTTON_PORT_DATA             GPIO_PORTB_DATA
#define ON_OFF_BUTTON_PIN                   GPIOB_PIN_0

// 5. Heating Element LED PIN 
#define HEATER_LED_PORT_DIRECTION           GPIO_PORTB_DIRECTION
#define HEATER_LED_PORT_DATA                GPIO_PORTB_DATA
#define HEATER_LED_PIN                      GPIOB_PIN_7

// 6. Electric Water Heater Display
#define EWH_SSD_1                          SSD_2
#define EWH_SSD_2                          SSD_3
#define EWH_SSD_CR_PORT                    SSD_CR_PORT
#define EWH_SSD_CR_DIRECTION               SSD_CR_DIRECTION
#define EWH_SSD_DR_PORT                    SSD_DR_PORT
#define EWH_SSD_DR_DIRECTION               SSD_DR_DIRECTION


// 7. Set Temp Address at EEPROM
#define EWH_TEMP_ADDRESS                   0x0020
#define EWH_INITIAL_SET_TEMP               60
#endif