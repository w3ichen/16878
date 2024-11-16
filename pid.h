#pragma once // only include this header file once

#include "main.h"

#define Kp 1 //proportional gain 
#define Ki 0 //Integral gain (Can be changed, but change in terms of decimals)
#define Kd 0 //Derivative gain (can be changed, but change in terms of decimals)

/*Is there a reason why these are not inputs into the PID function? Ig simplicity but ?*/
// Avoids having to change in code in multiple spots, ensures everywhere is using the same params

typedef struct PID_t {
    uint16_t prev_err; //previous error
    uint16_t i; // integral
    uint16_t i_min; //integral minimum
    uint16_t i_max; //integral maximum
} PID_t; 

/*Fucntion prototypes  */
uint16_t pid(uint16_t current, uint16_t setpoint, PID_t pid_state); 
/*Function: PID
Input: Current -> Current position (ex. 89.9)
        Setpoint -> The desired position (ex. 90)
        pid_state -> name for PID_t structure
Output: None */
