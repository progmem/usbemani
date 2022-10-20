#pragma once
#include <stdbool.h>
#include "pico/stdlib.h"

#include "helper/impl.h"
#include "impl/arch.h"
#include "impl/pin.h"
#include "config.h"
#include "error/analog.h"

#include "analog/defs.h"

/*** Declarations ***/
extern volatile _analog_t         _analogs[ANALOG_CHANNELS_ACTIVE];
extern volatile _analog_digital_t _analogs_digital;

/*** Prototypes ***/
void _impl_analog_init(void);

#if defined(ANALOG_DRIVER)
#include INCLUDE_IMPL(analog, ANALOG_DRIVER, h)
#endif