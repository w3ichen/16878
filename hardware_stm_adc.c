#include "hardware_stm_adc.h"
#include "stm32f4xx_rcc_mort.h"
#include <cstdint>

void initADC3_567_withDMA(void) {
    uint32_t *reg_pointer;
    // 1. Enable the APB2 clock:
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
    // Init GPIO pins F7, F8, F9 as analog
    initGpioF789AsAnalog();
    // Init and enable ADC3
    initDMAForAdc3_3channels();
    enableDMAForAdc3_3channels();
    // 2. Setup the clock Prescaler to divide the clock by 4 by writing to the ADC_COMMON_CCR_REGISTER
    reg_pointer = (uint32_t*) ADC_COMMON_CCR_REGISTER;
    *reg_pointer = ADC_PRESCALER_4;
    // 3. Configure the ADC to be 12 bit resolution, enable the Scan mode, and end of conversion interrupt
    //     disabled by writing bit ADC_SCAN to the CR1 register in ADC 3
    reg_pointer = (uint32_t*) ADC_3_CR1_REGISTER;
    *reg_pointer = ADC_SCAN;
    // 4. Configure the ADC to have DMA, EOC set at the end of each regular conversion, continuous 
    //      conversion enabled, and DMA requests keep being issued after each set of conversions by 
    //      setting EOCS, CONT, DDS and DMA bits to the CR2 register in ADC3.
    reg_pointer = (uint32_t*) ADC_3_CR2_REGISTER;
    *reg_pointer = ADC_EOCS + ADC_CONT + ADC_DDS + ADC_DMA;
    // 5. Select to have 3 conversion by writing a 2 to the L bits in SQR1 register in ADC3
    reg_pointer = (uint32_t*) ADC_3_SQR1_REGISTER;
    *reg_pointer = ADC_3_CONVERSIONS;
    // 6. Configure the sequence of conversions by writing a 5 to SQ1, 6 to SQ2 and 7 to SQ3 in 
    //      the SQR3 register of ADC 3.
    reg_pointer = (uint32_t*) ADC_3_SQR3_REGISTER;
    *reg_pointer = (ADC_CHANNEL_5_MORT2 << ADC_SQ1) + 
                   (ADC_CHANNEL_6_MORT2 << ADC_SQ2) + 
                   (ADC_CHANNEL_7_MORT2 << ADC_SQ3) + 
    // 7. Choose 480 cycles of sampling for channels 5, 6 and 7 in ADC3 by writing all ones to 
    //      the SMP5, SMP6 and SMP7 bits in the ADC3 SMPR2 register.
    reg_pointer = (uint32_t*) ADC_3_SMPR2_REGISTER;
    *reg_pointer = ADC_SMP_5_MX + ADC_SMP_6_MX + ADC_SMP_7_MX;
    // 8. Turn the ADC on by setting the ADON bit in the CR2 register in ADC 
    enableADC3();
}






