#include "main.h"
#include "debug_mort.h"
#include "mbed.h"
#include "hardware_stm_adc.h"
#include "hardware_stm_dma_controller.h"

// --------------------------
// Select code to run
#define PART1_Q1
// #define PART1_Q2

// --------------------------
// -- Helper functions ------

void delay(int num){
    for (int i=0; i<num*100000000; i++){
        // busy wait
    }
}
// --------------------------


// Serial setup between pc and micrcontroller
Serial pc(USBTX, USBRX);

#ifdef PART1_Q1
int main (void)
{
    initADC3_567_withDMA();
    startADCConversion();

    while (1) {
        pc.printf("ADC 1 = %u; ", returnADC3StoredValue(0));
        pc.printf("ADC 2 = %u; ", returnADC3StoredValue(1));
        pc.printf("ADC 3 = %u\n", returnADC3StoredValue(2));

        delay(100000);
    }

}
#endif
