#pragma once
#include "impl/timer.h"

static inline void Timer_Init(void) {
  _impl_timer_init();
}
