
#include "EWH.h"
#include "SW.h"

void main(void) 
{
    EWH_Init();
    
    GPIO_InitPin(GPIO_PORTB_DIRECTION,GPIOB_PIN_4,GPIO_OUT);
    GPIO_InitPin(GPIO_PORTB_DIRECTION,GPIOB_PIN_5,GPIO_OUT);
    GPIO_InitPin(GPIO_PORTB_DIRECTION,GPIOB_PIN_6,GPIO_OUT);
    
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_4,OFF);
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_5,OFF);
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_6,OFF);
    while(1)
    {
        switch(EWH_Mode)
        {
            case EWH_SLEEP_MODE: 
                EWH_Sleep_Mode(); 
                break;
            case EWH_WAKE_UP_MODE: 
                EWH_WakeUP_Mode(); 
                break;
            case EWH_OPERATING_MODE: 
                EWH_Operating_Mode(); 
                break;
            case EWH_SET_TEMP_MODE: 
                EWH_SetTemp_Mode(); 
                break; 
        }
    }
    return;
}
