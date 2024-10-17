/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_H_
#define __TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "task_scheduler.h"

/* Function definitions---------------------------------------------------------*/
void init_timer_ms(void);
void add_subtimer(double duration, event_t trigger_event);
void incr_high_counter (void);
void check_subtimers(void);

#ifdef __cplusplus
}
#endif

#endif
