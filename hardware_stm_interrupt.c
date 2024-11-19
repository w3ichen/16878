#include <cstdint>
#include "hardware_stm_timer3.h"
#include "hardware_stm_interrupt.h"
#include "hardware_stm_gpio.h"
#include "debug_mort.h"
#include "stm32f4xx_rcc_mort.h"

void enableEXTI_C6(void) {
    uint32_t* register_value;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    // Enable EXTI6
    register_value = (uint32_t*) SYSCFG_EXTICR2;
    // Clear bits
    *register_value = *register_value & EXTI_CLR_6;
    *register_value = *register_value | EXTI_6_PIN_C;

    // Configure EXTI6
    
    // Enable EXTI6 Trigger
    register_value = (uint32_t*) EXTI_IMR;
    *register_value = *register_value | EXTI_6_EN;

    // Rising edge trigger
    register_value = (uint32_t*) EXTI_RTRS;
    *register_value = *register_value | EXTI_6_EN;



    // Enable IRQ
    register_value = (uint32_t*) NVIC_INT_EN_REG_0_31;
    *register_value = EXTI9_5_INTERRUPT_BIT;

}

void enableEXTI_C13(void) {
    uint32_t* register_value;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    // Enable EXTI6
    register_value = (uint32_t*) SYSCFG_EXTICR4;
    // Clear bits
    // *register_value = *register_value & EXTI_CLR_6;
    *register_value = *register_value | EXTI_C << 4;

    // Configure EXTI13
    
    // Enable EXTI13 Trigger
    register_value = (uint32_t*) EXTI_IMR;
    *register_value = *register_value | 1 << 13;

    // Rising edge trigger
    register_value = (uint32_t*) EXTI_RTRS;
    *register_value = *register_value | 1 << 13;



    // Enable IRQ
    register_value = (uint32_t*) NVIC_INT_EN_REG_32_63;
    *register_value = EXTI15_10_INTERRUPT_BIT;

}

void enableEXTI_B6(void) {
    uint32_t* register_value;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    // Enable EXTI6
    register_value = (uint32_t*) SYSCFG_EXTICR2;
    // Clear bits
    *register_value = *register_value & EXTI_CLR_6;
    *register_value = *register_value | EXTI_B;

    // Configure EXTI6
    
    // Enable EXTI6 Trigger
    register_value = (uint32_t*) EXTI_IMR;
    *register_value = *register_value | EXTI_6_EN;

    // Rising edge trigger
    register_value = (uint32_t*) EXTI_RTRS;
    *register_value = *register_value | EXTI_6_EN;



    // Enable IRQ
    register_value = (uint32_t*) NVIC_INT_EN_REG_0_31;
    *register_value = EXTI9_5_INTERRUPT_BIT;

}

void enableEXTI_C0(void) {
    uint32_t* register_value;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    // Enable EXTI6
    register_value = (uint32_t*) SYSCFG_EXTICR2;
    // Clear bits
    *register_value = *register_value & EXTI_CLR_0;
    *register_value = *register_value | EXTI_C;

    // Configure EXTI6
    
    // Enable EXTI6 Trigger
    register_value = (uint32_t*) EXTI_IMR;
    *register_value = *register_value | EXTI_0_EN;

    // Rising edge trigger
    register_value = (uint32_t*) EXTI_RTRS;
    *register_value = *register_value | EXTI_0_EN;



    // Enable IRQ
    register_value = (uint32_t*) NVIC_INT_EN_REG_0_31;
    *register_value = EXTI0_INTERRUPT_BIT;
}

void enableNVIC_Timer3(void)
{
    uint32_t* register_value;
    register_value = (uint32_t*) NVIC_INT_EN_REG_0_31;
    *register_value = TIM3_INTERRUPT_BIT;
}

// void enableNVIC_Timer4(void)
// {
//     uint32_t* register_value;
//     register_value = (uint32_t*) NVIC_INT_EN_REG_0_31;
//     *register_value = TIM4_INTERRUPT_BIT;
// }

