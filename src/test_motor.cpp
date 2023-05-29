#include <Arduino.h>
#include <Wire.h>

#include "debug.hpp"
#include "motor.hpp"

Motors motors(1);

void setup() {
  // initialize I2C
  Wire.begin();

  // initialize motor manager
  motors.begin();

  SerialUSB.begin();
}

// initial direction pointing forward
uint32_t direction = 0;

void loop() {
  DEBUG_HEADER;
  DEBUG_PRINT("setting direction ");
  DEBUG_PRINTLN(direction);

  // output vibration for current direction
  motors.setDirection(direction);

  // rotate the direction by fixed amound
  direction += (1 << 28);

  // 1-second delay
  delay(1000);
}