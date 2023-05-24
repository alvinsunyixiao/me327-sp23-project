#include <Arduino.h>
#include <Wire.h>

#include "motor.h"

Motors motors(4);

void setup() {
  Wire.begin();
  motors.begin();
}

uint32_t direction = 0;

void loop() {
  // simple loop around the head
  motors.setDirection(direction);
  direction += (1 << 28);
  delay(1000);
}