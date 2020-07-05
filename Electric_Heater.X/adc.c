 /********************************************************************************
 * Module : ADC
 *
 * File Name : adc.c
 *
 * Description : Source File for ADC Module
 *
 * Author : Shreef Mohamed
 *
 * Created on: July 4, 2020
 *
 ********************************************************************************/

#include "adc.h"

void ADC_Init(tADC_Config* config)
{
        // Enable ADC (ADON=1))
    ADC_CONTROL0_REG |= (1<<0);
    // Select the configured clk pre_scaler
    switch(config->clk)
    {
        case FOSC_2: 
            ADC_CONTROL0_REG &= ~(0xC0); 
            break;
        case FOSC_8: 
            ADC_CONTROL0_REG |= (1<<6); 
            break;
        case FOSC_32: 
            ADC_CONTROL0_REG |= (2<<6); 
            break;
        case FRC: 
            ADC_CONTROL0_REG |= (3<<6); 
            break;
        case FOSC_4: 
            ADC_CONTROL0_REG &= ~(0xC0);
            ADC_CONTROL1_REG |= (1<<6); 
            break;
        case FOSC_16: 
            ADC_CONTROL0_REG |= (1<<6);
            ADC_CONTROL1_REG |= (1<<6); 
            break;
        case FOSC_64: 
            ADC_CONTROL0_REG |= (2<<6);
            ADC_CONTROL1_REG |= (1<<6); 
            break;  
            
        default: 
            ADC_CONTROL0_REG |= (1<<6); 
    }
    
    // Select Alignment Type for result (Right or Left)
    ADC_CONTROL1_REG |= ((config->alignment)<<7);
    
    // Select ALl Pins as Analog 
    ADC_CONTROL1_REG = (0x80); 
    

    
    if(config->mode==INTERRUPT_MODE)
    {
        ADIF = 0;  // Clear ADC Interrupt Flag
        ADIE = 1;  // ADC Interrupt Enable Bit
        PEIE = 1;  // Peripherals Interrupt Enable Bit
        GIE = 1;   // Global Interrupts Enable Bit
    }
}

uint16_t ADC_ReadChannel(tADC_Channel_Select channel)
{
    // Clear The Channel Selection Bits 
    ADC_CONTROL0_REG &= ~(7<<ADC_CHANNEL_POS); 
    
    // Select the Configured channel 
    ADC_CONTROL0_REG |= ((channel)<<ADC_CHANNEL_POS); 
    
    // Wait for minimum Tacq time according to Data sheet 
    __delay_us(ADC_MINIMUM_DELAY_us); 
    
    // ADC Start Conversion by set GO_DONE Bit in ADC_CONTROL0_REG
    ADC_START_CONVERSION; 
    
    // ADC Wait until Conversion complete 
    while(ADC_CONV_IN_PROGRESS);
    
    // Get Result form the buffer 
    uint16_t result =((ADC_RESULT_H_REG<<8) + ADC_RESULT_L_REG) ; 
    
    return result;
}