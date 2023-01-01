#include "usbemani.h"

const uint8_t offsetKeys  = (7 * CONTROLLER_RGB_LEDS_PER_KEY);
const uint8_t offsetE     = (4 * 1);

Effect_Rainbow_t rainbow = New_EffectRainbow(0, offsetKeys + offsetE, CONTROLLER_RGB_LEDS_TURNTABLE,
#if defined(ENCODER_CHANNELS_REVERSED)
  true
#else
  false
#endif
);

void CALLBACK_OnRGBDrawFallback() {
  const RGB_Color_t white = {.r=128,.g=128,.b=128};
  const RGB_Color_t red   = {.r=128};

  // Clear the channel
  RGB_ClearAll(0);
  // Draw the keys
  for (uint8_t i = 0; i < 7; i++) {
    if (Button_Get(i))
      RGB_SetRange(0, (i * CONTROLLER_RGB_LEDS_PER_KEY), CONTROLLER_RGB_LEDS_PER_KEY, (i % 2 ? red : white));
  }
  // Draw E1-E4, also white
  for (uint8_t i = 0; i < 4; i++) {
    if (Button_Get(7 + i))
      RGB_Set(0, offsetKeys + i, white);
  }
  // Set saturation and value to max
  Effect_SetSaturation(255);
  Effect_SetValue(255);
  // Draw the turntable rainbow ring
  EffectRainbow_Draw(&rainbow, Encoder_PhysicalPercent(0));
}

void CALLBACK_OnRGBDrawUSB(USB_OutputReport_t *output) {
  RGB_ClearAll(0);
  // Draw the 7 keys
  for (int i = 0; i < 7; i++) {
    RGB_SetRange(0, (i * CONTROLLER_RGB_LEDS_PER_KEY), CONTROLLER_RGB_LEDS_PER_KEY, output->rgb[i]);
  }
  // Draw E1-E4
  for (uint8_t i = 0; i < 4; i++) {
    RGB_Set(0, offsetKeys + i, output->rgb[7+i]);
  }
  // Draw TT
  RGB_SetRange(0, offsetKeys + offsetE, CONTROLLER_RGB_LEDS_TURNTABLE, output->rgb[7+4]);
}

void CALLBACK_OnUSBemaniInputRequest(USB_InputReport_USBemani_t *input) {
  input->axis[0]    = 128;
  input->encoder[0] = Quirks_IIDX_LR2_Encoder(
    Encoder_LogicalPosition(0)
  );
  input->buttons    = Quirks_IIDX_LR2_Button(
    Button_GetAll(),
    Encoder_Direction(0)
  );
}
