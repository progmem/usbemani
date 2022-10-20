#pragma once
#include <stdbool.h>
#include "pico/stdlib.h"

#include "helper/impl.h"
#include "impl/arch.h"
#include "impl/pin.h"
#include "config.h"
#include "error/light.h"

#include "light/defs.h"

/*** Declarations ***/
extern _light_t _lights;

/*** Prototypes ***/
void _impl_light_init(void);
void _impl_light_render(void);

#if defined(LIGHT_DRIVER)
#include INCLUDE_IMPL(light, LIGHT_DRIVER, h)
#endif