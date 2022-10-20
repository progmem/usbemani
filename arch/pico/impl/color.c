#include "color.h"

// FastLED's 256-hue "Rainbow" HSV implementation
// https://github.com/FastLED/FastLED
#define ALWAYS_INLINE __attribute__ ((always_inline)) static inline

#define FORCE_REFERENCE(var)  asm volatile( "" : : "r" (var) )
#define K255 255
#define K171 171
#define K170 170
#define K85  85

ALWAYS_INLINE uint8_t qadd8(uint8_t i, uint8_t j) {
  int r = i + j;
  if (r > 255) r = 255;
  return r;
}

ALWAYS_INLINE uint8_t qsub8(uint8_t i, uint8_t j) {
  int r = i - j;
  if (r < 0) r = 0;
  return r;
}

ALWAYS_INLINE uint8_t scale8(uint8_t i, uint8_t scale) {
  return (((uint16_t)i) * ((uint16_t)(scale)+1)) >> 8;
}

ALWAYS_INLINE uint8_t scale8_video(uint8_t i, uint8_t scale) {
  uint8_t j = (((int)i * (int)scale) >> 8) + ((i&&scale)?1:0);
  return j;
}

RGB_Color_t HSV_ToRGB(HSV_Color_t hsv) {
  uint8_t r = 0, g = 0, b = 0;
  uint8_t hue = hsv.h,
          sat = hsv.s,
          val = hsv.v;

  uint8_t offset = hue & 0x1F;
  uint8_t offset8 = offset << 3;

  uint8_t third = scale8(offset8, (256 / 3));
  uint8_t twothirds = scale8(offset8, ((256 * 2) / 3));

  // Hue
  if (!(hue & 0x80)) {
    if (!(hue & 0x40)) {
      // Red-Orange
      if (!(hue & 0x20)) {
        r = K255 - third;
        g = third;
        b = 0;
      }
      // Orange-Yellow
      else {
        r = K171;
        g = K85 + third;
        b = 0;
      }
      b = 0;
    } else {
      if (!(hue & 0x20)) {
        r = K171 - twothirds;
        g = K170 + third;
        b = 0;
      }
      // Green - Cyan
      else {
        r = 0;
        g = K255 - third;
        b = third;
      }
    }
  } else {
    if (!(hue & 0x40)) {
      // Cyan - Blue
      if (!(hue & 0x20)) {
        r = 0;
        g = K171 - twothirds;
        b = K85  + twothirds;
      }
      // Blue - Purple
      else {
        r = third;
        g = 0;
        b = K255 - third;
      }
    } else {
      // Purple - Pink
      if (!(hue & 0x20)) {
        r = K85  + third;
        g = 0;
        b = K171 - third;
      }
      // Pink - Red
      else {
        r = K170 + third;
        g = 0;
        b = K85  - third;
      }
    }
  }
  // Saturation
  if (sat != 255) {
    if (sat) {
      uint8_t desat = 255 - sat;
      desat = scale8_video(desat, desat);

      uint8_t satscale = 255 - desat;

      r = scale8(r, satscale);
      g = scale8(g, satscale);
      b = scale8(b, satscale);

      uint8_t brightness_floor = desat;
      r += brightness_floor;
      g += brightness_floor;
      b += brightness_floor;
    } else {
      r = 255, g = 255, b = 255;
    }
  }
  // Value
  if (val != 255) {
    val = scale8_video(val, val);
    if (val == 0) {
      r = 0, g = 0, b = 0;
    } else {
      r = scale8(r, val);
      g = scale8(g, val);
      b = scale8(b, val);
    }
  }

  RGB_Color_t color = {.r = r, .g = g, .b = b};
  return color;
}