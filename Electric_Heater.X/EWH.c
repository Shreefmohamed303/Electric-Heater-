 /********************************************************************************
 * Module : EWH (Electric Water Heater)
 *
 * File Name : EWH.c
 *
 * Description : Source File for EWH Application contains all specific App Functions and Types
 *
 * Author : Shreef Mohamed
 *
 * Created on: July 6, 2020
 *
 ********************************************************************************/
#include "EWH.h"
#include "SW.h"

/*------------------------- States Function Definition -----------------------*/
void EWH_Sleep_Mode()
{
        /*  EWH is all OFF  */
    // Clear Event Flag 
    //EWH_ClearEvent(EWH_ON_OFF_EVENT);
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

    //SLEEP();
}
void EWH_WakeUP_Mode()
{
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_4,ON);
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_5,OFF);
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_6,OFF);
   
    // Clear The ON_OFF Event 
    EWH_ClearEvent(EWH_ON_OFF_EVENT);
    
    // The Set Temp should be retrieved form external EEPROM
    set_Temp = EWH_EEPROM_Read();

    while(1)
    {
        // Turn On The Heater_Display and Display the temp from EEPROM
        EWH_SSD_Update(set_Temp);
        
        // Check for Events
        if(UP_BUTTON_IS_PRESSED)
        {
            __delay_ms(50);
            if(UP_BUTTON_IS_PRESSED)
            {
//                // Set The Event Flag
//                EWH_SetEvent(EWH_PRESS_UP_EVENT);
//                // Clear The Event Flag 
//                EWH_ClearEvent(EWH_PRESS_UP_EVENT);
                // Clear No Press Second Count
                NoPress_Sec_count=0;
                // Switch EWH_Mode to SET_TEMP_MODE
                EWH_SetMode(EWH_SET_TEMP_MODE);
                // Leave The Wakeup Mode
                break;
            }
        }
        if(DOWN_BUTTON_IS_PRESSED)
        {
            __delay_ms(50);
            if(DOWN_BUTTON_IS_PRESSED)
            {
//                // Set The Event Flag
//                EWH_SetEvent(EWH_PRESS_DOWN_EVENT);
//                // Clear The Event Flag 
//                EWH_ClearEvent(EWH_PRESS_DOWN_EVENT);
                // Clear No Press Second Count
                NoPress_Sec_count=0;
                // Switch EWH_Mode to SET_TEMP_MODE
                EWH_SetMode(EWH_SET_TEMP_MODE);
                // Leave The Wakeup Mode
                break;
            }
        }
        if(EWH_Events[EWH_ON_OFF_EVENT]==1)
        {
            // Clear The Event Flag
            EWH_ClearEvent(EWH_ON_OFF_EVENT);
            // Switch Mode to SLEEP Mode
            EWH_SetMode(EWH_SLEEP_MODE);
            // Leave Set temp Mode 
            break ;
        }
        
    }    
}
void EWH_SetTemp_Mode()
{
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_4,OFF);
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_5,ON);
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_6,OFF);
        
    // 1. Enable Timer 
    TMR1_Start();
    // 2. clear "No Press Second Count"
    NoPress_Sec_count=0;
    // 3. Turn oFF Heater cooler and Heating Element Led while setting Temperature
    DD_SetState(HEATER,OFF);
    DD_SetState(COOLER,OFF);
    DD_SetState(HEATER_LED,OFF);
    // 4. SSD show the set Temp 
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
        
             /* Check for Events */
        if(EWH_Events[EWH_ON_OFF_EVENT]==1)
        {
            // Save The Last Set Temp in EEPROM
            EWH_EEPROM_Update(set_Temp);
            // Clear The Event Flag 
            EWH_ClearEvent(EWH_ON_OFF_EVENT);
            // Switch Mode to SLEEP Mode
            EWH_SetMode(EWH_SLEEP_MODE);
            // Leave Set temp Mode 
            break ;
        }
        if(EWH_Events[EWH_NO_PRESS_5_SEC_EVENT]==1 && (EWH_Mode!=EWH_SLEEP_MODE))
        {
            // Save The Last Set Temp in EEPROM
            EWH_EEPROM_Update(set_Temp);
            // Clear The Event Flag 
            EWH_ClearEvent(EWH_NO_PRESS_5_SEC_EVENT);
            // Clear The No Press Second Count
            NoPress_Sec_count=0;
            // Switch Mode to Operating Mode
            EWH_SetMode(EWH_OPERATING_MODE);
            // Leave Set temp Mode 
            break ;
        }
        
    }

}
void EWH_Operating_Mode()
{
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_4,OFF);
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_5,OFF);
//    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_6,ON);
        
    // Enable Temp Sensing Timer 
    TMR1_Start();

    while(1)
    {
        EWH_SSD_Update(current_Temp);
        
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
        
            // Check for Events
        if(UP_BUTTON_IS_PRESSED && (EWH_Mode!=EWH_SLEEP_MODE))
        {
            __delay_ms(50);
            if(UP_BUTTON_IS_PRESSED)
            {
                // Set The Event Flag
                EWH_SetEvent(EWH_PRESS_UP_EVENT);
                // Disable Timer
                TMR1_Stop(); 
                // Clear The Event Flag 
                EWH_ClearEvent(EWH_PRESS_UP_EVENT);
                // Clear No Press Second Count
                NoPress_Sec_count=0;
                // Switch EWH_Mode to SET_TEMP_MODE
                EWH_SetMode(EWH_SET_TEMP_MODE);
                // Leave The Operating Mode
                break;
            }
        }
        if(DOWN_BUTTON_IS_PRESSED && (EWH_Mode!=EWH_SLEEP_MODE))
        {
            __delay_ms(50);
            if(DOWN_BUTTON_IS_PRESSED)
            {
                // Set The Event Flag
                EWH_SetEvent(EWH_PRESS_DOWN_EVENT);
                // Disable Timer
                TMR1_Stop(); 
                // Clear The Event Flag 
                EWH_ClearEvent(EWH_PRESS_DOWN_EVENT);
                // Clear No Press Second Count
                NoPress_Sec_count=0;
                // Switch EWH_Mode to SET_TEMP_MODE
                EWH_SetMode(EWH_SET_TEMP_MODE);
                // Leave The Operating Mode
                break;
            }
        }
        if(EWH_Events[EWH_ON_OFF_EVENT]==1)
        {
            // Clear The Event Flag
            EWH_ClearEvent(EWH_ON_OFF_EVENT);
            // Switch Mode to SLEEP Mode
            EWH_SetMode(EWH_SLEEP_MODE);
            // Leave Set temp Mode 
            break ;
        }
        
        EWH_SSD_Update(current_Temp);    
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
void EWH_SetMode(sEWH_Mode new_mode)
{
    EWH_Mode=new_mode;
}
void EWH_SetEvent(uint8_t Event_index)
{
    EWH_Events[Event_index]=1;
}
void EWH_ClearEvent(uint8_t Event_index)
{
    EWH_Events[Event_index]=0;
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
    /* External Interrupt from RB0 Pin */
    if(INTF==1)
    {
        // 1. Set The ON_OFF_EVENT
        EWH_SetEvent(EWH_ON_OFF_EVENT);
        
        // 2. Toggle The EWH State ON-->OFF or OFF--> ON 
        if(EWH_State==ON)
        {
            EWH_State=OFF;
            EWH_SetMode(EWH_SLEEP_MODE);
        }
        else if(EWH_State==OFF)
        {
            EWH_State=ON;
            EWH_SetMode(EWH_WAKE_UP_MODE);
        }        
        INTF=0;
    }
    /* Timer Over flow interrupt */
    if (TMR1IF)
    {
        count++;
        if(EWH_Mode==EWH_OPERATING_MODE)
        {
            uint16_t Reading = ADC_ReadChannel(ADC2);
            current_Temp=Reading*0.488;
            ReadingBuffer[TempReading_count]=current_Temp;
            TempReading_count++;
            TempReading_count= TempReading_count%TEMP_READING_BUFFER_LENGTH;
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
                    EWH_SetEvent(EWH_NO_PRESS_5_SEC_EVENT);
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
