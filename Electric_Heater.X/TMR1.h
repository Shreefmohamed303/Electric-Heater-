 /********************************************************************************
 * Module : TMR1 
 *
 * File Name : TMR1.c
 *
 * Description : Header File for Timer Module that contains all Timer Interfaces 
 *
 * Author : Shreef Mohamed
 *
 * Created on: July 5, 2020
 *
 ********************************************************************************/
#ifndef TMR1_H_
#define TMR1_H_

#include <xc.h>

#define TMR1_MAX_COUNT                  (65535)
#define TMR1_CONTROL_REG                T1CON:
#define TMR1_PRE_LOAD_VALUE             40536

/*-------------------------------- MACROS ------------------------------------*/  
#define TMR1_SET_PRESCALER_1            T1CKPS0 = 0;\
                                        T1CKPS1 = 0

#define TMR1_SET_PRESCALER_2            T1CKPS0 = 1;\
                                        T1CKPS1 = 0

#define TMR1_SET_PRESCALER_4            T1CKPS0 = 0;\
                                        T1CKPS1 = 1

#define TMR1_SET_PRESCALER_8            T1CKPS0 = 1;\
                                        T1CKPS1 = 1

#define TMR1_GET_FLAG                   (TMR1IF)
#define TMR1_CLEAR_FLAG                 (TMR1IF = 0)

//#define TMR0_UPDATE_REGISTER(TIME,Prescaler,)		(TMR0 = 256 -(TIME * 1000 )/(4*.125*8)) 

#define TMR1_ENABLE_INTERRUPT           (TMR1IE = 1)
#define PERIHPERAL_INTERRUPT_ENABLE 	(PEIE = 1)
#define GLOBAL_INTERRUPT_ENABLE         (GIE = 1)

#define TMR1_ENABLE                     (TMR1ON = 1)
#define TMR1_DISABLE                    (TMR1ON = 0)

#define TMR1_SET_INTERNAL_CLOCK         (T0CS = 0)
#define TMR1_SET_EXTERNAL_CLOCK         (T0CS = 1)

//#define TMR0_8_BIT_MODE                 (T08BIT = 1)
//#define TMR0_16_BIT_MODE                (T08BIT = 0)


/*-------------------------------- TypeDefs ----------------------------------*/
typedef enum 
{
    TMR1_PRESCALER_1=0,
    TMR1_PRESCALER_2=1,
    TMR1_PRESCALER_4=2,
    TMR1_PRESCALER_8=3           
}tTMR1_PrescalerSelect;


typedef enum 
{
    INTERNAL_CLK_SOURCE=0, 
    EXTERNAL_CLK_SOURCE=1
}tTMR1_ClkSourceSelect;

typedef struct 
{
    tTMR1_PrescalerSelect Prescaler; 
    tTMR1_ClkSourceSelect  clkSource;
}tTMR1_Config;

void TMR1_Init(tTMR1_Config *config); 
void TMR1_Start();
void TMR1_Stop(); 

#endif