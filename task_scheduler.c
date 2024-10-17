#include "stm32f4xx_rcc_mort.h"
#include "task_scheduler.h"
#include <cstdint>
#include <stdlib.h>
#include "led.h"
#include "hardware_stm_timer3.h"
#include "input_devices.h"


#define LED_DELAY_MS 1000

/* Global Variables ---------------------------------------------------------*/
// Initialize queue
struct queue_t queue = {
    .head = NULL,
    .tail = NULL,
    .size = 0
};

struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} led_vals;

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

// Set all value to 0
void reset_led_vals( void ) {
    led_vals.red = 0;
    led_vals.green = 0;
    led_vals.blue = 0;
}

// Print gummy color based on measured led values
void print_gummy_color ( void ) {
    /*
                                       Gummy Color
        LED Color   |   Red     |   Green   |   Orange  |   Clear   |
        ------------+-----------+-----------+-----------+-----------+
            Red     |    X      |           |     X     |     X     |
            Green   |           |     X     |     X     |     X     |
            Blue    |           |           |           |     X     |
    */
    uint8_t red = led_vals.red;
    uint8_t green = led_vals.green;
    uint8_t blue = led_vals.blue;

    printf("========= GUMMY BEAR COLOR =========\n");
    printf("RED LED = %d\n", led_vals.red);
    printf("GREEN LED = %d\n", led_vals.green);
    printf("BLUE LED = %d\n\n", led_vals.blue);

    if (red && !green && !blue) {
        printf("GUMMY BEAR IS RED!\n");
    } else if (!red && green && !blue) {
        printf("GUMMY BEAR IS GREEN!\n");
    } else if (red && green && !blue) {
        printf("GUMMY BEAR IS ORANGE!\n");
    } else if (red && green && blue){
        printf("GUMMY BEAR IS CLEAR!\n");
    } else {
        printf("NOT A VALID GUMMY BEAR COLOR!\n");
    }

    printf("====================================\n");

}


/* Task Scheduler ------------------------------------------------------------------*/
// List of all tasks
void tasks(event_t event){
  switch (event) {
        case BUTTON_PRESSED:
            // Reset data structures
            reset_led_vals();
             // Next event
            sched_event(RED_ON);
            break;
        case RED_ON:
            // Turn red on
            set_red();
            clear_green();
            clear_blue();
            // Next event w/ timeout
            add_subtimer(LED_DELAY_MS, READ_RED);
            break;
        case READ_RED:
            // Read phototransistor and set val to red
            led_vals.red = (uint8_t)(read_photo_trans() > 0); // 0 or 1
            // Next event
            sched_event(GREEN_ON);
            break;
        case GREEN_ON:
            // Turn on green
            clear_red();
            set_green();
            clear_blue();
            // Next event w/ timeout
            add_subtimer(LED_DELAY_MS, READ_GREEN);
            break;
        case READ_GREEN:
            // Read phototransistor and set val to green
            led_vals.green = (uint8_t)(read_photo_trans() > 0); // 0 or 1
            // Next event
            sched_event(BLUE_ON);
            break;
        case BLUE_ON:
            // Turn on blue
            clear_red();
            clear_green();
            set_blue();
            // Next event w/ timeout
            add_subtimer(LED_DELAY_MS, READ_BLUE);
            break;
        case READ_BLUE:
            // Read phototransistor and set val to blue
            led_vals.blue = (uint8_t)(read_photo_trans() > 0); // 0 or 1
            // Next event
            sched_event(PRINT_COLOR);
            break;
        case PRINT_COLOR:
            print_gummy_color();
            break;
        default:
            // Fallback if a case that is not defined
            printf("[ERROR] NOT A VALID EVENT RECEIVED!\n");
            break;
    }
}

// Iterate through queue and schedules tasks in the queue
void task_scheduler(void) {
    // Start at queue head and iterate through all pending tasks
    queue_node_t* node = queue.head;
    while (node != NULL) {
        tasks(node->event);
        node = node->next; // Go to next node
    }
}

