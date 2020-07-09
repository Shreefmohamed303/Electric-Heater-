
#include "EWH.h"
#include "SW.h"

void main(void) 
{

    tTMR1_Config TMR1_cfg; 
    TMR1_cfg.Prescaler=TMR1_PRESCALER_4; 
    TMR1_cfg.clkSource=EXTERNAL_CLK_SOURCE; 
 
    TMR1_Init(&TMR1_cfg); 
    //TMR1_Start(); 
    tADC_Config adc_config; 
    adc_config.alignment=RIGHT; 
    adc_config.channel=ADC2; 
    adc_config.clk=FOSC_8; 
    adc_config.mode= POLLING_MODE; 
    
    tI2C_Config i2c_config; 
    i2c_config.BaudRate=100000; 
    i2c_config.Mode=Master_Mode; 
    i2c_config.operationMode=POLLING;

    
    ADC_Init(&adc_config);
    DD_Init();
    SW_Init();
    I2C_Init(&i2c_config);
    EWH_EEPROM_Init();
    
    GPIO_InitPin(GPIO_PORTB_DIRECTION,GPIOB_PIN_4,GPIO_OUT);
    GPIO_InitPin(GPIO_PORTB_DIRECTION,GPIOB_PIN_5,GPIO_OUT);
    GPIO_InitPin(GPIO_PORTB_DIRECTION,GPIOB_PIN_6,GPIO_OUT);
    
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_4,OFF);
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_5,OFF);
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_6,OFF);
    while(1)
    {
        switch(EWH_Mode)
        {
            case EWH_SLEEP_MODE: 
                EWH_Sleep_Mode(); 
                break;
            case EWH_WAKE_UP_MODE: 
                EWH_WakeUP_Mode(); 
                break;
            case EWH_OPERATING_MODE: 
                EWH_Operating_Mode(); 
                break;
            case EWH_SET_TEMP_MODE: 
                EWH_SetTemp_Mode(); 
                break; 
        }
    }
    return;
}
