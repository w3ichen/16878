#include "hardware_stm_gpio.h"
#include "stm32f4xx_rcc_mort.h"
#include <cstdint>


#define MAX_POTENTIOMETER_VAL 3920

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


// Set Port B pin 0 as AF2, which connects it to timer 3
void initGpioB0AsAF2( void )
{
    uint32_t *reg_pointer;
    // (1) Enable the AHB1 clock
    /* GPIGB Peripheral clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    // (2) Set MODER0 in the GPIOB_MODER register to Alternative function mode
    /* GPIO B as an alternative function */
    reg_pointer = (uint32_t *)PORTB_MODER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)0b11)); // Clear the bit
    *reg_pointer = *reg_pointer | GPIO_0_MODER_AF; // Set as AF
    // (3) Set Port B pin 0 to push-pull in the GPIOB_OTYPER register
    /* GPIO B 0 push pull output */
    reg_pointer = (uint32_t *)PORTB_OTYPER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t) 0b01)); // Clear the bit
    *reg_pointer = *reg_pointer | 0b00; // Just for completenes, obviously not needed
    // (5) Set Port B pin 0 to not have a pull-up or pull-down by clearing the bits in the PUPDR register
    /* GPIO B 0 floating */
    reg_pointer = (uint32_t *)PORTB_PUPDR_REGISTER;
    *reg_pointer = *reg_pointer & (~( (uint32_t)0b11)); // Clear the bit
    *reg_pointer = *reg_pointer | 0b00; // Set as floating
    // (6) Set Port B pin 0 to alternative function 2 by writing 0b0010 in the AFRL0 bits of the AFRL register
    /* GPIO BO as alternative function 2 */
    reg_pointer = (uint32_t *)PORTB_AFR1_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_0_AFR1)); // Clear the bits
    *reg_pointer = *reg_pointer | GPIO_0_AFR1_AF2; // Set as alt func 2
}

// Set Port C pin 8 as AF2, which connects it to timer 3
void initGpioC8AsAF2( void )
{
    uint32_t *reg_pointer;
    // (1) Enable the AHB1 clock
    /* GPIOC Peripheral clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    // (2) Set MODER8 in the GPIOC_MODER register to Alternative function mode
    /* GPIO C as an alternative function */
    reg_pointer = (uint32_t *)PORTC_MODER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)0b11 << 16)); // Clear the bit
    *reg_pointer = *reg_pointer | GPIO_8_MODER_AF; // Set as AF
    // (3) Set Port C pin 8 to push-pull in the GPIOC_OTYPER register
    /* GPIO C 8 push pull output */
    reg_pointer = (uint32_t *)PORTC_OTYPER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t) 0b01 << 8)); // Clear the bit
    *reg_pointer = *reg_pointer | (0b00 << 8); // Just for completenes, obviously not needed
    // (5) Set Port C pin 8 to not have a pull-up or pull-down by clearing the bits in the PUPDR register
    /* GPIO C 8 floating */
    reg_pointer = (uint32_t *)PORTC_PUPDR_REGISTER;
    *reg_pointer = *reg_pointer & (~( (uint32_t)0b11 << 16)); // Clear the bit
    *reg_pointer = *reg_pointer | (0b00 << 16); // Set as floating
    // (6) Set Port C pin 8 to alternative function 2 by writing 0b0010 in the AFRH8 bits of the AFRH register
    /* GPIO C8 as alternative function 2 */
    reg_pointer = (uint32_t *)PORTC_AFR2_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_8_AFR1)); // Clear the bits
    *reg_pointer = *reg_pointer | GPIO_8_AFR1_AF2; // Set as alt func 2
}

void initGpioB1AsOutput( void )
{
    uint32_t *reg_pointer;
    // (1) Enable the AHB1 clock
    /* GPIOB Peripheral clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    // (2) Set MODER1 in the GPIOB_MODER register to Output mode by writing 0x01
    /* GPIOB1 configured as output */
    reg_pointer = (uint32_t *)PORTB_MODER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_1_MODER)); // Clear the bit
    *reg_pointer = *reg_pointer | GPIO_1_MODER_OUT; // Set as output with 0x01
    // (3) Set Port B pin 1 to push-pull in the GPIOB_OTYPER register
    /* GPIOB1 configured as push-pull */
    reg_pointer = (uint32_t *)PORTB_OTYPER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_1_OTYPER)); // Clear bit
    *reg_pointer = *reg_pointer | GPIO_1_OTYPER_PP; // Set bit
    // (5) Set Port B pin 1 to not have a pull-up or pull-down by clearing the bits in the PUPDR register
    // Since Port B pin 1 is connected to LED1, we do not need a pull-up or pull-down on it.
    /* GPIOB1 configured floating */
    reg_pointer = (uint32_t *)PORTB_PUPDR_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_1_PUPDR)); // Clear bit
    *reg_pointer = *reg_pointer | GPIO_1_PUPDR_NOPULL; // Set to no pull
    // (6) Can set Port B pin 1 to initialize as high or low by writing to the PORTB_ODR register.
    /* GPIOB1 driven high to start out with */
    reg_pointer = (uint32_t *)PORTB_ODR_REGISTER;
    *reg_pointer = *reg_pointer | GPIO_1_ODR_HIGH;
}

void setGPIOB1( void )
{
    uint32_t *reg_pointer;
    reg_pointer = (uint32_t *)PORTB_ODR_REGISTER; // Point to register
    *reg_pointer = *reg_pointer | (0b010); // Set to 1
}
void clearGPIOB1( void )
{
    uint32_t *reg_pointer;
    reg_pointer = (uint32_t *)PORTB_ODR_REGISTER; // Point to register
    *reg_pointer = *reg_pointer & (~(uint32_t)(0b010)); // Clear bit
}

void enableMotor( void ) {
    setGPIOB1();
}
void disableMotor( void ) {
    clearGPIOB1();
}

float map_analog_value(int analog_adc_val) {
    // Max ADC output from potentiometer is ~3920

    // Ensure the input is within the valid range
    if (analog_adc_val < 0) {
        analog_adc_val = 0;
    } else if (analog_adc_val > MAX_POTENTIOMETER_VAL) {
        analog_adc_val = MAX_POTENTIOMETER_VAL;
    }
    // Map the value from [0, 3920] to [0, 1]
    return (float)analog_adc_val / (float)MAX_POTENTIOMETER_VAL;
}
