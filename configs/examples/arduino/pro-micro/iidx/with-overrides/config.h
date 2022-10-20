#pragma once
// The Arduino Pro Micro is a general development board.
// The following provides a sample user configuration for the Pro Micro dev board in a IIDX controller.
// This example shows how to override parameters for a KOC.

/*** Encoder ***/
// Our KOC uses a 50PPR turntable, not a 360PPR encoder.
// To override, we first "undef" the original value.
#undef  ENCODER_PPR
// Now we can override it with our 50PPR value.
#define ENCODER_PPR 50
// Since our PPR has changed, we may want to make our encoder direction threshold smaller. We'll emit a direction every 2 quarter steps instead.
#undef  ENCODER_DIRECTION_THRESHOLD
#define ENCODER_DIRECTION_THRESHOLD 2

/*** Additional Includes ***/
// We'll include some friendly USB labels in a separate file.
// We'll pull the one from the "default" folder since the'll be the same.
#include "../default/labels.h"
