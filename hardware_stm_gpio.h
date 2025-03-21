/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HARDWARE_STM_GPIO_H_
#define __HARDWARE_STM_GPIO_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Macros for Everyone--------------------------------------------------------*/
#define PIN_0   0
#define PIN_1   1
#define PIN_2   2
#define PIN_3   3
#define PIN_4   4
#define PIN_5   5
#define PIN_6   6
#define PIN_7   7
#define PIN_8   8
#define PIN_9   9
#define PIN_10  10


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
#define GPIO_8_AFR1_AF2             0b0010   
#define GPIO_8_AFR1                 0xF

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
#define PORTF_IDR_REGISTER          (PORTF_BASE_ADDRESS + 0x10)


// OFFSETS

#define MODER_REG_OFFSET    (uint32_t) 0x00
#define OTYPER_REG_OFFSET   (uint32_t) 0x04
#define OSPEEDR_REG_OFFSET  (uint32_t) 0x08
#define PUPDR_REG_OFFSET    (uint32_t) 0x0c
#define IDR_REG_OFFSET      (uint32_t) 0x10
#define ODR_REG_OFFSET      (uint32_t) 0x14
#define AFR1_REG_OFFSET     (uint32_t) 0x20
#define AFR2_REG_OFFSET     (uint32_t) 0x24

//flags MODER Register:
#define MODER_INPUT (uint16_t) 0b00
#define MODER_OUPUT (uint16_t) 0b01
#define MODER_AF   (uint16_t) 0b10
#define MODER_ANLG  (uint16_t) 0b11


//flags OTYPER Register:
#define OTYPER_PP   (uint16_t) 0b00
#define OTYPER_OD   (uint16_t)  0b01

//flags OSPEEDR Register:
#define OSPEEDR_LOW     (uint16_t)  0b00
#define OSPEEDR_MED     (uint16_t)  0b01
#define OSPEEDR_FAST    (uint16_t)  0b10
#define OSPEEDR_HIGH    (uint16_t)  0b11

//flags PUPDR Register:
#define PUPDR_FLOAT (uint16_t)  0b00
#define PUPDR_UP    (uint16_t)  0b01
#define PUPDR_DOWN  (uint16_t)  0b10
#define PUPDR_RSVD  (uint16_t)  0b11

/*Function definitions---------------------------------------------------------*/
uint8_t read_b6(void);
uint8_t read_c6(void);
void initGpioF7AsAnalog( void );
void initGpioF789AsAnalog( void );
void initGpioB0AsAF2( void );
void initGpioC8AsAF2( void );
float map_analog_value(int analog_adc_val);

void initGpioAsInput(uint32_t BASE_ADDR, uint8_t pin);
void initGpioAsAnalog(uint32_t BASE_ADDR, uint8_t pin);
void initGpioAsOutput(uint32_t BASE_ADDR, uint8_t pin);
uint8_t read_pin(uint32_t BASE_ADDR, uint32_t pin);

#ifdef __cplusplus
}
#endif

#endif /*__GPIO_H */
