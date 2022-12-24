#pragma once
// DJDao made a number of IIDX controllers that all share similar specs.
// Until more differences are identified, the following describes the hardware for most DJDao IIDX controllers during a certain era of production.

/*** Controller Type ***/
#define CONTROLLER_TYPE iidx

/*** Buttons ***/
#define BUTTONS_ACTIVE    9

/*** Lights ***/
#define LIGHTS_ACTIVE     9

/*** Encoders ***/
// The encoder tooth wheel DJDao uses has some variety in it, with common tooth counts being 72, 80, and 100.
// 80 PPR has been selected as this appears to be the most common.
#define ENCODERS_ACTIVE   1
#define ENCODER_PPR       80

/*** Chain Inclusion ***/
#include_next "config.h"
