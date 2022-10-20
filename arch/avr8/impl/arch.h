#pragma once
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "impl/pin.h"
#include "config.h"

static inline void _impl_arch_init(void) {
  // Clear and disable the watchdog
  MCUSR &= ~(1 << WDRF);
  wdt_reset();
  wdt_disable();

  cli();

  // Configure the clock prescaler
  clock_prescale_set(clock_div_1);

#if defined(ONBOARD_LED)
  Pin_OutputLow(ONBOARD_LED);
#endif
}

static inline void _impl_arch_stabilize(void) {
  _delay_ms(10);
}

static inline void _impl_arch_resetToBootloader(void) {
  // TODO: Need to determine how to manage this
}