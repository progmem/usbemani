#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "config.h"
#include "quirks/defs.h"

extern Quirks_t quirks;

#define Quirks_Enable(QUIRK)     quirks.QUIRK = true
#define Quirks_Disable(QUIRK)    quirks.QUIRK = false
#define Quirks_IsEnabled(QUIRK) (quirks.QUIRK)

// Initialize quirks
void Quirks_Init(void);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

// Quirk_IIDX_LR2: When enabled, append directional data to buttons
static uint16_t Quirks_IIDX_LR2_Button(
  const uint16_t buttons,
  const ENCODER_EMIT direction
) {
  if (!quirks.Quirk_IIDX_LR2) return buttons;
  return buttons | ((direction >> 4) << BUTTONS_ACTIVE);
}
// Quirk_IIDX_LR2: When enabled, disable encoder output
static uint16_t Quirks_IIDX_LR2_Encoder(
  const uint16_t position
) {
  if (!quirks.Quirk_IIDX_LR2) return position;
  return (ENCODER_LOGICAL_MAX >> 1);
}
// Quirk_Mode_FiveKeys: When enabled, shift keys 3-7 down by 2
static uint16_t Quirks_IIDX_FiveKeys_Button(
  const uint16_t buttons
) {
  if (!quirks.Quirk_IIDX_FiveKeys) return buttons;

  const uint16_t maskKeys   = (1 << 7) - 1;
  const uint16_t maskOthers = maskKeys ^ 0xFFFF;

  return ((buttons & maskKeys) >> 2) | (buttons & maskOthers);
}

#pragma GCC diagnostic pop