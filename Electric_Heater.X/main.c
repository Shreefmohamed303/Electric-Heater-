#include "EWH.h"

void main(void) 
{
    EWH_Init();
    
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
