#include "rgb.h"

#if defined(RGB_DRIVER) && defined(RGB_LED_TYPE)
RGB_LED_t _rgb[RGB_LEDS];
_rgb_status_t _rgb_status = {
  .vsync  = true,
  .tick   = true,
  .transmitting = false
};

#include INCLUDE_IMPL_RGB(RGB_DRIVER, RGB_LED_TYPE, c)
#endif