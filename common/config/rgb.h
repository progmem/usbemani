#pragma once

/*** Fallbacks ***/
// By default, no RGB channels should be available. This is expected to be overriden by the board.
#ifndef RGB_CHANNELS_AVAILABLE
#define RGB_CHANNELS_AVAILABLE 0
#endif
#ifndef RGB_PINS
#define RGB_PINS
#endif

// By default, no RGB channels should be active. This is expected to be overridden by the controller
#ifndef RGB_CHANNELS_ACTIVE
#define RGB_CHANNELS_ACTIVE 0
#endif
#ifndef RGB_LEDS_PER_CHANNEL
#define RGB_LEDS_PER_CHANNEL 0
#endif
#ifndef RGB_CHANNELS
#define RGB_CHANNELS
#endif

