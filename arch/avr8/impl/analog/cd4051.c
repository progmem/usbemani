// Jump table entry, used for process unrolling.
#define _ANALOG_JUMP_TABLE(x) case x: if (x < ANALOG_CHANNELS_ACTIVE) _impl_analog_processChannel(x); return;

static const _pin_t  _analog_pins[ANALOG_CHANNELS_AVAILABLE] = { ANALOG_PINS };
static const uint8_t _analog_pidx[ANALOG_CHANNELS_ACTIVE]    = { ANALOG_CHANNELS };
static const uint8_t _analog_cd4051_pins[ANALOG_CD4051_SWITCHES]  = { ANALOG_CD4051_PINS };

volatile uint8_t _analogs_index = 0;

// Given a channel index, set the CD4051 switches
static inline void _impl_analog_setSwitches(const uint8_t i) {
  const uint8_t channel = _analog_pidx[i];
  const uint8_t mask = channel & ((1 << ANALOG_CD4051_SWITCHES) - 1);

  for (uint8_t s = 0; s < ANALOG_CD4051_SWITCHES; s++) {
    if (mask & (1 << s)) {
      Pin_WriteHigh(_analog_cd4051_pins[s]);
    } else {
      Pin_WriteLow(_analog_cd4051_pins[s]);
    }
  }
}

// Given an index, switch the ADC to this channel
static inline void _impl_analog_setADC(const uint8_t i) {
  const uint8_t pin = _analog_pins[_analog_pidx[i] >> ANALOG_CD4051_SWITCHES];

  register uint8_t admux  = _BV(ADLAR) | _BV(REFS0);
  register uint8_t adcsrb = 0;

  if (pin & 1) admux  |= _BV(MUX0);
  if (pin & 2) admux  |= _BV(MUX1);
  if (pin & 4) admux  |= _BV(MUX2);
  if (pin & 8) adcsrb |= _BV(MUX5);
  ADMUX   = admux;
  ADCSRB  = adcsrb;

  _impl_analog_setSwitches(i);
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
  // TODO:  12 AVR ADC pins * 8 switch states = 96 jumps(!).
  //        Can this be done cleaner while keeping per-instance cycle counts low?
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
    _ANALOG_JUMP_TABLE(12);
    _ANALOG_JUMP_TABLE(13);
    _ANALOG_JUMP_TABLE(14);
    _ANALOG_JUMP_TABLE(15);
    _ANALOG_JUMP_TABLE(16);
    _ANALOG_JUMP_TABLE(17);
    _ANALOG_JUMP_TABLE(18);
    _ANALOG_JUMP_TABLE(19);
    _ANALOG_JUMP_TABLE(20);
    _ANALOG_JUMP_TABLE(21);
    _ANALOG_JUMP_TABLE(22);
    _ANALOG_JUMP_TABLE(23);
    _ANALOG_JUMP_TABLE(24);
    _ANALOG_JUMP_TABLE(25);
    _ANALOG_JUMP_TABLE(26);
    _ANALOG_JUMP_TABLE(27);
    _ANALOG_JUMP_TABLE(28);
    _ANALOG_JUMP_TABLE(29);
    _ANALOG_JUMP_TABLE(30);
    _ANALOG_JUMP_TABLE(31);
    _ANALOG_JUMP_TABLE(32);
    _ANALOG_JUMP_TABLE(33);
    _ANALOG_JUMP_TABLE(34);
    _ANALOG_JUMP_TABLE(35);
    _ANALOG_JUMP_TABLE(36);
    _ANALOG_JUMP_TABLE(37);
    _ANALOG_JUMP_TABLE(38);
    _ANALOG_JUMP_TABLE(39);
    _ANALOG_JUMP_TABLE(40);
    _ANALOG_JUMP_TABLE(41);
    _ANALOG_JUMP_TABLE(42);
    _ANALOG_JUMP_TABLE(43);
    _ANALOG_JUMP_TABLE(44);
    _ANALOG_JUMP_TABLE(45);
    _ANALOG_JUMP_TABLE(46);
    _ANALOG_JUMP_TABLE(47);
    _ANALOG_JUMP_TABLE(48);
    _ANALOG_JUMP_TABLE(49);
    _ANALOG_JUMP_TABLE(50);
    _ANALOG_JUMP_TABLE(51);
    _ANALOG_JUMP_TABLE(52);
    _ANALOG_JUMP_TABLE(53);
    _ANALOG_JUMP_TABLE(54);
    _ANALOG_JUMP_TABLE(55);
    _ANALOG_JUMP_TABLE(56);
    _ANALOG_JUMP_TABLE(57);
    _ANALOG_JUMP_TABLE(58);
    _ANALOG_JUMP_TABLE(59);
    _ANALOG_JUMP_TABLE(60);
    _ANALOG_JUMP_TABLE(61);
    _ANALOG_JUMP_TABLE(62);
    _ANALOG_JUMP_TABLE(63);
    _ANALOG_JUMP_TABLE(64);
    _ANALOG_JUMP_TABLE(65);
    _ANALOG_JUMP_TABLE(66);
    _ANALOG_JUMP_TABLE(67);
    _ANALOG_JUMP_TABLE(68);
    _ANALOG_JUMP_TABLE(69);
    _ANALOG_JUMP_TABLE(70);
    _ANALOG_JUMP_TABLE(71);
    _ANALOG_JUMP_TABLE(72);
    _ANALOG_JUMP_TABLE(73);
    _ANALOG_JUMP_TABLE(74);
    _ANALOG_JUMP_TABLE(75);
    _ANALOG_JUMP_TABLE(76);
    _ANALOG_JUMP_TABLE(77);
    _ANALOG_JUMP_TABLE(78);
    _ANALOG_JUMP_TABLE(79);
    _ANALOG_JUMP_TABLE(80);
    _ANALOG_JUMP_TABLE(81);
    _ANALOG_JUMP_TABLE(82);
    _ANALOG_JUMP_TABLE(83);
    _ANALOG_JUMP_TABLE(84);
    _ANALOG_JUMP_TABLE(85);
    _ANALOG_JUMP_TABLE(86);
    _ANALOG_JUMP_TABLE(87);
    _ANALOG_JUMP_TABLE(88);
    _ANALOG_JUMP_TABLE(89);
    _ANALOG_JUMP_TABLE(90);
    _ANALOG_JUMP_TABLE(91);
    _ANALOG_JUMP_TABLE(92);
    _ANALOG_JUMP_TABLE(93);
    _ANALOG_JUMP_TABLE(94);
    _ANALOG_JUMP_TABLE(95);
  }
}

// Sets up analog systems for processing
void _impl_analog_init(void) {
  // Setup the analog subsystem
  ADMUX = _BV(ADLAR) | _BV(REFS0);

  // Setup each switch pin
  for (uint8_t i = 0; i < ANALOG_CD4051_SWITCHES; i++)
    Pin_OutputLow(_analog_cd4051_pins[i]);

  // Setup each pin for analog usage
  for (uint8_t i = 0; i < ANALOG_CHANNELS_ACTIVE; i += (1 << ANALOG_CD4051_SWITCHES)) {
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
