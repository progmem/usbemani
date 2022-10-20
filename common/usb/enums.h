#pragma once
typedef enum {
  USB_DeviceType_USBemani,
  USB_DeviceType_KonamiCloud,
} USB_DeviceType_t;

typedef enum {
  USB_Axis_X      = 0x30,
  USB_Axis_Y      = 0x31,
  USB_Axis_Z      = 0x32,
  USB_Axis_RX     = 0x33,
  USB_Axis_RY     = 0x34,
  USB_Axis_RZ     = 0x35,
  USB_Axis_Slider = 0x36,
  USB_Axis_Dial   = 0x37,
  USB_Axis_Wheel  = 0x38,
} USB_Axis_t;

typedef enum {
  InterfaceID_Joystick,
  InterfaceID_Total
} USB_InterfaceID_t;

typedef enum {
  /* Fixed IDs */
  StringID_None     = 0x00,
  StringID_Language = 0x00,
  StringID_Vendor_USBemani      = 0x01,
  StringID_Product_USBemani     = 0x02,
  StringID_Vendor_KonamiCloud   = 0x03,
  StringID_Product_KonamiCloud  = 0x04,
  StringID_Serial   = 0x0F,
  /* Types */
  StringType_USBStandard = 0x00,
  StringType_Button      = 0x10,
  StringType_Encoder     = 0x20,
  StringType_Axis        = 0x30,
  StringType_LightsBasic = 0x40,
  StringType_LightsRGB   = 0x80,
  StringTypeMask         = 0xF0,
  /* Index Masks for Types */
  StringIndexMask     = 0x0F,
  StringIndexMask_RGB = 0x7F,
} USB_StringType_t;

typedef enum {
  ReportID_Input = 0x01,
  ReportID_Output
} USB_ReportID_t;