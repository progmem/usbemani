#pragma once
#include "hardware/pio.h"

// PIO supports a maximum of 4 RGB channels
// (the max number of state machines per PIO)
#define RGB_CHANNELS_ACTIVE_MAXIMUM 4