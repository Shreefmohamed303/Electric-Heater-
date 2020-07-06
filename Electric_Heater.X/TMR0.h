#ifndef TMR0_H_
#define TMR0_H_

#include "xc.h"

#define TMR0_MAX_COUNT                  (256)
#define TMR0_CONTROL_REG                OPTION_REG
#define TMR0_PRESCALER_MSK              (0x07)

/*-------------------------------- MACROS ------------------------------------*/                   	
#define TMR0_SET_PRESCALER_2            PS0 = 0;\
                                        PS1 = 0;\
                                        PS2 = 0;\
                                        PSA = 0

#define TMR0_SET_PRESCALER_4            PS0 = 1;\
                                        PS1 = 0;\
                                        PS2 = 0;\
                                        PSA = 0

#define TMR0_SET_PRESCALER_8            PS0 = 0;\
                                        PS1 = 1;\
                                        PS2 = 0;\
                                        PSA = 0

#define TMR0_SET_PRESCALER_16           PS0 = 1;\
                                        PS1 = 1;\
                                        PS2 = 0;\
                                        PSA = 0

#define TMR0_SET_PRESCALER_32           PS0 = 0;\
                                        PS1 = 0;\
                                        PS2 = 1;\
                                        PSA = 0

#define TMR0_SET_PRESCALER_64           PS0 = 1;\
                                        PS1 = 0;\
                                        PS2 = 1;\
                                        PSA = 0

#define TMR0_SET_PRESCALER_128          PS0 = 0;\
                                        PS1 = 1;\
                                        PS2 = 1;\
                                        PSA = 0

#define TMR0_SET_PRESCALER_256          PS0 = 1;\
                                        PS1 = 1;\
                                        PS2 = 1;\
                                        PSA = 0

#define TMR0_GET_FLAG                   (TMR0IF)
#define TMR0_CLEAR_FLAG                 (TMR0IF = 0)

//#define TMR0_UPDATE_REGISTER(TIME,Prescaler,)		(TMR0 = 256 -(TIME * 1000 )/(4*.125*8)) 

#define TMR0_ENABLE_INTERRUPT           (TMR0IE = 1)
#define GLOBAL_INTERRUPT_ENABLE         (GIE = 1)

//#define TMR0_ENABLE                     (TMR0ON = 1)
//#define TMR0_DISABLE                    (TMR0ON = 0)

#define TMR0_SET_INTERNAL_CLOCK         (T0CS = 0)
#define TMR0_SET_EXTERNAL_CLOCK         (T0CS = 1)

//#define TMR0_8_BIT_MODE                 (T08BIT = 1)
//#define TMR0_16_BIT_MODE                (T08BIT = 0)

#define PERIHPERAL_INTERRUPT_ENABLE 	(TMR0IE = 1)
#define GLOBAL_INTERRUPT_ENABLE         (GIE = 1)

/*-------------------------------- TypeDefs ----------------------------------*/
typedef enum 
{
    TMR0_PRESCALE_2=2,
    TMR0_PRESCALE_4=4,
    TMR0_PRESCALE_8=8,
    TMR0_PRESCALE_16=16,
    TMR0_PRESCALE_32=32,
    TMR0_PRESCALE_64=64,
    TMR0_PRESCALE_128=128,
    TMR0_PRESCALE_256=256,            
}tTMR0_PrescalerSelect;


typedef enum 
{
    INTERNAL_CLK_SOURCE=0, 
    EXTERNAL_CLK_SOURCE=1
}tTMR_ClkSourceSelect;

typedef struct 
{
    tTMR0_PrescalerSelect Prescaler; 
    tTMR_ClkSourceSelect  clkSource;
}tTMR0_Config;

void TMR0_Init(tTMR0_Config *config); 
void TMR0_Start();
void TMR0_Update(); 
void TMR0_Stop(); 


#endif