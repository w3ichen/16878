/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HARDWARE_STM_TIMER3_H_
#define __HARDWARE_STM_TIMER3_H_

#include <cstdint>
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


#define OVERFLOW 20000 // Maximum value for clock



#define TIM_CR1_OFFSET 0x00
#define TIM_CR2_OFFSET 0x04
#define TIM_SMCR_OFFSET 0x08
#define TIM_DIER_OFFSET 0x0C
#define TIM_SR_OFFSET 0x10
#define TIM_EGR_OFFSET 0x14
#define TIM_CCMR1_OFFSET 0x18
#define TIM_CCMR2_OFFSET 0x1C
#define TIM_CCER_OFFSET 0x20
#define TIM_CNT_OFFSET 0x24
#define TIM_PSC_OFFSET 0x28
#define TIM_ARR_OFFSET 0x2C
#define TIM_CCR1_OFFSET 0x34
#define TIM_CCR2_OFFSET 0x38
#define TIM_CCR3_OFFSET 0x3C

#define TIMER_3_BASE_ADDR   0x40000400
#define TIM3_CR1            (TIMER_3_BASE_ADDR + TIM_CR1_OFFSET)
#define TIM3_CR2            (TIMER_3_BASE_ADDR + TIM_CR2_OFFSET)
#define TIM3_SMCR           (TIMER_3_BASE_ADDR + TIM_SMCR_OFFSET)
#define TIM3_DIER           (TIMER_3_BASE_ADDR + TIM_DIER_OFFSET)
#define TIM3_SR             (TIMER_3_BASE_ADDR + TIM_SR_OFFSET)
#define TIM3_PSC            (TIMER_3_BASE_ADDR + TIM_PSC_OFFSET)
#define TIM3_ARR            (TIMER_3_BASE_ADDR + TIM_ARR_OFFSET)
#define TIM3_CCMR1          (TIMER_3_BASE_ADDR + TIM_CCMR1_OFFSET)
#define TIM3_CCMR2          (TIMER_3_BASE_ADDR + TIM_CCMR2_OFFSET)
#define TIM3_CCER           (TIMER_3_BASE_ADDR + TIM_CCER_OFFSET)
#define TIM3_CCR1           (TIMER_3_BASE_ADDR + TIM_CCR1_OFFSET)
#define TIM3_CCR2           (TIMER_3_BASE_ADDR + TIM_CCR2_OFFSET)
#define TIM3_CCR3           (TIMER_3_BASE_ADDR + TIM_CCR3_OFFSET)
#define TIM3_CNT            (TIMER_3_BASE_ADDR + TIM_CNT_OFFSET)


#define TIM_ENABLE (uint16_t) (1)
#define TIM_DISABLE (uint16_t) ~(TIM_ENABLE)

#define TIM_CLR_UIF (uint16_t) (0)

#define TIM_CC1_ENABLE (uint16_t) (0)
#define TIM_CC1_DISABLE (uint16_t) (1)

#define TIM_CC1_ACTIVE_H (uint16_t) (0 << 1)
#define TIM_CC1_ACTIVE_L (uint16_t) (0 << 0)

#define CH3_CC_OUTPUT               (uint16_t) (0b00000000)
#define CH3_CC_PRELOAD_ENABLE       (uint16_t) (0b00001000)
#define CH3_CC_FAST_ENABLE          (uint16_t) (0b00000100)
#define CH3_CC_TOGGLE               (uint16_t) (0b00110000)
#define CH3_CC_PWM                  (uint16_t) (0b01100000)
#define CH3_OC_CLEAR                (uint16_t) (0)
#define CH3_OC_ENABLE               (uint16_t) (0b01000000)
#define CC3E                        (uint16_t) (0b0000000100000000)

#define CH1_CC_INPUT_T1             (uint16_t) (0b01)
#define CH1_CC_FAST_ENABLE          CH3_CC_FAST_ENABLE
#define CH1_CC_TOGGLE               CH3_CC_TOGGLE
#define CC1E                        (uint16_t) (0b1)
#define CC2E                        (uint16_t) (0x10)

// Event enable flags
#define TIM_CH3_INT_EN              (uint16_t) (0x8)
#define TIM_CH1_INT_EN              (uint16_t) (0b10)
#define TIM_UPDATE_INT_EN           (uint16_t) (0b1)

#define TIMER_4_BASE_ADDR   0x40000800
#define TIM4_CR1            (TIMER_4_BASE_ADDR + TIM_CR1_OFFSET)
#define TIM4_CR2            (TIMER_4_BASE_ADDR + TIM_CR2_OFFSET)
#define TIM4_SMCR           (TIMER_4_BASE_ADDR + TIM_SMCR_OFFSET)
#define TIM4_DIER           (TIMER_4_BASE_ADDR + TIM_DIER_OFFSET)
#define TIM4_SR             (TIMER_4_BASE_ADDR + TIM_SR_OFFSET)
#define TIM4_PSC            (TIMER_4_BASE_ADDR + TIM_PSC_OFFSET)
#define TIM4_ARR            (TIMER_4_BASE_ADDR + TIM_ARR_OFFSET)
#define TIM4_CCMR1          (TIMER_4_BASE_ADDR + TIM_CCMR1_OFFSET)
#define TIM4_CCMR2          (TIMER_4_BASE_ADDR + TIM_CCMR2_OFFSET)
#define TIM4_CCER           (TIMER_4_BASE_ADDR + TIM_CCER_OFFSET)
#define TIM4_CCR1           (TIMER_4_BASE_ADDR + TIM_CCR1_OFFSET)
#define TIM4_CCR2           (TIMER_4_BASE_ADDR + TIM_CCR2_OFFSET)
#define TIM4_CCR3           (TIMER_4_BASE_ADDR + TIM_CCR3_OFFSET)
#define TIM4_CNT            (TIMER_4_BASE_ADDR + TIM_CNT_OFFSET)


/* Function definitions---------------------------------------------------------*/
void initTimer3AsPWM( void );
void setTimer3PWMDutyCycle( float duty_cycle  );
uint32_t getTimerTime();

#ifdef __cplusplus
}
#endif

#endif
