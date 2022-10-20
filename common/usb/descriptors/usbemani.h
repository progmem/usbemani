#pragma once

#include "button.h"
#include "encoder.h"

typedef struct __attribute__((packed)) {
#if defined(USB_ENCODER_AXES_ACTIVE) && (USB_ENCODER_AXES_ACTIVE > 0)
  uint16_t  encoder[USB_ENCODER_AXES_ACTIVE];
#endif
#if defined(USB_GENERAL_AXES_ACTIVE) && (USB_GENERAL_AXES_ACTIVE > 0)
   int8_t   axis[USB_GENERAL_AXES_ACTIVE];
#endif
#if defined(USB_BUTTONS_ACTIVE) && (USB_BUTTONS_ACTIVE > 0)
  uint16_t  buttons;
#endif
} USB_InputReport_USBemani_t;
