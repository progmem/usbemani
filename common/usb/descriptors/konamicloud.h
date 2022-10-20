#pragma once

#define _KC_QUOTE(x)          #x
#define _KC(x)                _KC_QUOTE(x)
#define _KC_INCLUDE(x, y)     _KC(usb/descriptors/konamicloud.x.y)

#define USB_STRING_VENDOR_KONAMI_CLOUD "Konami Amusement"

#if defined(CONTROLLER_TYPE)
#include _KC_INCLUDE(CONTROLLER_TYPE, h)
#endif
