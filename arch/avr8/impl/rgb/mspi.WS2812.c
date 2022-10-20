static const uint16_t _rgb_counts[RGB_CHANNELS_ACTIVE] = { RGB_LEDS_PER_CHANNEL };

volatile uint16_t nibbles_sent = 0;
const _impl_rgb_sendbits_t nibble_lookup[16] = {
  {.lookup = 0x2222},
  {.lookup = 0x2226},
  {.lookup = 0x2262},
  {.lookup = 0x2266},

  {.lookup = 0x2622},
  {.lookup = 0x2626},
  {.lookup = 0x2662},
  {.lookup = 0x2666},

  {.lookup = 0x6222},
  {.lookup = 0x6226},
  {.lookup = 0x6262},
  {.lookup = 0x6266},

  {.lookup = 0x6622},
  {.lookup = 0x6626},
  {.lookup = 0x6662},
  {.lookup = 0x6666},
};

void _impl_rgb_init(void) {
#if (RGB_CHANNELS_ACTIVE > 0)
  // Zero out the USART baud rate
  UBRR1 = 0;
  // Configure USART as MSPI, mode 1
  UCSR1C = _BV(UMSEL10) | _BV(UMSEL11) | _BV(UCSZ10);
  // TODO:  According to the datasheet, DDR_XCNn should be set to output
  //        for proper operation of MSPI
  // Enable transmission only
  UCSR1B = _BV(TXEN1);

  // Configure the baud rate. This ends up being ~375/750ns.
  UBRR1 = (F_CPU / (2 * 2666666)) - 1;

  // Configure the delay timer between transmissions, with a divider of 8.
  OCR4C   = 140;
  TCNT4   = 0;
  TIMSK4 |=  _BV(TOIE4);
  TCCR4B &= ~_BV(CS42);
#endif
}

bool _impl_rgb_ready(void) {
  if (UCSR1B & _BV(UDRIE1))
    return false;

  if (TCCR4B & _BV(CS42))
    return false;

  return true;
}

void _impl_rgb_render(void) {
  nibbles_sent = 0;

  TCCR4B &= ~_BV(CS42);
  TCNT4   = 0;
  UCSR1B |= _BV(UDRIE1);
}

ISR(USART1_UDRE_vect) {
  // If we've transferred all nibbles (2 nibbles * 3 channels * number of LEDs), reset.
  // if (_impl_rgb_ready()) return;
  if (nibbles_sent >= (_rgb_counts[0] * 6)) {
    // Disable the transfer interrupt
    UCSR1B &= ~_BV(UDRIE1);
    // Trigger the cooldown timer
    TCCR4B |=  _BV(CS42);
    return;
  }

  register uint8_t *transfer = (uint8_t *)_rgb;
  register uint8_t lookup = *(transfer + (nibbles_sent >> 1));

  if (!(nibbles_sent & 1))
    lookup = (lookup >> 4);
  lookup &= 0x0F;

  const _impl_rgb_sendbits_t packet = nibble_lookup[lookup];
  // Retrieve the relevant 16-bit packet
  // Queue 16-bit packet for transfer
  UDR1 = ~packet.serial[1];
  UDR1 = ~packet.serial[0];
  nibbles_sent++;
}

// After entire buffer has transmitted, next transmission can be sent
ISR(TIMER4_OVF_vect) {
  TCCR4B &= ~_BV(CS42);
  TCNT4   = 0;
}