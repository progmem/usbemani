#pragma once
#include "impl/timer.h"

typedef struct {
  uint16_t ticks;
} TimerTick_t;

extern TimerTick_t _timer;

// Initialize the global timer
static inline void Timer_Init(void) {
  _impl_timer_init();
}

// Every 1/8000s, advance the global timer by one tick
static inline void Timer_Tick(void) {
  _timer.ticks++;
}

// Get the number of global timer ticks
static inline uint16_t Timer_GetTicks(void) {
  return _timer.ticks;
}

// Reset a user timer
static inline void Timer_Reset(TimerTick_t *store) {
  store->ticks = _timer.ticks;
}

// Every period milliseconds, return true
static inline bool Timer_EveryDurationInMs(TimerTick_t *store, uint16_t period) {
  const uint16_t duration = (period * TASK_TIMER_FREQUENCY) / 1000;

  const uint16_t delta = _timer.ticks - store->ticks;
  if (delta < duration) return false;

  Timer_Reset(store);
  return true;
}
