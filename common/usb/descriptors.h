#pragma once

// USBemani uses LUFA's naming convention will be used to handle report descriptors.
// To support this, we need to include some macros from LUFA regardless of the platform.
#ifndef CONCAT
#define CONCAT(x, y) x ## y
#define CONCAT_EXPANDED(x, y) CONCAT(x, y)
#endif
// Now we can include LUFA's HID report data.
#include "../lib/lufa/LUFA/Drivers/USB/Class/Common/HIDReportData.h"
// Even with including these, we're still missing some report items.
// We'll add these here.
#define HID_RI_STRING(DataBits, ...) _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x70, DataBits, __VA_ARGS__)
#define HID_RI_STRING_MINIMUM(DataBits, ...) _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x80, DataBits, __VA_ARGS__)
#define HID_RI_STRING_MAXIMUM(DataBits, ...) _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x90, DataBits, __VA_ARGS__)

#define USB_CONFIG USB_Descriptor_Configuration_t

typedef struct {
  USB_CONFIG_HEADER   Config;
  USB_INTERFACE       HID_Interface;
  USB_HID_DESCRIPTOR  HID_Report;
  USB_ENDPOINT        HID_ReportINEndpoint;
  USB_ENDPOINT        HID_ReportOUTEndpoint;
} USB_CONFIG;
