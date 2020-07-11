 /********************************************************************************
 * Module : TMR1 
 *
 * File Name : TMR1.c
 *
 * Description : Source File for Timer Module that contains all Timer Interfaces Implementation
 *
 * Author : Shreef Mohamed
 *
 * Created on: July 5, 2020
 *
 ********************************************************************************/
#include "TMR1.h"

void TMR1_Init(tTMR1_Config *config)
{
    switch(config->Prescaler)
    {
        case TMR1_PRESCALER_1: 
            TMR1_SET_PRESCALER_1; 
            break;
        case TMR1_PRESCALER_2: 
            TMR1_SET_PRESCALER_2; 
            break;
        case TMR1_PRESCALER_4: 
            TMR1_SET_PRESCALER_4; 
            break;
        case TMR1_PRESCALER_8: 
            TMR1_SET_PRESCALER_8; 
            break;
    }
    
    switch(config->clkSource)
    {
        case INTERNAL_CLK_SOURCE: 
            TMR1_SET_INTERNAL_CLOCK; 
            break ;
        case EXTERNAL_CLK_SOURCE: 
            TMR1_SET_EXTERNAL_CLOCK; 
            break ; 
    }
}
void TMR1_Start()
{
    TMR1_CLEAR_FLAG;
    TMR1_ENABLE_INTERRUPT; 
    PERIHPERAL_INTERRUPT_ENABLE; 
    GLOBAL_INTERRUPT_ENABLE;
    TMR1=TMR1_PRE_LOAD_VALUE;
    TMR1_ENABLE;
}
void TMR1_Update()
{
    
}
void TMR1_Stop()
{
    TMR1_DISABLE;
}

