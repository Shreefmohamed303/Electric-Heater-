#ifndef I2C_H 
#define I2C_H

#include "config.h"
#include "Std_Types.h"

/*--------------------------- Important Defines ------------------------------*/

#define I2C_MASTER
#define I2C_SCL_POSITION            3 
#define I2C_SDA_POSITION            4
#define I2C_ENABLE_POSITION         5

// Register Definitions
#define I2C_PORT_DATA               PORTC
#define i2C_PORT_DIRECTION          TRISC

#define I2C_BUFFER_R                SSPBUF
#define I2C_CONTROL1_R              SSPCON
#define I2C_CONTROL2_R              SSPCON2
#define I2C_STATUS_R                SSPSTAT
#define I2C_SLAVE_ADDRESS_R         SSPADD
#define I2C_MASTER_BAUDRATE_R       SSPADD


/*-------------------------------- TypeDefs ----------------------------------*/
typedef enum 
{
    Slave_7bit_Mode=0b0110,
    Slave_10bit_Mode=0b0111,
    Master_Mode=0b1000,
    Frimware_Master_Mode=0b1011,         
    Slave_7bit_INT_Mode=0b1110,
    Slave_10bit_INT_Mode=0b1111,
}tI2C_Mode;
typedef enum 
{
    I2C_IDLE=1,
    I2C_BUSY=0        
}tI2C_Satate;

typedef enum 
{
    I2C_CONTINUE_READING=0, //Continue Reading --> Send ACK
    I2C_STOP_READING=1 // Stop Reading --> Send NACK
}tI2C_ReadingState;

typedef enum 
{
    INTERRUPT=1,
    POLLING=0
}tI2C_OperationMode;

typedef struct 
{
    tI2C_Mode Mode; 
#ifdef I2C_SLAVE
    uint8_t SlaveAddress;
#endif
#ifdef I2C_MASTER 
    uint64_t BaudRate; 
#endif
     
    tI2C_OperationMode operationMode;
}tI2C_Config;


/*-------------------------- FUNCTION DECLARATION ----------------------------*/
void I2C_Init(tI2C_Config *i2c_config); 
void I2C_Master_Send_Start(); 
void I2C_Master_Send_Stop(); 
void I2C_Master_Send_RepeatedStart();
void I2C_Master_Send_ACK(); 
void I2C_Master_Send_NACK(); 
uint8_t I2C_Master_WriteByte(uint8_t Data); 
uint8_t I2C_Master_ReadByte(tI2C_ReadingState Read_State);
void I2C_Wait_IDLE(); 



#endif

