/**
  ******************************************************************************
  * @file    hardware_stm_gpio.c 
  * @author  mortamar@andrew.cmu.edu
  * @version 1.0
  * @date    Septembr-2021
  * @brief   Controls STM32F446ze GPIO
  ******************************************************************************
  */

#include "hardware_stm_gpio.h"
#include "stm32f4xx_rcc_mort.h"
#include <cstdint>


//led 1 is connected to PB0. 
// GPIO B addresses: 0x4002 0400 - 0x4002 07FF
// GPIO C addresses: 0x4002 0800 - 0x4002 0BFF


/* MACRO definitions----------------------------------------------------------*/
//Port B addresses:
#define PORTB_BASE_ADDRESS          ((uint32_t)0x40020400)        //The first address in memory corresponding to Port B (this is in the user manual!)
// I gave you the first one, now you fill in the rest, check in the user manual what is the offset from the base address for each register!
#define PORTB_MODER_REGISTER        (PORTB_BASE_ADDRESS + 0x00) //replace the question mark with the correct offset!
#define PORTB_OTYPER_REGISTER       (PORTB_BASE_ADDRESS + 0x04)
#define PORTB_OSPEEDR_REGISTER      (PORTB_BASE_ADDRESS + 0x08)
#define PORTB_PUPDR_REGISTER        (PORTB_BASE_ADDRESS + 0x0C)
#define PORTB_IDR_REGISTER          (PORTB_BASE_ADDRESS + 0x10)
#define PORTB_ODR_REGISTER          (PORTB_BASE_ADDRESS + 0x14)
#define PORTB_BSRRL_REGISTER        (PORTB_BASE_ADDRESS + 0x18)
#define PORTB_BSRR_REGISTER         (PORTB_BASE_ADDRESS + 0x18)
#define PORTB_BSRRH_REGISTER        (PORTB_BASE_ADDRESS + 0x1A)
#define PORTB_LCKR_REGISTER         (PORTB_BASE_ADDRESS + 0x1C)
#define PORTB_AFR1_REGISTER         (PORTB_BASE_ADDRESS + 0x20)
#define PORTB_AFR2_REGISTER         (PORTB_BASE_ADDRESS + 0x24)
#define PORTB_OSPEEDR_REGISTER      (PORTB_BASE_ADDRESS + 0x08)

//Port C addresses:
#define PORTC_BASE_ADDRESS          ((uint32_t)0x40020800) 
#define PORTC_MODER_REGISTER        (PORTC_BASE_ADDRESS + 0x00)
#define PORTC_OTYPER_REGISTER       (PORTC_BASE_ADDRESS + 0x04)
#define PORTC_OSPEEDR_REGISTER      (PORTC_BASE_ADDRESS + 0x08)
#define PORTC_PUPDR_REGISTER        (PORTC_BASE_ADDRESS + 0x0C)
#define PORTC_IDR_REGISTER          (PORTC_BASE_ADDRESS + 0x10)
#define PORTC_ODR_REGISTER          (PORTC_BASE_ADDRESS + 0x14)
#define PORTC_BSRRL_REGISTER        (PORTC_BASE_ADDRESS + 0x18)
#define PORTC_BSRR_REGISTER         (PORTC_BASE_ADDRESS + 0x18)
#define PORTC_BSRRH_REGISTER        (PORTC_BASE_ADDRESS + 0x1A)
#define PORTC_LCKR_REGISTER         (PORTC_BASE_ADDRESS + 0x1C)
#define PORTC_AFR1_REGISTER         (PORTC_BASE_ADDRESS + 0x20)
#define PORTC_AFR2_REGISTER         (PORTC_BASE_ADDRESS + 0x24)

// flags MODER Register:
#define GPIO_0_MODER                0x03
#define GPIO_0_MODER_OUT            0x01
#define GPIO_0_MODER_AF             0x02
#define GPIO_1_MODER                (uint32_t)(0x03<<2)
#define GPIO_1_MODER_OUT            (uint32_t)(0x01<<2)
#define GPIO_1_MODER_AF             (uint32_t)(0x02<<2)
#define GPIO_2_MODER                (uint32_t)(0x03<<4)
#define GPIO_2_MODER_OUT            (uint32_t)(0x01<<4)
#define GPIO_2_MODER_AF             (uint32_t)(0x02<<4)
#define GPIO_3_MODER                (uint32_t)(0x03<<6)
#define GPIO_3_MODER_OUT            (uint32_t)(0x01<<6)
#define GPIO_3_MODER_AF             (uint32_t)(0x02<<6)
#define GPIO_4_MODER                (uint32_t)(0x03<<8)
#define GPIO_4_MODER_OUT            (uint32_t)(0x01<<8)
#define GPIO_4_MODER_AF             (uint32_t)(0x02<<8)
#define GPIO_5_MODER                (uint32_t)(0x03<<10)
#define GPIO_5_MODER_OUT            (uint32_t)(0x01<<10)
#define GPIO_5_MODER_AF             (uint32_t)(0x02<<10)
#define GPIO_6_MODER                0x3000
#define GPIO_6_MODER_AF             0x2000
#define GPIO_6_MODER_OUT            0x1000
#define GPIO_6_MODER_IN             0x0000
#define GPIO_6_MODER_AN             0x3000
#define GPIO_7_MODER                (uint32_t)(0x03<<14)
#define GPIO_7_MODER_OUT            (uint32_t)(0x01<<14)
#define GPIO_7_MODER_AF             (uint32_t)(0x02<<14)
#define GPIO_8_MODER                (uint32_t)(0x03<<16)
#define GPIO_8_MODER_OUT            (uint32_t)(0x01<<16)
#define GPIO_8_MODER_AF             (uint32_t)(0x02<<16)
#define GPIO_9_MODER                (uint32_t)(0x03<<18)
#define GPIO_9_MODER_OUT            (uint32_t)(0x01<<18)
#define GPIO_9_MODER_AF             (uint32_t)(0x02<<18)
#define GPIO_10_MODER               (uint32_t)(0x03<<20)
#define GPIO_10_MODER_OUT           (uint32_t)(0x01<<20)
#define GPIO_10_MODER_AF            (uint32_t)(0x02<<20)

// flags OTYPER Register:
#define GPIO_0_OTYPER               0x01
#define GPIO_0_OTYPER_PP            0x00
#define GPIO_1_OTYPER               (uint32_t)(0x01<<1)
#define GPIO_1_OTYPER_PP            0x00
#define GPIO_2_OTYPER               (uint32_t)(0x01<<2)
#define GPIO_2_OTYPER_PP            0x00
#define GPIO_3_OTYPER               (uint32_t)(0x01<<3)
#define GPIO_3_OTYPER_PP            0x00
#define GPIO_4_OTYPER               (uint32_t)(0x01<<4)
#define GPIO_4_OTYPER_PP            0x00
#define GPIO_5_OTYPER               (uint32_t)(0x01<<5)
#define GPIO_5_OTYPER_PP            0x00
#define GPIO_6_OTYPER               0x40
#define GPIO_6_OTYPER_PP            0x00
#define GPIO_7_OTYPER               (uint32_t)(0x01<<7)
#define GPIO_7_OTYPER_PP            0x00
#define GPIO_8_OTYPER               (uint32_t)(0x01<<8)
#define GPIO_8_OTYPER_PP            0x00
#define GPIO_9_OTYPER               (uint32_t)(0x01<<9)
#define GPIO_9_OTYPER_PP            0x00
#define GPIO_10_OTYPER              (uint32_t)(0x01<<10)
#define GPIO_10_OTYPER_PP           0x00

// flags OSPEEDR Register:
#define GPIO_0_OSPEEDR_HIGH_SPEED   3
#define GPIO_6_OSPEEDR              0x3000
#define GPIO_6_OSPEEDR_HIGH_SPEED   0x3000

// flags PUPDR Register:
#define GPIO_0_PUPDR                0x03
#define GPIO_0_PUPDR_NOPULL         0x00
#define GPIO_0_PUPDR_PU             0x01
#define GPIO_0_PUPDR_PD             0x02
#define GPIO_1_PUPDR                (uint32_t)(0x03<<2)
#define GPIO_1_PUPDR_NOPULL         0x00
#define GPIO_1_PUPDR_PU             (uint32_t)(0x01<<2)
#define GPIO_1_PUPDR_PD             (uint32_t)(0x02<<2)
#define GPIO_2_PUPDR                (uint32_t)(0x03<<4)
#define GPIO_2_PUPDR_NOPULL         0x00
#define GPIO_2_PUPDR_PU             (uint32_t)(0x01<<4)
#define GPIO_2_PUPDR_PD             (uint32_t)(0x02<<4)
#define GPIO_3_PUPDR                (uint32_t)(0x03<<6)
#define GPIO_3_PUPDR_NOPULL         0x00
#define GPIO_3_PUPDR_PU             (uint32_t)(0x01<<6)
#define GPIO_3_PUPDR_PD             (uint32_t)(0x02<<6)
#define GPIO_4_PUPDR                (uint32_t)(0x03<<8)
#define GPIO_4_PUPDR_NOPULL         0x00
#define GPIO_4_PUPDR_PU             (uint32_t)(0x01<<8)
#define GPIO_4_PUPDR_PD             (uint32_t)(0x02<<8)
#define GPIO_5_PUPDR                (uint32_t)(0x03<<10)
#define GPIO_5_PUPDR_NOPULL         0x00
#define GPIO_5_PUPDR_PU             (uint32_t)(0x01<<10)
#define GPIO_5_PUPDR_PD             (uint32_t)(0x02<<10)
#define GPIO_6_PUPDR                0x3000
#define GPIO_6_PUPDR_NOPULL         0x00
#define GPIO_6_PUPDR_PD             0x2000
#define GPIO_6_PUPDR_PU             0x1000
#define GPIO_7_PUPDR                (uint32_t)(0x03<<14)
#define GPIO_7_PUPDR_NOPULL         0x00
#define GPIO_7_PUPDR_PU             (uint32_t)(0x01<<14)
#define GPIO_7_PUPDR_PD             (uint32_t)(0x02<<14)
#define GPIO_8_PUPDR                (uint32_t)(0x03<<16)
#define GPIO_8_PUPDR_NOPULL         0x00
#define GPIO_8_PUPDR_PU             (uint32_t)(0x01<<16)
#define GPIO_8_PUPDR_PD             (uint32_t)(0x02<<16)
#define GPIO_9_PUPDR                (uint32_t)(0x03<<18)
#define GPIO_9_PUPDR_NOPULL         0x00
#define GPIO_9_PUPDR_PU             (uint32_t)(0x01<<18)
#define GPIO_B_PUPDR_PD             (uint32_t)(0x02<<18)
#define GPIO_10_PUPDR               (uint32_t)(0x03<<20)
#define GPIO_10_PUPOR_NOPULL        0x00
#define GPIO_10_PUPDR_PU            (uint32_t)(0x01<<20)
#define GPIO_10_PUPDR_PD            (uint32_t)(0x02<<20)

// input data register:
#define GPIO_0_IDR                  0x01
#define GPIO_1_IDR                  (uint32_t)(0x01<<1)
#define GPIO_2_IDR                  (uint32_t)(0x01<<2)
#define GPIO_3_IDR                  (uint32_t)(0x01<<3)
#define GPIO_4_IDR                  (uint32_t)(0x01<<4)
#define GPIO_5_IDR                  (uint32_t)(0x01<<5)
#define GPIO_6_IDR                  0x40
#define GPIO_7_IDR                  (uint32_t)(0x01<<7)
#define GPIO_8_IDR                  (uint32_t)(0x01<<8)
#define GPIO_9_IDR                  (uint32_t)(0x01<<9)
#define GPIO_10_IDR                 (uint32_t)(0x01<<10)

// flags AFR1 Register:
#define GPIO_0_AFR1_AF2             2
#define GPIO_0_AFR1                 0xF
#define GPIO_6_AFR1                 0xF000000
#define GPIO_6_AFR1_AF2             0x2000000

// flags ODR Register:
#define GPIO_0_ODR_HIGH             0x01
#define GPIO_1_ODR_HIGH             (uint32_t)(0x01<<1)
#define GPIO_2_ODR_HIGH             (uint32_t)(0x01<<2)
#define GPIO_3_ODR_HIGH             (uint32_t)(0x01<<3)
#define GPIO_4_ODR_HIGH             (uint32_t)(0x01<<4)
#define GPIO_5_ODR_HIGH             (uint32_t)(0x01<<5)
#define GPIO_6_ODR_HIGH             0x40
#define GPIO_7_ODR_HIGH             (uint32_t)(0x01<<7)
#define GPIO_8_ODR_HIGH             (uint32_t)(0x01<<8)
#define GPIO_9_ODR_HIGH             (uint32_t)(0x61<<9)
#define GPIO_10_ODR_HIGH            (uint32_t)(0x01<<10)

/* function definitions----------------------------------------------------------*/

void initGpioC6AsInput( void )
{
    uint32_t *reg_pointer; 
    // (1) Enable the AHB1 clock
    /* GPIOC Peripheral clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    // (2) Clear the MODER6 bits in the GPIOC_MODER register in order to have PortC6 as input.
    /* GPIOC Pin 6 as input*/
    reg_pointer = (uint32_t *)PORTC_MODER_REGISTER; // Mode register
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_6_MODER)); // Clear the bit
    *reg_pointer = *reg_pointer | GPIO_6_MODER_IN; // Set to Input -> OR 0x00 
    // (3) Set Port C pin 6 to push-pull in the GPIOC_OTYPER register
    /* PUSH-PULL Pin */
    reg_pointer = (uint32_t *)PORTC_OTYPER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_6_OTYPER)); // Clear the bit
    *reg_pointer = *reg_pointer | GPIO_6_OTYPER_PP; // Set value
    // (4) Set Port C pin 6 to High Speed port in the OSPEEDR register
    /* GPIOC pin 6 high speed */
    reg_pointer = (uint32_t *)PORTC_OSPEEDR_REGISTER;
    *reg_pointer = *reg_pointer | GPIO_6_OSPEEDR_HIGH_SPEED; // Set to high speed
    // (5) Set Port C pin 6 to be a pulled-down by setting the bits in the PUPDR register
    // Don’t have anything connected to Pin 6 at the moment, it is better to either pull it up or down.
    /* Configure pulled-down */
    reg_pointer = (uint32_t *) PORTC_PUPDR_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_6_PUPDR)); // Clear bit
    *reg_pointer = *reg_pointer | GPIO_6_PUPDR_PD; // Set to LOW to stop it floating
}


void initGpioB0AsOutput( void )
{
    uint32_t  * reg_pointer;
    // (1) Enable the AHB1 clock
    /* GPIOB Peripheral clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    // (2) Set MODER0 in the GPIOB_MODER register to Output mode by writing 0x01
    /* GPIOB0 configured as output */
    reg_pointer = (uint32_t *)PORTB_MODER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_0_MODER)); // Clear the bit
    *reg_pointer = *reg_pointer | GPIO_0_MODER_OUT; // Set as output with 0x01
    // (3) Set Port B pin 0 to push-pull in the GPIOB_OTYPER register
    /* GPIOB0 configured as push-pull */
    reg_pointer = (uint32_t *)PORTB_OTYPER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_0_OTYPER)); // Clear bit
    *reg_pointer = *reg_pointer | GPIO_0_OTYPER_PP; // Set bit
    // (5) Set Port B pin 0 to not have a pull-up or pull-down by clearing the bits in the PUPDR register
    // Since Port B pin 0 is connected to LED1, we do not need a pull-up or pull-down on it.
    /* GPIOB0 configured floating */
    reg_pointer = (uint32_t *)PORTB_PUPDR_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_0_PUPDR)); // Clear bit
    *reg_pointer = *reg_pointer | GPIO_0_PUPDR_NOPULL; // Set to no pull
    // (6) Can set Port B pin 0 to initialize as high or low by writing to the PORTB_ODR register.
    /* GPIOB0 driven high to start out with */
    reg_pointer = (uint32_t *)PORTB_ODR_REGISTER;
    *reg_pointer = *reg_pointer | GPIO_0_ODR_HIGH;
}

void toggleGPIOB0( void )
{
    uint32_t value;
    uint32_t  * reg_pointer;
    
    // get the current value of the pin 
    reg_pointer = (uint32_t *)PORTB_ODR_REGISTER;
    value = *reg_pointer & GPIO_0_ODR_HIGH; // Get the bit from register
    if (value > 0) {
        // if high, clear the bit (low)
        *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_0_ODR_HIGH));
    } else {
        // if low, set the bit (high)
        *reg_pointer = *reg_pointer | GPIO_0_ODR_HIGH;
    } 
}


void setGPIOB0( void )
{
    uint32_t *reg_pointer;
    reg_pointer = (uint32_t *)PORTB_ODR_REGISTER; // Point to register
    *reg_pointer = *reg_pointer | 0b001; // Set to 1
}
void clearGPIOB0( void )
{
    uint32_t *reg_pointer;
    reg_pointer = (uint32_t *)PORTB_ODR_REGISTER; // Point to register
    *reg_pointer = *reg_pointer & (~(uint32_t)0b001); // Clear bit
}
void setGPIOB1( void )
{
    uint32_t *reg_pointer;
    reg_pointer = (uint32_t *)PORTB_ODR_REGISTER; // Point to register
    *reg_pointer = *reg_pointer | 0b010; // Set to 1
}
void clearGPIOB1( void )
{
    uint32_t *reg_pointer;
    reg_pointer = (uint32_t *)PORTB_ODR_REGISTER; // Point to register
    *reg_pointer = *reg_pointer & (~(uint32_t)0b010); // Clear bit
}
void setGPIOB2( void )
{
    uint32_t *reg_pointer;
    reg_pointer = (uint32_t *)PORTB_ODR_REGISTER; // Point to register
    *reg_pointer = *reg_pointer | 0b100; // Set to 1
}
void clearGPIOB2( void )
{
    uint32_t *reg_pointer;
    reg_pointer = (uint32_t *)PORTB_ODR_REGISTER; // Point to register
    *reg_pointer = *reg_pointer & (~(uint32_t)0b100); // Clear bit
}

uint32_t checkGPIOC6(void)
{
    uint32_t valueC6;
    uint32_t *reg_pointer;
    // Get the current value of the pin
    reg_pointer = (uint32_t *) PORTC_IDR_REGISTER;
    valueC6 = *reg_pointer & GPIO_6_IDR;
    return valueC6;   
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


void initGpioC6AsAF2( void )
{
    uint32_t *reg_pointer;
    // (1) Enable the AHB1 clock
    /* GPIOC Peripheral clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    // (2) Set MODER6 in the GPIOC_MODER register to Alternative function mode
    /* GPIOC pin 6 alternative function */
    reg_pointer = (uint32_t * )PORTC_MODER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t) GPIO_6_MODER)); // Clear the bit
    *reg_pointer = *reg_pointer | GPIO_6_MODER_AF; // Set mode to AF2
    // (3) Set Port C pin 6 to push-pull in the GPIOC_OTYPER register
    /* GPIOC pin 6 push pull */
    reg_pointer = (uint32_t *)PORTC_OTYPER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_6_OTYPER)); // Clear the bit
    *reg_pointer = *reg_pointer | GPIO_6_OTYPER_PP; // Set to push pull
    // (4) Set Port C pin 6 to High Speed port in the OSPEEDR register
    /* GPIOC pin 6 high speed (not necessary) */ 
    reg_pointer = (uint32_t *)PORTC_OSPEEDR_REGISTER;
    *reg_pointer = *reg_pointer | GPIO_6_OSPEEDR_HIGH_SPEED; // Set to high speed
    // (5) Set Port C pin 6 to not have a pull-up or pull-down by clearing the bits in the PUPDR register
    // Note: this depends on what you have connected to the input capture pin which generates your signal.
    reg_pointer = (uint32_t *)PORTC_PUPDR_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_6_PUPDR)); // Clear the bit
    *reg_pointer = *reg_pointer | GPIO_6_PUPDR_PD; //* GPIOC pin 6 pulled down */
    // (6) Set Port C pin 6 to alternative function 2 by writing 0x2000000 in the AFRL0 bits of the AFRL register
    /* GPIOC pin 6 alternative function 2 */
    reg_pointer = (uint32_t *)PORTC_AFR1_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t) GPIO_6_AFR1));
    *reg_pointer = *reg_pointer | GPIO_6_AFR1_AF2; // Set to alt func 2
}



// Init GPIO C6 and C7 as input
void initGpioC67AsInput( void )
{
    uint32_t *reg_pointer; 
    // (1) Enable the AHB1 clock
    /* GPIOC Peripheral clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    // (2) Clear the MODER6 bits in the GPIOC_MODER register in order to have PortC6 as input.
    /* GPIOC Pin 6 as input*/
    reg_pointer = (uint32_t *)PORTC_MODER_REGISTER; // Mode register
    *reg_pointer = *reg_pointer & (~((uint32_t)(GPIO_6_MODER + GPIO_7_MODER))); // Clear the bit
    // (3) Set Port C pin 6 to push-pull in the GPIOC_OTYPER register
    /* PUSH-PULL Pin */
    reg_pointer = (uint32_t *)PORTC_OTYPER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)(GPIO_6_OTYPER + GPIO_7_OTYPER))); // Clear the bit
    *reg_pointer = *reg_pointer | (GPIO_6_OTYPER_PP + GPIO_7_OTYPER_PP); // Set value
    // (5) Set Port C pin 6 to be a pulled-down by setting the bits in the PUPDR register
    // Don’t have anything connected to Pin 6 at the moment, it is better to either pull it up or down.
    /* Configure pulled-down */
    reg_pointer = (uint32_t *) PORTC_PUPDR_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)(GPIO_6_PUPDR + GPIO_7_PUPDR))); // Clear bit
    *reg_pointer = *reg_pointer | (GPIO_6_PUPDR_PD + GPIO_7_PUPDR_PD); // Set to LOW to stop it floating
}

// Initialize B
void initGpioB012AsOutput( void ) {
    uint32_t  * reg_pointer;
    // (1) Enable the AHB1 clock
    /* GPIOB Peripheral clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    // (2) Set MODER0 in the GPIOB_MODER register to Output mode by writing 0x01
    /* GPIOB0 configured as output */
    reg_pointer = (uint32_t *)PORTB_MODER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)(GPIO_0_MODER + GPIO_1_MODER + GPIO_2_MODER))); // Clear the bit
    *reg_pointer = *reg_pointer | (GPIO_0_MODER_OUT + GPIO_1_MODER_OUT + GPIO_2_MODER_OUT); // Set as output with 0x01
    // (3) Set Port B pin 0 to push-pull in the GPIOB_OTYPER register
    /* GPIOB0 configured as push-pull */
    reg_pointer = (uint32_t *)PORTB_OTYPER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)(GPIO_0_OTYPER + GPIO_1_OTYPER + GPIO_2_OTYPER))); // Clear bit
    *reg_pointer = *reg_pointer | (GPIO_0_OTYPER_PP + GPIO_1_OTYPER_PP + GPIO_2_OTYPER_PP); // Set bit
    // (5) Set Port B pin 0 to not have a pull-up or pull-down by clearing the bits in the PUPDR register
    // Since Port B pin 0 is connected to LED1, we do not need a pull-up or pull-down on it.
    /* GPIOB0 configured floating */
    reg_pointer = (uint32_t *)PORTB_PUPDR_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)(GPIO_0_PUPDR + GPIO_1_PUPDR + GPIO_2_PUPDR))); // Clear bit
    *reg_pointer = *reg_pointer | (GPIO_0_PUPDR_NOPULL + GPIO_1_PUPDR_NOPULL + GPIO_2_PUPDR_NOPULL); // Set to no pull
    // (6) Can set Port B pin 0 to initialize as high or low by writing to the PORTB_ODR register.
    /* GPIOB0 driven high to start out with */
    reg_pointer = (uint32_t *)PORTB_ODR_REGISTER;
    *reg_pointer = *reg_pointer | (GPIO_0_ODR_HIGH + GPIO_1_ODR_HIGH + GPIO_2_ODR_HIGH);
}