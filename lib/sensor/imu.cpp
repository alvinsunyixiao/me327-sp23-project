#include "imu.hpp"

Quaternion::Quaternion() : Quaternion(0, 0, 0, 1) {}

Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Quaternion Quaternion::conjugate() const {
  return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::inverse(bool is_unit) const {
  Quaternion q_inv = conjugate();
  if (!is_unit) {
    q_inv = q_inv / (*this * q_inv).w;
  } 

  return q_inv;
}

Quaternion Quaternion::operator*(const Quaternion& others) const {
  return Quaternion(
    x * others.w + y * others.z - z * others.y + w * others.x,
    -x * others.z + y * others.w + z * others.x + w * others.y,
    x * others.y - y * others.x + z * others.w + w * others.z,
    w * others.w - x * others.x - y * others.y - z * others.z
  );
}

Quaternion Quaternion::operator*(float others) const {
  return Quaternion(x * others, y * others, z * others, w * others);
}

Quaternion Quaternion::operator/(float others) const {
  return *this * (1. / others);
}

float Quaternion::toYaw() const {
  return atan2(2*w*z + 2*x*y, w*w + x*x - y*y - z*z);
}

bool IMU::begin() {
  // initialize with I2C
  if (!bno08x_.begin_I2C()) {
    return false;
  }

  // enable rotation vector report
  const sh2_SensorId_t report_type = SH2_ARVR_STABILIZED_RV;
  constexpr long report_interval_us = 5000;
  if (!bno08x_.enableReport(report_type, report_interval_us)) {
    return false;
  }

  return true;
}

void IMU::update() {
  if (bno08x_.getSensorEvent(&sensor_value_)) {
    if (!ready_ && sensor_value_.sensorId == SH2_ARVR_STABILIZED_RV) {
      ready_ = true;
      resetOrientation();
    }
  }
}

bool IMU::ready() const {
  return ready_;
}

bool IMU::resetOrientation() {
  if (!ready()) {
    return false;
  }

  world_R_reset_.x = sensor_value_.un.arvrStabilizedRV.i;
  world_R_reset_.y = sensor_value_.un.arvrStabilizedRV.j;
  world_R_reset_.z = sensor_value_.un.arvrStabilizedRV.k;
  world_R_reset_.w = sensor_value_.un.arvrStabilizedRV.real;

  return true;
}

float IMU::getYaw() const {
  const Quaternion world_R_now(
    sensor_value_.un.arvrStabilizedRV.i,
    sensor_value_.un.arvrStabilizedRV.j,
    sensor_value_.un.arvrStabilizedRV.k,
    sensor_value_.un.arvrStabilizedRV.real
  );

  return (world_R_now * world_R_reset_.inverse()).toYaw();
}