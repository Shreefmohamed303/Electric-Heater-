#ifndef EWH_H_ 
#define EWH_H_

#include "main.h"

/*-------------------------------- MACROOS -----------------------------------*/
#define NUM_OF_EVENTS               4

#define EWH_ON_OFF_EVENT            0
#define EWH_PRESS_UP_EVENT          1
#define EWH_PRESS_DOWN_EVENT        2
#define EWH_NO_PRESS_5_SEC_EVENT    3

#define MAX_SET_TEMP                75
#define MIN_SET_TEMP                35
/*-------------------------------- TypeDefs ----------------------------------*/
typedef tState tEWH_State; 
typedef enum
{
    EWH_SLEEP_MODE,
    EWH_POWER_UP_MODE,
    EWH_SET_TEMP_MODE,
    EWH_OPERATING_MODE
}sEWH_Mode;
/*------------------------------- Variables ----------------------------------*/
tEWH_State EWH_State=OFF;
sEWH_Mode EWH_Mode=EWH_SLEEP_MODE;
uint8_t set_Temp;//=EWH_INITIAL_SET_TEMP;
uint8_t current_Temp;//=EWH_INITIAL_SET_TEMP;
tState EWH_Events[NUM_OF_EVENTS]={OFF,OFF,OFF,OFF};
uint8_t NoPress_Sec_count=0;
/*-------------------------- FUNCTION DECLARATION ----------------------------*/
void EWH_PowerUP_Mode();
void EWH_SetTemp_Mode();
void EWH_Operating_Mode(); 
void EWH_Sleep_Mode();

void EWH_EEPROM_Init();
void EWH_EEPROM_Update(uint8_t newSetTemp);
uint8_t EWH_EEPROM_Read();


#endif