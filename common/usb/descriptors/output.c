// NOTE: This is a partial descriptor

#ifndef RI_LIGHT
#define RI_LIGHT(index) \
HID_RI_USAGE_PAGE(8, 0x0A), \
HID_RI_USAGE(8, index + 1),     \
HID_RI_COLLECTION(8, 0x02),   \
  HID_RI_USAGE_PAGE(8, 0x08), \
  HID_RI_USAGE(8, 0x4B),      \
  HID_RI_REPORT_SIZE(8, 1),   \
  HID_RI_REPORT_COUNT(8, 1),  \
  HID_RI_STRING(8, StringType_LightsBasic | index), \
  HID_RI_OUTPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NON_VOLATILE), \
HID_RI_END_COLLECTION(0)
#endif

#ifndef RI_RGB
#define RI_RGB(index) \
HID_RI_USAGE_PAGE(8, 0x0A), \
HID_RI_USAGE(8, 0x11 + (index * 3)), \
HID_RI_COLLECTION(8, 0x02),   \
  HID_RI_USAGE_PAGE(8, 0x08), \
  HID_RI_USAGE(8, 0x4B),      \
  HID_RI_REPORT_SIZE(8, 8),   \
  HID_RI_REPORT_COUNT(8, 1),  \
  HID_RI_STRING(8, (StringType_LightsRGB | (index * 3)) + 0), \
  HID_RI_OUTPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NON_VOLATILE), \
HID_RI_END_COLLECTION(0), \
HID_RI_USAGE_PAGE(8, 0x0A), \
HID_RI_USAGE(8, 0x12 + (index * 3)), \
HID_RI_COLLECTION(8, 0x02),   \
  HID_RI_USAGE_PAGE(8, 0x08), \
  HID_RI_USAGE(8, 0x4B),      \
  HID_RI_REPORT_SIZE(8, 8),   \
  HID_RI_REPORT_COUNT(8, 1),  \
  HID_RI_STRING(8, (StringType_LightsRGB | (index * 3)) + 1), \
  HID_RI_OUTPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NON_VOLATILE), \
HID_RI_END_COLLECTION(0), \
HID_RI_USAGE_PAGE(8, 0x0A), \
HID_RI_USAGE(8, 0x13 + (index * 3)),  \
HID_RI_COLLECTION(8, 0x02),   \
  HID_RI_USAGE_PAGE(8, 0x08), \
  HID_RI_USAGE(8, 0x4B),      \
  HID_RI_REPORT_SIZE(8, 8),   \
  HID_RI_REPORT_COUNT(8, 1),  \
  HID_RI_STRING(8, (StringType_LightsRGB | (index * 3)) + 2), \
  HID_RI_OUTPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NON_VOLATILE), \
HID_RI_END_COLLECTION(0)
#endif


#if defined(USB_LIGHTS_ACTIVE) && (USB_LIGHTS_ACTIVE > 0)
		HID_RI_LOGICAL_MINIMUM(8, 0),
		HID_RI_LOGICAL_MAXIMUM(8, 1),
    RI_LIGHT(0),
#if (USB_LIGHTS_ACTIVE > 1)
    RI_LIGHT(1),
#if (USB_LIGHTS_ACTIVE > 2)
    RI_LIGHT(2),
#if (USB_LIGHTS_ACTIVE > 3)
    RI_LIGHT(3),
#if (USB_LIGHTS_ACTIVE > 4)
    RI_LIGHT(4),
#if (USB_LIGHTS_ACTIVE > 5)
    RI_LIGHT(5),
#if (USB_LIGHTS_ACTIVE > 6)
    RI_LIGHT(6),
#if (USB_LIGHTS_ACTIVE > 7)
    RI_LIGHT(7),
#if (USB_LIGHTS_ACTIVE > 8)
    RI_LIGHT(8),
#if (USB_LIGHTS_ACTIVE > 9)
    RI_LIGHT(9),
#if (USB_LIGHTS_ACTIVE > 10)
    RI_LIGHT(10),
#if (USB_LIGHTS_ACTIVE > 11)
    RI_LIGHT(11),
#if (USB_LIGHTS_ACTIVE > 12)
    RI_LIGHT(12),
#if (USB_LIGHTS_ACTIVE > 13)
    RI_LIGHT(13),
#if (USB_LIGHTS_ACTIVE > 14)
    RI_LIGHT(14),
#if (USB_LIGHTS_ACTIVE > 15)
    RI_LIGHT(15),
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#if (USB_LIGHTS_ACTIVE < 16)
		HID_RI_REPORT_SIZE(8, 16 - USB_LIGHTS_ACTIVE),
		HID_RI_REPORT_COUNT(8, 1),
		HID_RI_OUTPUT(8, HID_IOF_CONSTANT),
#endif
#endif

#if defined(USB_RGB_ACTIVE) && (USB_RGB_ACTIVE > 0)
		HID_RI_LOGICAL_MINIMUM(8, 0),
		HID_RI_LOGICAL_MAXIMUM(16, 255),
    RI_RGB(0),
#if (USB_RGB_ACTIVE > 1)
    RI_RGB(1),
#if (USB_RGB_ACTIVE > 2)
    RI_RGB(2),
#if (USB_RGB_ACTIVE > 3)
    RI_RGB(3),
#if (USB_RGB_ACTIVE > 4)
    RI_RGB(4),
#if (USB_RGB_ACTIVE > 5)
    RI_RGB(5),
#if (USB_RGB_ACTIVE > 6)
    RI_RGB(6),
#if (USB_RGB_ACTIVE > 7)
    RI_RGB(7),
#if (USB_RGB_ACTIVE > 8)
    RI_RGB(8),
#if (USB_RGB_ACTIVE > 9)
    RI_RGB(9),
#if (USB_RGB_ACTIVE > 10)
    RI_RGB(10),
#if (USB_RGB_ACTIVE > 11)
    RI_RGB(11),
#if (USB_RGB_ACTIVE > 12)
    RI_RGB(12),
#if (USB_RGB_ACTIVE > 13)
    RI_RGB(13),
#if (USB_RGB_ACTIVE > 14)
    RI_RGB(14),
#if (USB_RGB_ACTIVE > 15)
    RI_RGB(15),
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
