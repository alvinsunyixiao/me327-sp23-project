#include <Arduino.h>
#include <Wire.h>

#include "debug.hpp"
#include "imu.hpp"

IMU imu;

void setup() {
  DEBUG_INIT(115200);

  // initialize I2C
  Wire.begin(23, 22);

  // initialize motor manager
  imu.begin();
}


void loop() {
  imu.update();
  //DEBUG_PRINT("IMU yaw: %f\n", imu.getYaw());
  DEBUG_PRINT("IMU yaw: %f\n", 0.5);

  // 100ms delay
  delay(100);
}