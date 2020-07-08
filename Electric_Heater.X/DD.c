 /********************************************************************************
 * File Name : DD.c
 *
 * Description : Source File for DD Module that contain all Digital output Devices interface
 *
 * Author : Shreef Mohamed
 *
 * Created on: July 4, 2020
 *
 ********************************************************************************/

#include "DD.h"
/*-------------------------- FUNCTION DECLARATION ----------------------------*/
void DD_Init(void)
{
    // 1. Initialize Direction of The Digital Devices
    GPIO_InitPin(HEATER_PORT_DIRECTION,HEATER_PIN,GPIO_OUT); 
    GPIO_InitPin(COOLER_PORT_DIRECTION,COOLER_PIN,GPIO_OUT);
    GPIO_InitPin(HEATER_LED_PORT_DIRECTION,HEATER_LED_PIN,GPIO_OUT);
    
    // 2. Initialize Output State of The Digital Devices
    GPIO_WritePin(HEATER_PORT_DATA,HEATER_PIN,OFF); 
    GPIO_WritePin(COOLER_PORT_DATA,COOLER_PIN,OFF);
    GPIO_WritePin(HEATER_LED_PORT_DATA,HEATER_LED_PIN,OFF);

}


void DD_SetState(tDD device ,tState state)
{
    switch(device)
    {
        case HEATER: 
            GPIO_WritePin(HEATER_PORT_DATA,HEATER_PIN,state);
            Devices_State.HEATER_State=state;
            break;
        case COOLER: 
            GPIO_WritePin(COOLER_PORT_DATA,COOLER_PIN,state);
            Devices_State.COOLER_State=state;
            break;
        case HEATER_LED: 
            GPIO_WritePin(HEATER_LED_PORT_DATA,HEATER_LED_PIN,state);
            Devices_State.HEATER_LED_State=state;
            break;
            
        default: 
            break ; 
    }
}
tState DD_GetState(tDD device)
{
    switch(device)
    {
        case HEATER: 
            return GPIO_ReadPin(HEATER_PORT_DATA,HEATER_PIN); 
            break;
        case COOLER: 
            return GPIO_ReadPin(COOLER_PORT_DATA,COOLER_PIN); 
            break;
        case HEATER_LED: 
            return GPIO_ReadPin(HEATER_LED_PORT_DATA,HEATER_LED_PIN); 
            break;
            
        default: 
            break; 
    }
}

void EWH_SSD_ON()
{
    SSD_ON(EWH_SSD_1); 
    SSD_ON(EWH_SSD_2);
}

void EWH_SSD_OFF()
{
    SSD_OFF(EWH_SSD_1); 
    SSD_OFF(EWH_SSD_2);
}

void EWH_SSD_Update(uint16_t temp)
{
    SSD_OFF(EWH_SSD_1); 
    SSD_Write(EWH_SSD_2,temp%10); 
    __delay_ms(60);
    SSD_OFF(EWH_SSD_2); 
    SSD_Write(EWH_SSD_1,(uint8_t)temp/10); 
}