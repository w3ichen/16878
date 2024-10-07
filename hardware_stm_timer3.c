#include "stm32f4xx_rcc_mort.h"
#include "hardware_stm_gpio.h"
#include "hardware_stm_timer3.h"

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
#define TIM_CCMR13_OC1M_0               (0b00010000)
#define TIM_CCMR13_OC1M_1               (0b00100000)
#define TIM_CCMR13_OC1M_2               (0b01000000)
#define TIM_CCMR13_OCM_012              (TIM_CCMR13_OC1M_2 | TIM_CMR13_OC1M_1 | TIM_CCMR13_OC1M_0)
#define TIM_CCMR13_PWM1                 (TIM_CCMR13_OC1M_2 |TIM_CCMR13_OC1M_1)
#define TIM_CCMR13_OCPE                 (0b00001000)
#define TIM_CCMR13_OUTPUT               0x00
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



// Initialize timer3
void initTimer3( void )
{
    uint16_t *reg_pointer_16;
    /* Timer 3 APB clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    // Set status register to 0 to disable it before making changes
    reg_pointer_16 = (uint16_t *)TIM3_STATUS_REGISTER;
    *reg_pointer_16 = 0;
    // Compute and set the prescaler value
    /* Compute the prescaler value */
    uint16_t PrescalerValue2 = 9999; // (uint16_t) ((SystemCoreClock / 2) / 90000000) - 1;
    reg_pointer_16 = (uint16_t *)TIM3_PRESCALER_REGISTER;
    *reg_pointer_16 = PrescalerValue2;
    // Set the autoreload register to what to count ti
    reg_pointer_16 = (uint16_t *)TIM3_AUTORELOAD_REGISTER;
    *reg_pointer_16 = 65500;
    // Set the CR1 register
    reg_pointer_16 = (uint16_t *)TIM3_CR1_REGISTER_1;
    // Disabling update (UDIS)
    *reg_pointer_16 = *reg_pointer_16 | COUNTER_ENABLE_BIT;
}


void initTimerAsOutputComparePB0( void )
{
    uint16_t *reg_pointer_16; 

    initGpioB0AsAF2();

    /* Timer 3 APB clock enable */
    RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM3, ENABLE);
    // Set status register to 0
    reg_pointer_16 = (uint16_t *)TIM3_STATUS_REGISTER;
    *reg_pointer_16 = 0;
    // Compute and set prescaler register
    uint16_t PrescalerValue2 = 999; // (uint16 t) ((SystemCoreClock / 2) / 90000000) - 1:
    reg_pointer_16 = (uint16_t *)TIM3_PRESCALER_REGISTER;
    *reg_pointer_16 = PrescalerValue2;
    // Set autoreloader register
    reg_pointer_16 = (uint16_t *)TIM3_AUTORELOAD_REGISTER;
    uint16_t autoreloadvalue = 0xFFFF;
    *reg_pointer_16 = autoreloadvalue;
    // Setup OCREF to toggle with TIMx_CNT = TIMx_CCR3
    reg_pointer_16 = (uint16_t *)TIM3_CAPTURE_COMPARE_MODE_2_REGISTER;
    *reg_pointer_16 = *reg_pointer_16 | TIM_CCMR13_OC1M_1 | TIM_CCMR13_OC1M_0 | TIM_CCMR13_OUTPUT;
    // Set the compare value:
    reg_pointer_16 = (uint16_t *)TIM3_COMPARE_3_REGISTER;
    *reg_pointer_16 = autoreloadvalue/2;
    // Enable the TIM3 channel 3 and keep the default configuration for channel polarity
    reg_pointer_16 = (uint16_t *)TIM3_CAPTURE_COMPARE_ENABLE_REGISTER;
    *reg_pointer_16 = *reg_pointer_16 | TIM3_CCER_CC3E;
    // Enable TIM3
    reg_pointer_16 = (uint16_t *)TIM3_CR1_REGISTER_1;
    *reg_pointer_16 = *reg_pointer_16 | COUNTER_ENABLE_BIT;
}


// Setup PortC6 and Timer3 channel 1 as an input capture
void initTimer3CH1AsInputCaptureOnPC6( void )
{
    uint16_t *reg_pointer_16;
    initGpioC6AsAF2(); // initialize port C6 as alternate function
    /* Timer 3 APB elock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    
     // Set status register to 0
    reg_pointer_16 = (uint16_t *)TIM3_STATUS_REGISTER;
    *reg_pointer_16 = 0;
    // Compute and set prescaler register
    reg_pointer_16 = (uint16_t *) TIM3_PRESCALER_REGISTER;
    uint16_t prescalerValue2 = 9999;
    *reg_pointer_16 = prescalerValue2;
    // Set autoreloader register
    reg_pointer_16 = (uint16_t *)TIM3_AUTORELOAD_REGISTER;
    uint16_t autoreloadValue = 0xFFFF; 
    *reg_pointer_16 = autoreloadValue;

    // Setup the TIM 3 channel 1 as input, CC1S bits are writable only when the channel is off.
    // After reset, all channels are turned off.
    reg_pointer_16 = (uint16_t *)TIM3_CAPTURE_COMPARE_MODE_1_REGISTER;
    *reg_pointer_16 = *reg_pointer_16 | TIM_CCMR13_CC1S_INPUT_TI1 | TIM_CCMR13_IC1F_N8; //experimented with filter but it doesn't seem to do anything
}


// Read the input capture flag from the status register
uint16_t getCaptureTimer3CH1( void )
{
    uint16_t * reg_pointer_16;
    reg_pointer_16 = (uint16_t *)TIM3_CAPTURE_COMPARE_MODE_1_REGISTER; // Point to the register
    return *reg_pointer_16 ; // Return the value in the register
}

void clearTimer3StatusRegister( void )
{
    // Set status register to 0
    uint16_t *reg_pointer_16 = (uint16_t *)TIM3_STATUS_REGISTER;
    *reg_pointer_16 = 0;
}

