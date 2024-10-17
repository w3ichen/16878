#include "main.h"
#include "debug_mort.h"
#include "led.h"
#include "input_devices.h"
#include <cstdint>
#include "timer.h"
#include "task_scheduler.h"

int main (void)
{
    /* Initializations */
    /*
        Inputs:
            C6 = User button press input
            C7 = Phototransistor input
        Outputs:
            B0 = Red LED
            B1 = Green LED
            B2 = Blue LED
    */
    // Initializations
    init_leds();
    init_input_devices();
    init_timer_ms();

    while (1){
        // Check for any expired timers
        check_subtimers();
        // Check for tasks in queue and then execute them
        task_scheduler();
    }

}

