#pragma once
#include "button.h"

#define USB_STRING_PRODUCT_KONAMI_CLOUD "Popn music controller premium model"

typedef struct __attribute__((packed)) {
        uint16_t  buttons;
          int8_t  axis[3];
  const  uint8_t _unused;
} USB_InputReport_KonamiCloud_t;
