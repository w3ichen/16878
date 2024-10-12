/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HARDWARE_STM_TIMER3_H_
#define __HARDWARE_STM_TIMER3_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Function definitions---------------------------------------------------------*/
void initTimer3( void );
void initTimerAsOutputComparePB0( void );
void initTimer3CH1AsInputCaptureOnPC6( void );
uint16_t getCaptureTimer3CH1( void );
void clearTimer3StatusRegister( void );
void initTimer3AsPWM( void );

#ifdef __cplusplus
}
#endif

#endif
