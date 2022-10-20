#pragma once
#include "button.h"
#include "encoder.h"

#if (BUTTONS_ACTIVE > 9)
#include _KC_INCLUDE(CONTROLLER_TYPE, premium_model.h)
#else
#include _KC_INCLUDE(CONTROLLER_TYPE, entry_model.h)
#endif

typedef struct __attribute__((packed)) {
          int8_t  turntable;
  const   int8_t _unused_1;
        uint16_t  buttons;
  const  uint8_t _unused_2;
} USB_InputReport_KonamiCloud_t;
