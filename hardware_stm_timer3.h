/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HARDWARE_STM_TIMER3_H_
#define __HARDWARE_STM_TIMER3_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "task_scheduler.h"

/* Types ---------------------------------------------------------*/
// Subtimer node
typedef struct SubtimerNode {
    double creation_time;
    double duration;
    event_t trigger_event;
    struct SubtimerNode* next; // Next node
} subtimer_node_t; // SubtimerNode type

extern subtimer_node_t* subtimers_list; // Head of subtimerlist


/* Function definitions---------------------------------------------------------*/
void initTimer3( void );
void initTimerAsOutputComparePB0( void );
void initTimer3CH1AsInputCaptureOnPC6( void );
uint16_t getCaptureTimer3CH1( void );
void clearTimer3StatusRegister( void );
void initTimer3AsPWM( void );
void init_timer_ms(void);
void incr_high_counter (void);


#ifdef __cplusplus
}
#endif

#endif
