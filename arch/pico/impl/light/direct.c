static const _pin_t  _light_pins[LIGHTS_AVAILABLE] = { LIGHT_PINS };
static const uint8_t _light_pidx[LIGHTS_ACTIVE]    = { LIGHT_CHANNELS };

void _impl_light_init(void) {
#if defined(LIGHTS_ACTIVE) && (LIGHTS_ACTIVE > 0)
  for (int i = 0; i < LIGHTS_ACTIVE; i++) {
    const _pin_t pin = _light_pins[_light_pidx[i]];

#if defined(LIGHTS_INVERT)
    Pin_OutputHigh(pin);
#else
    Pin_OutputLow(pin);
#endif
  }
  _lights.mask = 0;
  _impl_light_render();
#endif
}

void _impl_light_render(void) {
#if defined(LIGHTS_ACTIVE) && (LIGHTS_ACTIVE > 0)
  static uint16_t prevMask = -1;

  if (!(prevMask ^ _lights.mask)) return;
  prevMask = _lights.mask;

  for (int i = 0; i < LIGHTS_ACTIVE; i++) {
    const _pin_t pin = _light_pins[_light_pidx[i]];
#if defined(LIGHTS_INVERT)
    if (_lights.mask & (1 << i))
      Pin_WriteLow(pin);
    else
      Pin_WriteHigh(pin);
#else
    if (_lights.mask & (1 << i))
      Pin_WriteHigh(pin);
    else
      Pin_WriteLow(pin);
#endif
  }
#endif
}
