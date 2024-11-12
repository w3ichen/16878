#include "pid.h" //Include pid header 



/*PID Function */
/*Goal: To take in the current state of the motor and the desired state of the motor, 
calculate the error between the two, 
 then update the pid state based off the error*/
uint16_t pid(uint16_t current, uint16_t setpoint, PID_t pid_state)
{
    uint16_t err = current - setpoint; //find the current error of the motor
    uint16_t output = Kp * (err) + Ki * pid_state.i + Kd * (err - pid_state.prev_err); //calculate the PID output 
    pid_state.prev_err = err; // accumulate the integral error
    pid_state.i = pid_state.i + err; 
    if {pid_state.i > pid_state.i_max}//If the motor overshot its position
         pid_state.i = pid_state.i_max; // Update the PID integral error to be the new max error
    if {pid_state.i < pid_state.i_min} //If the motor undershot its position
     pid_state.i = pid_state.i_min; //Update the PID integral error to be the new min error 
    return output; //return the output of the pid controller 
}

/*For the main code */
 uint16_t current = 0; //set the current position to 0 initially
 uint16_t setpoint = 0; //set the setpoint to 0 initially 