/*
 * File:   Display.c
 * Author: Shreef Mohamed
 *
 * Created on June 30, 2020, 2:37 AM
 */
#include "Display.h"

/*-------------------------- FUNCTION DEFINITION ----------------------------*/

static void Display_config (Display_ID ID ,tState Display_state)
{
    // configure Enable bit of  Display_1 as OUTPUT
    // Setting the State of The Display Enable Bit (ON/OFF))
    switch(ID)
    {
        case DISPLAY_1:
            GPIO_WritePin(DISPLAY_CR_DIRECTION,DISPLAY_1,GPIO_OUT); 
            GPIO_WritePin(DISPLAY_CR_PORT,DISPLAY_1,Display_state); 
            break ; 
        case DISPLAY_2: 
            GPIO_WritePin(DISPLAY_CR_DIRECTION,DISPLAY_2,GPIO_OUT); 
            GPIO_WritePin(DISPLAY_CR_PORT,DISPLAY_2,Display_state); 
        case DISPLAY_3: 
            GPIO_WritePin(DISPLAY_CR_DIRECTION,DISPLAY_3,GPIO_OUT); 
            GPIO_WritePin(DISPLAY_CR_PORT,DISPLAY_3,Display_state); 
            break ; 
        case DISPLAY_4: 
            GPIO_WritePin(DISPLAY_CR_DIRECTION,DISPLAY_4,GPIO_OUT); 
            GPIO_WritePin(DISPLAY_CR_PORT,DISPLAY_4,Display_state); 
            break ;         
    }
}
Std_ReturnType Display_Write(Display_ID ID ,Display_Number Number)
{
    // 1. Enable Display
    Display_config(ID,ON); 
    // 2. Configure Display PORT OUTPUT 
    GPIO_WritePort(DISPLAY_DR_DIRECTION,GPIO_OUT);
    // 3. check The Correction of the input Number 
    if((Number>=0) && (Number<=9))
    {
        // Write The Data Number into The Display (7-segment))
        GPIO_WritePort(DISPLAY_DR_PORT,Display_code[Number]); 
        return E_OK ; 
    }
    else
    {
        // Wrong Input Number 
        return E_NOT_OK ; 
    }
}