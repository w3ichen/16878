/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EVENT_HANDLER_H_
#define __EVENT_HANDLER_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/*Event List*/
typdef enum {
    Ready, 
    Button_Pressed,
    Edge_Detected,
    No_Event,
    StartTimer, 
    EndTimer,
    Timeout,
    CW,
    CCW
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

/*Timer list  */
typedef struct timerList{
    list[Max_Queue_Size];
    uint16_t size; //Size of queue
    uint16_t start; //start of queue
    uint16_t end; //end of queue

}timerList;
}

/*Functions */
void eventHandler(void);
void timeoutCheck(void);
void deleteEvent(void);
void deleteTimerFromList(void);

