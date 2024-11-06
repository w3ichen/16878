#include "main.h"
#include "debug_mort.h"
#include "mbed.h"
#include "hardware_stm_adc.h"
#include "hardware_stm_dma_controller.h"
#include "hardware_stm_gpio.h"
#include "hardware_stm_timer3.h"


// --------------------------
// Select code to run
// #define PART1_Q1
// #define PART1_Q2
#define PART2

// --------------------------
// -- Helper functions ------

void delay(int num){
    for (int i=0; i<num*1000000; i++){
        // busy wait
    }
}
// --------------------------


// Serial setup between pc and micrcontroller
Serial pc(USBTX, USBRX);

#ifdef PART2
int main (void)
{
    // Variable declarations
    uint16_t analog_adc_val;
    float duty_cycle;
    int rotate_cw = 1;
    int start_motor = 1;

    // Initalizations
    initADC3_5_withDMA(); // Init ADC for analog reading
    initTimer3AsPWM(); // Init PWM signal at 30kHz

    if (rotate_cw) 
        initGpioB0AsAF2(); // Output PWM via B0
    else 
        initGpioC8AsAF2(); // Output PWM via C8

    delay(1); // delay for ADC start

    while (1) {
        startADCConversion();
        analog_adc_val = returnADC3StoredValue(0);
        pc.printf("potentiometer = %u;\n", analog_adc_val);
        duty_cycle = map_analog_value(analog_adc_val);
        pc.printf("duty_cycle = %f;\n", duty_cycle);

        setTimer3PWMDutyCycle(duty_cycle); // Set value between 0 and 1

        delay(10);
    }
}
#endif



#ifdef PART1_Q2
int main (void)
{
    initADC3_567_withDMA();
    // 11. NOTE: A conversion will not start until the SWSTART bit in CR2 bit is set, but we need to wait a few clock cycles for that.
    delay(1);
    startADCConversion();

    while (1) {
        pc.printf("F7 ADC = %u; ", returnADC3StoredValue(0));
        pc.printf("F8 ADC = %u; ", returnADC3StoredValue(1));
        pc.printf("F9 ADC = %u\n", returnADC3StoredValue(2));

        delay(10);
    }

}
#endif


#ifdef PART1_Q1
int main (void)
{
    initADC3_5_withDMA();
    // initADC3_5_NoInterrupt(); // debug
    // 11. NOTE: A conversion will not start until the SWSTART bit in CR2 bit is set, but we need to wait a few clock cycles for that.
    delay(1); // delay for ADC start

    while (1) {
        startADCConversion();
        pc.printf("F7 ADC value = %u;\n", returnADC3StoredValue(0));

        delay(10);
    }
}
#endif

