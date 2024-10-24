#include "stm32f4xx_rcc_mort.h"
#include "task_scheduler.h"
#include <cstdint>
#include <stdlib.h>
#include "led.h"
#include "hardware_stm_timer3.h"
#include "input_devices.h"
#include "timer.h"


#define LED_DELAY_MS 500

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
    // Allocate memory for queue node
    queue_node_t* new_node = malloc(sizeof(queue_node_t));
    new_node->event = event; // Set event
    new_node->next = NULL; // At end of queue
    new_node->prev = queue.tail; // Point to last tail node

    if (queue.tail == NULL){
        // List is empty, this is the first node so set tail and head
        queue.tail = new_node;
        queue.head = new_node;
    } else {
        // Not empty so add to end of queue
        // Current: tail -> NULL
        // Changed to: tail -> new_node (new tail) -> NULL
        queue.tail->next = new_node;
        queue.tail = new_node;
    }
    // Increment queue's size
    queue.size++;
}


// Pop event from start of queue
event_t pop_queue(void){
    if (queue.head == NULL){
        // Nothing in queue, pop should not have been popped!
        return READY;
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
        // If queue is now empty, make sure both head/tail are NULL
        queue.head = NULL;
        queue.tail = NULL;
    }
    return ret_event;
}

// Set all stored led values to 0
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
    // Extract stored led values
    uint8_t red = led_vals.red;
    uint8_t green = led_vals.green;
    uint8_t blue = led_vals.blue;

    // Print led values to serial monitor
    printf("========= GUMMY BEAR COLOR =========\n");
    printf("RED LED = %d\n", led_vals.red);
    printf("GREEN LED = %d\n", led_vals.green);
    printf("BLUE LED = %d\n\n", led_vals.blue);

    // Decision tree to determine which gummy bear color
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
            printf("BUTTON_PRESSED\n");
            // Reset data structures
            reset_led_vals();
             // Next event
            sched_event(RED_ON);
            break;
        case RED_ON:
            printf("RED_ON\n");
            // Turn red on
            set_red();
            clear_green();
            clear_blue();
            // Next event w/ timeout
            add_subtimer(LED_DELAY_MS, READ_RED);
            break;
        case READ_RED:
            printf("READ_RED\n");
            // Read phototransistor and set val to red
            led_vals.red = (uint8_t)(read_photo_trans() > 0); // 0 or 1
            // Next event
            sched_event(GREEN_ON);
            break;
        case GREEN_ON:
            printf("GREEN_ON\n");
            // Turn on green
            clear_red();
            set_green();
            clear_blue();
            // Next event w/ timeout
            add_subtimer(LED_DELAY_MS, READ_GREEN);
            break;
        case READ_GREEN:
            printf("READ_GREEN\n");
            // Read phototransistor and set val to green
            led_vals.green = (uint8_t)(read_photo_trans() > 0); // 0 or 1
            // Next event
            sched_event(BLUE_ON);
            break;
        case BLUE_ON:
            printf("BLUE_ON\n");
            // Turn on blue
            clear_red();
            clear_green();
            set_blue();
            // Next event w/ timeout
            add_subtimer(LED_DELAY_MS, READ_BLUE);
            break;
        case READ_BLUE:
            printf("READ_BLUE\n");
            // Read phototransistor and set val to blue
            led_vals.blue = (uint8_t)(read_photo_trans() > 0); // 0 or 1
            // Next event
            sched_event(PRINT_COLOR);
            break;
        case PRINT_COLOR:
            printf("PRINT_COLOR\n");
            // Print the color then clear the LEDs
            print_gummy_color();
            clear_all_LEDs();
            break;
        default:
            // Fallback if a case that is not defined
            printf("[ERROR] NOT A VALID EVENT RECEIVED: %d!\n", event);
            break;
    }
}

// Iterate through queue and schedules tasks in the queue
void task_scheduler(void) {
    // Pop the first event on the queue
    event_t event;
    while ((event = pop_queue()) != READY) {
        // READY if queue is empty, else keep popping
        tasks(event);
    }
}


