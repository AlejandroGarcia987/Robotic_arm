#include <Arduino.h>
#include <Servo.h>

#include "wifi_hal.h"
#include "arm_controller.h"

static Servo servo1;
static const int SERVO1_PIN = 5; // D1/GPIO5

void setup() {
    Serial.begin(115200);
    delay(10);

    // HAL servo Arduino
    servo1.attach(SERVO1_PIN);
    servo1.write(90);

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
        servo1.write(arm_get_servo1());
    }
}