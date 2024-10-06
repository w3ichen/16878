#include "main.h"
#include "debug_mort.h"
#include "nucleo_led.h"

void delay(int num){
    for (int i=0; i<num; i++){
        // busy wait
    }
}

int main (void)
{
    /* Initializations */
    init_LED1(); //uncomment once you have filled in the function
    while(1)
    {
        // toggle_LED1(); //uncomment once you have filled in the function
        set_LED1_to_C6();
        // debugprintHelloWorld();
        delay(10000000);
    }
}