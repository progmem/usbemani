// Jump table entry, used for process unrolling.
#define _ANALOG_JUMP_TABLE(x) case x: if (x < ANALOG_CHANNELS_ACTIVE) _impl_analog_processChannel(x); return;

static const _pin_t  _analog_pins[ANALOG_CHANNELS_AVAILABLE] = { ANALOG_PINS };
static const uint8_t _analog_pidx[ANALOG_CHANNELS_ACTIVE]    = { ANALOG_CHANNELS };

volatile uint8_t _analogs_index = 0;

// Given an index, switch the ADC to this channel
static inline void _impl_analog_setADC(const uint8_t i) {
  const uint8_t pin = _analog_pins[_analog_pidx[i]];

  register uint8_t admux  = _BV(ADLAR) | _BV(REFS0);
  register uint8_t adcsrb = 0;

  if (pin & 1) admux  |= _BV(MUX0);
  if (pin & 2) admux  |= _BV(MUX1);
  if (pin & 4) admux  |= _BV(MUX2);
  if (pin & 8) adcsrb |= _BV(MUX5);
  ADMUX   = admux;
  ADCSRB  = adcsrb;

  _analogs_index = i;
}

// Process a single ADC channel, switching to the next channel afterward.
static inline void _impl_analog_processChannel(const uint8_t i) {
  // Store the highest 8 bits from the ADC, inverting if needed
  _analogs[i].raw = (
    ADCH
#if defined(ANALOG_INVERT)
    ^ 0xFF
#endif
  );

  // Switch the ADC to the next channel
#if (ANALOG_CHANNELS_ACTIVE > 0)
  const uint8_t next_index = (i+1) % ANALOG_CHANNELS_ACTIVE;
  _impl_analog_setADC(next_index);
#endif

  // Flag the highest bit of the averaging index, to indicate a new ADC read is ready
  _analogs[i].average.index |= 0x80;

  // Start the next conversion
  ADCSRA |= _BV(ADSC);
}

// Interrupt handler after each conversion is completed.
ISR(ADC_vect) {
  switch(_analogs_index) {
    _ANALOG_JUMP_TABLE(0);
    _ANALOG_JUMP_TABLE(1);
    _ANALOG_JUMP_TABLE(2);
    _ANALOG_JUMP_TABLE(3);
    _ANALOG_JUMP_TABLE(4);
    _ANALOG_JUMP_TABLE(5);
    _ANALOG_JUMP_TABLE(6);
    _ANALOG_JUMP_TABLE(7);
    _ANALOG_JUMP_TABLE(8);
    _ANALOG_JUMP_TABLE(9);
    _ANALOG_JUMP_TABLE(10);
    _ANALOG_JUMP_TABLE(11);
  }
}

// Sets up analog systems for processing
void _impl_analog_init(void) {
  // Setup the analog subsystem
  ADMUX = _BV(ADLAR) | _BV(REFS0);

  // Setup each pin for analog usage
  for (int i = 0; i < ANALOG_CHANNELS_ACTIVE; i++) {
    const _pin_t pin = _analog_pins[_analog_pidx[i]];
    if (pin < 8)
      DIDR0 |= (1 << (pin & 7));
    else
      DIDR2 |= (1 << (pin & 7));
  }

  // Select the first input
  _impl_analog_setADC(0);

  // Start the analog subsystem
  ADCSRA   = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) | _BV(ADSC) | _BV(ADIE);
}
