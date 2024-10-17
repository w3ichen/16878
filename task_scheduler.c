#include "stm32f4xx_rcc_mort.h"
#include "task_scheduler.h"
#include <stdlib.h>
#include "led.h"


/* Global Variables ---------------------------------------------------------*/
// Initialize queue
struct queue_t queue = {
    .head = NULL,
    .tail = NULL,
    .size = 0
};

/* Queue ------------------------------------------------------------------*/
// Push new event to end of queue
void sched_event(event_t event) {
    queue_node_t* new_node = malloc(sizeof(queue_node_t));
    if (queue.tail == NULL){
        // List is empty, this is the first time
        queue.tail = new_node;
        queue.head = new_node;
    } else {
        // Add to end of queue
        // Current: tail -> NULL
        // Changed to: tail -> new_node (new tail) -> NULL
        new_node->next = NULL;
        queue.tail->next = new_node;
        queue.tail = new_node;
    }
    // Increment size
    queue.size++;
}

// Pop event from start of queue
event_t pop_queue(void){
    if (queue.head == NULL){
        // Nothing in queue, pop should not have been popped!
        return -1;
    }
    // Get the event from the first node
    queue_node_t* head_node = queue.head;
    event_t ret_event = head_node->event;
    // Change the head
    queue.head = head_node->next;
    // Free memory of head
    free(head_node);
    // Decrement size
    queue.size--;
    if (queue.size == 0){
        // Queue is now empty, make sure both head/tail are NULL
        queue.head = NULL;
        queue.tail = NULL;
    }
    return ret_event;
}


/* Task Scheduler ------------------------------------------------------------------*/
// List of all tasks
void tasks(event_t event){
  switch (event) {
        case READY:
            break;
        case RED_ON:
            // Turn red on
            set_red();
            clear_green();
            clear_blue();
            break;
        case GREEN_ON:
            clear_red();
            set_green();
            clear_blue();
            break;
        case BLUE_ON:
            clear_red();
            clear_green();
            set_blue();
            break;
        default:
            break;
    }
}

// Iterate through queue and schedules tasks in the queue
void task_scheduler(void) {
    event_t event;
    // Start at queue head and iterate through all pending tasks
    queue_node_t* node = queue.head;
    while (node != NULL) {
        tasks(node->event);
        node = node->next; // Go to next node
    }
}

