#include "usbemani.h"

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

// Change `true` to `false` if the direction appears to move opposite of the turntable.
Effect_Rainbow_t rainbow = New_EffectRainbow(0, 0, 32, true);

void CALLBACK_OnRGBDrawFallback() {
  static uint8_t count;
  count++;

  // Set saturation and value to max
  Effect_SetSaturation(255);
  Effect_SetValue(255);
  // Draw the turntable rainbow ring
  EffectRainbow_Draw(&rainbow, Encoder_PhysicalPercent(0) + count);
}
