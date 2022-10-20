#include "psx.h"
#include "psx/game.c"

PSX_Controller_t _psx = {
  .identity   = PSX_Digital,
  .padding_5a = 0x5A
};

#if defined(PSX_DRIVER)
#include INCLUDE_IMPL(psx, PSX_DRIVER, c)
#endif