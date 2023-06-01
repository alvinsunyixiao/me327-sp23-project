#pragma once

#include <Adafruit_DRV2605.h>
#include <Wire.h>

/**
 * @brief A class to manage multiple vibration motors arranged in circular pattern.
 *        The 0th motor always facing forward, and goes counter-clockwise
 *        For example of a 4-motor configuration indexing:
 * 
 *               ^      0
 *               |   1     3
 *                      2
 */
class Motors {
public:
  /**
   * @brief Construct a new Motors object
   * 
   * @param num_motors total number of motors
   */
  explicit Motors(size_t num_motors = 4);

  /**
   * @brief Call this function in setup()
   */
  void begin();

  /**
   * @brief Set the vibration amplitude of a specific motor
   * 
   * @param idx         index of the motor to manipulate in [0, num_motors)
   * @param amplitude   amplitude in [-128, 127]
   * @return true       if set amplitude is succesful
   * @return false      if idx out of bound
   */
  bool setAmplitude(size_t idx, int8_t amplitude);

  /**
   * @brief set multiple motor amplitude by giving a direction angle
   * 
   * @param direction direction in [0, UINT32_MAX] mapped to [0, 2pi]
   * @return true     if set direction is succesful  
   * @return false    if fails to set amplitude of any motor
   */
  bool setDirection(uint32_t direction);

  /**
   * @brief stop all motor by setting 0 amplitude
   *
   * @return true   if all motor is stopped succesfully
   * @return false  otherwise
   */
  bool stopAll();

private:
  bool selectDevice(size_t idx);

  size_t num_motors_;
  uint32_t angle_between_motors_;
  Adafruit_DRV2605 drv2605_;
};