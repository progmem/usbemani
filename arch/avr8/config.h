#pragma once

/* Encoder */
// The AVR is not powerful enough to process all encoders at once.
#define ENCODER_ROUND_ROBIN 1

#include_next "config.h"