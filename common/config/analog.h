#pragma once

/*** Fallbacks ***/
// By default, no analog channels should be available. This is expected to be overriden by the board.
#ifndef ANALOG_CHANNELS_AVAILABLE
#define ANALOG_CHANNELS_AVAILABLE 0
#endif
#ifndef ANALOG_PINS
#define ANALOG_PINS
#endif
// By default, no analog channels should be active. This is expected to be overridden by the controller
#ifndef ANALOG_CHANNELS_ACTIVE
#define ANALOG_CHANNELS_ACTIVE 0
#endif
#ifndef ANALOG_CHANNELS
#define ANALOG_CHANNELS
#endif
