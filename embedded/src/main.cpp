#include <Arduino.h>
#include <Wifi.h>
#include <Wire.h>

#include "debug.hpp"
#include "motor.hpp"
#include "imu.hpp"

Motors motors(8);
IMU imu;
WiFiServer server(4242);
WiFiClient client;

void setup() {
  DEBUG_INIT(115200);

  // initialize I2C
  Wire.begin(SDA1, SCL1, 800000);

  // initialize motor manager
  motors.begin();
  motors.setAngleOffset(2, -119304647);
  motors.setAngleOffset(3, 119304647);
  motors.setAngleOffset(5, -119304647);
  motors.setAngleOffset(6, 119304647);

  // intialize IMU
  imu.begin();

  // initialize WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP("HapticNav", "ME327group9", 10);
  IPAddress ip = WiFi.softAPIP();
  DEBUG_PRINT("AP IP address: %s\n", ip.toString().c_str());

  server.begin();
}

int32_t angle_user = 0;
int32_t angle_target;
bool stopped = true;

void loop() {
  // update IMU and read user orientation
  imu.update();
  angle_user = imu.getYaw() / PI * INT32_MAX;

  // try to connect to a client
  if (!client) {
    client = server.available();
    if (client) {
      DEBUG_PRINT("Connected to a client\n");
    }
  }

  // communicate with client
  if (client && client.connected()) {
    // read target
    uint8_t raw_data[5];
    if (client.available() >= sizeof(raw_data)) {
      const size_t num_bytes = client.readBytes(raw_data, sizeof(raw_data));
      if (num_bytes == sizeof(raw_data)) {
        switch (raw_data[4]) {
        // stop command
        case 0:
          stopped = true;
          break;
        // set target angle command
        case 1:
          angle_target = *(int32_t*)raw_data;
          stopped = false;
          DEBUG_PRINT("recieved target angle: %d\n", angle_target);
          break;
        // reset IMU command
        case 2:
          imu.resetOrientation();
          break;
        default:
          break;
        }
      }
    }

    // send user angle to server
    client.write_P((const char*)&angle_user, sizeof(angle_user));
    DEBUG_PRINT("sending virtual user angle: %lu\n", angle_user);
  }

  // convert to stereo vibration
  if (!stopped) {
    motors.setDirection(angle_target - angle_user);
  } else {
    motors.stopAll();
  }
}