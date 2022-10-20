#pragma once

/*** Fallbacks ***/
// By default, no light channels should be available. This is expected to be overriden by the board.
#ifndef LIGHTS_AVAILABLE
#define LIGHTS_AVAILABLE 0
#endif
#ifndef LIGHT_PINS
#define LIGHT_PINS
#endif

// By default, no light channels should be active. This is expected to be overridden by the controller
#ifndef LIGHTS_ACTIVE
#define LIGHTS_ACTIVE 0
#endif
#ifndef LIGHT_CHANNELS
#define LIGHT_CHANNELS
#endif

// If no framerate specified, assume 60FPS
#ifndef LIGHT_FRAMERATE_TARGET
#define LIGHT_FRAMERATE_TARGET 60
#endif
