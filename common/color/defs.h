#pragma once

typedef struct {
  union { uint8_t r, red; };
  union { uint8_t g, green; };
  union { uint8_t b, blue; };
} RGB_Color_t;

typedef struct {
  union { uint8_t h, hue; };
  union { uint8_t s, sat, saturation; };
  union { uint8_t v, val, value; };
} HSV_Color_t;
