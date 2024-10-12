#include "main.h"
#include "debug_mort.h"
#include "nucleo_led.h"
#include "hardware_stm_timer3.h"
#include "hardware_stm_timer3.h"

// --------------------------
// Select code to run
// #define HELLO_WORLD
// #define PART1_Q1
// #define PART1_Q2
// #define PART1_Q3
// #define PART1_Q4
#define PART1_Q5

// --------------------------


// -- Helper functions ------------------------

void delay(int num){
    for (int i=0; i<num; i++){
        // busy wait
    }
}


// -- Main functions ------------------------

#ifdef PART1_Q5
// Toggling LED1 using timer 3 channel 3 in PWM mode
int main(void){
    // Setup PortB pin 0 as an output so you can access LED1
    init_LED1_output();
    // Setup Timer 3 channel 3 in pwm mode and map the output to PortB pin 0.
    initTimer3AsPWM();
}
#endif


#ifdef PART1_Q4
// Reads input capture flag and prints it
int main (void){
    /* Variable declarations */
    uint16_t timer_val = 0;
    static uint16_t prev_printed_val = 0;
    /* Initializations */
    initTimer3CH1AsInputCaptureOnPC6(); // Setup PortC6 and Timer3 channel 1 as an input capture
    while (1){
        // 
        // Read the input capture flag from the status register
        timer_val = getCaptureTimer3CH1();
        if (timer_val > 0 && (timer_val != prev_printed_val)) {
            // If triggered, clear it and print the timer value to the screen.
            clearTimer3StatusRegister();
            printf("Timer Value = %d\n", timer_val);
            prev_printed_val = timer_val;
        }

    }
}
#endif

#ifdef PART1_Q3
// Toggle LED at 1Hz using output compare toggle mode
int main (void)
{
    /* Initializations */
    init_LED1(); 
    initTimerAsOutputComparePB0();
    // No need for compare checks, it's mapped directly to LED.
    // AF2 - ties LED directly to the timer
}
#endif


#ifdef PART1_Q2
// Sets LED state based on C6 input
int main (void)
{
    /* Initializations */
    init_LED1();
    while(1)
    {
        set_LED1_to_C6();
        delay(10000000);
    }
}
#endif


#ifdef PART1_Q1
// Toggles LED on and off with delay
int main (void)
{
    /* Initializations */
    init_LED1(); //uncomment once you have filled in the function
    while(1)
    {
        toggle_LED1(); //uncomment once you have filled in the function
        delay(10000000);
    }
}
#endif

#ifdef HELLO_WORLD
// Prints hello world
int main (void)
{
    while(1)
    {
        debugprintHelloWorld();
        delay(10000000);
    }
}
#endif
