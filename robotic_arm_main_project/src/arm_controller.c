#include "arm_controller.h"

//(ARM_MAX_SERVOS-1)
static uint16_t target[ARM_MAX_SERVOS];
static uint16_t current[ARM_MAX_SERVOS];

void arm_init(void) {
    for(int i = 0; i < ARM_MAX_SERVOS; i++){ 
        target[i] = DEFAULT_START_ANGLE;    
        current[i] = DEFAULT_START_ANGLE;    
    }
}

void arm_set_servo(uint8_t id, uint16_t angle) {
    if( id == 0 || id > ARM_MAX_SERVOS) return;
    if (angle > MAX_ANGLE) angle = MAX_ANGLE;
    target[id - 1] = angle; 
}

void arm_task_20ms(void) {
    for(int i = 0; i < ARM_MAX_SERVOS; i++){
        if(current[i] < target[i]) current[i]++;
        else if(current[i] > target[i]) current[i]--;
    }
}

uint16_t arm_get_servo(uint8_t id) {
    if (id == 0 || id > ARM_MAX_SERVOS) return DEFAULT_START_ANGLE;
    return current[id - 1];
}