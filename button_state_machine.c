#include "stm32f4xx_rcc_mort.h"
#include "hardware_stm_gpio.h"
#include "hardware_stm_interrupt.h"
#include "button_state_machine.h"

void initButtton(void)
{
    initGpioAsInput(PORTC_BASE_ADDRESS, 6);
    enableEXTI_C6();
}

void ButtonStateMachine(event_t newEvent, uint16_t param1, double param2)
{
    switch(button_state)
    {
        case Waiting_Button:
            if (newEvent == Edge_Detected){
                sendEvent(StartTimer, 10, 0);
                button_state = Maybe_Button;
            }
        break;
        case Maybe_Button:
            if ((newEvent == Timeout) && (param1 == 0))
            {
                if(read_button() > 0)
                {
                    sendEvent(Button_Pressed, 10, 0);
                };
                button_state = Waiting_Button;
            };
            break;
    }
}

uint32_t read_button()
{
    return read_pin(PORTC_BASE_ADDRESS, 6);
}