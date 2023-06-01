#include <Arduino.h>
#include <Wifi.h>
#include <Wire.h>

#include "debug.hpp"
#include "motor.hpp"

Motors motors(8);
WiFiServer server(80);
WiFiClient client;

void setup() {
  DEBUG_INIT(115200);

  // initialize I2C
  Wire.begin();

  // initialize motor manager
  motors.begin();

  // initialize WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP("HapticNav", "ME327group9", 10);
  IPAddress ip = WiFi.softAPIP();
  DEBUG_HEADER;
  DEBUG_PRINT("AP IP address: ");
  DEBUG_PRINTLN(ip);

  server.begin();
}

void loop() {
  // try to connect to a client
  if (!client) {
    client = server.available();
    if (client) {
      DEBUG_HEADER;
      DEBUG_PRINTLN("Connected to a client");
    }
  }

  if (client && client.connected()) {
    if (client.available()) {
      uint8_t raw_data[5];
      const size_t num_bytes = client.readBytes(raw_data, sizeof(raw_data));
      if (num_bytes == sizeof(raw_data)) {
        DEBUG_HEADER;
        if (raw_data[4]) {
          uint32_t *target_angle = (uint32_t*)raw_data;
          motors.setDirection(*target_angle);
          DEBUG_PRINTF("target angle: %lu\n", *target_angle);
        } else {
          motors.stopAll();
          DEBUG_PRINTLN("stop all motors");
        }
      }
    }
  }
}