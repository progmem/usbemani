#pragma once

// Which direction a given effect should draw in
typedef enum {
  Effect_Direction_LeftToRight,
  Effect_Direction_RightToLeft
} Effect_Direction_t;

//  Fixed effect parameters.
typedef struct {
  const uint8_t channel;      // Which RGB channel to draw on
  const uint8_t start;        // Which LED to start with
  const uint8_t count;        // Number of LEDs to draw
} Effect_Fixed_t;

//  Effect: Draw a hue gradient (rainbow).
typedef struct {
  Effect_Fixed_t fixed;       // Fixed effect parameters
  const uint16_t reciprocal;  // The reciprocal to increment/decrement by
  union {
    uint16_t current;
    struct {
      uint8_t _unused;
      uint8_t  value;
    };
  };
} Effect_Rainbow_t;
