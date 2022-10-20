#pragma once

static inline void _impl_psx_acknowledge(void) {
  // TODO: How long should we wait until responding?
  asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  // Bring the pin low
  Pin_OutputLow(PSX_ACK_PIN);
  // Wait 40 cycles, the length of a PS1 controller.
  asm volatile(
    "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n"
    "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n"
    "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n"
    "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n"
    "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n"
  );
  // Release the pin
  Pin_InputFloat(PSX_ACK_PIN);
}

static inline void _impl_psx_write(uint8_t data) {
  SPDR = (data
#if defined(PSX_INVERT_MISO)
  ^ 0xFF
#endif
  );
}

// When 8 bits have come in
ISR(SPI_STC_vect) {
  // Read from RX
  const uint8_t raw_data = SPDR;
  // Write new data
  if (_psx.index < sizeof(_psx.raw))
    _impl_psx_write(_psx.raw[_psx.index]);
  else
    _impl_psx_write(0xFF);
  // Advance the index for the next write
  _psx.index++;

  switch(_psx.index) {
  case 1:
    if (raw_data == 0x01) _impl_psx_acknowledge();
    break;
  case 2:
    if (raw_data == 0x42) _impl_psx_acknowledge();
    break;
  case 3:
  case 4:
    _impl_psx_acknowledge();
    break;
  case 5:
  case 6:
  case 7:
  case 8:
    if (_psx.identity == PSX_AnalogRed) _impl_psx_acknowledge();
  }
}

void _impl_psx_init(void) {
  // Configure DAT/MISO and ACK
  Pin_InputFloat(PSX_ACK_PIN);
  Pin_OutputLow(PSX_DAT_PIN);

  // Enable SPI mode 3. Data in on falling edge, sampled on rising edge.
  // Transmit LSB first with interrupts.
  SPCR = _BV(CPOL) | _BV(CPHA) | _BV(DORD) | _BV(SPIE) | _BV(SPE);

  // Pre-load the first byte
  _impl_psx_write(0xFF);
}

bool _impl_psx_addressed(void) {
  static bool alreadyReset = false;

  if (Pin_Read(PSX_ATT_PIN)) {
    if (!alreadyReset) {
      _psx.shouldPoll = true;
      _psx.index = 0;
      _impl_psx_write(0xFF);
    }

    alreadyReset = true;
    return false;
  }

  alreadyReset = false;
  return true;
}

