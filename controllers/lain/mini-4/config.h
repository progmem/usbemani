#pragma once

/*** Controller Type ***/
#define CONTROLLER_TYPE iidx

/*** Buttons ***/
#define BUTTONS_ACTIVE  11

/*** Encoders ***/
#define ENCODERS_ACTIVE 1
#define ENCODER_PPR     36

/*** RGB ***/
#define RGB_CHANNELS_ACTIVE   1
#define RGB_LED_TYPE          WS2812
#define RGB_LEDS_PER_CHANNEL  (7 * CONTROLLER_RGB_LEDS_PER_KEY) + (4 * 1) + (CONTROLLER_RGB_LEDS_TURNTABLE)

#include_next "config.h"
