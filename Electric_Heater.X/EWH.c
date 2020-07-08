#include "EWH.h"
#include "SW.h"


void EWH_Sleep_Mode()
{
        /*  EWH is all OFF  */
    // Display OFF 
    EWH_SSD_OFF();
    // Heater Element OFF
    DD_SetState(HEATER,OFF); 
    // Cooler Element OFF
    DD_SetState(COOLER,OFF); 
    // Stop timer 
    TMR1_Stop();
    // Heater_Led OFF
    DD_SetState(HEATER_LED,OFF);
    
    EWH_Events[EWH_ON_OFF_EVENT]=0;
    EWH_Events[EWH_PRESS_DOWN_EVENT]=0;
    EWH_Events[EWH_PRESS_UP_EVENT]=0;
    EWH_Events[EWH_NO_PRESS_5_SEC_EVENT]=0;
    
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_4,OFF);
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_5,OFF);
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_6,OFF);
}
void EWH_PowerUP_Mode()
{
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_4,ON);
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_5,OFF);
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_6,OFF);
    
    EWH_Events[EWH_ON_OFF_EVENT]=0;
    EWH_Events[EWH_PRESS_DOWN_EVENT]=0;
    EWH_Events[EWH_PRESS_UP_EVENT]=0;
    EWH_Events[EWH_NO_PRESS_5_SEC_EVENT]=0;
    
    /* ON/OFF Button is Released */
    EWH_Events[EWH_ON_OFF_EVENT]=0;
    
    //EWH_Mode=EWH_POWER_UP_MODE;

    // The Set Temp should be retrieved form external EEPROM
    set_Temp = EWH_EEPROM_Read();

    // Turn On The Heater_Display and Display the temp from EEPROM
    Heater_Display (set_Temp);
    
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
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_4,OFF);
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_5,ON);
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_6,OFF);
    
    EWH_Events[EWH_ON_OFF_EVENT]=0;
    EWH_Events[EWH_PRESS_DOWN_EVENT]=0;
    EWH_Events[EWH_PRESS_UP_EVENT]=0;
    EWH_Events[EWH_NO_PRESS_5_SEC_EVENT]=0;
    

    // 1. get The set Temp From EEPROM
    set_Temp = EWH_EEPROM_Read();
    
    DD_SetState(HEATER,OFF);
    DD_SetState(COOLER,OFF);
    // 2. SSD show the set Temp 
    Heater_Display(set_Temp);
    // 3. Enable Timer 
    TMR1_Start();
    
    while(1)
    {
        if(UP_BUTTON_IS_PRESSED && set_Temp<MAX_SET_TEMP)
        {
            __delay_ms(30); 
            if(UP_BUTTON_IS_PRESSED)
            {
                set_Temp+=5; 
                NoPress_Sec_count=0;
            }
        }
        else if (DOWN_BUTTON_IS_PRESSED && set_Temp>MIN_SET_TEMP)
        {
            __delay_ms(30); 
            if(DOWN_BUTTON_IS_PRESSED)
            {
                set_Temp-=5; 
                NoPress_Sec_count=0;
            }
        }
        if(EWH_Events[EWH_NO_PRESS_5_SEC_EVENT] || EWH_Events[EWH_ON_OFF_EVENT])
        {
            // Save The Last Set Temp in EEPROM
            EWH_EEPROM_Update(set_Temp);
            // Leave Set temp Mode and Go to Operating Mode 
            break ;
        }
        //  SSD show the current set Temp 
        Heater_Display(set_Temp);
        
    }
    
    if(EWH_Events[EWH_ON_OFF_EVENT])
    {
        EWH_Events[EWH_ON_OFF_EVENT]=0;
        // Go to PowerUp Mode
        //EWH_PowerUP_Mode();
        EWH_Mode=EWH_POWER_UP_MODE;
    }
    else if(EWH_Events[EWH_NO_PRESS_5_SEC_EVENT])
    {
        EWH_Events[EWH_NO_PRESS_5_SEC_EVENT]=0;
        // Go to Operating Mode
        //EWH_Operating_Mode();
        EWH_Mode=EWH_OPERATING_MODE;
    }

}
void EWH_Operating_Mode()
{
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_4,OFF);
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_5,OFF);
    GPIO_WritePin(GPIO_PORTB_DATA,GPIOB_PIN_6,ON);
    
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
        Heater_Display(current_Temp);
        if(current_Temp>(set_Temp+5))
        {
            DD_SetState(HEATER,OFF); 
            DD_SetState(COOLER,ON); 
            DD_SetState(HEATER_LED,ON);
        }
        else if(current_Temp<(set_Temp-5))
        {
            DD_SetState(HEATER,ON); 
            DD_SetState(COOLER,OFF); 
            DD_SetState(HEATER_LED,ON);// Blinking Every 1 sec         
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
    
         Heater_Display(current_Temp);    
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
             //EWH_SetTemp_Mode();
             EWH_Mode=EWH_SET_TEMP_MODE;
        }
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
            EWH_Mode=EWH_POWER_UP_MODE;
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
        Heater_Display(current_Temp);        
      }

      if(count==4)
      {
        // Put Your Second Event Here
          if(EWH_Mode==EWH_SET_TEMP_MODE)
          {
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
        //Heater_Display(temp);
        // Clear The Global Counter
        count = 0;
      }
      TMR1IF = 0; // Clear The Flag Bit
      TMR1=TMR1_PRE_LOAD_VALUE;
   }
}