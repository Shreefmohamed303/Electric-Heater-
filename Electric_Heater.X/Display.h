#ifndef DISPLAY_H_
#define DISPLAY_H_

#include"GPIO.h"

/*-------------------------- Important Defines -------------------------------*/
#define DISPLAY_CONTROL_PIN_1       GPIOA_PIN_2   
#define DISPLAY_CONTROL_PIN_2       GPIOA_PIN_3 
#define DISPLAY_CONTROL_PIN_3       GPIOA_PIN_4   
#define DISPLAY_CONTROL_PIN_4       GPIOA_PIN_5 

#define DISPLAY_1                   GPIOA_PIN_2          // Display_1 Control Pin 
#define DISPLAY_2                   GPIOA_PIN_3          // Display_2 Control Pin  
#define DISPLAY_3                   GPIOA_PIN_4          // Display_3 Control Pin  
#define DISPLAY_4                   GPIOA_PIN_5          // Display_4 Control Pin 

#define DISPLAY_CR_PORT             GPIO_PORTA_DATA      // Display Control PORT Register
#define DISPLAY_CR_DIRECTION        GPIO_PORTA_DIRECTION // Display Control Direction Register 

#define DISPLAY_DR_PORT             GPIO_PORTD_DATA      // Display Data Port Register 
#define DISPLAY_DR_DIRECTION        GPIO_PORTD_DIRECTION // Display Data Direction Register 
/*-------------------------------- Variables ------------------------------------*/
uint8_t Display_code[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
/*-------------------------------- TypeDefs ----------------------------------*/
typedef uint8_t Display_ID;
typedef uint8_t Display_Number;
/*-------------------------- FUNCTION DECLARATION ----------------------------*/
static void Display_config (Display_ID ID ,tState Display_state); 
Std_ReturnType Display_Write(Display_ID ID ,Display_Number Number); 
void Heater_Display(uint16_t temp);
#endif  