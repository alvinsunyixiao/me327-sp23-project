#include "motor.h"

#define PCAADDR 0x70  // address of I2C mux

Motors::Motors(size_t num_motors) 
: num_motors_(num_motors),
  angle_between_motors_(UINT32_MAX / num_motors) {}

void Motors::begin() {
  // initialize all motors
  for (size_t i = 0; i < num_motors_; ++i) {
    this->selectDevice(i);
    drv2605_.begin();
    drv2605_.setMode(DRV2605_MODE_REALTIME);
  }
}

bool Motors::setAmplitude(size_t idx, uint8_t amplitude) {
  if (!selectDevice(idx)) {
    return false;
  }

  drv2605_.setRealtimeValue(amplitude);

  return true;
}

bool Motors::setDirection(uint32_t direction) {
  bool flag = true;
  for (size_t i = 0; i < num_motors_; ++i) {
    uint32_t angle_offset = i * angle_between_motors_;
    int32_t angle_diff = angle_offset - direction;

    // motor i is close to the specified direction
    if (abs(angle_diff) <= angle_between_motors_) {
      flag &= this->setAmplitude(i, 
        (angle_between_motors_ - abs(angle_diff)) / (angle_between_motors_ >> 8));
    }
  }

  return flag;
}

bool Motors::selectDevice(size_t idx) {
  // idx out of bound
  if (idx < 0 || idx >= num_motors_) {
    return false;
  }

  Wire.beginTransmission(PCAADDR);
  Wire.write(1 << idx);
  Wire.endTransmission();

  return true;
}