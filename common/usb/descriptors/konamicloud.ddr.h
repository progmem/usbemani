#pragma once
#include "button.h"
#include "analog.h"

#define USB_STRING_PRODUCT_KONAMI_CLOUD "DDR MAT controller"

typedef struct __attribute__((packed)) {
  const   int8_t _unused_1[2]; // X/Y Axes
        uint16_t  buttons;
  const  uint8_t _unused_2;
} USB_InputReport_KonamiCloud_t;
