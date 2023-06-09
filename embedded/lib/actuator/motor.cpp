#include "motor.hpp"
#include "debug.hpp"

#define PCAADDR 0x70  // address of I2C mux

Motors::Motors(size_t num_motors) 
: num_motors_(num_motors),
  angle_between_motors_(UINT32_MAX / num_motors),
  motor_range_(angle_between_motors_ * 2.) {
  for (size_t i = 0; i < num_motors; ++i) {
    motor_offset_[i] = 0;
  }
}

void Motors::begin() {
  // initialize all motors
  for (size_t i = 0; i < num_motors_; ++i) {
    this->selectDevice(i);
    if (!drv2605_.begin()) {
      DEBUG_PRINT("Failed to initialize DRV2605 #%u\n", i);
    }
    
    drv2605_.setMode(DRV2605_MODE_REALTIME);
  }
}

bool Motors::setAmplitude(size_t idx, int8_t amplitude) {
  // select device idx
  if (!selectDevice(idx)) {
    return false;
  }

  // set real-time vibration amplitude
  drv2605_.setRealtimeValue(amplitude);

  return true;
}

bool Motors::setDirection(int32_t direction) {
  bool flag = true;
  for (size_t i = 0; i < num_motors_; ++i) {
    // compute angle offset of each motor
    uint32_t angle_offset = i * angle_between_motors_ + motor_offset_[i];

    // compute angle difference with natural overflow wrapping
    int32_t angle_diff = angle_offset - direction;

    // motor i is close to the specified direction
    int32_t amplitude = 0;
    if (abs(angle_diff) <= motor_range_) {
      // linear interpolation
      amplitude = (motor_range_ - abs(angle_diff)) / ((motor_range_ >> 7) + 1);
    }
    flag &= this->setAmplitude(i, (int8_t)amplitude);
  }

  return flag;
}

bool Motors::selectDevice(size_t idx) {
  // idx out of bound
  if (idx < 0 || idx >= num_motors_) {
    return false;
  }

  // send device id to I2C mux
  Wire.beginTransmission(PCAADDR);
  Wire.write(1 << idx);
  Wire.endTransmission();

  return true;
}

bool Motors::stopAll() {
  bool flag = true;
  for (size_t i = 0; i < num_motors_; ++i) {
    flag &= this->setAmplitude(i, 0);
  }

  return flag;
}

bool Motors::setAngleOffset(size_t idx, int32_t offset) {
  // idx out of bound
  if (idx < 0 || idx >= num_motors_) {
    return false;
  }

  motor_offset_[idx] = offset;

  return true;
}