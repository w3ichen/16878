#include "main.h"
#include "debug_mort.h"
#include "nucleo_led.h"
#include "hardware_stm_gpio.h"

int main (void)
{
    /* Initializations */
    /*
        Inputs:
            C6 = Phototransistor input
            C7 = User button press input
        Outputs:
            B0 = Red LED
            B1 = Green LED
            B2 = Blue LED
    */
    initGpioC67AsInput();
    initGpioB012AsOutput();
}

