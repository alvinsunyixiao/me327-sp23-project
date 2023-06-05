#pragma once

#include <Adafruit_BNO08x.h>

class Quaternion {
public:
  float x;
  float y;
  float z;
  float w;

  Quaternion();
  Quaternion(float x, float y, float z, float w);
  Quaternion conjugate() const;
  Quaternion inverse(bool is_unit = true) const;
  Quaternion operator*(const Quaternion& others) const;
  Quaternion operator*(float others) const;
  Quaternion operator/(float others) const;
  float toYaw() const;
};

class IMU {
public:
  bool begin();
  void update();
  bool resetOrientation();
  bool ready() const;
  float getYaw() const;

private:
  Adafruit_BNO08x bno08x_;
  sh2_SensorValue_t sensor_value_;
  Quaternion world_R_reset_;
  bool ready_ = false;
};