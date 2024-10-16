#include "stm32f4xx_rcc_mort.h"
#include "hardware_stm_gpio.h"
#include "hardware_stm_interruptcontroller.h"

void init_input_devices(void) {
    initGpioC67AsInput();
    enableEXTI6OnPortC();
    EXTI9_5_IRQHandler();
}



// C6 input is button
uint32_t read_button(void) {
  uint32_t C6_val = checkGPIOC6();
  return C6_val;
}

// C7 input is phototransistor input
uint32_t read_photo_trans(void) {
  uint32_t C7_val = checkGPIOC7();
  return C7_val;
}

