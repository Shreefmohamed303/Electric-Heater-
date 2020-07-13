 /********************************************************************************
 * Module : Switch
 *
 * File Name : SW.h
 *
 * Description : Header File for Switches that contain all Switches interface
 *
 * Author : Shreef Mohamed
 *
 * Created on: July 4, 2020
 *
 ********************************************************************************/

#ifndef SW_H
#define SW_H

#include "GPIO.h"
#include "Port.h"
#include "config.h"
/*-------------------------- Important Defines -------------------------------*/
#define NUM_OF_SWs              3
#define UP_BUTTON_IS_PRESSED    (!GPIO_ReadPin(UP_BUTTON_PORT_DATA,UP_BUTTON_PIN)==SW_PRESSED)
#define DOWN_BUTTON_IS_PRESSED  (!GPIO_ReadPin(DOWN_BUTTON_PORT_DATA,DOWN_BUTTON_PIN)==SW_PRESSED)
/*-------------------------------- TypeDefs ----------------------------------*/
typedef enum 
{
    ON_OFF_BUTTON,
    UP_BUTTON, 
    DOWN_BUTTON,
}tSW;

typedef enum 
{
    SW_REALESED=0,
    SW_PRESSED=1
}tSW_State;

typedef struct 
{
    tSW_State ON_OFF_Button_State; 
    tSW_State UP_Button_State;
    tSW_State DOWN_Button_State;
}tSW_StateControl; 


/*------------------------------- Variables ----------------------------------*/
tSW_StateControl SW_StateControl={SW_REALESED,SW_REALESED,SW_REALESED};
tSW_State SW_State[NUM_OF_SWs]={SW_REALESED,SW_REALESED,SW_REALESED};
/*-------------------------- FUNCTION DECLARATION ----------------------------*/
void SW_Init(void);
void SW_Update(void); 
void SW_SetState(tSW SW_Name ,tSW_State state);
tSW_State SW_GetState(tSW SW_Name);

#endif