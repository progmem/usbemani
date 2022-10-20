#pragma once
#include "usb/strings.c"
#include "usb/descriptors/output.h"
#include "usb/descriptors/usbemani.c"
#if defined(KONAMI_CLOUD_ENABLED)
#include "usb/descriptors/konamicloud.c"
#endif

_usb_status_t _usb_status = {
  .mode = USB_DeviceType_USBemani,
  .device_descriptor = (USB_DEVICE *)&USBemani_Device,
  .report_descriptor = (USB_REPORT *)&USBemani_Report,
  .config_descriptor = (USB_CONFIG *)&USBemani_Configuration,
};

void HID_SetMode(USB_DeviceType_t new_mode) {
  _usb_status.mode = new_mode;

  // Set descriptors based on the current mode
  switch(_usb_status.mode) {
#if defined(KONAMI_CLOUD_ENABLED)
  case USB_DeviceType_KonamiCloud:
    _usb_status.device_descriptor = (USB_DEVICE *)&KonamiCloud_Device,
    _usb_status.report_descriptor = (USB_REPORT *)&KonamiCloud_Report,
    _usb_status.config_descriptor = (USB_CONFIG *)&KonamiCloud_Configuration;
    return;
#endif
  // Default behavior: use USBemani descriptors
  default:
    _usb_status.device_descriptor = (USB_DEVICE *)&USBemani_Device,
    _usb_status.report_descriptor = (USB_REPORT *)&USBemani_Report,
    _usb_status.config_descriptor = (USB_CONFIG *)&USBemani_Configuration;
  }
}
