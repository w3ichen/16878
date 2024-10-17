#include "hardware_stm_timer3.h"
#include "stm32f4xx_rcc_mort.h"
#include "hardware_stm_gpio.h"
#include "task_scheduler.h"
#include <cstdint>

/* MACRO definitions----------------------------------------------------------*/
#define SYSTEM_CONTROL_BASE_ADDRESS                     (0xE000E000)
#define NVIC_BASE_ADDRESS                               (SYSTEM_CONTROL_BASE_ADDRESS + 0x100)
#define NVIC_INTERRUPT_SET_ENABLE_REGISTER_0_31         (NVIC_BASE_ADDRESS)
#define NVIC_INTERRUPT_SET_ENABLE_REGISTER_32_63        (NVIC_BASE_ADDRESS+0x4)
#define NVIC_INTERRUPT_SET_ENABLE_REGISTER_64_95        (NVIC_BASE_ADDRESS+0x8)
#define NVIC_INTERRUPT_CLEAR_ENABLE_REGISTER_0_31       (NVIC_BASE_ADDRESS + 0x80)
#define NVIC_INTERRUPT_CLEAR_ENABLE_REGISTER_32_63      (NVIC_INTERRUPT_CLEAR_ENABLE_REGISTER_0_31 + 0x4)
#define NVIC_INTERRUPT_CLEAR_ENABLE_REGISTER_64_95      (NVIC_INTERRUPT_CLEAR_ENABLE_REGISTER_0_31 + 0x8)
#define NVIC_INTERRUPT_SET_PENDING_REGISTER_0_31        (NVIC_BASE_ADDRESS + 0x100)
#define NVIC_INTERRUPT_SET_PENDING_REGISTER_32_63       (NVIC_INTERRUPT_SET_PENDING_REGISTER_0_31 + 0x4)
#define NVIC_INTERRUPT_SET_PENDING_REGISTER_64_95       (NVIC_INTERRUPT_SET_PENDING_REGISTER_0_31 + 0x8)
#define NVIC_INTERRUPT_CLEAR_PENDING_REGISTER_0_31      (NVIC_BASE_ADDRESS + 0x180)
#define NVIC_INTERRUPT_CLEAR_PENDING_REGISTER_32_63     (NVIC_INTERRUPT_CLEAR_PENDING_REGISTER_0_31 + 0x4)
#define NVIC_INTERRUPT_CLEAR_PENDING_REGISTER_64_95     (NVIC_INTERRUPT_CLEAR_PENDING_REGISTER_0_31 + 0x8)
#define TIM3_INTERRUPT_BIT                              (0x20000000)
#define EXTI9_5_INTERRUPT_BIT                           (0x800000)

#define TIM3_BASE_ADDRESS                               ((uint32_t)0x40000400)
// Timer 3 control register 1
#define TIM3_CR1_REGISTER_1                             (TIM3_BASE_ADDRESS + 0x00)
// Flags for CR1 register:
#define COUNTER_ENABLE_BIT                              (uint16_t)0x01
// Timer 3 status register
#define TIM3_STATUS_REGISTER                            (TIM3_BASE_ADDRESS + 0x10)
// Flags for Status register:
#define TIM_UIF                                         0x01 // Timer 3 overflow flag
#define TIM_CH1_CC1IF                                   0x02 // Timer channel 1 capture/compare event
#define TIM_CH3_CC3IF                                   0x8  // Timer channel 3 capture/compare event
// Timer 3 interrupt enable register
# define TIM3_INTERRUPT_ENABLE_REGISTER                 (TIM3_BASE_ADDRESS + 0x0C)
// Flags for interrupt enable register:
#define TIM_CH3_CC_INTERRUPT_ENABLE                     0x8 // Timer channel 3 capture/compare interrupt
#define TIM_UPDATE_INTERRUPT_ENABLE                     0x1 // Timer overflow or event interrupt
// Capture compare enable register
#define TIM3_CAPTURE_COMPARE_ENABLE_REGISTER            (TIM3_BASE_ADDRESS + 0x20)
// Flags for TIM3_CCER registers for output:
#define TIM3_CCER_CC3E                                  (0x0100)
// Capture compare mode registers
#define TIM3_CAPTURE_COMPARE_MODE_1_REGISTER            (TIM3_BASE_ADDRESS + 0x18)
#define TIM3_CAPTURE_COMPARE_MODE_2_REGISTER            (TIM3_BASE_ADDRESS + 0x1C)
// Flags for Capture compare mode register
#define TIM_CCMR13_OCPE                                 (0b00001000) // Enable preload register channels 1 and 3
// Compare, autoreload and Prescaler registers
#define TIM3_COMPARE_1_REGISTER                         (TIM3_BASE_ADDRESS + 0x34)
#define TIM3_COMPARE_2_REGISTER                         (TIM3_BASE_ADDRESS + 0x38)
#define TIM3_COMPARE_3_REGISTER                         (TIM3_BASE_ADDRESS + 0x3C)
#define TIM3_COMPARE_4_REGISTER                         (TIM3_BASE_ADDRESS + 0x40)
#define TIM3_PRESCALER_REGISTER                         (TIM3_BASE_ADDRESS + 0x28)
#define TIM3_AUTORELOAD_REGISTER                        (TIM3_BASE_ADDRESS + 0X2C)
// For external interrupts:
#define SYSCFG_BASE_ADDRESS                             ((uint32_t)(0x40013800))
#define SYSCFG_EXTERNAL_INTERRUPT_REGISTER_2            (SYSCFG_BASE_ADDRESS + 0x0C)
#define SYSCFG_EXTERNAL_INTERRUPT_6_BITS                ((uint32_t)0xF00)  // Flags for External interrupt register 2
#define SYSCFG_EXTERNAL_INTERRUPT_6_PORTC               ((uint32_t)0x200)
// External interrupt controller :
#define EXTERNAL_INTERRUPT_CONTROLLER_BASE_ADDRESS      ((uint32_t)(0x40013C00))
#define EXTERNAL_INTERRUPT_CONTROLLER_MASK_REGISTER     (EXTERNAL_INTERRUPT_CONTROLLER_BASE_ADDRESS)
#define EXTERNAL_INTERRUPT_CONTROLLER_MASK_REGISTER_EXTI6 ((uint32_t)0x40)  // Flags for external interrupt controller mask register
#define EXTERNAL_INTERRUPT_CONTROLLER_RTSR              (EXTERNAL_INTERRUPT_CONTROLLER_BASE_ADDRESS+0x08)
#define EXTERNAL_INTERRUPT_CONTROLLER_RTSR_EXTI6        ((uint32_t)0x40)
#define EXTERNAL_INTERRUPT_CONTROLLER_FTSR              (EXTERNAL_INTERRUPT_CONTROLLER_BASE_ADDRESS+0x0C)
#define EXTERNAL_INTERRUPT_CONTROLLER_FTSR_EXTI6        ((uint32_t)0x40)
#define EXTERNAL_INTERRUPT_CONTROLLER_PENDING_REGISTER  (EXTERNAL_INTERRUPT_CONTROLLER_BASE_ADDRESS+0x14)
#define EXTERNAL_INTERRUPT_CONTROLLER_PENDING_EXTI6     ((uint32_t)0x40)


void enableNVIC_Timer3(void)
{
    // In order to actually use an interrupt on a peripheral like the TIMER 3, we need to tell the nested
    // interrupt vector controller to act on that signal by setting the bit in the appropriate Interrupt-Set-
    // Enable register.
    uint32_t * reg_pointer_32;
    reg_pointer_32 = (uint32_t *)NVIC_INTERRUPT_SET_ENABLE_REGISTER_0_31;
    *reg_pointer_32 = TIM3_INTERRUPT_BIT;
}


void initTimer3ToInterrupt( void )
{
    uint16_t *reg_pointer_16;
    /* Timer 3 APB clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    /* Enable the interrupt that would go to timer 3 */
    enableNVIC_Timer3();
    /* Clear any pending flags in the status register */
    reg_pointer_16 = (uint16_t *)TIM3_STATUS_REGISTER;
    *reg_pointer_16 = 0;
    /* Compute and Set Prescale and Autorreload */
    uint16_t prescalervalue2 = 9999; // For 0.25Hz
    uint16_t autoreloadvalue = 36000; // For 0.25Hz
    reg_pointer_16 = (uint16_t *)TIM3_PRESCALER_REGISTER;
    *reg_pointer_16 = prescalervalue2;
    reg_pointer_16 = (uint16_t *)TIM3_AUTORELOAD_REGISTER;
    *reg_pointer_16 = autoreloadvalue;
    /* Set Compare Value */
    reg_pointer_16 = (uint16_t *)TIM3_COMPARE_3_REGISTER;
    *reg_pointer_16 = autoreloadvalue/4;
    /* Enable Preload Register (Don’t HAVE to, but good practice) */
    reg_pointer_16 = (uint16_t *)TIM3_CAPTURE_COMPARE_MODE_2_REGISTER;
    *reg_pointer_16 = *reg_pointer_16 | TIM_CCMR13_OCPE;
    /* Enable the TIM3 channel 3 counter and keep the default configuration for channel polarity */
    reg_pointer_16 = (uint16_t *)TIM3_CAPTURE_COMPARE_ENABLE_REGISTER;
    *reg_pointer_16 = *reg_pointer_16 | TIM3_CCER_CC3E;
    /* Enable interrupt on capture compare channel 3 */
    reg_pointer_16 = (uint16_t *)TIM3_INTERRUPT_ENABLE_REGISTER;
    *reg_pointer_16 = (TIM_CH3_CC_INTERRUPT_ENABLE | TIM_UPDATE_INTERRUPT_ENABLE);
    /* Enable timer 3 */
    reg_pointer_16 = (uint16_t *)TIM3_CR1_REGISTER_1;
    *reg_pointer_16 = *reg_pointer_16 | COUNTER_ENABLE_BIT;
}


void TIM3_IRQHandler(void)
{
    uint16_t *reg_pointer_16_sr; // status register
    uint16_t *reg_pointer_16_dier; // interrupt enable register
    reg_pointer_16_sr = (uint16_t *)TIM3_STATUS_REGISTER;
    reg_pointer_16_dier = (uint16_t *)TIM3_INTERRUPT_ENABLE_REGISTER;
    // Logic:
    //      (i)   check which interrupts fired and if they were supposed to fire, 
    //      (ii)  then clear the flags so they don’t keep firing,
    //      (iii) then perform actions according to these interrupts
    
    // Check if Output Compare 3 triggered the interrupt:
    // If OC3 has interrupt flag and its interrupt is enabled
    if (((*reg_pointer_16_sr & TIM_CH3_CC3IF) > 0) && ((*reg_pointer_16_dier & TIM_CH3_CC_INTERRUPT_ENABLE) > 0)) {
        // Clear interrupt to stop firing
        *reg_pointer_16_sr = ~((uint16_t)TIM_CH3_CC3IF);
        // Perform action, turn off LED
        clearGPIOB0();
    }
    // Check if Overflow triggered the interrupt: I.e. Timer Counter 3 >= Autorreload value
    if (( (*reg_pointer_16_sr & TIM_UIF) > 0) && ((*reg_pointer_16_dier & TIM_UPDATE_INTERRUPT_ENABLE) > 0)) {
        // Clear interrupt to stop firing
        *reg_pointer_16_sr = ~((uint16_t)TIM_UIF);
        // Perform action, turn on LED
        setGPIOB0();
    }
}


void enableEXTI6OnPortC(void)
{
    uint32_t *reg_pointer_32;
    // Init GPIO 6 C as input. Setup PortC pin 6 as an input.
    initGpioC6AsInput();
    // As a test, Init GPIO B0 as output for debugging. 
    // Setup PortB pin 0 as an output so you can access LED1.
    initGpioB0AsOutput();
    // Enable SYSCFG clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    // Map EXTI6 (External interrupt) to port C bit 6
    reg_pointer_32 = (uint32_t *)SYSCFG_EXTERNAL_INTERRUPT_REGISTER_2;
    // Clear EXTI6
    *reg_pointer_32 = *reg_pointer_32 & ~SYSCFG_EXTERNAL_INTERRUPT_6_BITS;
    // Set EXTI6 to Port C
    *reg_pointer_32 = *reg_pointer_32 | SYSCFG_EXTERNAL_INTERRUPT_6_PORTC;
    // Un-mask EXTI6 (ie. enable it)
    reg_pointer_32 = (uint32_t *)EXTERNAL_INTERRUPT_CONTROLLER_MASK_REGISTER;
    *reg_pointer_32 = *reg_pointer_32 | EXTERNAL_INTERRUPT_CONTROLLER_MASK_REGISTER_EXTI6;
    // Trigger on rising edge
    // Idea is to listen to rising edge trigger and then do action
    reg_pointer_32 = (uint32_t *)EXTERNAL_INTERRUPT_CONTROLLER_RTSR;
    *reg_pointer_32 = *reg_pointer_32 | EXTERNAL_INTERRUPT_CONTROLLER_RTSR_EXTI6;
    // Set the NVIC to respond to EXTI9_5
    // NOTE: there is not a specific function for EXTI6 but it is packed together 
    // with EXTI5, EXTI7, EXTI8, and EXTI9 - hence EXTI9_5
    reg_pointer_32 = (uint32_t *)NVIC_INTERRUPT_SET_ENABLE_REGISTER_0_31;
    *reg_pointer_32 = EXTI9_5_INTERRUPT_BIT;
}

// External interrupts 9-5 handler
void EXTI9_5_IRQHandler(void)
{
    uint32_t *EXTI_pending_reg = (uint32_t *)EXTERNAL_INTERRUPT_CONTROLLER_PENDING_REGISTER;
    uint16_t *status_reg = (uint16_t *)TIM3_STATUS_REGISTER;
    uint16_t *interrupt_enable_reg = (uint16_t *)TIM3_INTERRUPT_ENABLE_REGISTER;

    // Check which interrupt fired: check if EXTI6 bit in interrupt pending register is true
    if ((*EXTI_pending_reg & EXTERNAL_INTERRUPT_CONTROLLER_PENDING_EXTI6) > 0) {
        // Clear the interrupt, so doesn't get triggered again
        *EXTI_pending_reg = EXTERNAL_INTERRUPT_CONTROLLER_PENDING_EXTI6;
        sched_event(BUTTON_PRESSED);
    } else if (((*status_reg & TIM_UIF) > 0) && 
               ((*interrupt_enable_reg & TIM_UPDATE_INTERRUPT_ENABLE) > 0)) {
        // If overflow interrupt has occured (check status register)
        // And timer update interrupt is enabled
        // Clear the interrupt
        *status_reg = ~((uint16_t)TIM_UIF);
        // Perform the action: increment the high counter
        incr_high_counter();
    }
}