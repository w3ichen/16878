#include "stm32f4xx_rcc_mort.h"
#include "motor_state_machine.h"

motorState_t motorState = Initialize;

uint8_t button = 1; //1 for CW, 2 for CCW

void motorStateMachine(event_t newEvent, uint16_t param1, double param2)
{
    switch (motorState)
    {
        case Initialize:
            motorstate = Start;
            break;
        case Start:
            if (newEvent == Button_Pressed){
                if(button == 1)
                {motorState = CW; //motor will move in the CW direction
                button = button + 1;} //update the direction for next time
                if(button == 2)
                {motorState = CCW; //motor will move in CCW direction
                button = button - 1;} //update direction for next time
            }
            break;
        case CW:
        //motor moves 90 degrees in CW direction
            break;
        case CCW:
        //motor moves 90 degrees in CCW direction
            break;
    }
}