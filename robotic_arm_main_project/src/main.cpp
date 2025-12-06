#include <Arduino.h>
#include "ESP32Servo.h"
#include "wifi_hal.h"
#include "arm_controller.h"
#include "globals.h"


static Servo servos[ARM_MAX_SERVOS];

typedef struct {
    uint8_t pwm_pin;
    uint8_t feedback_pin;
} ServoConfig;

static const ServoConfig ARM_CONFIG[ARM_MAX_SERVOS] = {

// Servo 1
    { 
        .pwm_pin = 32, 
        .feedback_pin = 33, 
    },
};

uint16_t feedback_array[5];
uint16_t feedback_sum;
uint16_t feedback_result;
uint16_t feedback_adc;


void setup() {
    Serial.begin(115200);
    delay(10);

    // HAL servo Arduino
    for (uint i = 0; i < ARM_MAX_SERVOS; i++){
        servos[i].attach(ARM_CONFIG[i].pwm_pin);
        pinMode(ARM_CONFIG[i].feedback_pin, INPUT);
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
        for(uint8_t i = 0; i < ARM_MAX_SERVOS; i++){
            if(ARM_CONFIG[i].pwm_pin != 0){
                servos[i].write(arm_get_servo(i + 1));
                for(uint i = 0; i < 5; i++){
                    feedback_array[i] = feedback_adc = analogReadMilliVolts(ARM_CONFIG[i].feedback_pin);
                }
                for(uint i = 0; i < 5; i++){
                    feedback_sum += feedback_array[i];
                }
                feedback_result = feedback_sum/5;
                Serial.printf("adc: %d\n",feedback_result);
                feedback_array[5] = 0;
                feedback_sum = 0;
                feedback_result = 0;
            }
        }
    }
}