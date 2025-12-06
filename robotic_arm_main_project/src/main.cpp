#include <Arduino.h>
#include "ESP32Servo.h"
#include "wifi_hal.h"
#include "arm_controller.h"
#include "globals.h"


static Servo servos[ARM_MAX_SERVOS];

static const int SERVO_PINS[ARM_MAX_SERVOS] = {
<<<<<<< Updated upstream
    5, //SERVO1 D1/GPIO5
    4, //SERVO2 D2/GPIO4
=======
    32, //SERVO1 GPIO32
>>>>>>> Stashed changes
    //extend for more
};


void setup() {
    Serial.begin(115200);
    delay(10);

    // HAL servo Arduino
    for(int i = 0; i < ARM_MAX_SERVOS; i ++){
        if(SERVO_PINS[i] >= 0){
            servos[i].attach(SERVO_PINS[i]);
            servos[i].write(90);
            delay(500);
        }
    }

    arm_init();

    // HAL WiFi/HTTP
    wifi_hal_init();
}

void loop() {
    // HAL HTTP
    wifi_hal_task();

    // 50Hz logic
    static uint32_t last = 0;
    if (millis() - last >= 20) {
        last = millis();
        arm_task_20ms();

        //Apply logic output
        for (int i = 0; i < ARM_MAX_SERVOS; i++){
            if(SERVO_PINS[i] >= 0){
                servos[i].write(arm_get_servo(i + 1));
            }
        }
    }
}