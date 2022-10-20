#pragma once
#include "helper/config.h"

/*** Chain Inclusion ***/
#include_next "config.h"

/*** Final Calculations ***/
#if defined(CONTROLLER_TYPE)
#include _CONFIG_INCLUDE(CONTROLLER_TYPE, h)
#endif

#include "config/arch.h"
#include "config/analog.h"
#include "config/encoder.h"
#include "config/light.h"
#include "config/usb.h"