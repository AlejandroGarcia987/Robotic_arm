
/*
 * ESP8266 Servo Control (Base Version)
 *
 * This firmware connects the NodeMCU ESP8266 to a WiFi network and exposes
 * a simple HTTP endpoint for controlling a servo motor.
 *
 * Usage:
 *   - Send an HTTP GET or POST request to:
 *       /set?val=ANGLE
 *
 *   - ANGLE must be an integer between 0 and 180 degrees.
 *
 * Example (Postman):
 *   GET http://<ESP_IP>/set?val=90    -> Moves the servo to 90°
 *
 * Notes:
 *   - This is the base version of the project and is intended to validate
 *     WiFi communication and basic actuator control.
 *   - WiFi credentials are stored in wifi_config.h, which is excluded from
 *     version control. You can modifiy the "wifi_config_template.h" file to add your credentials.
 *   - Future revisions will expand this to multi-servo control and JSON-based
 *     API communication.
 */



#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include "wifi_config.h"
// #include "wifi_config_template.h"


ESP8266WebServer server(80);

const int LED_PIN = 2;       
const int SERVO1_PIN = 5;    

Servo servo1;

void handleSet() {
  if (!server.hasArg("val")) {
    server.send(400, "text/plain", "Falta parametro val");
    return;
  }

  int ang = server.arg("val").toInt();
  ang = constrain(ang, 0, 180);

  servo1.write(ang);

  // feedback LED rápido
  digitalWrite(LED_PIN, LOW);
  delay(30);
  digitalWrite(LED_PIN, HIGH);

  Serial.print("Servo1 -> ");
  Serial.println(ang);

  server.send(200, "text/plain", "Servo1 set to " + String(ang));
}
void handleRoot() {
  server.send(200, "text/plain", "ESP8266 OK. Usa /set?val=0..180");
}

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // LED apagado

  // Servo reposo
  servo1.attach(SERVO1_PIN);
  servo1.write(90);

  // WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.print("Connecting to:\t");
  Serial.println(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print('.');
  }

  Serial.println();
  Serial.print("Connected to:\t");
  Serial.println(WiFi.SSID());
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/set", HTTP_GET, handleSet);
  server.on("/set", HTTP_POST, handleSet);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}