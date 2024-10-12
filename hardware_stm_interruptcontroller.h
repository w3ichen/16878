/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HARDWARE_STM_INTERRUPTCONTROLLER_H_
#define __HARDWARE_STM_INTERRUPTCONTROLLER_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Function definitions---------------------------------------------------------*/
void initTimer3ToInterrupt( void );
void TIM3_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif
