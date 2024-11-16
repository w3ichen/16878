/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MOTOR_STATE_MACHINE_H_
#define __MOTOR_STATE_MACHINE_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "event_handler.h"

/* Macros for Everyone--------------------------------------------------------*/

/* Types */
typedef enum {
    Initialize,
    Start,
    CW,
    CCW
} motorState_t;


static motorState_t motorState = Initialize;
/*Function definitions---------------------------------------------------------*/

void MotorStateMachine (event_t newevent, uint16_t param1, double param2);

#ifdef __cplusplus
}
#endif

#endif /*__LED1_H */
