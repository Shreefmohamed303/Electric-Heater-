#ifndef EEPROM_H
#define EEPROM_H

#include "i2c.h"

/*--------------------------- Important Defines ------------------------------*/
#define EEPROM_ADDRESS_READ      0xA1
#define EEPROM_ADDRESS_WRITE     0xA0

/*-------------------------- FUNCTION DECLARATION ----------------------------*/
void EEPROM_WriteByte(uint16_t address , uint8_t data); 
void EEPROM_WritePage(uint16_t address , uint8_t *data , uint8_t Data_length); 
uint8_t EEPROM_ReadByte(uint16_t address ); 
void EEPROM_ReadPage(uint16_t address , uint8_t *data , uint8_t Data_length); 



#endif