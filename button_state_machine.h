/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTON_STATE_MACHINE_H_
#define __BUTTON_STATE_MACHINE_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Macros for Everyone--------------------------------------------------------*/




/*Function definitions---------------------------------------------------------*/

void initButton(void);
uint32_t read_button(void);
void buttonStateMachine(event_t newEvent, uint16_t param1, double param2);

#ifdef __cplusplus
}
#endif

#endif /*__LED1_H */
