#include "timer.h"
#include "callbacks.h"

repeating_timer_t    _task_timer;

bool _impl_timer_wrapInterrupt(repeating_timer_t *rt) {
  if (CALLBACK_OnTimer)
    CALLBACK_OnTimer();
  return true;
}

void _impl_timer_init() {
  alarm_pool_add_repeating_timer_us(
    _impl_arch_alarmPool(),
    (1000000 / TASK_TIMER_FREQUENCY),
    _impl_timer_wrapInterrupt,
    NULL,
    &_task_timer
  );
}
