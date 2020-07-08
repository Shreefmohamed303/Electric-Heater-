 /********************************************************************************
 * File Name : SW.c
 *
 * Description : Source File for Switches that contain all Switches interface
 *
 * Author : Shreef Mohamed
 *
 * Created on: July 4, 2020
 *
 ********************************************************************************/

#include "SW.h"


/*-------------------------- FUNCTION DEFINITION ----------------------------*/
void SW_Init(void)
{
    // 1. Initialize Direction of All Switches
    GPIO_InitPin(UP_BUTTON_PORT_DIRECTION,UP_BUTTON_PIN,GPIO_IN);
    GPIO_InitPin(DOWN_BUTTON_PORT_DIRECTION,DOWN_BUTTON_PIN,GPIO_IN);
    GPIO_InitPin(ON_OFF_BUTTON_PORT_DIRECTION,ON_OFF_BUTTON_PIN,GPIO_IN);
    
    // 2. Configure ON/OFF_Button with interrupt on falling Edge 
    INTEDG=0; 
    INTE=1; // Enable interrupt on Pin 0 on Port B RB0
    GIE=1;  // Enable Global interrupt 
}
void SW_SetState(tSW SW_Name ,tSW_State state)
{
    switch(SW_Name)
    {
        case ON_OFF_BUTTON: 
            SW_State[ON_OFF_BUTTON]=state; 
            SW_StateControl.ON_OFF_Button_State= state;
            break;
        case UP_BUTTON: 
            SW_State[UP_BUTTON]=state; 
            break;
        case DOWN_BUTTON: 
            SW_State[DOWN_BUTTON]=state; 
            break; 
    }
}
tSW_State SW_GetState(tSW SW_Name)
{
    switch(SW_Name)
    {
        case ON_OFF_BUTTON: 
            return SW_State[ON_OFF_BUTTON]; 
            break;
        case UP_BUTTON: 
            return SW_State[UP_BUTTON]; 
            break;
        case DOWN_BUTTON: 
            return SW_State[DOWN_BUTTON]; 
            break; 
    }
}

void SW_Update(void)
{
    SW_State[DOWN_BUTTON]  =GPIO_ReadPin(DOWN_BUTTON_PORT_DATA,DOWN_BUTTON_PIN); 
    SW_State[UP_BUTTON]    =GPIO_ReadPin(UP_BUTTON_PORT_DATA,UP_BUTTON_PIN);
    SW_State[ON_OFF_BUTTON]=GPIO_ReadPin(ON_OFF_BUTTON_PORT_DATA,ON_OFF_BUTTON_PIN);
}