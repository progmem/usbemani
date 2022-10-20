#include "timer.h"

void _impl_timer_init() {
  static const uint8_t  clock_divider = 8;
  static const uint16_t frequency     = 8000;

  TCCR0A = 0, TCCR0B = 0, TCNT0 = 0;
  // Count up to OCR0A
  OCR0A   = ((uint32_t)F_CPU / clock_divider) / frequency;
  TCCR0A |= _BV(WGM01);

  // Fire an interrupt when OCR0A is hit
  TIMSK0 |= _BV(OCIE0A);

  // Finally, set the clock divider to start the timer
  TCCR0B |= _BV(CS01);
}

ISR(TIMER0_COMPA_vect) {
  if (CALLBACK_OnTimer)
    CALLBACK_OnTimer();
}