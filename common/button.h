#pragma once
#include <stdint.h>

#include "error/button.h"
#include "impl/button.h"

/*** Declarations ***/
// Storage for buttons
extern _button_t _buttons;

static inline void Button_Init(void) {
#if (BUTTONS_ACTIVE > 0)
  for (int i = 0; i < BUTTONS_ACTIVE; i++)
    _buttons.debounce[i] = 0;

  _impl_button_init();
#endif
}

static inline uint16_t Button_GetAll(void) {
  return _buttons.mask;
}

static inline bool Button_Get(const uint8_t i) {
  return !!(_buttons.mask & (1 << i));
}

static inline bool Button_GetRaw(const uint8_t i) {
  return !(_buttons.debounce[i] & 1);
}
