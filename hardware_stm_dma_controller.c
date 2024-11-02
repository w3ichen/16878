#include "hardware_stm_dma_controller.h"
#include "stm32f4xx_rcc_mort.h"
#include <cstdint>
#include "hardware_stm_adc.h"
#include "hardware_stm_gpio.h"


#define DMA2_BASE_ADDRESS       ((uint32_t) 0x40026400)
#define DMA2_LISR_REGISTER      (DMA2_BASE_ADDRESS + 0×00)
#define DMA2_HISR_REGISTER      (DMA2_BASE_ADDRESS + 0x04)
#define DMA2_LIFCR_REGISTER     (DMA2_BASE_ADDRESS + 0x08)
#define DMA2_HIFCR_REGISTER     (DMA2_BASE_ADDRESS + 0x0C)
#define DMA2_S0CR_REGISTER      (DMA2_BASE_ADDRESS + 0x10)
#define DMA2_S0NDTR_REGISTER    (DMA2_BASE_ADDRESS + 0x14)
#define DMA2_S0PAR_REGISTER     (DMA2_BASE_ADDRESS + 0x18)
#define DMA2_S0M0AR_REGISTER    (DMA2_BASE_ADDRESS + 0x1C)
#define DMA2_S0M1AR_REGISTER    (DMA2_BASE_ADDRESS + 0x20)
#define DMA2_S0FCR_REGISTER     (DMA2_BASE_ADDRESS + 0x24)

// Bits and flags
// DMA SxCR: Dma stream x configuration register
#define DMA_SxCR_CHANNEL_2_SELECT   (((uint32_t)2)<<25) // Select channel 2
#define DMA_SxCR_MSIZE_HALF_WORD    (((uint32_t)1)<<13) // The location memory is 16 bits in length 
#define DMA_SxCR_PSIZE_HALF_WORD    (((uint32_t)1)<<11) // The peripheral data size is 16 bits in length
#define DMA_SxCR_MINC_INCREMENT     (((uint32_t)1)<<10) // Increment the place where you store the data each transfer
#define DMA_SxCR_CIRC_ENABLE        (((uint32_t)1)<<8) // ENABLE circular mode
#define DMA_SxCR_DIR_PERTOMEM       (uint32_t)0
#define DMA_SxCR_STREAM_ENABLE      (uint32_t)1


uint16_t adc_dma_buffer[3] = {0, 0, 0};

void initDMAForAdc3_3channels( void ) {
    uint32_t* reg_pointer;
    // 1. Enable the AHB1 clock:
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    // 2. Configure DMA 2 Stream 0 to use channel 2 (ADC3) with memory size of 
    //      Half Word (16 bits), Peripheral size of Half Word (16 bits),
    //      Increment the source memory address after each transfer, do peripheral 
    //      to memory transfers, enable the DMA circular buﬀer to go back
    //      to the first memory address after the last transfer has been completed. 
    //      This configuration gets written to the S0CR register in DMA2
    reg_pointer = (uint32_t*) DMA2_S0CR_REGISTER;
    *reg_pointer = DMA_SxCR_CHANNEL_2_SELECT + DMA_SxCR_MSIZE_HALF_WORD +
                   DMA_SxCR_PSIZE_HALF_WORD + DMA_SxCR_MINC_INCREMENT + 
                   DMA_SxCR_DIR_PERTOMEM + DMA_SxCR_CIRC_ENABLE;
    // 3. Configure the S0NDTR to perform 3 transfers
    reg_pointer = (uint32_t*) DMA2_S0NDTR_REGISTER;
    *reg_pointer = 3;
    // 4. Write the address of the ADC Data Register in the DMA 2 S0PAR Register to
    //      tell it to transfer from that address.
    reg_pointer = (uint32_t*) DMA2_S0PAR_REGISTER;
    *reg_pointer = ADC_3_DR_REGISTER;
    // 5. Write the address of a buﬀer where you can store the values transfered in memory 
    //      to the S0M0AR register so the DMA2 stream 0 knows to transfer data to that buﬀer.
    reg_pointer = (uint32_t*) DMA2_S0M0AR_REGISTER;
    *reg_pointer = (uint32_t)&adc_dma_buffer[0];
}


void initDMAForAdc3_1channel( void ) {
    uint32_t* reg_pointer;
    // 1. Enable the AHB1 clock:
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    // 2. Configure DMA 2 Stream 0 to use channel 2 (ADC3) with memory size of 
    //      Half Word (16 bits), Peripheral size of Half Word (16 bits),
    //      Increment the source memory address after each transfer, do peripheral 
    //      to memory transfers, enable the DMA circular buﬀer to go back
    //      to the first memory address after the last transfer has been completed. 
    //      This configuration gets written to the S0CR register in DMA2
    reg_pointer = (uint32_t*) DMA2_S0CR_REGISTER;
    *reg_pointer = DMA_SxCR_CHANNEL_2_SELECT + DMA_SxCR_MSIZE_HALF_WORD +
                   DMA_SxCR_PSIZE_HALF_WORD + DMA_SxCR_MINC_INCREMENT + 
                   DMA_SxCR_DIR_PERTOMEM + DMA_SxCR_CIRC_ENABLE;
    // 3. Configure the S0NDTR to perform 1 transfers
    reg_pointer = (uint32_t*) DMA2_S0NDTR_REGISTER;
    *reg_pointer = 1;
    // 4. Write the address of the ADC Data Register in the DMA 2 S0PAR Register to
    //      tell it to transfer from that address.
    reg_pointer = (uint32_t*) DMA2_S0PAR_REGISTER;
    *reg_pointer = ADC_3_DR_REGISTER;
    // 5. Write the address of a buﬀer where you can store the values transfered in memory 
    //      to the S0M0AR register so the DMA2 stream 0 knows to transfer data to that buﬀer.
    reg_pointer = (uint32_t*) DMA2_S0M0AR_REGISTER;
    *reg_pointer = (uint32_t)&adc_dma_buffer[0];
}


void enableDMAForAdc3_3channels( void ) {
    uint32_t* reg_pointer;
    reg_pointer = (uint32_t*) DMA2_S0CR_REGISTER;
    *reg_pointer = *reg_pointer | DMA_SxCR_STREAM_ENABLE;
}

void enableDMAForAdc3_1channel( void ) {
    uint32_t* reg_pointer;
    reg_pointer = (uint32_t*) DMA2_S0CR_REGISTER;
    *reg_pointer = *reg_pointer | DMA_SxCR_STREAM_ENABLE;
}

uint16_t returnADC3StoredValue(uint8_t index) {
    uint32_t* reg_pointer;
    uint16_t val;
    // Debug: print ADC data register
    printADC3dataRegister();
    // Debug: print GPIO7 value
    reg_pointer = (uint32_t *) PORTF_IDR_REGISTER;
    val = *reg_pointer & GPIO_7_IDR;
    printf("GPIO 7: %u\n", val);
    return adc_dma_buffer[index];
}




