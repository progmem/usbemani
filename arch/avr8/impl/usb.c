#include "usb.h"
#include "usb/descriptors.c"

void _impl_hid_init(void) {
  USB_Init();
  GlobalInterruptEnable();
}

// LUFA event handler for USB_Connect events.
// void EVENT_USB_Device_Connect(void) { }

// LUFA event handler for USB_Disconnect events.
// void EVENT_USB_Device_Disconnect(void) { }

// LUFA event handler for USB_ConfigurationChanged events. Configures endpoints.
void EVENT_USB_Device_ConfigurationChanged(void) {
  Endpoint_ConfigureEndpoint(USB_ENDPOINT_ADDR_IN,  EP_TYPE_INTERRUPT, HID_EPSIZE, 1);
  Endpoint_ConfigureEndpoint(USB_ENDPOINT_ADDR_OUT, EP_TYPE_INTERRUPT, HID_EPSIZE, 1);
}

void EVENT_USB_Device_ControlRequest(void) {
  switch (USB_ControlRequest.bRequest) {
  case HID_REQ_GetReport:
    if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE)) {

#if defined(KONAMI_CLOUD_ENABLED)
      if (_usb_status.mode == USB_DeviceType_KonamiCloud) {
        USB_InputReport_KonamiCloud_t input;
        CALLBACK_OnKonamiCloudInputRequest(&input);
        Endpoint_ClearSETUP();
        Endpoint_Write_Control_Stream_LE(&input, sizeof(input));
      } else {
#else
      {
#endif
        USB_InputReport_USBemani_t input;
        CALLBACK_OnUSBemaniInputRequest(&input);
        Endpoint_ClearSETUP();
        Endpoint_Write_Control_Stream_LE(&input, sizeof(input));
      }

      Endpoint_ClearOUT();
    }
    break;
  case HID_REQ_SetReport:
    if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE)) {
      USB_OutputReport_t output;
      Endpoint_ClearSETUP();
      Endpoint_Read_Control_Stream_LE(&output, sizeof(output));
      Endpoint_ClearIN();
      CALLBACK_OnUSBOutputAvailable(&output);
    }
    break;
  }
}
// Standard task for building input/output reports.
void _impl_hid_dataHandlerTask(void) {
  // Device must be connected and configured before we can continue
  if (USB_DeviceState != DEVICE_STATE_Configured) return;

  Endpoint_SelectEndpoint(USB_ENDPOINT_ADDR_OUT);
  if (Endpoint_IsOUTReceived()) {
    if (Endpoint_IsReadWriteAllowed()) {
      USB_OutputReport_t output;
      Endpoint_Read_Stream_LE(&output, sizeof(output), NULL);
      CALLBACK_OnUSBOutputAvailable(&output);
    }
    Endpoint_ClearOUT();
  }

  Endpoint_SelectEndpoint(USB_ENDPOINT_ADDR_IN);
  if (Endpoint_IsINReady()) {

#if defined(KONAMI_CLOUD_ENABLED)
    if (_usb_status.mode == USB_DeviceType_KonamiCloud) {
      USB_InputReport_KonamiCloud_t input;
      CALLBACK_OnKonamiCloudInputRequest(&input);
      Endpoint_Write_Stream_LE(&input, sizeof(input), NULL);
    } else {
#else
    {
#endif
      USB_InputReport_USBemani_t input;
      CALLBACK_OnUSBemaniInputRequest(&input);
      Endpoint_Write_Stream_LE(&input, sizeof(input), NULL);
    }

    Endpoint_ClearIN();
  }
}

uint16_t CALLBACK_USB_GetDescriptor(
  const uint16_t wValue,
  const uint16_t wIndex,
  const void** const DescriptorAddress
) {
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	const void* Address = NULL;
	uint16_t    Size    = NO_DESCRIPTOR;

  uint8_t StringType = 0, StringIndex = 0;

	switch (DescriptorType) {
	case DTYPE_Device:
		Address = _usb_status.device_descriptor;
		Size    = sizeof(USB_Descriptor_Device_t);
		break;
	case DTYPE_Configuration:
		Address = _usb_status.config_descriptor;
		Size    = sizeof(USB_Descriptor_Configuration_t);
		break;
	case HID_DTYPE_HID:
		Address = _usb_status.report_descriptor;
		Size    = sizeof(USB_HID_Descriptor_HID_t);
		break;
	case HID_DTYPE_Report:
    if (_usb_status.mode == USB_DeviceType_KonamiCloud) {
  		Address = &KonamiCloud_Report;
	  	Size    = sizeof(KonamiCloud_Report);
	  } else {
  		Address = &USBemani_Report;
	  	Size    = sizeof(USBemani_Report);
	  }
		break;
	case DTYPE_String:
	  StringType = DescriptorNumber & StringTypeMask;
    if (StringType & StringType_LightsRGB) {
      StringType   = StringType_LightsRGB;
      StringIndex  = DescriptorNumber & StringIndexMask_RGB;
    } else {
      StringIndex  = DescriptorNumber & StringIndexMask;
    }

	  switch (StringType) {
	  case StringType_USBStandard:
	    Address = (const void *)pgm_read_word(&(String_USB[StringIndex]));
      Size    = pgm_read_byte(Address);
      break;
	  case StringType_Button:
	    Address = (const void *)pgm_read_word(&(String_Button[StringIndex]));
      Size    = pgm_read_byte(Address);
      break;
	  case StringType_Encoder:
	    Address = (const void *)pgm_read_word(&(String_Encoder[StringIndex]));
      Size    = pgm_read_byte(Address);
      break;
	  case StringType_Axis:
	    Address = (const void *)pgm_read_word(&(String_Axis[StringIndex]));
      Size    = pgm_read_byte(Address);
      break;
	  case StringType_LightsBasic:
	    Address = (const void *)pgm_read_word(&(String_Light[StringIndex]));
      Size    = pgm_read_byte(Address);
      break;
	  case StringType_LightsRGB:
	    Address = (const void *)pgm_read_word(&(String_RGB[StringIndex]));
      Size    = pgm_read_byte(Address);
      break;
    }
	  break;
	}

	*DescriptorAddress = Address;
	return Size;
}
