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

// Flags ODR Register:
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

// Port F addresses:
#define PORTF_BASE_ADDRESS          ((uint32_t)0x40021400) // 0x4002 1400 - 0x4002 17FF
#define PORTF_MODER_REGISTER        (PORTF_BASE_ADDRESS + 0x00)
#define PORTF_OTYPER_REGISTER       (PORTF_BASE_ADDRESS + 0x04)
#define PORTF_OSPEEDR_REGISTER      (PORTF_BASE_ADDRESS + 0x08)
#define PORTF_PUPDR_REGISTER        (PORTF_BASE_ADDRESS + 0x0C)

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
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_7_OTYPER));
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
    *reg_pointer = *reg_pointer | ((uint32_t) (GPIO_7_MODER + GPIO_8_MODER + GPIO_9_MODER));
    // 3. Setup GPIO F pin 7,8,9 to be a push-pull output by writing to the OTYPER register
    reg_pointer = (uint32_t*) PORTF_OTYPER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)(GPIO_7_OTYPER + GPIO_8_OTYPER + GPIO_9_OTYPER)));
    // 4. Setup GPIO F pin 7,8,9 to be floating by writing to the PUPDR register
    reg_pointer = (uint32_t*) PORTF_PUPDR_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)(GPIO_7_PUPDR + GPIO_8_PUPDR + GPIO_9_PUPDR)));
}





