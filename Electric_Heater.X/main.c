#include "config.h"
#include "GPIO.h"
#include "Display.h"
#include "i2c.h"
#include "EEPROM.h"
#include "adc.h"
#include "DD.h"

void main(void) 
{
 
    tADC_Config adc_config; 
    adc_config.alignment=RIGHT; 
    adc_config.channel=ADC2; 
    adc_config.clk=FOSC_8; 
    adc_config.mode= POLLING_MODE; 
    
    ADC_Init(&adc_config);
    DD_Init();
    DD_SetState(HEATER,ON); 

    while(1)
    {
       uint16_t Reading = ADC_ReadChannel(ADC2);
        Heater_Display(Reading*0.488);
        __delay_ms(200);
    }
    return;
}

