#include "main.h"


void main(void) 
{

    tTMR1_Config TMR1_cfg; 
    TMR1_cfg.Prescaler=TMR1_PRESCALER_8; 
    TMR1_cfg.clkSource=EXTERNAL_CLK_SOURCE; 
 
    TMR1_Init(&TMR1_cfg); 
    TMR1_Start(); 
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

//        __delay_ms(200);
    }
    return;
}

void __interrupt() Timer()
{
    static uint8_t count =0; 
   if (TMR1IF)
   {
      count++;
      if(count==2)
      {
        // Put Your Second Event Here
        uint16_t Reading = ADC_ReadChannel(ADC2);
        Heater_Display(Reading*0.488);
        // Clear The Global Counter
        count = 0;
      }
      TMR1IF = 0; // Clear The Flag Bit
      TMR1=TMR1_PRE_LOAD_VALUE;
   }
}