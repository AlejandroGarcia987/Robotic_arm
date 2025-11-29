#pragma once
#include <stdint.h>
#include "globals.h"

#ifdef __cplusplus
extern "C" {
#endif

void arm_init(void);

// set target (0..180)
void arm_set_servo(uint8_t servo_id ,uint16_t angle);

// periodic task (call each 20ms)
void arm_task_20ms(void);

// get current (after smoothing)
uint16_t arm_get_servo(uint8_t id);


#ifdef __cplusplus
}
#endif