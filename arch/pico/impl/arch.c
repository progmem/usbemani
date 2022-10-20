#include "arch.h"

alarm_pool_t *_impl_arch_secondCoreAlarmPool = NULL;

void _impl_arch_secondCoreProcess(void) {
  // Create an alarm pool, allocating memory
  alarm_pool_t *pool = alarm_pool_create(2, 16);
  // Push the address to this alarm pool over the FIFO
  multicore_fifo_push_blocking((uint32_t)pool);

  // Wait, reacting only to alarms
  for(;;) { tight_loop_contents(); }
}

void _impl_arch_init(void) {
#if defined(ONBOARD_LED)
  Pin_OutputLow(ONBOARD_LED);
#endif

  // Launch second core with our loop
  multicore_launch_core1(_impl_arch_secondCoreProcess);

  // Retrieve the adddres to our second core's alarm pool and store it
  uint32_t pool = multicore_fifo_pop_blocking();
  _impl_arch_secondCoreAlarmPool = (void *)pool;
}

alarm_pool_t *_impl_arch_alarmPool(void) {
  return _impl_arch_secondCoreAlarmPool;
}