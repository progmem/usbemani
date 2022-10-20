#include "usb/descriptors/konamicloud.iidx.premium_model.h"

// When differing, original values are commented to the right
const USB_DEVICE USB_ATTRIBUTES KonamiCloud_Device = {
  .bLength          = sizeof(USB_DEVICE),                     // 18
  .bDescriptorType  = USB_DEVICE_TYPE,                        // 0x01
  .bcdUSB           = 0x0110,                                 // 0x0200
  .bDeviceClass     = 0,
  .bDeviceSubClass  = 0,
  .bDeviceProtocol  = 0,
  .bMaxPacketSize0  = USB_DEVICE_MAX_PACKET_SIZE,             // 8
  .idVendor         = 0x1ccf,
  .idProduct        = 0x8048,
  .bcdDevice        = 0x0100,
  .iManufacturer    = StringID_Vendor_KonamiCloud,            // 1
  .iProduct         = StringID_Product_KonamiCloud,           // 2
  .iSerialNumber    = StringID_None,                          // 0
  .bNumConfigurations = 1
};

const USB_CONFIG USB_ATTRIBUTES KonamiCloud_Configuration = {
  .Config = {
    .bLength                = sizeof(USB_CONFIG_HEADER),      // 9
    .bDescriptorType        = USB_CONFIG_HEADER_TYPE,         // 0x02
    .wTotalLength           = sizeof(USB_CONFIG),             // 34
    .bNumInterfaces         = InterfaceID_Total,              // 1
    .bConfigurationValue    = 1,
    .iConfiguration         = StringID_None,                  // 0
    .bmAttributes           = USB_CONFIG_HEADER_ATTRS,        // 0x80, Not Self-Powered, No Remote-Wake
    .bMaxPower              = USB_CONFIG_HEADER_MAX_POWER,    // 100 (200mA)
  },

  .HID_Interface = {
    .bLength                = sizeof(USB_INTERFACE),          // 9
    .bDescriptorType        = USB_INTERFACE_TYPE,             // 0x04
    .bInterfaceNumber       = InterfaceID_Joystick,           // 0
    .bAlternateSetting      = 0,
    .bNumEndpoints          = 2,                              // 1
    .bInterfaceClass        = USB_INTERFACE_CLASS,            // 0x03
    .bInterfaceSubClass     = 0,
    .bInterfaceProtocol     = 0,
    .iInterface             = StringID_None,                  // 1
  },

  .HID_Report = {
    .bLength                = sizeof(USB_HID_DESCRIPTOR),     // 9
    .bDescriptorType        = USB_HID_DESCRIPTOR_TYPE,        // 0x21
    .bcdHID                 = 0x0111,
    .bCountryCode           = 0x00,
    .bNumDescriptors        = 1,
    .bDescriptorType2       = USB_HID_DESCRIPTOR_REPORT_TYPE, // 0x22
    .wDescriptorLength      = sizeof(KonamiCloud_Report)      // 50
  },

  .HID_ReportINEndpoint = {
    .bLength                = sizeof(USB_ENDPOINT),           // 7
    .bDescriptorType        = USB_ENDPOINT_TYPE,              // 0x05
    .bEndpointAddress       = USB_ENDPOINT_ADDR_IN,           // 0x81
    .bmAttributes           = USB_ENDPOINT_ATTRS_IN,          // 0x03, Interrupt
    .wMaxPacketSize         = USB_ENDPOINT_SIZE,              // 16
    .bInterval              = 0x01                            // 4
  },
  // NOTE: This device does not normally provide an output endpoint.
  .HID_ReportOUTEndpoint = {
    .bLength                = sizeof(USB_ENDPOINT),
    .bDescriptorType        = USB_ENDPOINT_TYPE,
    .bEndpointAddress       = USB_ENDPOINT_ADDR_OUT,
    .bmAttributes           = USB_ENDPOINT_ATTRS_OUT,
    .wMaxPacketSize         = USB_ENDPOINT_SIZE,
    .bInterval              = 0x01
  },
};
