#pragma once

#include "pico/bootrom.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/time.h"

#include "impl/pin.h"
#include "config.h"

alarm_pool_t *_impl_arch_alarmPool(void);

void _impl_arch_init(void);

static inline void _impl_arch_stabilize(void) {
  sleep_ms(10);
}

static inline void _impl_arch_resetToBootloader(void) {
  reset_usb_boot(0, 0);
}
