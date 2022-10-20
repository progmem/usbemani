#include "usbemani.h"

Quirks_t quirks;

#define Quirks_CheckAndEnable(BUTTONS, QUIRK) \
{ \
  const uint8_t check_buttons[] = { BUTTONS }; \
  uint16_t required_buttons = 0; \
  uint16_t held_buttons = 0; \
  for (uint8_t i = 0; i < sizeof(check_buttons); i++) { \
    const uint16_t mask = (1 << check_buttons[i]); \
    required_buttons |= mask; \
    if (Button_GetRaw(check_buttons[i])) \
      held_buttons |= mask; \
  } \
  if (held_buttons == required_buttons) \
    quirks.QUIRK = true; \
}


// Performs on-boot checks for enabling various quirks
void Quirks_Init(void) {
#if defined(QUIRK_IIDX_LR2_BUTTON_COMBO)
  Quirks_CheckAndEnable(QUIRK_IIDX_LR2_BUTTON_COMBO, Quirk_IIDX_LR2);
#endif
#if defined(QUIRK_IIDX_FIVEKEYS_BUTTON_COMBO)
  Quirks_CheckAndEnable(QUIRK_IIDX_FIVEKEYS_BUTTON_COMBO, Quirk_IIDX_FiveKeys);
#endif
}
