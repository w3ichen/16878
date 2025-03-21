#include "stm32f4xx_rcc_mort.h"
#include "hardware_stm_gpio.h"
#include "hardware_stm_timer3.h"
#include "hardware_stm_interrupt.h"
#include <cstdint>

#define TIM3_BASE_ADDRESS               ((uint32_t)0x40000400)
#define TIM3_CR1_REGISTER_1             (TIM3_BASE_ADDRESS + 0x00) // Timer 3 control register 1 -> accessed as a 16 bit register

// Flags for CR1 register:
#define CLOCK_DIVISION_BITS             (uint16_t)0x600
#define COUNTER_ENABLE_BIT              (uint16_t)0x01
#define UPDATE_REQUEST_JUST_OVERFLOW    (uint16_t) 0x02
#define TIM3_CR1_REGISTER_2             (TIM3_BASE_ADDRESS + 0x04) // Timer 3 control register 2
#define TIM3_COUNTER_REGISTER           (TIM3_BASE_ADDRESS + 0x24) // Timer 3 counter register
#define TIM3_PRESCALER_REGISTER         (TIM3_BASE_ADDRESS + 0x28) // The valid number is a 16 bit number here
#define TIM3_AUTORELOAD_REGISTER        (TIM3_BASE_ADDRESS + 0x2C) // The valid number is a 16 bit number here
#define TIM3_EVENT_GEN_REGISTER         (TIM3_BASE_ADDRESS + 0x14)
#define TIM3_STATUS_REGISTER            (TIM3_BASE_ADDRESS + 0x10)

// Flags for Status register:
#define TIM_UIF                         0x01
#define TIM_CH1_CC1IF                   0x02
#define TIM_CH3_CC3IF                   0x8 // timer channel 3 capture/copare interrupt match

#define TIM3_INTERRUPT_ENABLE_REGISTER (TIM3 BASE ADDRESS + 0x0C)

// Flags for interrupt enable register: 
#define TIM_CH3_CC_INTERRUPT_ENABLE     0x8
#define TIM_UPDATE_INTERRUPT_ENABLE     0x1

#define TIM3_CAPTURE_COMPARE_MODE_1_REGISTER (TIM3_BASE_ADDRESS + 0x18)
#define TIM3_CAPTURE_COMPARE_MODE_2_REGISTER (TIM3_BASE_ADDRESS + 0x1C)

// Flags for TIM3_CCMR registers:
#define TIM_CCMR13_OC1M_0 (0b00010000)
#define TIM_CCMR13_OC1M_1 (0b00100000)
#define TIM_CCMR13_OC1M_2 (0b01000000)
#define TIM_CCMR13_OCPE (0b00001000)
#define TIM_CCMR13_CC3S (0b00000011)
#define TIM_CCRM13_OC3PE (0b00001000)
#define TIM_CCMR13_OUTPUT 0x00
#define TIM_CCMR13_OCM_012              (TIM_CCMR13_OC1M_2 | TIM_CCMR13_OC1M_1 | TIM_CCMR13_OC1M_0)
#define TIM_CCMR13_PWM1                 (TIM_CCMR13_OC1M_2 |TIM_CCMR13_OC1M_1)
#define TIM_CCMR13_CC1S_INPUT_TI1       0x01
#define TIM_CCMR13_IC1F_N2              ((0x01)<<4)
#define TIM_CCMR13_IC1F_N8              ((0x03)<<4)

#define TIM3_COMPARE_1_REGISTER         (TIM3_BASE_ADDRESS + 0x34)
#define TIM3_COMPARE_2_REGISTER         (TIM3_BASE_ADDRESS + 0x38)
#define TIM3_COMPARE_3_REGISTER         (TIM3_BASE_ADDRESS + 0x3C)
#define TIM3_COMPARE_4_REGISTER         (TIM3_BASE_ADDRESS + 0x40)

#define TIM3_CAPTURE_COMPARE_ENABLE_REGISTER (TIM3_BASE_ADDRESS + 0x20)

// Flags for TIM3_CCER registers for output:
#define TIM3_CCER_CC3E                  (0x0100)
#define TIM3_CCER_CC1E                  1

// Flags for TIM_CCER register for input capture:
// CCINP and CC1P bits select the active polarity of TIIFP1 and TI2FP1 for trigger or capture opeartions
#define TIM3_CH1_IN_POLARITY_BITS       0xF
#define TIM3_CH1_IN_POLARITY_RISING     0x00
#define TIM3_CH1_ENABLE                 0x01

#define TIM3_CNT            (TIMER_3_BASE_ADDR + TIM_CNT_OFFSET)
#define TIM_CNT_OFFSET 0x24
#define TIMER_3_BASE_ADDR   0x40000400



// duty_cycle in range 0-1
void setTimer3PWMDutyCycle( float duty_cycle  ) {
    uint16_t *reg_pointer_16; 
    uint16_t autoreloadvalue = 3; // For 30kHz
    // Set the value to compare to in CCR3, which will set the duty cycle. For example if CCR3 = autoreload/2, then the duty cycle will be 50%.
    reg_pointer_16 = (uint16_t *)TIM3_COMPARE_3_REGISTER; // CCR3
    *reg_pointer_16 = autoreloadvalue * duty_cycle;
}

void initTimer3AsPWM( void )
{
    uint16_t *reg_pointer_16; 
    // (1) Enable the APB1 clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    // (2) Clear the update event flag in the status register TIM3_SR
    reg_pointer_16 = (uint16_t *)TIM3_STATUS_REGISTER;
    *reg_pointer_16 = 0;
    // (3) Upload the pre-scale value to TIM3_PSC
    uint16_t prescalervalue = 999; // For 30kHz
    reg_pointer_16 = (uint16_t *)TIM3_PRESCALER_REGISTER;
    *reg_pointer_16 = prescalervalue;
    // (4) Set the wanted period value to the autoreload register TIM3_ARR
    reg_pointer_16 = (uint16_t *)TIM3_AUTORELOAD_REGISTER;
    uint16_t autoreloadvalue = 3; // For 30kHz
    *reg_pointer_16 = autoreloadvalue; 
    // (5) Select PWM Mode 1 for Timer 3 channel 3 by writing 110 to the OC3M bit fields in the CCMR2 register
    reg_pointer_16 = (uint16_t *)TIM3_CAPTURE_COMPARE_MODE_2_REGISTER; // CCMR2
    *reg_pointer_16 = *reg_pointer_16 & (~((uint32_t)TIM_CCMR13_OCM_012)); // Clear the OCM_012 bits
    *reg_pointer_16 = *reg_pointer_16 | TIM_CCMR13_OC1M_2 | TIM_CCMR13_OC1M_1; // 110 
    // (6) Set channel 3 of Timer 3 to an output by clearing the CC3S bits in the CCMR2 register
    reg_pointer_16 = (uint16_t *)TIM3_CAPTURE_COMPARE_MODE_2_REGISTER; // CCMR2
    *reg_pointer_16 = *reg_pointer_16 & (~((uint32_t)TIM_CCMR13_CC3S)); // clear last 2 bits
    // (7) Set the value to compare to in CCR3, which will set the duty cycle. For example if CCR3 = autoreload/2, then the duty cycle will be 50%.
    reg_pointer_16 = (uint16_t *)TIM3_COMPARE_3_REGISTER; // CCR3
    *reg_pointer_16 = autoreloadvalue/2;
    // (8) Enable the Preload register for Timer 3 channel 3 by setting the OC3PE bit in the CCMR2 register
    reg_pointer_16 = (uint16_t *)TIM3_CAPTURE_COMPARE_MODE_2_REGISTER; // CCMR2
    *reg_pointer_16 = *reg_pointer_16 | TIM_CCRM13_OC3PE;
    // (9) Enable the TIM3 channel 3 by setting the CC3E bit in the CCER register
    reg_pointer_16 = (uint16_t *)TIM3_CAPTURE_COMPARE_ENABLE_REGISTER; // CCER
    *reg_pointer_16 = *reg_pointer_16 | TIM3_CCER_CC3E;
    // (10) Enable the timer subsystem by setting the CEN bit in TIM3_CR1
    reg_pointer_16 = (uint16_t *)TIM3_CR1_REGISTER_1; // TIM3_CR1
    *reg_pointer_16 = *reg_pointer_16 | COUNTER_ENABLE_BIT;
}

uint32_t getTimerTime()
{
    uint16_t* register_value;
    uint16_t cnt;
    register_value = (uint16_t*) TIM4_CNT;
    cnt = *register_value;
    return cnt;
}