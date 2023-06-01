#include <Arduino.h>
#include <Wifi.h>
#include <Wire.h>

#include "debug.hpp"
#include "motor.hpp"

Motors motors(8);
WiFiServer server(4242);
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
  DEBUG_PRINTF("AP IP address: %s\n", ip.toString().c_str());

  server.begin();
}

void loop() {
  // try to connect to a client
  if (!client) {
    client = server.available();
    if (client) {
      DEBUG_PRINTF("Connected to a client\n");
    }
  }

  if (client && client.connected()) {
    if (client.available()) {
      uint8_t raw_data[5];
      const size_t num_bytes = client.readBytes(raw_data, sizeof(raw_data));
      if (num_bytes == sizeof(raw_data)) {
        if (raw_data[4]) {
          uint32_t *target_angle = (uint32_t*)raw_data;
          motors.setDirection(*target_angle);
          DEBUG_PRINTF("recieved target angle: %lu\n", *target_angle);
        } else {
          motors.stopAll();
          DEBUG_PRINTF("received stop command\n");
        }
      }
    }
  }
}