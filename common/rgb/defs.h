#pragma once
#include <stdbool.h>
#include "rgb/leds.h"

// Macros to facilitate adds
#define _RGB_ADD_0(a)               0
#define _RGB_ADD_1(a)               (a)
#define _RGB_ADD_2(a, b)            (a)+(b)
#define _RGB_ADD_3(a, b, c)         (a)+(b)+(c)
#define _RGB_ADD_4(a, b, c, d)      (a)+(b)+(c)+(d)
#define _RGB_ADD_PASTE(x, args...)  _RGB_ADD_##x(args)
#define _RGB_ADD(x, y)              _RGB_ADD_PASTE(x, y)

#define RGB_LEDS                    _RGB_ADD(RGB_CHANNELS_ACTIVE, RGB_LEDS_PER_CHANNEL)

typedef struct {
  volatile bool vsync;
  volatile bool tick;
  volatile bool transmitting;
} _rgb_status_t;
