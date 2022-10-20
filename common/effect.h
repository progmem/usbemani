#pragma once

#include "color.h"
#include "rgb.h"

#include "effect/defs.h"

extern HSV_Color_t _effect_global;

//  Sets the global hue for all effect draw calls going forward.
static inline void Effect_SetHue(const uint8_t hue) {
  _effect_global.hue = hue;
}
//  Sets the global saturation for all effect draw calls going forward.
static inline void Effect_SetSaturation(const uint8_t sat) {
  _effect_global.sat = sat;
}
//  Sets the global value (brightness) for all effect draw calls going forward.
static inline void Effect_SetValue(const uint8_t val) {
  _effect_global.val = val;
}

//  Effect: Rainbow
//  Ex: Draw a 20-LED rainbow ring based on encoder's physical position
//  Effect_Rainbow_t rainbow = Effect_NewRainbow(0, 0, 20, false);
//  Effect_DrawRainbow(&rainbow, Encoder_PhysicalPercent(0));
//  Parameters: channel, start, count, direction
//    * channel:    The RGB channel to draw the effect on
//    * start:      The LED on the channel to start with
//    * count:      The number of LEDs to draw
//    * direction:  `false` to draw LEDs clockwise, `true` to draw counter-clockwise.
#define New_EffectRainbow(w, x, y, z) \
{ \
  .fixed = { .channel = w, .start = x, .count = y }, \
  .reciprocal = (0xFFFF / y) * (z ? -1 : 1), \
}

static inline void EffectRainbow_Draw(Effect_Rainbow_t *rainbow, const uint8_t hue) {
  // Setup our hue for math
  // Make sure to reset the `current` value in order to reset the reciprocal
  rainbow->current = (hue << 8);

  // For each LED draw requested
  for (int i = 0; i < rainbow->fixed.count; i++) {
    // Setup HSV color object
    HSV_Color_t hsv = {
      .hue = rainbow->value,
      .sat = _effect_global.sat,
      .val = _effect_global.val,
    };
    // Draw our LED
    RGB_Set(rainbow->fixed.channel, rainbow->fixed.start + i, HSV_ToRGB(hsv));
    // Advance the calculation
    rainbow->current += rainbow->reciprocal;
  }
}