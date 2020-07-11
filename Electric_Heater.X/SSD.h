 /********************************************************************************
 * Module : SSD (Seven Segment Display)
 *
 * File Name : SSD.h
 *
 * Description : Header File for SSD Module that contains all SSD Interfaces
 *
 * Author : Shreef Mohamed
 *
 * Created on: July 3, 2020
 *
 ********************************************************************************/
#ifndef SSD_H_
#define SSD_H_

#include"GPIO.h"

/*-------------------------- Important Defines -------------------------------*/
#define SSD_CONTROL_PIN_1       GPIOA_PIN_2   
#define SSD_CONTROL_PIN_2       GPIOA_PIN_3 
#define SSD_CONTROL_PIN_3       GPIOA_PIN_4   
#define SSD_CONTROL_PIN_4       GPIOA_PIN_5 

#define SSD_1                   GPIOA_PIN_2             // Display_1 Control Pin 
#define SSD_2                   GPIOA_PIN_3             // Display_2 Control Pin  
#define SSD_3                   GPIOA_PIN_4             // Display_3 Control Pin  
#define SSD_4                   GPIOA_PIN_5             // Display_4 Control Pin 

#define SSD_CR_PORT             GPIO_PORTA_DATA         // Display Control PORT Register
#define SSD_CR_DIRECTION        GPIO_PORTA_DIRECTION    // Display Control Direction Register 

#define SSD_DR_PORT             GPIO_PORTD_DATA         // Display Data Port Register 
#define SSD_DR_DIRECTION        GPIO_PORTD_DIRECTION    // Display Data Direction Register 
/*-------------------------------- Variables ------------------------------------*/
uint8_t SSD_code[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
/*-------------------------------- TypeDefs ----------------------------------*/
typedef uint8_t SSD_ID;
typedef uint8_t SSD_Number;
/*-------------------------- FUNCTION DECLARATION ----------------------------*/
static void SSD_config (SSD_ID ID ,tState Display_state); 
Std_ReturnType SSD_Write(SSD_ID ID ,SSD_Number Number); 
void Heater_Display(uint16_t temp);
void SSD_OFF(SSD_ID ID); 
void SSD_ON(SSD_ID ID); 
#endif  