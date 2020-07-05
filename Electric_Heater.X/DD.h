 /********************************************************************************
 * Module : DD (Digital Devices)
 *
 * File Name : DD.h
 *
 * Description : Header File for DD Module that contain all Digital Devices interface
 *
 * Author : Shreef Mohamed
 *
 * Created on: July 4, 2020
 *
 ********************************************************************************/

#ifndef DD_H
#define DD_H

#include "GPIO.h"
#include "Port.h"
/*-------------------------------- TypeDefs ----------------------------------*/
typedef enum 
{
    ON_OFF_BUTTON,
    UP_BUTTON, 
    DOWN_BUTTON,
    HEATER,
    COOLER,
    HEATER_LED
}tDD;

typedef struct 
{
    tState HEATER_State; 
    tState HEATER_LED_State;
    tState COOLER_State; 
}tDD_State;

/*------------------------------- Variables ----------------------------------*/
tDD_State Devices_State={OFF,OFF,OFF};
/*-------------------------- FUNCTION DECLARATION ----------------------------*/
void DD_Init(void);
void DD_SetState(tDD device ,tState state);
tState DD_GetState(tDD device);

#endif