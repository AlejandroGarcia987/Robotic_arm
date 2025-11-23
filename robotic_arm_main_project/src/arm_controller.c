#include "arm_controller.h"

static uint16_t target1 = 90;
static uint16_t current1 = 90;

void arm_init(void) {
    target1 = 90;
    current1 = 90;
}

void arm_set_servo1(uint16_t angle) {
    if (angle > 180) angle = 180;
    target1 = angle;
}

void arm_task_20ms(void) {
    if (current1 < target1) current1++;
    else if (current1 > target1) current1--;
}

uint16_t arm_get_servo1(void) {
    return current1;
}