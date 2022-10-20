#pragma once

typedef enum {
  ENCODER_CCW  = 0x10,
  ENCODER_CW   = 0x20,
  ENCODER_MASK = 0x30,
} ENCODER_EMIT;

typedef struct {
  volatile uint8_t      current;      // Current state of the encoder
  volatile ENCODER_EMIT pending;      // Pending encoder emit
  volatile uint8_t      timeout;      // When to process the emit
} _encoder_state_t;

typedef struct {
  volatile ENCODER_EMIT current;      // Current direction
  volatile int8_t       delta;        // How far the encoder has moved since last direction emit
  volatile uint16_t     timeout;      // How much longer to hold the direction
} _encoder_direction_t;

typedef struct {
  volatile uint16_t     physical;     // Current physical position (0-PPR*4)
  union {
    volatile uint32_t   logical_raw;  // Raw position to apply deltas to
    struct {
      volatile uint16_t logical_unused;
      volatile uint16_t logical;      // Current logical position (0-game max)
    };
  };
} _encoder_position_t;

typedef struct {
  _encoder_state_t      state;
  _encoder_direction_t  direction;
  _encoder_position_t   position;
} _encoder_t;