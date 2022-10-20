#pragma once
#include <stdint.h>

#include "error/encoder.h"
#include "impl/encoder.h"
#include "utils.h"

/*** Declarations ***/
// Storage for encoders
extern _encoder_t _encoder[ENCODERS_ACTIVE];

// Initialize the encoders
static inline void Encoder_Init(void) {
#if (ENCODERS_ACTIVE > 0)
  for (uint8_t i = ENCODERS_ACTIVE; i < ENCODERS_ACTIVE; i++) {
    _encoder[i].state.current = 0,
    _encoder[i].state.pending = 0,
    _encoder[i].state.timeout = 0;

    _encoder[i].position.physical = 0,
    _encoder[i].position.logical_raw = 0;

    _encoder[i].direction.current = 0,
    _encoder[i].direction.delta   = 0,
    _encoder[i].direction.timeout = 0;

    _encoder[i].position.logical = (ENCODER_LOGICAL_MAX / 2);
  }
  _impl_encoder_init();
#endif
}
// Get an encoder's physical position, 0 - (PPR * stepping - 1)
static inline uint16_t Encoder_PhysicalPosition(const uint8_t i) {
  if (i >= ENCODERS_ACTIVE) return 0;
  return _encoder[i].position.physical;
}

// Get an encoder's physical position in percent (0-255)
static inline uint8_t Encoder_PhysicalPercent(const uint8_t i) {
  return Utils_RangeToU8(_encoder[i].position.physical, ENCODER_STEPS);
}

// Get an encoder's logical position (for e.g. USBemani reports)
static inline uint16_t Encoder_LogicalPosition(const uint8_t i) {
  if (i >= ENCODERS_ACTIVE) return 0;
  return _encoder[i].position.logical & ENCODER_LOGICAL_MAX;
}

// Get an encoder's logical position in percent (0-255, for e.g. Konami Cloud reports)
static inline uint16_t Encoder_LogicalPercent(const uint8_t i) {
  if (i >= ENCODERS_ACTIVE) return 0;
#if (ENCODER_LOGICAL_SHIFT > 0)
  return _encoder[i].position.logical >> ENCODER_LOGICAL_SHIFT;
#elif (ENCODER_LOGICAL_SHIFT < 0)
  const uint8_t shift = (-1 * ENCODER_LOGICAL_SHIFT);
  return _encoder[i].position.logical << shift;
#else
  return _encoder[i].position.logical;
#endif
}

// Get an encoder's held direction
static inline ENCODER_EMIT Encoder_Direction(const uint8_t i) {
  if (i >= ENCODERS_ACTIVE) return 0;
  return _encoder[i].direction.current & ENCODER_MASK;
}

// Get an encoder's physical maximum
static inline const uint16_t Encoder_PhysicalMaximum(void) {
  return ENCODER_STEPS;
}

// Get an encoder's logical maximum
static inline const uint16_t Encoder_LogicalMaximum(void) {
  return ENCODER_LOGICAL_MAX;
}