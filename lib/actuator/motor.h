#pragma once

#include <Adafruit_DRV2605.h>
#include <Wire.h>

class Motors {
public:
  explicit Motors(size_t num_motors = 4);
  void begin();
  bool setAmplitude(size_t idx, uint8_t amplitude);
  bool setDirection(uint32_t direction);

private:
  bool selectDevice(size_t idx);

  size_t num_motors_;
  uint32_t angle_between_motors_;
  Adafruit_DRV2605 drv2605_;
};