#pragma once
#include "helper/impl.h"
#include "impl/arch.h"
#include "impl/pin.h"
#include "config.h"
#include "error/analog.h"

#include "analog/defs.h"

extern volatile _analog_t         _analogs[ANALOG_CHANNELS_ACTIVE];
extern volatile _analog_digital_t _analogs_digital;

void _impl_analog_init(void);

#if defined(ANALOG_DRIVER)
#include INCLUDE_IMPL(analog, ANALOG_DRIVER, h)
#endif