#pragma once

#define ONBOARD_LED 25

#define BUTTON_DRIVER direct
#define BUTTONS_AVAILABLE 11
#define BUTTON_PINS \
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

#define ENCODER_DRIVER direct
#define ENCODERS_AVAILABLE 1
#define ENCODER_PINS [0] = {20,21}

#define RGB_DRIVER pio
#define RGB_CHANNELS_AVAILABLE 1
#define RGB_PINS 22
#define RGB_PIO pio0

/*** Chain Inclusion ***/
#include_next "config.h"