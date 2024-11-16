/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EVENT_HANDLER_H_
#define __EVENT_HANDLER_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define Max_Queue_Size 10

/*Event List*/
typedef enum {
    Ready, 
    Button_Pressed,
    Edge_Detected,
    No_Event,
    StartTimer, 
    EndTimer,
    Timeout,
} event_t;

/*Event Objects */
typedef struct event_o 
{
    event_t type;
    uint16_t param1;
    double param2; 
} event_o;

/*Event Queue Object */
typedef struct eventQueue_o
{
    event_o queue[Max_Queue_Size];
    uint16_t size; //Size of queue
    uint16_t start; //start of queue
    uint16_t end; //end of queue
}eventQueue;

typedef struct  {
    uint32_t timeouts[Max_Queue_Size];
    uint16_t size;
    uint16_t start;
    uint16_t end;
} timerList;

static eventQueue event_q;
static timerList timer_list;

/*Functions */
void eventHandler(void);
void timeoutCheck(void);
void deleteEvent(void);
void addEvent(event_o event);
// void deleteTimerFromList(void);
void sendEvent(event_t event, uint16_t param1, double param2);
void insertTimer(uint32_t timeout);
void deleteTimerFromList(uint8_t indx);

#ifdef __cplusplus
 }
#endif

#endif