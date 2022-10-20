#pragma once

#if defined(BUTTONS_ACTIVE)
#if BUTTONS_ACTIVE > 16
#error BUTTONS_ACTIVE cannot exceed 16
#endif

#if BUTTONS_ACTIVE < 0
#error BUTTONS_ACTIVE cannot be less than 0
#endif
#endif