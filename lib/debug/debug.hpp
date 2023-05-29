#pragma once

#include <Arduino.h>

#ifdef DEBUG
#ifdef USBCON
#define DEBUG_PRINTLN(msg) SerialUSB.println(msg)
#define DEBUG_PRINT(msg) SerialUSB.print(msg)
#else
#define DEBUG_PRINTLN(msg) Serial.println(msg)
#define DEBUG_PRINT(msg) Serial.print(msg)
#endif
#else
#define DEBUG_PRINTLN(msg)
#endif

#define DEBUG_HEADER            \
  do {                          \
    DEBUG_PRINT("[DEBUG] ");    \
    DEBUG_PRINT(__FUNCTION__);  \
    DEBUG_PRINT(":");           \
    DEBUG_PRINT(__LINE__);      \
    DEBUG_PRINT(" ");           \
  } while (0)
