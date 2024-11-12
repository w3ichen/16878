#include "stm32f4xx_rcc_mort.h"
#include "hardware_stm_gpio.h"
#include "hardware_stm_interruptcontroller.h"
#include "button_state_machine.h"

void initButtton(void)
{
    initGpioC67AsInput();
    enableEXTI6OnPortC();
    EXTI9_5_IRQHandler();
}

// C6 input is button
uint32_t read_button(void) {
  uint32_t C6_val = checkGPIOC6();
  return C6_val;
}

buttonState = Waiting_Button;
void buttomStateMachine(event_t newEvent, uint16_t param1, double param2)
{
    switch(buttonState)
    {
        case Waiting_Button:
            if (newEvent == Edge_Detected){
                sendEvent(startTimer, 0, 10.0);
                buttonState = Maybe_Button;
            }
        break;
        case Maybe_Button:
            if ((newEvent == Timeout) && (param1 == 0))
            {
                if(read_button() > 0)
                {sendEvent(Button_Pressed, 0, 10.0);
                };
                buttonState = Waiting_Button;
            };
            break;
    }
}