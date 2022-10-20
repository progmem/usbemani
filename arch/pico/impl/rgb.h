#pragma once
#include <stdbool.h>
#include "pico/types.h"

#include "helper/impl.h"

#include "impl/arch.h"
#include "impl/pin.h"
#include "config.h"
#include "rgb/defs.h"

void _impl_rgb_init(void);
bool _impl_rgb_ready(void);
void _impl_rgb_render(void);

#if defined(RGB_DRIVER) && defined(RGB_LED_TYPE)
#include INCLUDE_IMPL(rgb, RGB_DRIVER, h)
#endif

#include "error/rgb.h"

#if defined(RGB_DRIVER) && defined(RGB_LED_TYPE)
#include INCLUDE_IMPL_RGB(RGB_DRIVER, RGB_LED_TYPE, h)
#endif

