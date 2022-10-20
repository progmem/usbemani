#pragma once
#include <stdbool.h>

#include "helper/impl.h"
#include "impl/arch.h"
#include "impl/pin.h"
#include "config.h"
#include "error/psx.h"

#include "psx/defs.h"

/*** Declarations ***/
// Storage for generic console input report
extern PSX_Controller_t _psx;

/*** Prototypes ***/
void _impl_psx_init(void);
bool _impl_psx_addressed(void);

#if defined(PSX_DRIVER) && defined(PSX_ACTIVE)
#include INCLUDE_IMPL(psx, PSX_DRIVER, h)
#endif