/**
  ******************************************************************************
  * @file    nucleo_led.c 
  * @author  mortamar@andrew.cmu.edu
  * @version 1.0
  * @date    Septembr-2021
  * @brief   Controls the LED's on the nucleo board
  ******************************************************************************
  */

#include "hardware_stm_gpio.h"
#include "nucleo_led.h"

/************************************
* Initializes LED1 on the nucleo Board which is connected to Port B Pin 0
*************************************/
void init_LED1(void )
{
    // Call something from hardware_stm_gpio   
    initGpioB0AsOutput();
    initGpioC6AsInput();
}
/************************************
* Toggles LED1 
*************************************/
void toggle_LED1( void )
{
    // Call something else from hardware_stm_gpio
    toggleGPIOB0();
}
/************************************
* Sets LED1 value of input C6
*************************************/
void set_LED1_to_C6( void )
{
    static int prev_C6_val = -1;
    int C6_val = checkGPIOC6();
    printf("C6_val=%d\n", C6_val);
    if (prev_C6_val != C6_val){
        // Value has changed, need to set it!
        if (C6_val > 0){
            // Is HIGH, then turn LED1 on!
            setGPIOB0();
        }else{
            // Is HIGH, then turn LED1 off!
            clearGPIOB0();
        }
        prev_C6_val = C6_val;
    }
}

