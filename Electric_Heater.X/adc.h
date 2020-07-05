 /********************************************************************************
 * Module : ADC
 *
 * File Name : adc.h
 *
 * Description : Header File for ADC Module
 *
 * Author : Shreef Mohamed
 *
 * Created on: July 4, 2020
 *
 ********************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "GPIO.h"
#include "config.h"

/*-------------------------- Important Defines -------------------------------*/
#define ADC_CONTROL0_REG            ADCON0
#define ADC_CONTROL1_REG            ADCON1
#define ADC_RESULT_H_REG            ADRESH
#define ADC_RESULT_L_REG            ADRESL

#define ADC_CHANNEL_POS             3
#define ADC_GO_DONE_POS             2
#define ADC_MINIMUM_DELAY_us        30
/*-------------------------------- MACROS ------------------------------------*/

#define ADC_START_CONVERSION       (ADC_CONTROL0_REG|=(1<<ADC_GO_DONE_POS)) 
#define ADC_CONV_IN_PROGRESS       (ADC_CONTROL0_REG & (1<<ADC_GO_DONE_POS))
/*-------------------------------- TypeDefs ----------------------------------*/
typedef enum {ADC0=0,ADC1=1,ADC2=2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC8}tADC_Channel_Select;
typedef enum {POLLING_MODE ,INTERRUPT_MODE}tADC_Mode_Select;
typedef enum {LEFT=0,RIGHT=1}tADC_Result_Alignment;
typedef enum {FOSC_2,FOSC_8,FOSC_32,FRC,FOSC_4,FOSC_16,FOSC_64}tADC_clkSelect; 

typedef struct 
{
    tADC_Channel_Select channel ; 
    tADC_Mode_Select     mode; 
    tADC_Result_Alignment alignment; 
    tADC_clkSelect  clk;
}tADC_Config; 
/*-------------------------------- Variables ------------------------------------*/

/*-------------------------- FUNCTION DECLARATION ----------------------------*/
void ADC_Init(tADC_Config* config); 
uint16_t ADC_ReadChannel(tADC_Channel_Select channel); 

#endif