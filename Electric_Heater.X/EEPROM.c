#include "EEPROM.h"

/*-------------------------- FUNCTION DEFINITION ----------------------------*/
void EEPROM_WriteByte(uint16_t address , uint8_t data)
{
  I2C_Master_Send_Start();
  // Wait Until EEPROM Is IDLE
  
  while(I2C_Master_WriteByte(EEPROM_ADDRESS_WRITE | ((address & 0x0700)>>7)) )
        I2C_Master_Send_RepeatedStart();
  
  //I2C_Master_WriteByte(address>>8);
  I2C_Master_WriteByte((uint8_t)address);
  I2C_Master_WriteByte(data);
  I2C_Master_Send_Stop();
}


void EEPROM_WritePage(uint16_t address , uint8_t *data , uint8_t Data_length)
{
  I2C_Master_Send_Start();
  
  // Wait Until EEPROM Is IDLE
  while(I2C_Master_WriteByte(EEPROM_ADDRESS_WRITE | ((address & 0x0700)>>7)) )
       I2C_Master_Send_RepeatedStart();
  
  //I2C_Master_WriteByte(address>>8);
  I2C_Master_WriteByte((uint8_t)address);
  for(uint8_t i=0 ; i<Data_length ; i++)
  {
      I2C_Master_WriteByte(data[i]);
  }
  I2C_Master_Send_Stop();
    
}
uint8_t EEPROM_ReadByte(uint16_t address )
{
    uint8_t data; 
    
    I2C_Master_Send_Start(); 
    
    while(I2C_Master_WriteByte(EEPROM_ADDRESS_WRITE | ((address & 0x0700)>>7)) )
        I2C_Master_Send_RepeatedStart(); 
    
    //I2C_Master_WriteByte(address>>8); 
    I2C_Master_WriteByte((uint8_t)address);
    
    I2C_Master_Send_RepeatedStart(); 
    I2C_Master_WriteByte(EEPROM_ADDRESS_READ | ((address & 0x0700)>>7)); 
    
    data=I2C_Master_ReadByte(I2C_STOP_READING); 
    I2C_Master_Send_Stop(); 
    
    return data;
}
void EEPROM_ReadPage(uint16_t address , uint8_t *data , uint8_t Data_length)
{
    I2C_Master_Send_Start(); 
    
    while(I2C_Master_WriteByte(EEPROM_ADDRESS_WRITE | ((address & 0x0700)>>7)) ) 
        I2C_Master_Send_RepeatedStart(); 
    
    //I2C_Master_WriteByte(address>>8); 
    I2C_Master_WriteByte((uint8_t)address);
    
    I2C_Master_Send_RepeatedStart(); 
    I2C_Master_WriteByte(EEPROM_ADDRESS_READ | ((address & 0x0700)>>7) ); 
    
    for(uint8_t i=0 ; i<Data_length-1 ;i++)
    {
        data[i]=I2C_Master_ReadByte(I2C_CONTINUE_READING); 
    }
    data[Data_length-1]=I2C_Master_ReadByte(I2C_STOP_READING); 
    I2C_Master_Send_Stop(); 
}

