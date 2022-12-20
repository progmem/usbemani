#pragma once
#include "impl/timer.h"

typedef struct {
  uint16_t ticks;
} TimerTick_t;

extern TimerTick_t _timer;

static inline void Timer_Init(void) {
  _impl_timer_init();
}

static inline void Timer_Tick(void) {
  _timer.ticks++;
}

static inline uint16_t Timer_GetTicks(void) {
  return _timer.ticks;
}

static inline bool Timer_EveryDurationInMs(TimerTick_t *store, uint16_t period) {
  const uint16_t duration = (period * TASK_TIMER_FREQUENCY) / 1000;

  const uint16_t delta = _timer.ticks - store->ticks;
  if (delta < duration) return false;

  store->ticks = _timer.ticks;
  return true;
}
