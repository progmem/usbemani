#include "psx.h"

typedef enum {
  _psx_pio0 = 0,
  _psx_pio1 = 1,
} _psx_pio_t;

#define _PSX_QUOTE(x)   #x
#define _PSX(x)         _PSX_QUOTE(x)
#define _PSX_CONCAT(y)  _PSX(_psx_y)

volatile uint8_t data_index = 0;

int64_t _impl_psx_releaseAck(alarm_id_t id, void *user_data) {
  Pin_OutputLow(PSX_ACK_PIN);
  asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  Pin_Input(PSX_ACK_PIN);
  return 0;
}

static inline void _impl_psx_acknowledge(void) {
  alarm_pool_add_alarm_in_us(
    _impl_arch_alarmPool(),
    10,
    _impl_psx_releaseAck,
    NULL,
    true
  );
}

static inline void _impl_psx_write(uint8_t byte) {
  pio_sm_clear_fifos(PSX_PIO, 0);
  pio_sm_put(PSX_PIO, 0, byte ^ 0xFF);
  // pio_sm_exec(PSX_PIO, 0, pio_encode_pull(true, true));
}

// When 8 bits have come in
void _impl_psx_handle(void) {
  // Read from RX
  uint8_t raw_data = ((pio_sm_get(PSX_PIO, 0)) >> 24);
  // Write new data
  if (_psx.index < sizeof(_psx.raw))
    _impl_psx_write(_psx.raw[_psx.index]);
  else
    _impl_psx_write(0xFF);
  // Advance the index for the next write
  _psx.index++;

  // Clear both FIFOs and interrupts
  // Repopulate TX (since we only need to push 8 bits at a time)
  pio_interrupt_clear(PSX_PIO, 0);
  irq_clear(PIO1_IRQ_0);

  switch (_psx.index) {
  case 1:
    if (raw_data == 0x01)
      _impl_psx_acknowledge();
    break;
  case 2:
    if (raw_data == 0x42)
      _impl_psx_acknowledge();
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

  if (_PSX_CONCAT(PSX_PIO)) {
    irq_set_exclusive_handler(PIO0_IRQ_0, _impl_psx_handle);
    irq_set_enabled(PIO0_IRQ_0, true);
  } else {
    irq_set_exclusive_handler(PIO1_IRQ_0, _impl_psx_handle);
    irq_set_enabled(PIO1_IRQ_0, true);
  }

  uint offset = pio_add_program(PSX_PIO, &psx_program);
  psx_program_init(PSX_PIO, 0, offset, PSX_CMD_CLK_PINBASE, PSX_DAT_PIN, PSX_ATT_PIN);
}

bool _impl_psx_addressed(void) {
  static bool alreadyReset = false;

  if (Pin_Read(PSX_ATT_PIN)) {
    if (!alreadyReset) {
      pio_sm_restart(PSX_PIO, 0);
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