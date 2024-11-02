#include "hardware_stm_gpio.h"
#include "stm32f4xx_rcc_mort.h"
#include <cstdint>


/* function definitions----------------------------------------------------------*/
void initGpioF7AsAnalog( void ) {
    uint32_t* reg_pointer;
    // 1. Enable the AHB1 clock for GPIO F clock:
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    // 2. Setup GPIO F pin 7 as analog by writing setting bits 14 and 15 in the MODER register
    reg_pointer = (uint32_t*) PORTF_MODER_REGISTER;
    *reg_pointer = *reg_pointer | ((uint32_t) GPIO_7_MODER);
    // 3. Setup GPIO F pin 7 to be a push-pull output by writing to the OTYPER register
    reg_pointer = (uint32_t*) PORTF_OTYPER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_7_OTYPER)); // First clear bit
    *reg_pointer = *reg_pointer | GPIO_7_OTYPER_PP; // Set bit
    // 4. Setup GPIO F pin 7 to be floating by writing to the PUPDR register
    reg_pointer = (uint32_t*) PORTF_PUPDR_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_7_PUPDR));
}

void initGpioF789AsAnalog( void ) {
    uint32_t* reg_pointer;
    // 1. Enable the AHB1 clock for GPIO F clock:
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    // 2. Setup GPIO F pin 7,8,9 as analog by writing setting bits 14 and 15 in the MODER register
    reg_pointer = (uint32_t*) PORTF_MODER_REGISTER;
    *reg_pointer = *reg_pointer | ((uint32_t)GPIO_7_MODER + (uint32_t)GPIO_8_MODER + (uint32_t)GPIO_9_MODER);
    // 3. Setup GPIO F pin 7,8,9 to be a push-pull output by writing to the OTYPER register
    reg_pointer = (uint32_t*) PORTF_OTYPER_REGISTER;
    // First clear the value, then set the value
    *reg_pointer = *reg_pointer & (~((uint32_t)(GPIO_7_OTYPER + GPIO_8_OTYPER + GPIO_9_OTYPER)));
    *reg_pointer = *reg_pointer | ((uint32_t)(GPIO_7_OTYPER_PP + GPIO_8_OTYPER_PP + GPIO_9_OTYPER_PP));
    // 4. Setup GPIO F pin 7,8,9 to be floating by writing to the PUPDR register
    reg_pointer = (uint32_t*) PORTF_PUPDR_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)(GPIO_7_PUPDR + GPIO_8_PUPDR + GPIO_9_PUPDR))); // Clear it so floating
}
