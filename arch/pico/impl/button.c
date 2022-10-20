#include "button.h"

_button_t _buttons = {
  .mask = 0,
  .curr = 0
};

#if defined(BUTTON_DRIVER)
#include INCLUDE_IMPL(button, BUTTON_DRIVER, c)
#endif