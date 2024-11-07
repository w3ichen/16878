#pragma once

#ifdef __cplusplus
    extern "C" {
#endif

// NVIC
#define SYSTEM_CONTROL_BASE_ADDR    (0xE000E000)
#define SYSTEM_CONTROL_BASE_ADDRESS SYSTEM_CONTROL_BASE_ADDR
#define NVIC_ADDR_OFFSET            (0x100)
#define NVID_ADDR                   (SYSTEM_CONTROL_BASE_ADDR + NVIC_ADDR_OFFSET)
#define NVIC_INT_EN_REG_0_31        (NVID_ADDR)
#define NVIC_INT_EN_REG_32_63       (NVIC_ADDR+0x4)
#define NVIC_INT_EN_REG_64_95       (NVIC_ADDR+0x8)
#define TIM3_INTERRUPT_BIT          (0x20000000)
#define EXTI9_5_INTERRUPT_BIT       (0x800000)
#define EXTI0_INTERRUPT_BIT         (0b100000)

// Interupt flags
#define CH3_INT_FLAG                (uint16_t) (0x8)
#define OVERFLOW_FLAG               (uint16_t) (0x1)


// External interrupts
#define SYSCFG_BASE_ADDR            (0x40013800)
#define EXTICR1_OFFSET              (uint32_t) (0x08)
#define EXTICR2_OFFSET              (uint32_t) (0x0C)
#define EXTICR3_OFFSET              (uint32_t) (0x10)
#define EXTICR4_OFFSET              (uint32_t) (0x14)
#define SYSCFG_EXTICR1              (SYSCFG_BASE_ADDR + EXTICR1_OFFSET)
#define SYSCFG_EXTICR2              (SYSCFG_BASE_ADDR + EXTICR2_OFFSET)
#define SYSCFG_EXTICR3              (SYSCFG_BASE_ADDR + EXTICR3_OFFSET)
#define SYSCFG_EXTICR4              (SYSCFG_BASE_ADDR + EXTICR4_OFFSET)

#define EXTI_6_PIN_C                (uint32_t) (0x200)
#define EXTI_CLR_6                  (uint32_t) ~(0xF00)
#define EXTI_0_PIN_G                (uint32_t) (0b0110)
#define EXTI_CLR_0                  (uint32_t) (0x10)

#define EXTI_BASE_ADDR              (0x40013C00)
#define EXTI_IMR_OFFSET             (0x00)
#define EXTI_IMR                    (EXTI_BASE_ADDR + EXTI_IMR_OFFSET)
#define EXTI_RTRS_OFFSET            (0x08)
#define EXTI_FTRS_OFFSET            (0x0C)
#define EXTI_RTRS                   (EXTI_BASE_ADDR + EXTI_RTRS_OFFSET)
#define EXTI_FTRS                   (EXTI_BASE_ADDR + EXTI_FTRS_OFFSET)
#define EXTI_PR_OFFSET              (0x14)
#define EXTI_PR                     (EXTI_BASE_ADDR + EXTI_PR_OFFSET)

#define EXTI_6_EN                   (uint32_t) (0x40) //0b100000)
#define EXTI_PR_6                   EXTI_6_EN
#define EXTI_0_EN                   (uint32_t) (0b1)
#define EXTI_PR_0                   EXTI_0_EN


#define EXTI_A                      (uint16_t) 0
#define EXTI_B                      (uint16_t) 1
#define EXTI_C                      (uint16_t) 2
#define EXTI_D                      (uint16_t) 3
#define EXTI_E                      (uint16_t) 4
#define EXTI_F                      (uint16_t) 5
#define EXTI_G                      (uint16_t) 6


void TIM3_IRQHandler(void);
void enableNVIC_Timer3(void);
void enableEXTI_C6(void);
void enableEXTI_A0(void);
void enableEXTI_A6(void);
void EXTI9_5_IRQHandler( void);
void enableEXTI6OnPortC(void);

#ifdef __cplusplus
    }
#endif
