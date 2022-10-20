#pragma once
#include <avr/interrupt.h>

#include "impl/arch.h"

#include "config.h"
#include "callbacks.h"

void _impl_timer_init(void);
