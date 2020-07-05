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

/*-------------------------- Important Defines -------------------------------*/

// 1. Electric Heater PIN Connection
#define HEATER_PORT_DIRECTION               GPIO_PORTC_DIRECTION
#define HEATER_PORT_DATA                    GPIO_PORTC_DIRECTION
#define HEATER_PIN                          GPIOC_PIN_5

// 2. Cooler Fan PIN Connection
#define COOLER_PORT_DIRECTION               GPIO_PORTC_DIRECTION
#define COOLER_PORT_DATA                    GPIO_PORTC_DIRECTION
#define COOLER_PIN                          GPIOC_PIN_2

// 3. UP Button PIN 
#define UP_BUTTON_PORT_DIRECTION            GPIO_PORTB_DIRECTION
#define UP_BUTTON_PORT_DATA                 GPIO_PORTB_DIRECTION
#define UP_BUTTON_PIN                       GPIOB_PIN_2

// 3. Down Button PIN 
#define DOWN_BUTTON_PORT_DIRECTION          GPIO_PORTB_DIRECTION
#define DOWN_BUTTON_PORT_DATA               GPIO_PORTB_DIRECTION
#define DOWN_BUTTON_PIN                     GPIOB_PIN_0

// 4. ON/OFF Button PIN 
#define ON_OFF_BUTTON_PORT_DIRECTION        GPIO_PORTB_DIRECTION
#define ON_OFF_BUTTON_PORT_DATA             GPIO_PORTB_DIRECTION
#define ON_OFF_BUTTON_PIN                   GPIOB_PIN_1

// 5. Heating Element LED PIN 
#define HEATER_LED_PORT_DIRECTION           GPIO_PORTB_DIRECTION
#define HEATER_LED_PORT_DATA                GPIO_PORTB_DIRECTION
#define HEATER_LED_PIN                      GPIOB_PIN_7

#endif