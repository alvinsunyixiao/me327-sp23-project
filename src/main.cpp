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

void loop() {
}