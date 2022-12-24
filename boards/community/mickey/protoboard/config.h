#pragma once

#define BUTTON_DRIVER direct
#define BUTTONS_AVAILABLE 9
#define BUTTON_PINS 5, 6, 8, 10, 12, 14, 19, 2, 20

#define LIGHT_DRIVER direct
#define LIGHTS_AVAILABLE 8
#define LIGHT_PINS 4, 7, 9, 11, 13, 15, 18, 3

#define ENCODER_DRIVER direct
#define ENCODERS_AVAILABLE 1
#define ENCODER_PINS [0] = {16,17}

#define RGB_DRIVER pio
#define RGB_CHANNELS_AVAILABLE 1
#define RGB_PINS 28
#define RGB_PIO pio0

/*** Chain Inclusion ***/
#include_next "config.h"
