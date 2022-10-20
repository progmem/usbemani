#pragma once

typedef struct {
  volatile uint16_t mask; // Mask of all lights
  volatile bool vsync;
} _light_t;
