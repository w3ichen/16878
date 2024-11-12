#include "main.h"
#include "debug_mort.h"
#include "mbed.h"
#include "hardware_stm_adc.h"
#include "hardware_stm_dma_controller.h"
#include "hardware_stm_gpio.h"
#include "hardware_stm_timer3.h"
#include "hardware_stm_interrupt.h"
#include "pid.h"


// --------------------------
// Select code to run
// #define PART1_Q1
// #define PART1_Q2
#define PART2
#define PART3

// --------------------------
// Global variables

#define CPR 42


typedef struct encoder_state {
    uint16_t pos;
    float vel;
    uint8_t enc_a;
    uint8_t enc_b;
    uint32_t last_read_time;
}

static encoder_state es;

// -- Helper functions ------

void delay(int num){
    for (int i=0; i<num*1000000; i++){
        // busy wait
    }
}

void EXTI9_5_IRQHandler( void) {
    uint32_t * register_value;
    register_value = (uint32_t *)EXTI_PR;
    //check which interrupt fired:
    if ((*register_value & EXTI_PR_6)>0)
    {
        //clear the interrupt:
        *register_value = EXTI_PR_6; //rc_w1
        // Check the values of the pins
        uint8_t c6 = read_c6();
        uint8_t b6 = read_b6();
        uint8_t current = c6 << 1 | b6;
        uint8_t old = es.enc_a << 1 | es.enc_b;
        uint16_t current_pos = es.pos;
        // Encoder logic
        switch (old)
        {
            case 0:
                if (current == 1) current_pos += 1;
                else if (current == 2) current_pos -= 1;
                break;
            case 1:
                if (current == 3) current_pos += 1;
                else if (current == 0) current_pos  -= 1;
                break;
            case 2:
                if (current == 0) current_pos += 1;
                else if (current == 3) current_pos -= 1;
                break;
            case 3:
                if (current == 2) current_pos += 1;
                else if (current == 1) current_pos -= 1;
                break;
        }
        // C = A, B = B
        // 0 0 -> 0 1 Forward 0 -> 1
        // 0 1 -> 1 1 Forward 1 -> 3
        // 1 1 -> 1 0 Forward 3 -> 2
        // 1 0 -> 0 0 Forward 2 -> 0

        uint32_t current_time = get_timer_time();
        uint32_t dt = 0xFFFF;
        // Condition on overflow
        if (current_time < last_time)
        {
            dt = (overflow-last_time) + current_time;
        } else {
            dt = current_time - last_time;
        }
        es.vel = 1 / CPR_TO_RPM / dt;


        
    }
}

void EXTI0_IRQHandler(void)
{
    register_value = (uint32_t *)EXTI_PR;
    //check which interrupt fired:
    if ((*register_value & EXTI_PR_0)>0)
    {
        //clear the interrupt:
        *register_value = EXTI_PR_0; //rc_w1
        // Check the values of the pins
        pc.printf("Button press handler");
        
    }
}

// --------------------------


// Serial setup between pc and micrcontroller
Serial pc(USBTX, USBRX);

#ifdef PART3
int main(void)
{
    
    while(1)
    {
        //Event Checker:
        timeoutCheck();
        //Service Handler:
        eventHandler();
    }

}

#ifdef PART2
int main (void)
{
    // Variable declarations
    uint16_t analog_adc_val;
    float duty_cycle;
    int rotate_cw = 1;

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

        delay(1);
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

