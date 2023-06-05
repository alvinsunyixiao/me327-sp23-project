#include <Arduino.h>
#include <Wire.h>

#include "debug.hpp"
#include "motor.hpp"

#ifndef NUM_MOTORS
#define NUM_MOTORS 8
#endif

Motors motors(NUM_MOTORS);

void setup() {
  DEBUG_INIT(115200);

  // initialize I2C
  Wire.begin(SDA1, SCL1, 800000);

  // initialize motor manager
  motors.begin();
}

// initial direction pointing forward
uint32_t direction = 0;

void loop() {
  DEBUG_PRINT("setting direction %lu\n", direction);

  // output vibration for current direction
  motors.setDirection(direction);

  // rotate the direction by fixed amound
  direction += (1 << 27);

  // 1-second delay
  delay(1000);
}