#include "usbemani.h"

void CALLBACK_OnHardwareReady() {
}

// RGB Map:
// * [ 0] Button -> Start
// * [ 1] Label  -> Start
// * [ 2] Button -> BT-A
// * [ 3] Label  -> BT-A
// * [ 4] Button -> BT-B
// * [ 5] Label  -> BT-B
// * [ 6] Button -> BT-C
// * [ 7] Label  -> BT-C
// * [ 8] Button -> BT-D
// * [ 9] Label  -> BT-D
// * [10] Button -> FX-L
// * [11] Label  -> FX-L
// * [12] Button -> FX-R
// * [13] Label  -> FX-R

// * [14-17] Bottom-Right
// * [18   ] VOL-R
// * [19-21] Top-Right

// * [22-24] Top-Right
// * [25   ] VOL-R
// * [26-29] Bottom-Right

// * [30-31] SDVX Logo

void CALLBACK_RGBCalculateNextFrame(void) {
  // Original controller uses a 768-hue wheel
  // Every 1ms, counter increments. Once at 32, hue increments.
  // USBemani uses 256-hue wheel, so we'll increment every 96ms.
  // 24.5s to advance through entire color wheel.
  static TimerTick_t hueIncrement;

  if (Timer_EveryDurationInMs(&hueIncrement, 96))
    _effect_global.hue++;
}

const RGB_Color_t white = {.r=255,.g=255,.b=255};
const RGB_Color_t blue  = {.r=  0,.g=  0,.b=255};
const RGB_Color_t red   = {.r=255,.g=  0,.b=  0};

void CALLBACK_OnRGBDrawFallback() {
  // Clear the channel
  RGB_ClearAll(0);

  // Labels
  for (uint8_t i = 0; i < 7; i++)
    RGB_Set(0, (i << 1) + 1, white);

  // BT-A - BT-D
  for (uint8_t i = 0; i < 4; i++) {
    if (Button_Get(i))
      RGB_Set(0, (1 + i) << 1, white);
  }
  // FX-L and FX-R
  for (uint8_t i = 0; i < 2; i++) {
    if (Button_Get(4 + i))
      RGB_Set(0, (5 + i) << 1, red);
  }
  // Start
  if (Button_Get(6))
    RGB_Set(0, 0, blue);

  // Set saturation and value to max
  Effect_SetSaturation(255);
  Effect_SetValue(0.3 * 256);

  // Draw RGB rim
  RGB_SetRange(0, 14, 18, HSV_ToRGB(_effect_global));
}

void CALLBACK_OnRGBDrawUSB(USB_OutputReport_t *output) {
  // Clear the channel
  RGB_ClearAll(0);

  // Labels
  for (uint8_t i = 0; i < 7; i++)
    RGB_Set(0, (i << 1) + 1, white);

  // BT-A - BT-D
  for (uint8_t i = 0; i < 4; i++) {
    if (output->lights & (1 << i))
      RGB_Set(0, (1 + i) << 1, white);
  }
  // FX-L and FX-R
  for (uint8_t i = 0; i < 2; i++) {
    if (output->lights & (1 << (4 + i)))
      RGB_Set(0, (5 + i) << 1, red);
  }
  // Start
  if (output->lights & (1 << 6))
    RGB_Set(0, 0, blue);

  // Set saturation and value to max
  Effect_SetSaturation(255);
  Effect_SetValue(255);

  // Draw rim
  RGB_SetRange(0, 14, 18, output->rgb[0]);
}
