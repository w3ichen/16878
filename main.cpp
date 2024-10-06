#include "main.h"
#include "debug_mort.h"
#include "nucleo_led.h"

// --------------------------
// Select code to run
// #define HELLO_WORLD
// #define PART1_Q1
// #define PART1_Q2
#define PART1_Q3
// --------------------------


void delay(int num){
    for (int i=0; i<num; i++){
        // busy wait
    }
}


#ifdef PART1_Q3
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
