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
  asm volatile(
    "add %0, %1    \n\t"
    "brcc L_%=     \n\t"
    "ldi %0, 0xFF  \n\t"
    "L_%=: "
    : "+a" (i)
    : "a"  (j)
  );
  return i;
}

ALWAYS_INLINE uint8_t qsub8(uint8_t i, uint8_t j) {
  asm volatile(
    "sub %0, %1    \n\t"
    "brcc L_%=     \n\t"
    "ldi %0, 0x00  \n\t"
    "L_%=: "
    : "+a" (i)
    : "a"  (j)
  );
  return i;
}

ALWAYS_INLINE uint8_t scale8(uint8_t i, uint8_t scale) {
  asm volatile(
    // Multiply 8-bit i * 8-bit scale, giving 16-bit r1,r0
    "mul %0, %1         \n\t"
    // Add i to r0, possibly setting the carry flag
    "add r0, %0         \n\t"
    // load the immediate 0 into i (note, this does _not_ touch any flags)
    "ldi %0, 0x00       \n\t"
    // walk and chew gum at the same time
    "adc %0, r1         \n\t"
    "clr __zero_reg__   \n\t"
    : "+a" (i)      // writes to i
    : "a"  (scale)  // uses scale
    : "r0", "r1"    // clobbers r0, r1
  );
  return i;
}

ALWAYS_INLINE uint8_t scale8_video(uint8_t i, uint8_t scale) {
  uint8_t j = 0;
  asm volatile(
    "tst  %[i]            \n\t"
    "breq L_%=            \n\t"
    "mul  %[i], %[scale]  \n\t"
    "mov  %[j], r1        \n\t"
    "clr  __zero_reg__    \n\t"
    "cpse %[scale], r1    \n\t"
    "subi %[j], 0xFF      \n\t"
    "L_%=:                \n\t"
    : [j] "+a" (j)
    : [i] "a" (i), [scale] "a" (scale)
    : "r0", "r1"
  );
  return j;
}

ALWAYS_INLINE uint8_t scale8_LEAVING_R1_DIRTY(uint8_t i, uint8_t scale) {
  asm volatile(
    // Multiply 8-bit i * 8-bit scale, giving 16-bit r1,r0
    "mul %0, %1         \n\t"
    // Add i to r0, possibly setting the carry flag
    "add r0, %0         \n\t"
    // load the immediate 0 into i (note, this does _not_ touch any flags)
    "ldi %0, 0x00       \n\t"
    // walk and chew gum at the same time
    "adc %0, r1         \n\t"
    // "clr __zero_reg__   \n\t"
    : "+a" (i)      // writes to i
    : "a"  (scale)  // uses scale
    : "r0", "r1"    // clobbers r0, r1
  );
  return i;
}

ALWAYS_INLINE uint8_t scale8_video_LEAVING_R1_DIRTY(uint8_t i, uint8_t scale) {
  uint8_t j = 0;
  asm volatile(
    "tst  %[i]            \n\t"
    "breq L_%=            \n\t"
    "mul  %[i], %[scale]  \n\t"
    "mov  %[j], r1        \n\t"
    "breq L_%=            \n\t"
    "subi %[j], 0xFF      \n\t"
    "L_%=:                \n\t"
    : [j] "+a" (j)
    : [i] "a" (i), [scale] "a" (scale)
    : "r0", "r1"
  );
  return j;
}

ALWAYS_INLINE void cleanup_R1(void) {
  asm volatile("clr __zero_reg__  \n\t" : : : "r1");
}

/*
#define scale8_LEAVING_R1_DIRTY scale8
#define scale8_video_LEAVING_R1_DIRTY scale8_video
#define cleanup_R1() ;
*/
RGB_Color_t HSV_ToRGB(HSV_Color_t hsv) {
  uint8_t r = 0, g = 0, b = 0;
  uint8_t hue = hsv.h,
          sat = hsv.s,
          val = hsv.v;

  uint8_t offset  = hue & 0x1f;
  uint8_t offset8 = offset;
  offset8 <<= 1;
  asm volatile("");
  offset8 <<= 1;
  asm volatile("");
  offset8 <<= 1;

  uint8_t third = scale8(offset8, (256 / 3));

  // Hue
  if (!(hue & 0x80)) {
    if (!(hue & 0x40)) {
      // Red-Orange
      if (!(hue & 0x20)) {
        r = K255 - third;
        g = third;
        b = 0;
        FORCE_REFERENCE(b);
      }
      // Orange-Yellow
      else {
        r = K171;
        g = K85 + third;
        b = 0;
        FORCE_REFERENCE(b);
      }
      b = 0;
    } else {
      // Yellow - Green
      if (!(hue & 0x20)) {
        uint8_t twothirds = scale8( offset8, ((256 * 2) / 3));
        r = K171 - twothirds;
        g = K170 + third;
        b = 0;
        FORCE_REFERENCE(b);
      }
      // Green - Cyan
      else {
        r = 0;
        FORCE_REFERENCE(r);
        g = K255 - third;
        b = third;
      }
    }
  } else {
    if (!(hue & 0x40)) {
      // Cyan - Blue
      if (!(hue & 0x20)) {
        uint8_t twothirds = scale8( offset8, ((256 * 2) / 3));
        r = 0;
        FORCE_REFERENCE(r);
        g = K171 - twothirds;
        b = K85  + twothirds;
      }
      // Blue - Purple
      else {
        r = third;
        g = 0;
        FORCE_REFERENCE(g);
        b = K255 - third;
      }
    } else {
      // Purple - Pink
      if (!(hue & 0x20)) {
        r = K85  + third;
        g = 0;
        FORCE_REFERENCE(g);
        b = K171 - third;
      }
      // Pink - Red
      else {
        r = K170 + third;
        g = 0;
        FORCE_REFERENCE(g);
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

      r = scale8_LEAVING_R1_DIRTY(r, satscale);
      g = scale8_LEAVING_R1_DIRTY(g, satscale);
      b = scale8_LEAVING_R1_DIRTY(b, satscale);
      cleanup_R1();

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
    val = scale8_video_LEAVING_R1_DIRTY(val, val);
    if (val == 0) {
      r = 0, g = 0, b = 0;
    } else {
      r = scale8_LEAVING_R1_DIRTY(r, val);
      g = scale8_LEAVING_R1_DIRTY(g, val);
      b = scale8_LEAVING_R1_DIRTY(b, val);
      cleanup_R1();
    }
  }

  RGB_Color_t color = {.r = r, .g = g, .b = b};
  return color;
}
