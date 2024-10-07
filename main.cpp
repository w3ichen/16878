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
#define PART1_Q4
// --------------------------


void delay(int num){
    for (int i=0; i<num; i++){
        // busy wait
    }
}


// TODO: not working!!!
// #ifdef PART1_Q4
// int main (void){
//     /* Variable declarations */
//     uint16_t timer_val = 0;
//     /* Initializations */
//     initTimer3CH1AsInputCaptureOnPC6(); // Setup PortC6 and Timer3 channel 1 as an input capture

//     while (1){
//         // Read the input capture flag from the status register
//         timer_val = getCaptureTimer3CH1();
//         if (timer_val > 0) {
//             // If triggered, clear it and print the timer value to the screen.
//             clearTimer3StatusRegister();
//             printf("Timer Value = %d\n", timer_val);
//         }
//     }
// }
// #endif

// TODO: not working!!!
// #ifdef PART1_Q3
// int main (void)
// {
//     /* Initializations */
//     init_LED1(); 
//     initTimerAsOutputComparePB0();
//     while(1)
//     {
//         toggle_LED1();

//     }
// }
// #endif

#ifdef PART1_Q2
int main (void)
{
    /* Initializations */
    init_LED1(); //uncomment once you have filled in the function
    while(1)
    {
        set_LED1_to_C6();
        delay(10000000);
    }
}
#endif

#ifdef PART1_Q1
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
int main (void)
{
    while(1)
    {
        debugprintHelloWorld();
        delay(10000000);
    }
}
#endif
