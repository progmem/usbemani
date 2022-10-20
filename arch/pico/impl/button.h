#pragma once
#include <stdbool.h>
#include "pico/stdlib.h"

#include "helper/impl.h"
#include "impl/arch.h"
#include "impl/pin.h"
#include "config.h"
#include "error/button.h"

#include "button/defs.h"

/*** Declarations ***/
// Storage for buttons
extern _button_t _buttons;

/*** Prototypes ***/
void _impl_button_init(void);

#if defined(BUTTON_DRIVER)
#include INCLUDE_IMPL(button, BUTTON_DRIVER, h)
#endif