#include "motor.hpp"
#include "debug.hpp"

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
    // use unsigned data format for RTP data
    drv2605_.writeRegister8(DRV2605_REG_CONTROL3, 
      drv2605_.readRegister8(DRV2605_REG_CONTROL3) | 0x8);
  }
}

bool Motors::setAmplitude(size_t idx, uint8_t amplitude) {
  // select device idx
  if (!selectDevice(idx)) {
    return false;
  }

  // set real-time vibration amplitude
  drv2605_.setRealtimeValue(amplitude);

  return true;
}

bool Motors::setDirection(uint32_t direction) {
  bool flag = true;
  for (size_t i = 0; i < num_motors_; ++i) {
    // compute angle offset of each motor
    uint32_t angle_offset = i * angle_between_motors_;

    // compute angle difference with natural overflow wrapping
    int32_t angle_diff = angle_offset - direction;

    // motor i is close to the specified direction
    uint32_t amplitude  = 0;
    if (abs(angle_diff) <= angle_between_motors_) {
      // linear interpolation
      amplitude = (angle_between_motors_ - abs(angle_diff)) / (angle_between_motors_ >> 8);
      amplitude = min(amplitude, 255UL);
    }
    flag &= this->setAmplitude(i, amplitude);
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