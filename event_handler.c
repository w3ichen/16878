#include "hardware_stm_timer3.h"
#include "stm32f4xx_rcc_mort.h"
#include "event_handler.h"
#include "button_state_machine.h"
#include "motor_state_machine.h"
#include "hardware_stm_interrupt.h"


void sendEvent(event_t event, uint16_t param1, double param2) {
    event_o new_event;
    new_event.type = event;
    new_event.param1 = param1;
    new_event.param2 = param2;
    addEvent(new_event);
}

void eventHandler(void)
{
    event_o currentEvent; 

    if(event_q.size == 0)
    {
        currentEvent.type = No_Event;
    }
    else {
        currentEvent = event_q.queue[event_q.start];
        deleteEvent();
        switch (currentEvent.type)
        {
            case No_Event:
                MotorStateMachine(No_Event, currentEvent.param1, currentEvent.param2);
                break;
            case StartTimer:
                insertTimer(currentEvent.param1);
                break;
            // case EndTimer:
            //     insertTimer(currentEvent.param1, currentEvent.param2, getTimerTime());
            //     break;
            case Timeout:
                MotorStateMachine(Timeout, currentEvent.param1, currentEvent.param2);
                ButtonStateMachine(Timeout, currentEvent.param1, currentEvent.param2);
            case Edge_Detected:
                ButtonStateMachine(Edge_Detected, currentEvent.param1, currentEvent.param2);
            case Button_Pressed:
                ButtonStateMachine(Button_Pressed, currentEvent.param1, currentEvent.param2);
                break;
            // case CW:
            //     MotorStateMachine(CW, currentEvent.param1, currentEvent.param2);
            //     break;
            // case CCW:
            //     MotorStateMachine(CCW, currentEvent.param1, currentEvent.param2);
            //     break;
            default:
                break;
        }
    }
}

void insertTimer(uint32_t timeout)
{
    uint32_t current_time = getTimerTime();
    uint32_t timeout_time = current_time + timeout;
    if (timeout_time > OVERFLOW)
    {
        timeout_time = timeout_time - OVERFLOW; // Wrap around in case the timeout exceeds the max
    }
    timer_list.timeouts[timer_list.end] = timeout_time;
    timer_list.end++;
    timer_list.size++;
}

void timeoutCheck(void)
{
    uint32_t current_time = getTimerTime();

    for(uint16_t i = 0; i < timer_list.size; i++)
    {
        uint32_t timeout = timer_list.timeouts[i];
        if (current_time >= timeout)
        {
            sendEvent(Timeout, i, current_time);
            deleteTimerFromList(i);
            return;   // Only fire one timeout at a time
        }
    }


    // if(timer_list.size > 0)
    // {
    //     if(timer_list.size == 1)
    //     {
    //         timeoutTime = timer_list.list[timer_list.start].timeoutTime;
    //         prevTime = timer_list[timer_list.start].prevTime;
    //         timerNumber = timer_list.list[timer_list.start].timerNumber;

    //         currTime = getTime_timer();

    //         if(absoluteVal2(currTime-prevTime) > timeoutTime)
    //         {

    //             deleteTimerFromList(0);
    //             sendEvent(Timeout, timerNumber, timeoutTime);
    //         }
    //         else {
    //         {
    //             index = timer_list.start;
    //             for (int i = 0; i < timer_list.size; i++)
    //             {
    //                 index = 0;
    //             }
    //             timeoutTime = timer_list.list[index].timeoutTime;
    //             prevTime = timer_list.list[index].prevTime;
    //             timerNumber = timer_list[index].timerNumber;

    //             currTime = getTime_timer();

    //             if(absoluteVal2(currTime - prevTime) > timeoutTime)
    //             {
    //                 deleteTimerFromList(i);
    //                 sendEvent(Timeout, timerNumber, timeoutTime);
    //                 return;
    //             }
    //             index = index + 1;
    //         }
    //         }
    //     }
}

/*Needs to be changed since exti9 5 irq handler is already in use */
// void EXTI9_5_IRQHandler(void)
// {
//     uint32_t * reg_pointer_32;
//     reg_pointer_32 = (uint32_t *) EXTI_PR;

//     //check which interrupt fired:
//     if((*reg_pointer_32 & EXTI_PR_6))    {
//         //clear the interrupt
//         *reg_pointer_32 = EXTI_PR_6;
//         sendEvent(Edge_Detected, 6, 0);
//     }
// }

void deleteEvent(void)
{
    for (int a = 0; a < event_q.end -1; a ++)
    {
        event_q.queue[a] = event_q.queue[a + 1];
    }

    //Adjust the end index
    event_q.end = (event_q.end) -1;
    
}

void addEvent(event_o event)
{
    event_q.queue[event_q.end] = event;
    event_q.end++;    
}

void deleteTimerFromList(uint8_t indx)
{
    int insert_indx = 0;
    for (int b = 0; b < timer_list.size; b++)   // Minus one due to size change
    {
        if (b == indx) continue;
        timer_list.timeouts[insert_indx] = timer_list.timeouts[insert_indx + 1];
        insert_indx++;
    }
    //Adjust the end index
    timer_list.end--;
}

void initevent_q(eventQueue event_q)
{
    event_q.start = -1;
    event_q.end = -1;
}

void inittimerList(timerList timer_list)
{
    timer_list.start = -1;
    timer_list.end = -1;
}

// void sendEvent(event_q eq, uint8_t value)
// {
//     if( (eq.end + 1) > Max_Queue_Size)
//     {
//         printf("Event Queue full");
//     }
//     else
//     {
//         if (eq.start == -1){
//             eq.start = 0;
//         }
//         evq.end = eq.end + 1;
//         eq.queue[eq.end] = value;
//     }
// }