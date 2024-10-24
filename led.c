#include "hardware_stm_gpio.h"
#include "led.h"

void init_leds(void) {
    initGpioB012AsOutput(); // Init GPIO B0, B1, B2 as output
    clear_all_LEDs(); // Start with all LEDs off
}
void set_red( void){
    setGPIOB0(); // Set B0 to 1
}
void clear_red( void ){
    clearGPIOB0(); // Set B0 to 0
}
void set_green( void){
    setGPIOB1();  // Set B1 to 1
}
void clear_green( void ){
    clearGPIOB1(); // Set B1 to 0
}
void set_blue( void){
    setGPIOB2(); // Set B2 to 1
}
void clear_blue( void ){
    clearGPIOB2(); // Set B2 to 0
}
void clear_all_LEDs(void) {
    clear_red();
    clear_green();
    clear_blue();
}

