#pragma once

#include <Arduino.h>

#ifdef DEBUG
#ifdef USBCON
#define DEBUG_INIT(baudrate) SerialUSB.begin()
#define DEBUG_PRINTF(fmt...) SerialUSB.printf(fmt)
#else
#define DEBUG_INIT(baudrate) Serial.begin(baudrate)
#define DEBUG_PRINTF(fmt...) Serial.printf(fmt)
#endif
#else
#define DEBUG_INIT(baudrate)
#define DEBUG_PRINTF(fmt...)
#endif

#define DEBUG_PRINT(fmt...)                                 \
  do {                                                      \
    DEBUG_PRINTF("[DEBUG] %s:%d ", __FUNCTION__, __LINE__); \
    DEBUG_PRINTF(fmt);                                      \
  } while (0)
