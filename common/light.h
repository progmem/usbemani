#pragma once
#include <stdint.h>

#include "error/light.h"
#include "light/defs.h"
#include "impl/light.h"

/*** Declarations ***/
// Storage for lights
extern _light_t _lights;

static inline void Light_Init(void) {
#if (LIGHTS_ACTIVE > 0)
  _impl_light_init();
#endif
}

static inline void Light_Render(void) {
#if (LIGHTS_ACTIVE > 0)
  _impl_light_render();
#endif
}

static inline void Light_SetAll(uint16_t data) {
  _lights.mask = data;
}

static inline void Light_Set(const uint8_t i, bool toggle) {
  if (toggle)
    _lights.mask |=  (1 << i);
  else
    _lights.mask &= ~(1 << i);
}

static inline uint16_t Light_GetAll(void) {
  return _lights.mask;
}

static inline bool Light_Get(const uint8_t i) {
  return !!(_lights.mask & (1 << i));
}

static inline bool Light_ReadyToDraw(void) {
  bool ready = _lights.vsync;
  _lights.vsync = false;
  return ready;
}

static inline void Light_UpdateStatus(void) {
  static const uint16_t wait = (TASK_TIMER_FREQUENCY / LIGHT_FRAMERATE_TARGET);
  static       uint16_t curr = wait;

  if (curr) {
    curr--;
    return;
  }

  curr = wait;
  _lights.vsync  = true;
}
