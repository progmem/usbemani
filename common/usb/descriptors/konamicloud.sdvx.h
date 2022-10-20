#pragma once
#include "button.h"
#include "encoder.h"
#include "analog.h"

#define USB_STRING_PRODUCT_KONAMI_CLOUD "SOUND VOLTEX controller"

typedef struct __attribute__((packed)) {
          int8_t  vol_l;
          int8_t  vol_r;
        uint16_t  buttons;
  const  uint8_t _unused;
} USB_InputReport_KonamiCloud_t;
