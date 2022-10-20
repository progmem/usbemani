#pragma once

typedef struct {
  union {
    uint16_t lookup;
    uint8_t  serial[2];
  };
} _impl_rgb_sendbits_t;

extern RGB_LED_t _rgb[RGB_LEDS];
