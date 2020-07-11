 /********************************************************************************
 * Module : I2C 
 *
 * File Name : i2c.c
 *
 * Description : Source File for i2c Module that contains all i2c Interfaces Implementation
 *
 * Author : Shreef Mohamed
 *
 * Created on: July 3, 2020
 *
 ********************************************************************************/

#include "i2c.h"
#include "GPIO.h"

void I2C_Init(tI2C_Config *i2c_config)
{
    // 1. Initialize Control Registers with zero before starting Configuration
    I2C_CONTROL2_R=0x00; 
    I2C_STATUS_R=0x00;
    // 2. get I2C_Mode and configure it in the Control Register 
    I2C_CONTROL1_R |= i2c_config->Mode; 
    
#ifdef I2C_MASTER
    // 3. Configure BuadRate in Case of Master Mode 
    I2C_MASTER_BAUDRATE_R = (((_XTAL_FREQ/4)/i2c_config->BaudRate) - 1); 
#endif

#ifdef I2C_SLAVE
    // 3. Configure Slave address in Case of Slave Mode 
    I2C_SLAVE_ADDRESS_R = i2c_config->SlaveAddress ; 
    I2C_CONTROL1_R |= (1<<CKP); // Release the clock (No clock Stretching)
#endif
    
    // 4. Enable the serial port and configures the SDA and SCL pins as the serial port pins
    SSPEN=1;
    
   // 5. Disable SlewRate for Standard speed Mode 
    I2C_STATUS_R=0x80; 
    
    // 6. Set the I2C Pins into input mode (High-Impedance). SCL, SDA pins are set to input.
    GPIO_InitPin(i2C_PORT_DIRECTION,I2C_SDA_POSITION,GPIO_IN); 
    GPIO_InitPin(i2C_PORT_DIRECTION,I2C_SCL_POSITION,GPIO_IN);
    

    
    // 7. check if the Operation Mode is using Interrupt
    if(i2c_config->operationMode==INTERRUPT)
    {
          GIE = 1;    // Global Interrupt Enable 
          PEIE = 1;   // Peripheral Interrupt Enable 
          SSPIF = 0;  // Clearing peripheral interrupt Flag bit 
          SSPIE = 1;  // Enable I2C Interrupt
    }
}

void I2C_Wait_IDLE()
{
    /* polling till indicating that I2C is in IDLE State 
     * ORing R/W bit with SEN, RSEN, PEN, RCEN or ACKEN will indicate that I2C in IDLE State
     */
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
    
}
void I2C_Master_Send_Start()
{
    // Wait till IDLE State
    I2C_Wait_IDLE(); 
    SEN=1 ; 
}
void I2C_Master_Send_Stop()
{
    // Wait till IDLE State
    I2C_Wait_IDLE(); 
    PEN=1 ; 
}
void I2C_Master_Send_RepeatedStart()
{
    // Wait till IDLE State
    I2C_Wait_IDLE(); 
    RSEN=1 ; 
}
void I2C_Master_Send_ACK()
{
    // Wait till IDLE State
    I2C_Wait_IDLE();
    // send ACK is used for Master Receiver Mode 
    ACKDT=0; // 0 -> ACK, 1 -> NACK
    ACKEN=1; // Send ACK Signal
}
void I2C_Master_Send_NACK()
{
    // Wait till IDLE State
    I2C_Wait_IDLE();
    // send ACK is used for Master Receiver Mode 
    ACKDT=1; // 0 -> ACK, 1 -> NACK
    ACKEN=1; // Send ACK Signal
}
uint8_t I2C_Master_WriteByte(uint8_t Data)
{
    // Wait till IDLE State
    I2C_Wait_IDLE();
    I2C_BUFFER_R=Data;
    while(!SSPIF);
    SSPIF=0;
    I2C_Wait_IDLE();
    return ACKSTAT; // return The ACK state to ensure success of the Transmission
}
uint8_t I2C_Master_ReadByte(tI2C_ReadingState Read_State)
{
    // Only for Master Receiver Mode 
    uint8_t data;
    // Wait till IDLE State
    I2C_Wait_IDLE();
    RCEN=1; // Enable I2C Receiver 
    I2C_Wait_IDLE(); // Wait till IDLE State
    data=I2C_BUFFER_R;  // Read data from buffer 
    //check Reading_state Either continue_Reading--> Send_ACK , Stop_Reading-->Send_NACK
    if(Read_State==I2C_STOP_READING)
        I2C_Master_Send_NACK();
    else
        I2C_Master_Send_ACK();
    
    return I2C_BUFFER_R ;
}

