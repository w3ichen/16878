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
    RED_ON,
    GREEN_ON,
    BLUE_ON,
    PRINT_COLOR
} state_t;

// Queue node
struct Node {
    state_t state;
    struct Node* next; // Next node
    struct Node* prev; // Previous node
};
typedef struct Node queue_node_t; // Node type

// Defintion of FIFO queue
struct {
    queue_node_t* head;
    queue_node_t* tail;
    uint32_t size;
} queue = {NULL, NULL, 0}; // Initial values


/* Function definitions ---------------------------------------------------------*/
void push(state_t state);


#ifdef __cplusplus
}
#endif
#endif