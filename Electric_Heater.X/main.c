
#include "EWH.h"
#include "SW.h"

    uint16_t Reading , temp; 
void main(void) 
{

    tTMR1_Config TMR1_cfg; 
    TMR1_cfg.Prescaler=TMR1_PRESCALER_8; 
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
            case EWH_POWER_UP_MODE: 
                EWH_PowerUP_Mode(); 
                break;
            case EWH_OPERATING_MODE: 
                EWH_Operating_Mode(); 
                break;
            case EWH_SET_TEMP_MODE: 
                EWH_SetTemp_Mode(); 
                break; 
        }
        
//        if(EWH_Events[EWH_PRESS_UP_EVENT])
//        {
//            EWH_Events[EWH_PRESS_UP_EVENT]=0;
//            EWH_SetTemp_Mode(); 
//        }
//        else if(EWH_Events[EWH_PRESS_DOWN_EVENT])
//        {
//            EWH_Events[EWH_PRESS_DOWN_EVENT]=0;
//            EWH_SetTemp_Mode();
//        }
//        else if(EWH_Events[EWH_ON_OFF_EVENT])
//        {
//            EWH_Events[EWH_ON_OFF_EVENT]=0;
//            EWH_PowerUP_Mode();
//        }
//        else if(EWH_Events[EWH_NO_PRESS_5_SEC_EVENT])
//        {
//            EWH_Events[EWH_NO_PRESS_5_SEC_EVENT]=0;
//            EWH_Operating_Mode();
//        }
        
        
        
        
        
//        if(UP_BUTTON_IS_PRESSED || DOWN_BUTTON_IS_PRESSED)
//            GPIO_TogglePin(HEATER_LED_PORT_DATA,HEATER_LED_PIN);
//        __delay_ms(500);
//        uint16_t Reading = ADC_ReadChannel(ADC2);
//        current_Temp=Reading*0.488;
//        Heater_Display(current_Temp);

    }
    return;
}
