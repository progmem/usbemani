// Jump table entry, used for process unrolling.
#define _ANALOG_JUMP_TABLE(x) case x: if (x < ANALOG_CHANNELS_ACTIVE) _impl_analog_processChannel(x); return;

// The Pi Pico ADC calls use relative indexes. GPIO 26 is analog pin 0.
#define ANALOG_BASE_INDEX 26

#if defined(ANALOG_CHANNELS_ACTIVE) && (ANALOG_CHANNELS_ACTIVE > 0)
static const uint8_t _analog_pidx[ANALOG_CHANNELS_ACTIVE]         = { ANALOG_CHANNELS };
#endif
static const _pin_t  _analog_pins[ANALOG_CD4051_ANALOG_PINS]      = { ANALOG_PINS };
static const uint8_t _analog_cd4051_pins[ANALOG_CD4051_SWITCHES]  = { ANALOG_CD4051_PINS };

volatile uint8_t _analogs_index = 0;

// Given a pin index, convert it to the correct relative analog index.
static inline uint8_t _impl_analog_indexToInput(const uint8_t i) {
  return _analog_pins[_analog_pidx[i] >> ANALOG_CD4051_SWITCHES] - ANALOG_BASE_INDEX;
}

// Given a channel index, set the CD4051 switch pins
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

// Given a channel index, switch the ADC to this channel
static inline void _impl_analog_setADC(const uint8_t i) {
  adc_select_input(_impl_analog_indexToInput(i));
  _impl_analog_setSwitches(i);
  _analogs_index = i;
}

// Sets up the IRQ handler on the second core and begin the first conversion
int64_t _impl_analog_startConversion(alarm_id_t id, void *user_data) {
  hw_set_bits(&adc_hw->cs, ADC_CS_START_ONCE_BITS);
  return 0;
}

// Process a single ADC channel, switching to the next channel afterward.
static inline void _impl_analog_processChannel(const uint8_t i) {
  // Store the highest 8 bits from the ADC, inverting if needed.
  _analogs[i].value = (
    adc_fifo_get()
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

  // Start the next conversion after a brief delay
  alarm_pool_add_alarm_in_us(
    _impl_arch_alarmPool(),
    1,
    _impl_analog_startConversion,
    NULL,
    true
  );
}

// Interrupt handler after each conversion is completed.
void _impl_analog_interrupt(void) {
  // TODO:  4 RP2040 ADC pins * 8 switch states = 32 jumps.
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
  }
}

// Sets up the IRQ handler on the second core and begin the first conversion
int64_t _impl_analog_multicoreInit(alarm_id_t id, void *user_data) {
  adc_irq_set_enabled(true); // Enable interrupts

  irq_set_exclusive_handler(ADC_IRQ_FIFO, _impl_analog_interrupt);
  irq_set_enabled(ADC_IRQ_FIFO, true);

  hw_set_bits(&adc_hw->cs, ADC_CS_START_ONCE_BITS);
  return 0;
}

void _impl_analog_init(void) {
  // Setup the analog subsystem
  adc_init();
  adc_fifo_setup(
    true,   // Write each conversion to the ADC FIFO
    false,  // Don't use DMA
    1,      // Threshold for interrupts
    false,  // Don't set the error flag
    true    // 8-bit samples in the FIFO (to help reduce noise)
  );
  adc_set_clkdiv(9600); // 9600 == ~5000 samples/second to reduce noise

  // Setup each switch pin
  for (uint8_t i = 0; i < ANALOG_CD4051_SWITCHES; i++)
    Pin_OutputLow(_analog_cd4051_pins[i]);

  // Setup each pin for analog usage
  for (uint i = 0; i < ANALOG_CHANNELS_ACTIVE; i += (1 << ANALOG_CD4051_SWITCHES))
    adc_gpio_init(_analog_pins[_analog_pidx[i] >> ANALOG_CD4051_SWITCHES]);

  // Select the first input
  _analogs_index = 0;
  _impl_analog_setADC(_analogs_index);

  // Start the interupt handler on the second core. We'll use a single-fire timer to achieve this.
  alarm_pool_add_alarm_in_us(
    _impl_arch_alarmPool(),
    1,
    _impl_analog_multicoreInit,
    NULL,
    true
  );
}