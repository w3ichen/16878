/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HARDWARE_STM_TIMER3_H_
#define __HARDWARE_STM_TIMER3_H_

#include <cstdint>
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Function definitions---------------------------------------------------------*/
void initTimer3AsPWM( void );
void setTimer3PWMDutyCycle( float duty_cycle  );

#ifdef __cplusplus
}
#endif

#endif
