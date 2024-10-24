#include "stm32f4xx_rcc_mort.h"
#include "hardware_stm_gpio.h"
#include "hardware_stm_interruptcontroller.h"
#include "hardware_stm_timer3.h"
#include "timer.h"
#include <math.h>
#include <stdlib.h>

#define MAX_TIME_BEFORE_OVERFLOW        7274.4
#define TIM3_RESOLUTION                 0.1

/* Global Variables ---------------------------------------------------------*/
uint16_t high_counter = 0; // For timer
subtimer_node_t* subtimers_list = NULL;

// Initialize timer ms
void init_timer_ms(void) {
    high_counter = 0; // Set to 0
    initTimer3(); // Init timer 3
}
// Get current time
double get_timer_ms(void) {
    // Calculate timer in ms: multiply number of overflows by max value before overflow and add to current timer value.
    // Then multiply by resolution
    double time_ms = ((double) high_counter)*MAX_TIME_BEFORE_OVERFLOW + ((double) readTim3Count())*TIM3_RESOLUTION;
    return time_ms;
}
// Increment high counter on overflow
void incr_high_counter (void) {
    high_counter++;
}


// Delete the timer from list
int delete_subtimer(subtimer_node_t* prev_node, subtimer_node_t* curr_node) {
    if (prev_node == NULL){
        // No previous node, then set head to null
        subtimers_list = NULL; // Empty list
    } else {
        // Change prev -> curr -> next
        // Skip curr: prev -> next
        prev_node->next = curr_node->next;
    }
    // Free curr node memory
    free(curr_node);
    return 0; // Success
}

// Add new subtimer to list
void add_subtimer(double duration, event_t trigger_event) {
    // Allocate memory for subtimer item
    subtimer_node_t* new_node = malloc(sizeof(subtimer_node_t));
    new_node->creation_time = get_timer_ms(); // Get current time
    new_node->next = NULL; // New node at tail so next is NULL
    new_node->duration = duration; // Set duration value
    new_node->trigger_event = trigger_event; // Set event for timer node

    // Add new node to end of list
    if (subtimers_list == NULL) {
        // If first item in list, list is empty right now
        subtimers_list = new_node;
    } else {
        subtimer_node_t* node = subtimers_list;
        while (node->next != NULL) {
            // Find the last node in list
            node = node->next;
        }
        // Now node is the last node in list
        node->next = new_node;
    }
}


// Iterate through timers list and check for durations
void check_subtimers(void) {
    double curr_time;
    subtimer_node_t* prev_node;
    // Start at list head and iterate through all active timers
    subtimer_node_t* node = subtimers_list;
    while (node != NULL) {
        // Get current time
        curr_time = get_timer_ms();

        // Take floating abs val of current time - creation time
        if (fabs(curr_time - node->creation_time) > node->duration){
            // If difference > duration, then timer has timed out!
            // Schedule the trigger event
            sched_event(node->trigger_event);   
            // Delete the timer
            delete_subtimer(prev_node, node);
        }

        prev_node = node; // Curr node becomes previous
        node = node->next; // Go to next node
    }
}


