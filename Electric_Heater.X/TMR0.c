#include "TMR0.h"

void TMR0_Init(tTMR0_Config *config)
{
    switch(config->Prescaler)
    {
        case TMR0_PRESCALE_2: 
            TMR0_SET_PRESCALER_2; 
            break;
        case TMR0_PRESCALE_4: 
            TMR0_SET_PRESCALER_4; 
            break;
        case TMR0_PRESCALE_8: 
            TMR0_SET_PRESCALER_8; 
            break;
        case TMR0_PRESCALE_16: 
            TMR0_SET_PRESCALER_16; 
            break;
        case TMR0_PRESCALE_32: 
            TMR0_SET_PRESCALER_32; 
            break;
        case TMR0_PRESCALE_64: 
            TMR0_SET_PRESCALER_64; 
            break;
        case TMR0_PRESCALE_128: 
            TMR0_SET_PRESCALER_128; 
            break;
        case TMR0_PRESCALE_256: 
            TMR0_SET_PRESCALER_256; 
            break;
    }
    
    switch(config->clkSource)
    {
        case INTERNAL_CLK_SOURCE: 
            TMR0_SET_INTERNAL_CLOCK; 
            break ;
        case EXTERNAL_CLK_SOURCE: 
            TMR0_SET_EXTERNAL_CLOCK; 
            break ; 
    }
}
void TMR0_Start()
{
    TMR0_CLEAR_FLAG;
    TMR0_ENABLE_INTERRUPT; 
    PERIHPERAL_INTERRUPT_ENABLE; 
    GLOBAL_INTERRUPT_ENABLE; 
}
void TMR0_Update()
{
}
void TMR0_Stop()
{
    TMR0_SET_EXTERNAL_CLOCK ; 
}