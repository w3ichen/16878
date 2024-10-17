#include "hardware_stm_gpio.h"
#include "led.h"

void init_leds(void) {
    initGpioB012AsOutput();
    // Start with all LEDs off
    clear_all_LEDs();
}

void set_red( void){
    setGPIOB0();
}
void clear_red( void ){
    clearGPIOB0();
}
void set_green( void){
    setGPIOB1();
}
void clear_green( void ){
    clearGPIOB1();
}
void set_blue( void){
    setGPIOB2();
}
void clear_blue( void ){
    clearGPIOB2();
}

void clear_all_LEDs(void) {
    clear_red();
    clear_green();
    clear_blue();
}