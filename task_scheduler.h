#ifndef _TASK_SCHEDULER_H_
#define _TASK_SCHEDULER_H_

#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Types ---------------------------------------------------------*/
// List of all states in state machine
typedef enum {
    READY,
    BUTTON_PRESSED,
    RED_ON,
    GREEN_ON,
    BLUE_ON,
    PRINT_COLOR
} state_t;

// Queue node
struct QueueNode {
    state_t state;
    struct QueueNode* next; // Next node
    struct QueueNode* prev; // Previous node
};
typedef struct QueueNode queue_node_t; // QueueNode type

// Defintion of FIFO queue
struct {
    queue_node_t* head;
    queue_node_t* tail;
    uint32_t size;
} queue = {NULL, NULL, 0}; // Initial values


/* Function definitions ---------------------------------------------------------*/
void sched_event (state_t state);

#ifdef __cplusplus
}
#endif
#endif