/*** Timer Flags ***/
#define _IMPL_AVR8_TIMER3 "button/direct"

/*** Defines ***/
// Jump table case block, used to generate faster-executing code
#define _BUTTON_JUMP_TABLE(x) \
  case x: if (x < BUTTONS_ACTIVE) _impl_button_poll(x); return;

/*** Declarations ***/
// Pin and pin indexes for our buttons
static const _pin_t   _button_pins[BUTTONS_AVAILABLE] = { BUTTON_PINS };
static const uint8_t  _button_pidx[BUTTONS_ACTIVE]    = { BUTTON_CHANNELS };

/*** Functions ***/
static inline void _impl_button_poll(const uint8_t i) {
#if BUTTONS_ACTIVE > 0
  const _pin_t  pin = _button_pins[_button_pidx[i]];

  // Update the debounce state
  register uint8_t s = _buttons.debounce[i];
  s <<= 1; if (Pin_Read(pin)) s |= 1;
  _buttons.debounce[i] = s;

  // If we have 7 consecutive lows, the button is pressed
  if (s == 0x80) { _buttons.mask |=  _BV(i); return; }
  // If we have 7 consecutive highs, the button has been released
  if (s == 0x7F) { _buttons.mask &= ~_BV(i); return; }

  _buttons.curr = (i+1) % BUTTONS_ACTIVE;
#endif
}

ISR(TIMER3_COMPA_vect) {
  switch(_buttons.curr) {
    _BUTTON_JUMP_TABLE(0);
    _BUTTON_JUMP_TABLE(1);
    _BUTTON_JUMP_TABLE(2);
    _BUTTON_JUMP_TABLE(3);
    _BUTTON_JUMP_TABLE(4);
    _BUTTON_JUMP_TABLE(5);
    _BUTTON_JUMP_TABLE(6);
    _BUTTON_JUMP_TABLE(7);
    _BUTTON_JUMP_TABLE(8);
    _BUTTON_JUMP_TABLE(9);
    _BUTTON_JUMP_TABLE(10);
    _BUTTON_JUMP_TABLE(11);
    _BUTTON_JUMP_TABLE(12);
    _BUTTON_JUMP_TABLE(13);
    _BUTTON_JUMP_TABLE(14);
    _BUTTON_JUMP_TABLE(15);
  }
}

// Initializes the state of all buttons, including the timer
void _impl_button_init(void) {
#if BUTTONS_ACTIVE > 0
  static const uint8_t  div   = 8;
  static const uint16_t freq  = 1000 * BUTTONS_ACTIVE;

  for (int i = 0; i < BUTTONS_ACTIVE; i++) {
    const _pin_t pin = _button_pins[_button_pidx[i]];
    Pin_InputPullup(pin);
  }

  // Reset registers
  TCCR3A  = 0;
  TCCR3B  = 0;
  TCNT3   = 0;
  // Count up to OCR3A
  OCR3A   = (F_CPU / div) / freq;
  TCCR3B |= _BV(WGM32);
  // Fire an interrupt when OCR3A is hit
  TIMSK3 |= _BV(OCIE3A);
  // Set the clock divider to start the timer
  TCCR3B |= _BV(CS31);
#endif

}