#include "usbemani.h"

extern USB_LightingHelper_t USB_LightingHelper;

// When USB output is available, setup enumerated lighting.
WEAK void CALLBACK_OnUSBOutputAvailable(USB_OutputReport_t *output) {
  USB_LightingHelper.last_output = output;
  // TODO: Make this configurable
  USB_LightingHelper.active = 4000;
}

// When no USB output is available, traditional lights should fallback to mirroring buttons 1:1
WEAK void CALLBACK_OnLightingDrawFallback(void) {
#if defined(LIGHTS_ACTIVE) && (LIGHTS_ACTIVE > 0)
  Light_SetAll(Button_GetAll());
#endif
}

// When USB output is available, traditional lights should mirror the incoming data 1:1
WEAK void CALLBACK_OnLightingDrawUSB(USB_OutputReport_t *output) {
#if defined(USB_LIGHTS_ACTIVE) && (USB_LIGHTS_ACTIVE > 0)
  Light_SetAll(output->lights);
#endif
}
