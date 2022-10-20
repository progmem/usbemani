#pragma once
#include "color/defs.h"

typedef struct __attribute__((packed)) {
#if defined(USB_LIGHTS_ACTIVE) && (USB_LIGHTS_ACTIVE > 0)
  uint16_t lights;
#endif
#if defined(USB_RGB_ACTIVE) && (USB_RGB_ACTIVE > 0)
  RGB_Color_t rgb[USB_RGB_ACTIVE];
#endif
} USB_OutputReport_t;