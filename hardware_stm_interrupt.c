#include <cstdint>
#include "hardware_stm32_timer3.h"
#include "hardware_stm_interrupt.h"
#include "hardware_stm_gpio.h"
#include "debug_mort.h"

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

void enableEXTI_B6(void) {
    uint32_t* register_value;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    // Enable EXTI6
    register_value = (uint32_t*) SYSCFG_EXTICR2;
    // Clear bits
    *register_value = *register_value & EXTI_CLR_6;
    *register_value = *register_value | EXTI_PIN_B;

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
    *register_value = *register_value | EXTI_PIN_C;

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



void TIM3_IRQHandler_ex4(void)
{
    uint16_t* sr_reg;
    uint16_t* dier_reg;
    sr_reg = (uint16_t*) TIM3_SR;
    dier_reg = (uint16_t*) TIM3_DIER;

    // Check flags
    // If OC3 Triggered the flag
    if ((*dier_reg & TIM_CH3_INT_EN) > 0 ) { // Check if interupt is enabled
        if ((*sr_reg & CH3_INT_FLAG) > 0) {
            *sr_reg = ~(CH3_INT_FLAG); // Clear flag
            clearGPIOB0();
        }
    }

    
    // Check overflow
    if ((*dier_reg & TIM_UPDATE_INT_EN) > 0) { //Check if interupt is enabled
        if ((*sr_reg & OVERFLOW_FLAG) > 0) { // Check if interupt is triggered
            *sr_reg = ~(OVERFLOW_FLAG); // Clear flag
            setGPIOB0();
        }
    }

}

void enableNVIC_Timer3(void)
{
    uint32_t* register_value;
    register_value = (uint32_t*) NVIC_INT_EN_REG_0_31;
    *register_value = TIM3_INTERRUPT_BIT;

}

