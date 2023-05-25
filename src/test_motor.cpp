#include <Arduino.h>
#include <Wire.h>

#include "motor.hpp"

Motors motors(4);

void setup() {
  // initialize I2C
  Wire.begin();

  // initialize motor manager
  motors.begin();
}

// initial direction pointing forward
uint32_t direction = 0;

void loop() {
  // output vibration for current direction
  motors.setDirection(direction);

  // rotate the direction by fixed amound
  direction += (1 << 28);

  // 1-second delay
  delay(1000);
}