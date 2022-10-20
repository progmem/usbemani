#pragma once

#define ONBOARD_LED 25

#define BUTTON_DRIVER direct
#define BUTTONS_AVAILABLE 11
#define BUTTON_PINS 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

#define ANALOG_DRIVER direct
#define ANALOG_CHANNELS_AVAILABLE 3
#define ANALOG_PINS 26, 27, 28

#define ENCODER_DRIVER direct
#define ENCODERS_AVAILABLE 2
#define ENCODER_PINS [0] = {20,21}, [1] = {26,27}

#define LIGHT_DRIVER direct
#define LIGHTS_AVAILABLE 11
#define LIGHT_PINS 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21

#define RGB_DRIVER pio
#define RGB_CHANNELS_AVAILABLE 2
#define RGB_PINS 22, 28
#define RGB_PIO pio0

#define PSX_DRIVER pio
#define PSX_PIO pio1
#define PSX_CMD_CLK_PINBASE 26 // QE1 for CMD, 27 for CLK
#define PSX_ATT_PIN          9 // VEFX, Yellow
#define PSX_DAT_PIN         10 // Effect, Brown
#define PSX_ACK_PIN         28 // RGB1

/*** Chain Inclusion ***/
#include_next "config.h"
