#pragma once
#include <stdint.h>

#include "error/psx.h"
#include "impl/psx.h"

#include "callbacks.h"

/*** Declarations ***/
// Storage for data packet
extern PSX_Controller_t _psx;

static inline void PSX_SetMode(const PSX_Identity_t identity) {
  _psx.identity = identity;
}

static inline void PSX_Task(void) {
#if defined(PSX_ACTIVE)
  // If currently addressed, exit
  if (_impl_psx_addressed()) return;

  // Poll for new input
  if (_psx.shouldPoll) {
    // Capture input
    PSX_Input_t input = {
      .buttons = 0, .rx = 0, .ry = 0, .lx = 0, .ly = 0
    };
    // Request input data from the callback
    CALLBACK_OnPlaystationInputRequest(&input);
    // Invert the buttons before copying our input over
    input.buttons ^= 0xFFFF;
    for (uint8_t i = 0; i < sizeof(input.raw); i++)
      _psx.input.raw[i] = input.raw[i];

    // Wait until the next polling window
    _psx.shouldPoll = false;
  }
#endif
}

static inline void PSX_Init(void) {
  _psx.input.buttons = 0xFFFF;
  for (uint8_t i = 0; i < 4; i++)
    _psx.input.axis[i] = 0x80;

#if defined(PSX_ACTIVE)
  _impl_psx_init();
#endif
}
