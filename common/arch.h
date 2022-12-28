#pragma once

#include <stdint.h>
#include "impl/arch.h"
#include "error/arch.h"

#include "button.h"

static inline void Arch_Init(void) {
  _impl_arch_init();
}

static inline void Arch_Stabilize(void) {
  _impl_arch_stabilize();
}

// Check if a specific set of buttons is being held. If so, reset to bootloader.
static inline void Arch_BootloaderCheck(void) {
#if defined(BUTTON_COMBO_ARCH_RESET)
   uint8_t  check_buttons[] = { BUTTON_COMBO_ARCH_RESET };
  uint16_t required_buttons = 0;
  uint16_t     held_buttons = 0;

  for (uint8_t i = 0; i < sizeof(check_buttons); i++) {
    const uint16_t mask = (1 << check_buttons[i]);
    required_buttons |= mask;

    if (Button_GetRaw(check_buttons[i]))
      held_buttons |= mask;
  }

  if (held_buttons == required_buttons)
    _impl_arch_resetToBootloader();
#endif
}
