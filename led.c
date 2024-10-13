#include "hardware_stm_gpio.h"



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

void clear_all_LED(void) {
    clear_red();
    clear_green();
    clear_blue();
}