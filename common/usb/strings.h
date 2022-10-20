#pragma once

#define STRING_DESCRIPTOR(String) { .bLength = 2 + sizeof(String) - 2, .bDescriptorType = USB_STRING_TYPE, .bString = String }
#define STRING_DESCRIPTOR_ARRAY(...) { .bLength = 2 + sizeof((uint16_t){__VA_ARGS__}), .bDescriptorType = USB_STRING_TYPE, .bString = { __VA_ARGS__ } }

/*** Required Strings ***/
/* Standard Strings */
#if !defined(USB_LANGUAGE_ID)
#define USB_LANGUAGE_ID 0x0409
#endif
#if !defined(USB_STRING_VENDOR_USBEMANI)
#define USB_STRING_VENDOR_USBEMANI "@progmem"
#endif
#if !defined(USB_STRING_PRODUCT_USBEMANI)
#define USB_STRING_PRODUCT_USBEMANI "USBemani"
#endif

/* Fallbacks */
#define USB_FALLBACK_BUTTON   "Button"
#define USB_FALLBACK_ENCODER  "Encoder"
#define USB_FALLBACK_AXIS     "Axis"
#define USB_FALLBACK_LIGHT    "Light"
#define USB_FALLBACK_RGB      "RGB"

#define WIDE_STRING(x)      USB_STRING_QUALIFIER x
#define WIDE_FALLBACK(x, y) USB_STRING_QUALIFIER x " " y
