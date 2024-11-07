#pragma once

#define Kp 1
#define Ki 0
#define Kd 0


typedef struct PID_t {
    uint16_t prev_error;
    uint16_t i;
    uint16_t i_min;
    uint16_t i_max;
}

uint16_t pid(uint16_t current, uint16_t setpoint);