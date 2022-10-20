static const uint8_t _encoder_lookup[16] = {
  0x00, 0x11, 0x22, 0x03, // 00
  0x20, 0x01, 0x02, 0x13, // 01
  0x10, 0x01, 0x02, 0x23, // 10
  0x00, 0x21, 0x12, 0x03, // 11
};

// Pin and pin indexes for our encoders
static const _pin_pair_t  _encoder_pins[ENCODERS_AVAILABLE] = { ENCODER_PINS };
static const uint8_t      _encoder_pidx[ENCODERS_ACTIVE]    = { ENCODER_CHANNELS };

// Our stored repeating timer
repeating_timer_t _encoder_timer;

#if defined(ENCODER_CHANNELS_REVERSED)
const uint8_t _encoder_state_increments[2] = {2, 1};
#else
const uint8_t _encoder_state_increments[2] = {1, 2};
#endif

// Updates all encoders
static inline void _encoder_update(void) {
  for (uint i = 0; i < ENCODERS_ACTIVE; i++) {
    //// Part 1: State Updates
    // Decrement timeouts. Clear the currently-set direction if this timeout is depleted.
    if (_encoder[i].state.timeout)      _encoder[i].state.timeout--;
    if (_encoder[i].direction.timeout)  _encoder[i].direction.timeout--;
    else _encoder[i].direction.current = 0;

    // Capture the current encoder state and advance it
    const _pin_t a = _encoder_pins[_encoder_pidx[i]].a;
    const _pin_t b = _encoder_pins[_encoder_pidx[i]].b;

    uint8_t state = _encoder[i].state.current << 2;
    if (Pin_Read(a))
      state += _encoder_state_increments[0];
    if (Pin_Read(b))
      state += _encoder_state_increments[1];

    // Lookup our result and save it, then reduce our result to emits only
    uint8_t result = _encoder_lookup[state & 0x0F];
    _encoder[i].state.current = result;
    result &= ENCODER_MASK;

    // If we have an emit, push it through error correction
    if (result) {
      // If we don't have a pending state recorded, copy our state over
      if (!_encoder[i].state.pending) {
        _encoder[i].state.pending = result;
        _encoder[i].state.timeout = ENCODER_SAMPLES_UNTIL_VALID;
        continue;
      }
      // Otherwise, check if our state matches the pending state.
      // If if does, let it pass through, resetting the timeout in the process
      if (result & _encoder[i].state.pending) {
        _encoder[i].state.timeout = ENCODER_SAMPLES_UNTIL_VALID;
      // If it doesn't, we have opposing states and need to reset
      } else {
        _encoder[i].state.pending = 0;
        _encoder[i].state.timeout = 0;
        continue;
      }
    }
    // If we don't have an emit, pull our pending state if available
    else if (_encoder[i].state.pending && !_encoder[i].state.timeout) {
      result = _encoder[i].state.pending;
      _encoder[i].state.pending = 0;
    }

    // If we don't have a result to process at this point, move to the next encoder
    if (!result) continue;

    //// Part 2: Value Updates
    // At this point, we can update our position and direction
    uint16_t physical = _encoder[i].position.physical;

    if (result & ENCODER_CCW) {
      // Physical position needs to be updated and should loop back around.
      physical--; if (physical >= ENCODER_STEPS) physical = ENCODER_STEPS - 1;
      // Logical position updates on the raw and will loop back automatically.
      _encoder[i].position.logical_raw -= ENCODER_LOGICAL_DELTA;

      // Our direction delta should also be updated.
      _encoder[i].direction.delta--;
      // If it exceeds the threshold, zero out and emit a direction
      if (_encoder[i].direction.delta <= (ENCODER_DIRECTION_THRESHOLD * -1)) {
        _encoder[i].direction.delta   = 0;
        _encoder[i].direction.current = ENCODER_CCW;
        _encoder[i].direction.timeout = ENCODER_TIMEOUT;
      }
    } else {
      physical++; if (physical >= ENCODER_STEPS) physical = 0;
      _encoder[i].position.logical_raw += ENCODER_LOGICAL_DELTA;
      _encoder[i].direction.delta++;

      if (_encoder[i].direction.delta >= ENCODER_DIRECTION_THRESHOLD) {
        _encoder[i].direction.delta   = 0;
        _encoder[i].direction.current = ENCODER_CW;
        _encoder[i].direction.timeout = ENCODER_TIMEOUT;
      }
    }
    // Commit the new physical position
    _encoder[i].position.physical = physical;
  }
}

// A wrapper for our encoder interrupt
bool _encoder_interrupt(repeating_timer_t *rt) {
  _encoder_update();
  return true;
}

// Initialize the encoder subsystem
void _impl_encoder_init(void) {
  static const uint poll = (1000000 / ENCODER_FREQUENCY);

  for (uint i = 0; i < ENCODERS_ACTIVE; i++) {
    const _pin_t a = _encoder_pins[_encoder_pidx[i]].a;
    const _pin_t b = _encoder_pins[_encoder_pidx[i]].b;

    // Set each pair of pins as inputs
    Pin_InputPullup(a);
    Pin_InputPullup(b);
  }

  alarm_pool_add_repeating_timer_us(
    _impl_arch_alarmPool(),
    poll,
    _encoder_interrupt,
    NULL,
    &_encoder_timer
  );
}
