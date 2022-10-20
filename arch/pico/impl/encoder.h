#pragma once
#include "pico/stdlib.h"

#include "helper/impl.h"
#include "impl/arch.h"
#include "impl/pin.h"
#include "config.h"
#include "error/encoder.h"

#include "encoder/defs.h"

/*** Prototypes ***/
void _impl_encoder_init(void);

#if defined(ENCODER_DRIVER)
#include INCLUDE_IMPL(encoder, ENCODER_DRIVER, h)
#endif
