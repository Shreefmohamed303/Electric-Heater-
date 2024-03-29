 /********************************************************************************
 * Module : SSD (Seven Segment Display)
 *
 * File Name : SSD.c
 *
 * Description : Source File for SSD Module that contains all SSD Interfaces Implementation
 *
 * Author : Shreef Mohamed
 *
 * Created on: July 3, 2020
 *
 ********************************************************************************/
#include "SSD.h"
#include "config.h"
/*-------------------------- FUNCTION DEFINITION ----------------------------*/

static void SSD_config (SSD_ID ID ,tState SSD_state)
{
    // configure Enable bit of  Display_1 as OUTPUT
    // Setting the State of The Display Enable Bit (ON/OFF))
    switch(ID)
    {
        case SSD_1:
            GPIO_WritePin(SSD_CR_DIRECTION,SSD_1,GPIO_OUT); 
            GPIO_WritePin(SSD_CR_PORT,SSD_1,SSD_state); 
            break; 
        case SSD_2: 
            GPIO_WritePin(SSD_CR_DIRECTION,SSD_2,GPIO_OUT); 
            GPIO_WritePin(SSD_CR_PORT,SSD_2,SSD_state); 
            break;
        case SSD_3: 
            GPIO_WritePin(SSD_CR_DIRECTION,SSD_3,GPIO_OUT); 
            GPIO_WritePin(SSD_CR_PORT,SSD_3,SSD_state); 
            break ; 
        case SSD_4: 
            GPIO_WritePin(SSD_CR_DIRECTION,SSD_4,GPIO_OUT); 
            GPIO_WritePin(SSD_CR_PORT,SSD_4,SSD_state); 
            break ;         
    }
}
Std_ReturnType SSD_Write(SSD_ID ID ,SSD_Number Number)
{
    // 1. Enable Display
    SSD_config(ID,ON); 
    // 2. Configure Display PORT OUTPUT 
    GPIO_WritePort(SSD_DR_DIRECTION,GPIO_OUT);
    // 3. check The Correction of the input Number 
    if((Number>=0) && (Number<=9))
    {
        // Write The Data Number into The Display (7-segment))
        GPIO_WritePort(SSD_DR_PORT,SSD_code[Number]); 
        return E_OK ; 
    }
    else
    {
        // Wrong Input Number 
        return E_NOT_OK ; 
    }
}

void SSD_OFF (SSD_ID ID)
{
    SSD_config(ID,OFF);
}

void SSD_ON (SSD_ID ID)
{
    SSD_config(ID,ON);
}