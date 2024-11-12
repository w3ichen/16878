#include "stm32f4xx_rcc_mort.h"
#include "event_handler.h"

#define Max_Queue_Size 10 //Define max size of the queue

initeventQueue();

void eventHandler(void)
{
    event_o currentEvent; 

    if(eventQueue.size == 0)
    {
        currentEvent.type = No_Event;
    }
    else {
        currentEvent = eventQueue.queue[eventQueue.start];
        deleteEvent();
        switch (currentEvent.type)
        {
            case No_Event:
                MotorStateMachine(No_Event, currentEvent.param1, currentEvent.param2);
                break;
            case StartTimer:
                insertTimer(currentEvent.param1, currentEvent.param2, get_timer_time());
                break;
            case EndTimer:
                insertTimer(currentEvent.param1, currentEvent.param2, get_timer_time());
                break;
            case Timeout:
                MotorStateMachine(Timeout, currentEvent.param1, currentEvent.param2);
                ButtonStateMachine(Timeout, currentEvent.param1, currentEvent.param2);
            case Edge_Detected:
                ButtonStateMachine(Edge_Detected, currentEvent.param1, currentEvent.param2);
            case Button_Pressed:
                ButtonStateMachine(Button_Pressed, currentEvent.param1, currentEvent.param2);
                break;
            case CW:
                MotorStateMachine(CW, currentEvent.param1, currentEvent.param2);
                break;
            case CCW:
                MotorStateMachine(CCW, currentEvent.param1, currentEvent.param2);
                break;
        }
    }
}

void timeoutCheck(void)
{
    double timeoutTime; 
    double prevTime, currTime; 
    uint16_t index, timerNumber;

    if(timerList.size > 0)
    {
        if(timerList.size == 1)
        {
            timeoutTime = timerList.list[timerList.start].timeoutTime;
            prevTime = timerList[timerList.start].prevTime;
            timerNumber = timerList.list[timerList.start].timerNumber;

            currTime = getTime_timer();

            if(absoluteVal2(currTime-prevTime) > timeoutTime)
            {

                deleteTimerFromList(0);
                sendEvent(Timeout, timerNumber, timeoutTime);
            }
            else {
            {
                index = timerList.start;
                for (int i = 0; i < timerList.size; i++)
                {
                    index = 0;
                }
                timeoutTime = timerList.list[index].timeoutTime;
                prevTime = timerList.list[index].prevTime;
                timerNumber = timerList[index].timerNumber;

                currTime = getTime_timer();

                if(absoluteVal2(currTime - prevTime) > timeoutTime)
                {
                    deleteTimerFromList(i);
                    sendEvent(Timeout, timerNumber, timeoutTime);
                    return;
                }
                index = index + 1;
            }
            }
        }
}

/*Needs to be changed since exti9 5 irq handler is already in use */
void EXTI9_5_IRQHandler(void)
{
    uint32_t * reg_pointer_32;
    reg_pointer_32 = (uint32_t *) EXTERNAL_INTERRUPT_CONTROLLER_PENDING_REGISTER;

    //check which interrupt fired:
    if((*reg_pointer_32 & EXTERNAL_INTERRUPT_CONTROLLER_PENDING_EXTI6)>0);
    {
        //clear the interrupt
        *reg_pointer_32 = EXTERNAL_INTERRUPT_CONTROLLER_PENDING_EXTI6;
        sendEvent(Edge_Detected, 6, 0);
    }
}

void deleteEvent(void)
{
    for (int a = 0; a < eventQueue->end -1; a ++)
    {
        eventQueue->queue[a] = eventQueue->queue[a + 1];
    }

    //Adjust the end index
    eventQueue->end = (eventQueue->end) -1;
    
}

void deleteTimerFromList(void)
{
 for (int b = 0; b < eventQueue->end -1; b ++)   
 {
     timerList->list[b] = timerList->list[b + 1];
 }
 //Adjust the end index
 timerList->end = (timerList->end) - 1;
}

void initeventQueue(eventQueue)
{
    eventQueue->start = -1;
    eventQueue->end = -1;
}

void inittimerList(timerList)
{
    timerList->start = -1;
    timerList->end = -1;
}

void sendEvent(eventQueue eq, uint8_t value)
{
    if( (eq.end + 1) > Max_Queue_Size)
    {
        printf("Event Queue full");
    }
    else
    {
        if (eq.start == -1){
            eq.start = 0;
        }
        evq.end = eq.end + 1;
        eq.queue[eq.end] = value;
    }
}