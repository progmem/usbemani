#pragma once
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Platform/Platform.h>

#include "lufa/AppConfig.h"

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
  USB_USBTask();
}