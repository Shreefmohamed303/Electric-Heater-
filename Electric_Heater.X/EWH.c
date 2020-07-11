#include "EWH.h"
#include "SW.h"

/*------------------------- States Function Definition -----------------------*/
void EWH_Sleep_Mode()
{
        /*  EWH is all OFF  */
    // Display OFF 
    EWH_SSD_OFF();
    // Heater Element OFF
    DD_SetState(HEATER,OFF); 
    // Cooler Element OFF
    DD_SetState(COOLER,OFF); 
    // Heater_Led OFF
    DD_SetState(HEATER_LED,OFF);
    // Stop timer 
    TMR1_Stop();

    EWH_Events[EWH_ON_OFF_EVENT]=0;
    EWH_Events[EWH_PRESS_DOWN_EVENT]=0;
    EWH_Events[EWH_PRESS_UP_EVENT]=0;
    EWH_Events[EWH_NO_PRESS_5_SEC_EVENT]=0;
    
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_4,OFF);
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_5,OFF);
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_6,OFF);
    
    //SLEEP();
}
void EWH_WakeUP_Mode()
{
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_4,ON);
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_5,OFF);
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_6,OFF);
   
    EWH_Events[EWH_ON_OFF_EVENT]=0;
    EWH_Events[EWH_PRESS_DOWN_EVENT]=0;
    EWH_Events[EWH_PRESS_UP_EVENT]=0;
    EWH_Events[EWH_NO_PRESS_5_SEC_EVENT]=0;
    
    /* ON/OFF Button is Released */
    EWH_Events[EWH_ON_OFF_EVENT]=0;
    
    //EWH_Mode=EWH_WAKE_UP_MODE;

    // The Set Temp should be retrieved form external EEPROM
    set_Temp = EWH_EEPROM_Read();

    // Turn On The Heater_Display and Display the temp from EEPROM
    EWH_SSD_Update(set_Temp);
    
    if(UP_BUTTON_IS_PRESSED)
    {
        __delay_ms(50); 
        if(UP_BUTTON_IS_PRESSED)
        {
            EWH_Events[EWH_PRESS_UP_EVENT]=1;
            NoPress_Sec_count=0;
            EWH_Mode=EWH_SET_TEMP_MODE; 
        }
    }
    else if (DOWN_BUTTON_IS_PRESSED)
    {
        __delay_ms(50); 
        if(DOWN_BUTTON_IS_PRESSED)
        {
            EWH_Events[EWH_PRESS_DOWN_EVENT]=1;
            NoPress_Sec_count=0;
            EWH_Mode=EWH_SET_TEMP_MODE;
        }
    }
}
void EWH_SetTemp_Mode()
{
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_4,OFF);
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_5,ON);
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_6,OFF);
    
    EWH_Events[EWH_ON_OFF_EVENT]=0;
    EWH_Events[EWH_PRESS_DOWN_EVENT]=0;
    EWH_Events[EWH_PRESS_UP_EVENT]=0;
    EWH_Events[EWH_NO_PRESS_5_SEC_EVENT]=0;
    

//    // 1. get The set Temp From EEPROM
//    set_Temp = EWH_EEPROM_Read();
    
    // 2. Enable Timer 
    TMR1_Start();
    // 3. clear "No Press Second Count"
    NoPress_Sec_count=0;
    // 4. Turn oFF Heater cooler and Heating Element Led while setting Temperature
    DD_SetState(HEATER,OFF);
    DD_SetState(COOLER,OFF);
    DD_SetState(HEATER_LED,OFF);
    // 5. SSD show the set Temp 
    EWH_SSD_Update(set_Temp);
    while(1)
    {
        if(UP_BUTTON_IS_PRESSED && set_Temp<MAX_SET_TEMP)
        {
            __delay_ms(50); 
            if(UP_BUTTON_IS_PRESSED)
            {
                set_Temp+=5; 
                NoPress_Sec_count=0;
            }
        }
        else if (DOWN_BUTTON_IS_PRESSED && set_Temp>MIN_SET_TEMP)
        {
            __delay_ms(50); 
            if(DOWN_BUTTON_IS_PRESSED)
            {
                set_Temp-=5; 
                NoPress_Sec_count=0;
            }
        }
        //  SSD show the current set Temp with Blinking Every 1 sec
        if(SSD_Blink_flag)
        {
            EWH_SSD_Update(set_Temp);
        }
        else
        {
            EWH_SSD_OFF();
        }
        if(EWH_Events[EWH_NO_PRESS_5_SEC_EVENT] || EWH_Events[EWH_ON_OFF_EVENT])
        {
            // Save The Last Set Temp in EEPROM
            EWH_EEPROM_Update(set_Temp);
            // Leave Set temp Mode and Go to Operating Mode 
            break ;
        }

    }

    if(EWH_Events[EWH_NO_PRESS_5_SEC_EVENT])
    {
        EWH_Events[EWH_NO_PRESS_5_SEC_EVENT]=0;
        // Go to Operating Mode
        //EWH_Operating_Mode();
        EWH_Mode=EWH_OPERATING_MODE;
    }

}
void EWH_Operating_Mode()
{
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_4,OFF);
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_5,OFF);
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_6,ON);
    
    EWH_Events[EWH_ON_OFF_EVENT]=0;
    EWH_Events[EWH_PRESS_DOWN_EVENT]=0;
    EWH_Events[EWH_PRESS_UP_EVENT]=0;
    EWH_Events[EWH_NO_PRESS_5_SEC_EVENT]=0;
    
    EWH_Mode=EWH_OPERATING_MODE;
    // 1. Enable Temp Sensing Timer 
    TMR1_Start();
    // 2. Enable ADC 
    while(1)
    {
        EWH_SSD_Update(current_Temp);
        ReadingBuffer[TempReading_count]=current_Temp;
        TempReading_count++;
        TempReading_count= TempReading_count%TEMP_READING_BUFFER_LENGTH;
        if(TempReading_count==9)
        {
            TempavgReading= EWH_getAvrgTempReading(ReadingBuffer,TEMP_READING_BUFFER_LENGTH);
            ReadingBufferFull=TRUE;
        }
        if(ReadingBufferFull)
        {
            if(TempavgReading>=(set_Temp+5))
            {
                DD_SetState(HEATER,OFF); 
                DD_SetState(COOLER,ON); 
            }
            else if(TempavgReading<=(set_Temp-5))
            {
                DD_SetState(HEATER,ON); 
                DD_SetState(COOLER,OFF);       
            }
        }
        if(UP_BUTTON_IS_PRESSED || DOWN_BUTTON_IS_PRESSED )
        {
            __delay_ms(50);
           if(UP_BUTTON_IS_PRESSED || DOWN_BUTTON_IS_PRESSED )
           {
            EWH_Events[EWH_PRESS_DOWN_EVENT]=1;
            EWH_Events[EWH_PRESS_UP_EVENT]=1;
            break;
           }
        }
        if(EWH_Events[EWH_ON_OFF_EVENT]==1)
            break;
    
         EWH_SSD_Update(current_Temp);    
    }
    
    if(EWH_Events[EWH_PRESS_UP_EVENT] )
        {
            EWH_Events[EWH_PRESS_UP_EVENT]=0;
            TMR1_Stop();
            //EWH_SetTemp_Mode();
            EWH_Mode=EWH_SET_TEMP_MODE;
        }
    if( EWH_Events[EWH_PRESS_DOWN_EVENT])
        {
             EWH_Events[EWH_PRESS_DOWN_EVENT]=0;
             TMR1_Stop();
             EWH_Mode=EWH_SET_TEMP_MODE;
        }
}


/*------------------------- Helper Function Definition -----------------------*/
void EWH_Init()
{
    // 1. Make Configuration for Timer
    tTMR1_Config TMR1_cfg; 
    TMR1_cfg.Prescaler=TMR1_PRESCALER_4; 
    TMR1_cfg.clkSource=EXTERNAL_CLK_SOURCE; 
    
    // 2. Call TMR1_Init() to Initialize the Timer with the required configuration
    TMR1_Init(&TMR1_cfg); 
    
    // 3. Make Configuration for ADC
    tADC_Config adc_config; 
    adc_config.alignment=RIGHT; 
    adc_config.channel=ADC2; 
    adc_config.clk=FOSC_8; 
    adc_config.mode= POLLING_MODE; 
    
    // 4. Call ADC_Init() to Initialize the ADC with the required configuration
    ADC_Init(&adc_config);
    
    // 5. Make Configuration for I2C
    tI2C_Config i2c_config; 
    i2c_config.BaudRate=100000; 
    i2c_config.Mode=Master_Mode; 
    i2c_config.operationMode=POLLING;
    
    // 6. Call I2C_Init() to Initialize the I2C with the required configuration
    I2C_Init(&i2c_config);
    
    // 7. Call DD_Init() to Initialize All Digital Output Devices
    DD_Init();
    
    // 8. Call SW_Init() to Initialize All  Buttons with required configurations
    SW_Init();
    
    // 9. Initialize our EEPROM with the initial Temperature Value 
    EWH_EEPROM_Init();
   
}
void EWH_EEPROM_Init()
{
    EEPROM_WriteByte(EWH_TEMP_ADDRESS,EWH_INITIAL_SET_TEMP); 
}
void EWH_EEPROM_Update(uint8_t newSetTemp)
{
    EEPROM_WriteByte(EWH_TEMP_ADDRESS,newSetTemp); 
}
uint8_t EWH_EEPROM_Read()
{
    return EEPROM_ReadByte(EWH_TEMP_ADDRESS);
}

void EWH_SSD_ON()
{
    SSD_ON(EWH_SSD_1); 
    SSD_ON(EWH_SSD_2);
}
void EWH_SSD_OFF()
{
    SSD_OFF(EWH_SSD_1); 
    SSD_OFF(EWH_SSD_2);
}
void EWH_SSD_Update(uint16_t temp)
{
    SSD_OFF(EWH_SSD_1); 
    SSD_Write(EWH_SSD_2,temp%10); 
    __delay_ms(30);
    SSD_OFF(EWH_SSD_2); 
    SSD_Write(EWH_SSD_1,(uint8_t)temp/10);
    __delay_ms(30);
}

uint8_t EWH_getAvrgTempReading(uint8_t *buffer, uint8_t length)
{
    uint16_t sumOfReadings=0;
    for(uint8_t i=0 ; i<length ; i++)
    {
        sumOfReadings += buffer[i];
    }
    uint8_t averageReading= sumOfReadings/length;
    return averageReading;
}

/*---------------------- INTERRUPT SERVICE ROUTINE ---------------------------*/
void __interrupt() ISR()
{
    static uint8_t count =0; 
    if(INTF==1)
    {
        EWH_Events[EWH_ON_OFF_EVENT]=1;
            //1. Toggle The EWH State ON-->OFF or OFF--> ON 
        if(EWH_State==ON)
        {
            EWH_State=OFF;
            EWH_Mode=EWH_SLEEP_MODE;
        }
        else if(EWH_State==OFF)
        {
            EWH_State=ON;
            EWH_Mode=EWH_WAKE_UP_MODE;
        }        
        INTF=0;
    }
    
    if (TMR1IF)
    {
        count++;
        if(EWH_Mode==EWH_OPERATING_MODE)
        {
          uint16_t Reading = ADC_ReadChannel(ADC2);
          current_Temp=Reading*0.488;       
        }

        if(count==10)
        {
            // Put Your Second Event Here
            if(EWH_Mode==EWH_SET_TEMP_MODE)
            {
                SSD_Blink_flag = ~SSD_Blink_flag;
                NoPress_Sec_count++;
                if(NoPress_Sec_count==5)
                {
                    EWH_Events[EWH_NO_PRESS_5_SEC_EVENT]=1;
                }
            }

            if(EWH_Mode==EWH_OPERATING_MODE && DD_GetState(HEATER)==ON)
            {
                GPIO_TogglePin(HEATER_LED_PORT_DATA,HEATER_LED_PIN);
            }
            else if(EWH_Mode==EWH_OPERATING_MODE && DD_GetState(COOLER)==ON)
            {
                GPIO_WritePin(HEATER_LED_PORT_DATA,HEATER_LED_PIN,ON);
            }
            // Clear The Global Counter
            count = 0;
        }
    TMR1IF = 0; // Clear The Flag Bit
    TMR1=TMR1_PRE_LOAD_VALUE;
   }
}
