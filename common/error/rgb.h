#pragma once

#if defined(RGB_CHANNELS_ACTIVE)
#if RGB_CHANNELS_ACTIVE > RGB_CHANNELS_ACTIVE_MAXIMUM
#error RGB_CHANNELS_ACTIVE cannot exceed the RGB_CHANNELS_ACTIVE_MAXIMUM declared by the driver
#endif

#if RGB_CHANNELS_ACTIVE < 0
#error RGB_CHANNELS_ACTIVE cannot be less than 0
#endif
#endif