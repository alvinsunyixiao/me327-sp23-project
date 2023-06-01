#pragma once

#include <Arduino.h>

#ifdef DEBUG
#ifdef USBCON
#define DEBUG_INIT(baudrate) SerialUSB.begin()
#define DEBUG_PRINTLN(msg) SerialUSB.println(msg)
#define DEBUG_PRINT(msg) SerialUSB.print(msg)
#define DEBUG_PRINTF(fmt...) SerialUSB.printf(fmt)
#else
#define DEBUG_INIT(baudrate) Serial.begin(baudrate)
#define DEBUG_PRINTLN(msg) Serial.println(msg)
#define DEBUG_PRINT(msg) Serial.print(msg)
#define DEBUG_PRINTF(fmt...) Serial.printf(fmt)
#endif
#else
#define DEBUG_INIT(baudrate)
#define DEBUG_PRINTLN(msg)
#define DEBUG_PRINT(msg)
#define DEBUG_PRINTF(fmt...)
#endif

#define DEBUG_HEADER            \
  do {                          \
    DEBUG_PRINT("[DEBUG] ");    \
    DEBUG_PRINT(__FUNCTION__);  \
    DEBUG_PRINT(":");           \
    DEBUG_PRINT(__LINE__);      \
    DEBUG_PRINT(" ");           \
  } while (0)
