#pragma once
#include "usb/descriptors.h"
#include "usb/enums.h"

#define HID_EPADDR_IN        0x81
#define HID_EPADDR_OUT       0x02
#define HID_EPSIZE           8

typedef struct {
  // The current mode
  USB_DeviceType_t mode;
  // Pointers to each of the descriptors in use for a given mode
  USB_DEVICE *device_descriptor;
  USB_REPORT *report_descriptor;
  USB_CONFIG *config_descriptor;
} _usb_status_t;
