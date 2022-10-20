#include "usb/descriptors/konamicloud.iidx.h"

const USB_REPORT USB_ATTRIBUTES KonamiCloud_Report[] = {
  0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
  0x09, 0x04,        // Usage (Joystick)
  0xA1, 0x01,        // Collection (Application)
  0x09, 0x01,        //   Usage (Pointer)
  0xA1, 0x00,        //   Collection (Physical)
  0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
  0x09, 0x30,        //     Usage (X)
  0x09, 0x31,        //     Usage (Y)
  // NOTE: This technically should be 0x80 to cover the full range.
  0x15, 0x81,        //     Logical Minimum (-127)
  0x25, 0x7F,        //     Logical Maximum (127)
  0x75, 0x08,        //     Report Size (8)
  0x95, 0x02,        //     Report Count (2)
  0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x05, 0x09,        //     Usage Page (Button)
  0x19, 0x01,        //     Usage Minimum (0x01)
  0x29, 0x10,        //     Usage Maximum (0x10)
  0x15, 0x00,        //     Logical Minimum (0)
  0x25, 0x01,        //     Logical Maximum (1)
  0x75, 0x01,        //     Report Size (1)
  0x95, 0x10,        //     Report Count (16)
  0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x75, 0x08,        //     Report Size (8)
  0x95, 0x01,        //     Report Count (1)
  0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0xC0,              //   End Collection
  // NOTE: This device does not normally provide an output endpoint.
#include "usb/descriptors/output.c"
  0xC0,              // End Collection
};

#if (BUTTONS_ACTIVE > 9)
#include _KC_INCLUDE(CONTROLLER_TYPE, premium_model.c)
#else
#include _KC_INCLUDE(CONTROLLER_TYPE, entry_model.c)
#endif

//  Default behavior:
//  * Buttons: Buttons 1-7 directly mapped, 1 skip, E1-E4
//  * Encoder: 0, directly mapped
WEAK void CALLBACK_OnKonamiCloudInputRequest(USB_InputReport_KonamiCloud_t *input) {
  const uint16_t buttons = Button_GetAll();
  input->buttons  = (buttons & 0x007F);
  input->buttons |= (buttons & 0x0780) << 1;

  input->turntable = Encoder_LogicalPercent(0) ^ 0xFF;
}
