#include "main.h"
#include "debug_mort.h"
#include "led.h"
#include "input_devices.h"
#include <cstdint>
#include "hardware_stm_timer3.h"


void delay(int num){
    for (int i=0; i<num; i++){
        // busy wait
    }
}

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

    uint32_t btn, photo_trans;
    while (1){
        btn = read_button();
        photo_trans = read_photo_trans();
        printf("btn=%u | photo=%u\n", btn, photo_trans);
        
        delay(10000000);
    }

}

