#pragma once
#include "button.h"

#define USB_STRING_PRODUCT_KONAMI_CLOUD "GuitarFreaks controller"

typedef struct __attribute__((packed)) {
        uint16_t  buttons;
          int8_t  gyro[3];
  const  uint8_t _unused;
} USB_InputReport_KonamiCloud_t;
