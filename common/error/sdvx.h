#pragma once
#if !defined(ANALOG_CHANNELS_ACTIVE) || (ANALOG_CHANNELS_ACTIVE < 2)
#if !defined(ENCODERS_ACTIVE) || (ENCODERS_ACTIVE < 2)
#error SDVX requires 2 analog devices/encoders for gameplay (knobs)
#endif
#endif

#if !defined(BUTTONS_ACTIVE) || (BUTTONS_ACTIVE < 6)
#error SDVX controllers requires 6 buttons for gameplay (BT and FX buttons)
#endif
