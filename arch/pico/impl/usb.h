#pragma once
#include <stdlib.h>

#include "tusb.h"
#include "common/tusb_common.h"
#include "device/usbd.h"

#include "impl/arch.h"
#include "impl/usb/descriptors.h"

#include "config.h"
#include "callbacks.h"

#include "helper/usb.h"
#include "usb/defs.h"
#include "usb/strings.h"

void _impl_hid_init(void);
void _impl_hid_dataHandlerTask(void);

static inline void _impl_hid_task(void) {
  _impl_hid_dataHandlerTask();
  tud_task();
}