#pragma once
/*** Fallbacks ***/
// If no frequency has been specified for the universal task timer, set it to 8kHz
#if !defined(TASK_TIMER_FREQUENCY)
#define TASK_TIMER_FREQUENCY 8000
#endif
