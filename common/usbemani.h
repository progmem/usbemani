#pragma once

#include "arch.h"
#include "analog.h"
#include "button.h"
#include "color.h"
#include "effect.h"
#include "encoder.h"
#include "light.h"
#include "psx.h"
#include "quirks.h"
#include "rgb.h"
#include "timer.h"
#include "utils.h"
#include "usb.h"

#include "callbacks.h"

typedef struct {
  uint16_t active;                 // Timer indicating whether USB lighting is active
  USB_OutputReport_t *last_output; // Copy of the last output report received
} USB_LightingHelper_t;
