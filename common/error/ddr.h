#pragma once
#if !defined(ANALOG_CHANNELS_ACTIVE) || (ANALOG_CHANNELS_ACTIVE < 4)
#if !defined(BUTTONS_ACTIVE) || (BUTTONS_ACTIVE < 4)
#error DDR requires 4 FSRs/buttons for gameplay (arrow panels)
#endif
#endif
