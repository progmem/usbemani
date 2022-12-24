#pragma once

/*** Controller Type ***/
#define CONTROLLER_TYPE sdvx

/*** Buttons ***/
#define BUTTONS_ACTIVE    8

/*** Encoders ***/
#define ENCODERS_ACTIVE   2
#define ENCODER_PPR       24

/*** RGB ***/
#define RGB_CHANNELS_ACTIVE   1
#define RGB_LED_TYPE          WS2812
#define RGB_LEDS_PER_CHANNEL  32

/*** Chain Inclusion ***/
#include_next "config.h"
