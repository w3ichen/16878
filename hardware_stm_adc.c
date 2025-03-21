#include "hardware_stm_adc.h"
#include "hardware_stm_gpio.h"
#include "hardware_stm_dma_controller.h"
#include "stm32f4xx_rcc_mort.h"
#include <cstdint>


void initADC3_5_withDMA( void ) {
    uint32_t* reg_pointer;
    // 1. Enable the APB2 clock:
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
    // Init GPIO F7 as analog
    initGpioF7AsAnalog();
    // Init and enable ADC3
    initDMAForAdc3_1channel();
    enableDMAForAdc3_1channel();
    // 2. Setup the clock Prescaler to divide the clock by 4 by writing to
    //      the ADC_COMMON_CCR_REGISTER
    reg_pointer = (uint32_t*) ADC_COMMON_CCR_REGISTER;
    *reg_pointer = ADC_PRESCALER_4;
    // Clear status register
    reg_pointer = (uint32_t*) ADC_3_SR_REGISTER;
    *reg_pointer = 0;
    // 3. Configure the ADC to be 12 bit resolution, and end of conversion interrupt 
    //      disabled by writing to the CR1 register in ADC 3
    reg_pointer = (uint32_t*) ADC_3_CR1_REGISTER;
    *reg_pointer = 0;
    // 4. Configure the ADC to have the external trigger disabled, right data alignment, 
    //      ADC_DDS, DMA, EOC set at the end of each regular conversion and single conversion 
    //      enabled by setting EOCS to the CR2 register in ADC3.
    reg_pointer = (uint32_t*) ADC_3_CR2_REGISTER;
    *reg_pointer = ADC_EOCS + ADC_DDS + ADC_DMA;
    // 5. Select to have 1 conversion by writing a 0 to the L bits in SQR1 register in ADC3
    reg_pointer = (uint32_t*) ADC_3_SQR1_REGISTER;
    *reg_pointer = ADC_1_CONVERSIONS;
    // 6. Configure the sequence of conversions by writing a 5 to SQ1 in the SQR3 register of ADC 3.
    reg_pointer = (uint32_t*) ADC_3_SQR3_REGISTER;
    *reg_pointer = (ADC_CHANNEL_5_MORT2 << ADC_SQ1);
    // 7. Choose 480 cycles of sampling for channel 5 in ADC3 by writing all ones to the SMP7 bits in the ADC3 SMPR2 register.
    reg_pointer = (uint32_t*)ADC_3_SMPR2_REGISTER;
    *reg_pointer = ADC_SMP_5_MX;
    // 8. Turn the ADC on by setting the ADON bit in the CR2 register in ADC 3
    reg_pointer = (uint32_t*) ADC_3_CR2_REGISTER;
    *reg_pointer = *reg_pointer | ADC_ADON;
    // 11. NOTE: A conversion will not start until the SWSTART bit in CR2 bit is set, but we need to wait a few clock cycles for that.
}


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
                   (ADC_CHANNEL_7_MORT2 << ADC_SQ3);
    // 7. Choose 480 cycles of sampling for channels 5, 6 and 7 in ADC3 by writing all ones to 
    //      the SMP5, SMP6 and SMP7 bits in the ADC3 SMPR2 register.
    reg_pointer = (uint32_t*) ADC_3_SMPR2_REGISTER;
    *reg_pointer = ADC_SMP_5_MX + ADC_SMP_6_MX + ADC_SMP_7_MX;
    // 8. Turn the ADC on by setting the ADON bit in the CR2 register in ADC 
    reg_pointer = (uint32_t*) ADC_3_CR2_REGISTER;
    *reg_pointer = *reg_pointer | ADC_ADON;
}



void startADCConversion(void) {
    // Need to have a small delay before enabling SWSTART
    // to allow ADC time to actually turn on
    uint32_t* reg_pointer;
    // Clear status register
    reg_pointer = (uint32_t*) ADC_3_SR_REGISTER;
    *reg_pointer = 0;
    // Set the SWSTART bit in CR2 register
    reg_pointer = (uint32_t*) ADC_3_CR2_REGISTER;
    *reg_pointer = *reg_pointer | ADC_SWSTART;
}

void printADC3dataRegister(void) {
    uint32_t* reg_pointer;
    uint32_t value;
    // Read value of status register
    reg_pointer = (uint32_t*) ADC_3_SR_REGISTER;
    value = *reg_pointer;

    // Check if end of conversion (EOC)
    if ((value & ADC_EOC) > 0) {
        reg_pointer = (uint32_t*) ADC_3_DR_REGISTER;
        // Only first 12 bits are relevant
        value = *reg_pointer & 0xFFF;
        printf("ADC_3_DR_REGISTER : %u\n", value);
    } else {
        printf("ADC_EOC not set\n");

    }
}


void initADC3_5_NoInterrupt ( void )
{
    uint32_t * reg_pointer;
    /* Turn on ADC3 bus clocks */ 
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_ADC3, ENABLE) ;
    /* Initialize GPIO F 7 as analog */ 
    initGpioF7AsAnalog();
    /* Setup the clock Preescaler */
    reg_pointer = (uint32_t *) ADC_COMMON_CCR_REGISTER;
    *reg_pointer = ADC_PRESCALER_4;
    /* Clear status register */
    reg_pointer = (uint32_t*) ADC_3_SR_REGISTER;
    /* Configure ADC 12bit resolution, End of conversion interrupt Disabl*/
    reg_pointer = (uint32_t *) ADC_3_CR1_REGISTER;
    *reg_pointer = 0;
    /* Configure ADC External trigger dissabled, right data alignment, no EOC is set at the end of each regular conversion, single conversion e*/
    reg_pointer = (uint32_t *)ADC_3_CR2_REGISTER;
    *reg_pointer = ADC_EOCS; //since it is only a sequence of 1, this is
    /* There will be 1 channel in the sequene of conversions */
    reg_pointer = (uint32_t *)ADC_3_SQR1_REGISTER;
    *reg_pointer = ADC_1_CONVERSIONS;
    /*Configure the sequence of conversion for the ADC (5)*/
    reg_pointer = (uint32_t *)ADC_3_SQR3_REGISTER;
    *reg_pointer = (ADC_CHANNEL_5_MORT2<<ADC_SQ1);
    /*Configure Channels 5 to max sampling times (480 cycles) */
    reg_pointer = (uint32_t *) ADC_3_SMPR2_REGISTER;
    *reg_pointer = ADC_SMP_5_MX;
    /*Enable the ADC3*/
    reg_pointer = (uint32_t *)ADC_3_CR2_REGISTER;
    *reg_pointer = *reg_pointer | ADC_ADON;
    /*Start a software conversion*/
    //cannot start software conversion here, need to have a small delay
    // allowing the ADC to actually turn on.
}