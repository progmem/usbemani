#pragma once
// The following provides a sample controller configuration for a IIDX "premium model" controller. This sample assumes the following:
// * 11 buttons (7 keys, E1-E4)
// * 11 lights  (for the above)
// * 1 encoder (turntable)

/*** Controller Type ***/
// Our example is a IIDX controller. Including this line tells USBemani how to setup certain properties to best support IIDX.
#define CONTROLLER_TYPE iidx

/*** Buttons ***/
// The number of active buttons to use
#define BUTTONS_ACTIVE 11

/*** Lights ***/
// The number of active lights to use
#define LIGHTS_ACTIVE 11

/*** Encoders ***/
// The number of active encoders to use
#define ENCODERS_ACTIVE 1
// The PPR of the encoders in use.
// For optical tooth wheels, count the number of teeth on the wheel.
// For pre-packaged encoders, use the PPR as stated on the encoder or in the datasheet.
// USBemani will use this information to automatically scale the encoder to meet what the game expects for a full rotation of the encoder.
// Our example will use a generic 360PPR encoder.
#define ENCODER_PPR     360

/*** Chain Inclusion ***/
// This is what tells the compiler to include the user layout configuration.
#include_next "config.h"
