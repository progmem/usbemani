#pragma once

#define ONBOARD_LED 25

#define BUTTON_DRIVER direct
#define BUTTONS_AVAILABLE 8
// A/B/C/D, L/R, Start
#define BUTTON_PINS \
  29, 3, 4, 5, 17, 12, 1, 0

#define ENCODER_DRIVER direct
#define ENCODERS_AVAILABLE 2
// VOL-L, VOL-R
#define ENCODER_PINS [0] = {27,28}, [1] = {6,7}

#define RGB_DRIVER pio
#define RGB_CHANNELS_AVAILABLE 1
#define RGB_PINS 2
#define RGB_PIO pio0

/*** Chain Inclusion ***/
#include_next "config.h"