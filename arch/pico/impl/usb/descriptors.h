#pragma once

// NOTE: TinyUSB provides tusb_desc_string_t, but has two issues:
// A) bString is named unicode_string, which does not match USB naming convention.
// B) It uses ((packed)), which can cause misaligned pointer addresses.
// LUFA's definition is provided here instead.
typedef struct TU_ATTR_PACKED {
  uint8_t   bLength;
  uint8_t   bDescriptorType;
  uint16_t  bString[];
} USB_Fallback_String_t;

// NOTE: TinyUSB provides tusb_hid_descriptor_hid_t, but has a naming issue.
// The naming `bReportType` and `wReportLength` are more sensible names.
// However, they don't match the USB naming convention (which duplicates `bDescriptorType`).
// LUFA's definition is provided here instead.
typedef struct TU_ATTR_PACKED {
  uint8_t   bLength;
  uint8_t   bDescriptorType;
  uint16_t  bcdHID;
  uint8_t   bCountryCode;
  uint8_t   bNumDescriptors;
  uint8_t   bDescriptorType2;
  uint16_t  wDescriptorLength;
} USB_HID_Fallback_HID_t;

#define USB_ATTRIBUTES
#define USB_REPORT                      uint8_t
#define USB_DEVICE                      tusb_desc_device_t
#define USB_CONFIG_HEADER               tusb_desc_configuration_t
#define USB_INTERFACE                   tusb_desc_interface_t
#define USB_HID_DESCRIPTOR              USB_HID_Fallback_HID_t
#define USB_ENDPOINT                    tusb_desc_endpoint_t
#define USB_STRING                      USB_Fallback_String_t

#define USB_DEVICE_TYPE                 TUSB_DESC_DEVICE
#define USB_DEVICE_MAX_PACKET_SIZE      CFG_TUD_ENDPOINT0_SIZE

#define USB_CONFIG_HEADER_TYPE          TUSB_DESC_CONFIGURATION
#define USB_CONFIG_HEADER_ATTRS         TU_BIT(7)
#define USB_CONFIG_HEADER_MAX_POWER     TUSB_DESC_CONFIG_POWER_MA(500)

#define USB_INTERFACE_TYPE              TUSB_DESC_INTERFACE
#define USB_INTERFACE_CLASS             TUSB_CLASS_HID

#define USB_HID_DESCRIPTOR_TYPE         HID_DESC_TYPE_HID
#define USB_HID_DESCRIPTOR_REPORT_TYPE  HID_DESC_TYPE_REPORT

#define USB_ENDPOINT_TYPE               TUSB_DESC_ENDPOINT
#define USB_ENDPOINT_SIZE               {.size = CFG_TUD_HID_BUFSIZE}

#define USB_ENDPOINT_ADDR_IN            HID_EPADDR_IN
#define USB_ENDPOINT_ATTRS_IN           {.xfer = TUSB_XFER_INTERRUPT,}

#define USB_ENDPOINT_ADDR_OUT           HID_EPADDR_OUT
#define USB_ENDPOINT_ATTRS_OUT          {.xfer = TUSB_XFER_INTERRUPT,}

#define USB_STRING_TYPE                 TUSB_DESC_STRING
#define USB_STRING_QUALIFIER            u""
