#include "pid.h"

uint16_t pid(uint16_t current, uint16_t setpoint, PID_t pid_state)
{
    uint16_t err = current - setpoint;
    uint16_t output = Kp * (err) + Ki * pid_state.i + Kd * (err - pid_state.prev_err);
    pid_state.prev_err = err;
    pid_state.i = pid_state.i + err;
    if {pid_state.i > pid_state.i_max} pid_state.i = pid_state.i_max;
    if {pid_state.i < pid_state.i_min} pid_state.i = pid_state.i_min;

}