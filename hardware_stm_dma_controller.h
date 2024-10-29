/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HARDWARE_STM_DMA_CONTROLLER_H_
#define __HARDWARE_STM_DMA_CONTROLLER_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Function definitions ---------------------------------------------------------*/
uint16_t returnADC3StoredValue(uint8_t index);
void enableDMAForAdc3_3channels( void );
void initDMAForAdc3_3channels( void );
void initDMAForAdc3_1channel( void );
void enableDMAForAdc3_1channel( void );

#ifdef __cplusplus
}
#endif

#endif /*__GPIO_H */
