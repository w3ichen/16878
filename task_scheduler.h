#ifndef _TASK_SCHEDULER_H_
#define _TASK_SCHEDULER_H_

#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Types ---------------------------------------------------------*/
// List of all events in event machine
typedef enum {
    BUTTON_PRESSED,
    RED_ON,
    READ_RED,
    GREEN_ON,
    READ_GREEN,
    BLUE_ON,
    READ_BLUE,
    PRINT_COLOR
} event_t;

// Queue node
struct QueueNode {
    event_t event;
    struct QueueNode* next; // Next node
    struct QueueNode* prev; // Previous node
};
typedef struct QueueNode queue_node_t; // QueueNode type

// Defintion of FIFO queue
struct queue_t {
    queue_node_t* head;
    queue_node_t* tail;
    uint32_t size;
};
extern struct queue_t queue;


/* Function definitions ---------------------------------------------------------*/
void sched_event (event_t event);
void task_scheduler(void);

#ifdef __cplusplus
}
#endif
#endif