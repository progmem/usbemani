#pragma once

/*** Fallbacks ***/
// By default, no encoders should be available. This is expected to be overriden by the board.
#ifndef ENCODERS_AVAILABLE
#define ENCODERS_AVAILABLE 0
#endif
#ifndef ENCODER_PINS
#define ENCODER_PINS
#endif

// By default, no encoders should be active. This is expected to be overridden by the controller
#ifndef ENCODERS_ACTIVE
#define ENCODERS_ACTIVE 0
#endif
#ifndef ENCODER_CHANNELS
#define ENCODER_CHANNELS
#endif

// If no encoder resolution specified, default to 8
#ifndef ENCODER_AXIS_RESOLUTION
#define ENCODER_AXIS_RESOLUTION 8
#endif

// If no encoder scaling factor was provided, use the full axis (256)
#ifndef ENCODER_SCALING_FULL_ROTATION
#define ENCODER_SCALING_FULL_ROTATION 256
#endif

// If no polling rate was provided, use 8kHz.
#ifndef ENCODER_FREQUENCY
#define ENCODER_FREQUENCY 8000
#endif

// If no PPR was provided, use the game's full rotation amount, shifted down by our quarter-step tracking
#ifndef ENCODER_PPR
#define ENCODER_PPR (ENCODER_SCALING_FULL_ROTATION >> 2)
#endif

// If no hold timeout was provided, default to 1 second (1000ms).
#ifndef ENCODER_DIRECTION_HOLD_TIMEOUT
#define ENCODER_DIRECTION_HOLD_TIMEOUT 1000
#endif

// If no directional threshold (the number of steps before a direction is emitted) is set, default to 2.
#ifndef ENCODER_DIRECTION_THRESHOLD
#define ENCODER_DIRECTION_THRESHOLD 2
#endif

// If no error correction threhold (the number of samples), max out at 255.
#ifndef ENCODER_SAMPLES_UNTIL_VALID
#define ENCODER_SAMPLES_UNTIL_VALID 255
#endif

/*** Final Calcuations ***/
// The amount to shift an encoder value down by to normalize its value
#define ENCODER_LOGICAL_SHIFT (ENCODER_AXIS_RESOLUTION - 8)

// The number of steps an encoder has
#define ENCODER_STEPS (ENCODER_PPR << 2)

// The axis maximum
#define ENCODER_LOGICAL_MAX ((1 << ENCODER_AXIS_RESOLUTION) - 1)

// The delta per rotation
#define _ENCODER_LOGICAL_DELTA \
  ((ENCODER_SCALING_FULL_ROTATION * 65536) / ENCODER_STEPS)
#define  ENCODER_LOGICAL_DELTA \
  (_ENCODER_LOGICAL_DELTA + (__builtin_popcount(_ENCODER_LOGICAL_DELTA) == 1 ? 0 : 1))

// The amount of time before an encoder's direction should be released
#if defined(ENCODER_ROUND_ROBIN)
#define ENCODER_TIMEOUT \
  (((ENCODER_FREQUENCY / ENCODERS_ACTIVE) / 1000.0) * ENCODER_DIRECTION_HOLD_TIMEOUT)
#else
#define ENCODER_TIMEOUT \
  (((ENCODER_FREQUENCY) * ENCODER_DIRECTION_HOLD_TIMEOUT) / 1000.0)
#endif
