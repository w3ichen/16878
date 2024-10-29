/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HARDWARE_STM_ADC_H_
#define __HARDWARE_STM_ADC_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Function definitions ---------------------------------------------------------*/
void initADC3_567_withDMA(void);
void initADC3_7_withDMA(void);
void startADCConversion(void);


#ifdef __cplusplus
}
#endif

#endif /*__GPIO_H */
