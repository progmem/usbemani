#include "usb/descriptors/usbemani.h"

/*** PID Generation ***/
// Flattened CRC calculation
#define _CRCLOOP(x) (((x) >> 1) ^ (((x) & 1) ? 0xA001 : 0))
#define _CRC(x, y) _CRCLOOP(_CRCLOOP(_CRCLOOP(_CRCLOOP(_CRCLOOP(_CRCLOOP(_CRCLOOP(_CRCLOOP((x) ^ (y)))))))))
// Intermediate PIDs
const uint16_t _pid1 = _CRC(0xFFFF,
#if defined(USB_ENCODER_AXES_ACTIVE)
    (USB_ENCODER_AXES_ACTIVE << 4) +
#endif
#if defined(USB_GENERAL_AXES_ACTIVE)
    USB_GENERAL_AXES_ACTIVE +
#endif
    0
);
const uint16_t _pid2 = _CRC(_pid1,
#if defined(USB_BUTTONS_ACTIVE)
  USB_BUTTONS_ACTIVE +
#endif
  0
);
const uint16_t _pid3 = _CRC(_pid2,
#if defined(USB_LIGHTS_ACTIVE)
  USB_LIGHTS_ACTIVE +
#endif
  0
);
// Final PID
const uint16_t _usb_product_id = _CRC(_pid3,
#if defined(USB_RGB_ACTIVE)
  USB_RGB_ACTIVE +
#endif
  0
);


#if defined(USB_ENCODER_AXES_ACTIVE)
const int32_t _usb_encoder_axis_max = ENCODER_LOGICAL_MAX;
const uint8_t _usb_encoder_axes[USB_ENCODER_AXES_ACTIVE] = { USB_ENCODER_AXES };
#endif

#if defined(USB_GENERAL_AXES_ACTIVE)
const uint8_t _usb_general_axes[USB_GENERAL_AXES_ACTIVE] = { USB_GENERAL_AXES };
#endif


const USB_REPORT USB_ATTRIBUTES USBemani_Report[] = {
	HID_RI_USAGE_PAGE(8, 0x01), // Generic Desktop
	HID_RI_USAGE(8, 0x04),      // Joystick
	HID_RI_COLLECTION(8, 0x01), // Application
#if defined(USB_ENCODER_AXES_ACTIVE) && (USB_ENCODER_AXES_ACTIVE > 0)
    HID_RI_USAGE_PAGE(8, 0x01),
    HID_RI_LOGICAL_MINIMUM(8, 0),
    HID_RI_LOGICAL_MAXIMUM(16, _usb_encoder_axis_max),
    HID_RI_USAGE(8, _usb_encoder_axes[0]),
#if (USB_ENCODER_AXES_ACTIVE > 1)
    HID_RI_USAGE(8, _usb_encoder_axes[1]),
#if (USB_ENCODER_AXES_ACTIVE > 2)
    HID_RI_USAGE(8, _usb_encoder_axes[2]),
#if (USB_ENCODER_AXES_ACTIVE > 3)
    HID_RI_USAGE(8, _usb_encoder_axes[3]),
#if (USB_ENCODER_AXES_ACTIVE > 4)
    HID_RI_USAGE(8, _usb_encoder_axes[4]),
#endif
#endif
#endif
#endif
    HID_RI_REPORT_COUNT(8, USB_ENCODER_AXES_ACTIVE),
    HID_RI_REPORT_SIZE(8, 16),
    HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_WRAP | HID_IOF_NO_PREFERRED_STATE),
#endif
#if defined(USB_GENERAL_AXES_ACTIVE) && (USB_GENERAL_AXES_ACTIVE > 0)
    HID_RI_USAGE_PAGE(8, 0x01),
    HID_RI_LOGICAL_MINIMUM(8, 0),
    HID_RI_LOGICAL_MAXIMUM(16, 255),
    HID_RI_USAGE(8, _usb_general_axes[0]),
#if (USB_GENERAL_AXES_ACTIVE > 1)
    HID_RI_USAGE(8, _usb_general_axes[1]),
#if (USB_GENERAL_AXES_ACTIVE > 2)
    HID_RI_USAGE(8, _usb_general_axes[2]),
#if (USB_GENERAL_AXES_ACTIVE > 3)
    HID_RI_USAGE(8, _usb_general_axes[3]),
#if (USB_GENERAL_AXES_ACTIVE > 4)
    HID_RI_USAGE(8, _usb_general_axes[4]),
#if (USB_GENERAL_AXES_ACTIVE > 5)
    HID_RI_USAGE(8, _usb_general_axes[5]),
#if (USB_GENERAL_AXES_ACTIVE > 6)
    HID_RI_USAGE(8, _usb_general_axes[6]),
#if (USB_GENERAL_AXES_ACTIVE > 7)
    HID_RI_USAGE(8, _usb_general_axes[7]),
#if (USB_GENERAL_AXES_ACTIVE > 8)
    HID_RI_USAGE(8, _usb_general_axes[8]),
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
    HID_RI_REPORT_COUNT(8, USB_GENERAL_AXES_ACTIVE),
    HID_RI_REPORT_SIZE(8, 8),
    HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
#endif
#if defined(USB_BUTTONS_ACTIVE) && (USB_BUTTONS_ACTIVE > 0)
		HID_RI_USAGE_PAGE(8, 0x09), // Button
		HID_RI_USAGE_MINIMUM(8, 1),
		HID_RI_USAGE_MAXIMUM(8, USB_BUTTONS_ACTIVE),
		HID_RI_LOGICAL_MINIMUM(8, 0),
		HID_RI_LOGICAL_MAXIMUM(8, 1),
		HID_RI_REPORT_SIZE(8, 1),
		HID_RI_REPORT_COUNT(8, USB_BUTTONS_ACTIVE),
		HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
#if (USB_BUTTONS_ACTIVE < 16)
		HID_RI_REPORT_SIZE(8, 16 - USB_BUTTONS_ACTIVE),
		HID_RI_REPORT_COUNT(8, 1),
		HID_RI_INPUT(8, HID_IOF_CONSTANT),
#endif
#endif
#include "usb/descriptors/output.c"
  HID_RI_END_COLLECTION(0),
};

const USB_DEVICE USB_ATTRIBUTES USBemani_Device = {
  .bLength          = sizeof(USB_DEVICE),
  .bDescriptorType  = USB_DEVICE_TYPE,
  .bcdUSB           = 0x110,
  .bDeviceClass     = 0,
  .bDeviceSubClass  = 0,
  .bDeviceProtocol  = 0,
  .bMaxPacketSize0  = USB_DEVICE_MAX_PACKET_SIZE,
  .idVendor         = 0x0573,
  .idProduct        = _usb_product_id,
  .bcdDevice        = 0x0100,
  .iManufacturer    = StringID_Vendor_USBemani,
  .iProduct         = StringID_Product_USBemani,
  .iSerialNumber    = StringID_None,
  .bNumConfigurations = 1
};

const USB_CONFIG USB_ATTRIBUTES USBemani_Configuration = {
  .Config = {
    .bLength                = sizeof(USB_CONFIG_HEADER),
    .bDescriptorType        = USB_CONFIG_HEADER_TYPE,
    .wTotalLength           = sizeof(USB_CONFIG),
    .bNumInterfaces         = InterfaceID_Total,
    .bConfigurationValue    = 1,
    .iConfiguration         = StringID_None,
    .bmAttributes           = USB_CONFIG_HEADER_ATTRS,
    .bMaxPower              = USB_CONFIG_HEADER_MAX_POWER,
  },

  .HID_Interface = {
    .bLength                = sizeof(USB_INTERFACE),
    .bDescriptorType        = USB_INTERFACE_TYPE,
    .bInterfaceNumber       = InterfaceID_Joystick,
    .bAlternateSetting      = 0,
    .bNumEndpoints          = 2,
    .bInterfaceClass        = USB_INTERFACE_CLASS,
    .bInterfaceSubClass     = 0,
    .bInterfaceProtocol     = 0,
    .iInterface             = StringID_None,
  },

  .HID_Report = {
    .bLength                = sizeof(USB_HID_DESCRIPTOR),
    .bDescriptorType        = USB_HID_DESCRIPTOR_TYPE,
    .bcdHID                 = 0x0111,
    .bCountryCode           = 0x00,
    .bNumDescriptors        = 1,
    .bDescriptorType2       = USB_HID_DESCRIPTOR_REPORT_TYPE,
    .wDescriptorLength      = sizeof(USBemani_Report),
  },

  .HID_ReportINEndpoint = {
    .bLength                = sizeof(USB_ENDPOINT),
    .bDescriptorType        = USB_ENDPOINT_TYPE,
    .bEndpointAddress       = USB_ENDPOINT_ADDR_IN,
    .wMaxPacketSize         = USB_ENDPOINT_SIZE,
    .bInterval              = 0x01,
    .bmAttributes           = USB_ENDPOINT_ATTRS_IN,
  },

  .HID_ReportOUTEndpoint = {
    .bLength                = sizeof(USB_ENDPOINT),
    .bDescriptorType        = USB_ENDPOINT_TYPE,
    .bEndpointAddress       = USB_ENDPOINT_ADDR_OUT,
    .wMaxPacketSize         = USB_ENDPOINT_SIZE,
    .bInterval              = 0x01,
    .bmAttributes           = USB_ENDPOINT_ATTRS_OUT,
  },
};

WEAK void CALLBACK_OnUSBemaniInputRequest(USB_InputReport_USBemani_t *input) {
  input->buttons = Button_GetAll();

  // Pull encoder input unless disabled
#if defined(USB_ENCODER_AXES_ACTIVE) && (USB_ENCODER_AXES_ACTIVE > 0)
  for (uint8_t i = 0; i < USB_ENCODER_AXES_ACTIVE; i++) {
    input->encoder[i] = Encoder_LogicalPosition(i);
  }
#endif

#if defined(USB_GENERAL_AXES_ACTIVE) && (USB_GENERAL_AXES_ACTIVE > 0)
  // Center the axes
  for (uint8_t i = 0; i < USB_GENERAL_AXES_ACTIVE; i++)
    input->axis[i] = 128;
#endif
}
