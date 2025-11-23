#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "wifi_config.h"
#include "wifi_hal.h"
#include "arm_controller.h"

// Server y LED in HAL
static ESP8266WebServer server(80);
static const int LED_PIN = 2;

// --- handlers HTTP (C++ for WebServer) ---
static void handle_root() {
    server.send(200, "text/plain", "ESP8266 Robotic Arm API (Base)");
}

static void handle_set() {
    if (!server.hasArg("val")) {
        server.send(400, "text/plain", "Missing val");
        return;
    }

    int ang = server.arg("val").toInt();
    if (ang < 0) ang = 0;
    if (ang > 180) ang = 180;

    arm_set_servo1((uint16_t)ang);

    // feedback LED
    digitalWrite(LED_PIN, LOW);
    delay(30);
    digitalWrite(LED_PIN, HIGH);

    server.send(200, "text/plain", "OK");
}

// --- HAL interface ---
void wifi_hal_init(void) {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    Serial.print("Connecting to: ");
    Serial.println(WIFI_SSID);

    while (WiFi.status() != WL_CONNECTED) {
        delay(200);
        Serial.print(".");
    }

    Serial.println();
    Serial.print("Connected. IP: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, handle_root);
    server.on("/set", HTTP_GET, handle_set);
    server.on("/set", HTTP_POST, handle_set);

    server.begin();
    Serial.println("HTTP server started");
}

void wifi_hal_task(void) {
    server.handleClient();
}