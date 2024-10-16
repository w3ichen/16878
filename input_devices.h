/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INPUT_DEVICES_H_
#define __INPUT_DEVICES_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Function definitions---------------------------------------------------------*/
void init_input_devices(void);
uint32_t read_photo_trans(void);
uint32_t read_button(void);

#ifdef __cplusplus
}
#endif

#endif
