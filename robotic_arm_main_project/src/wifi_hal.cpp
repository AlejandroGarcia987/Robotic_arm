#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "wifi_config.h"
#include "wifi_hal.h"
#include "arm_controller.h"

static WiFiUDP Udp;
static const int LOCAL_PORT = 4210; // UDP Port where NodeMCU will listen for commands
static const int LED_PIN = 2;

// Receive data buffer
char packetBuffer[255]; 

void wifi_hal_init(void) {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    // Router connection
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(200);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Given IP: ");
    Serial.println(WiFi.localIP());

    // Start UDP listening
    Udp.begin(LOCAL_PORT);
    Serial.printf("Listening UDP at port %d\n", LOCAL_PORT);
}

void wifi_hal_task(void) {
    // Check for new packet
    int packetSize = Udp.parsePacket();
    
    if (packetSize) {
        // Read UDP packet
        int len = Udp.read(packetBuffer, 255);
        
        // Simple Binary protocol: [ID, ANGLE]
        // Wait for 2 bytes 
        // Byte 0: Servo ID (in this case, is 1)
        // Byte 1: Angle (0-180)
        
        if (len >= 2) {
            uint8_t servo_id = (uint8_t)packetBuffer[0];
            uint8_t angle = (uint8_t)packetBuffer[1];

            // Visual feedback
            digitalWrite(LED_PIN, LOW); 
            
            arm_set_servo(servo_id, (uint16_t)angle);
            // here we will add if servo:id == 2...
            
            digitalWrite(LED_PIN, HIGH);
        }
    }
}