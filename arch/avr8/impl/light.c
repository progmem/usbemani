#include "light.h"

_light_t _lights = {
  .mask = 0,
};

#if defined(LIGHT_DRIVER)
#include INCLUDE_IMPL(light, LIGHT_DRIVER, c)
#endif