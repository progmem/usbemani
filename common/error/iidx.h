#pragma once
#if !defined(ENCODERS_ACTIVE) || (ENCODERS_ACTIVE < 1)
#error IIDX controllers requires at least 1 encoder for gameplay (turntable)
#endif

#if !defined(BUTTONS_ACTIVE) || (BUTTONS_ACTIVE < 7)
#error IIDX controllers requires at least 7 buttons for gameplay (keys)
#endif
