#pragma once

#define USB_ATTRIBUTES                  PROGMEM
#define USB_REPORT                      USB_Descriptor_HIDReport_Datatype_t
#define USB_DEVICE                      USB_StdDescriptor_Device_t
#define USB_CONFIG_HEADER               USB_StdDescriptor_Configuration_Header_t
#define USB_INTERFACE                   USB_StdDescriptor_Interface_t
#define USB_HID_DESCRIPTOR              USB_HID_StdDescriptor_HID_t
#define USB_ENDPOINT                    USB_StdDescriptor_Endpoint_t
#define USB_STRING                      USB_StdDescriptor_String_t

#define USB_DEVICE_TYPE                 DTYPE_Device
#define USB_DEVICE_MAX_PACKET_SIZE      FIXED_CONTROL_ENDPOINT_SIZE

#define USB_CONFIG_HEADER_TYPE          DTYPE_Configuration
#define USB_CONFIG_HEADER_ATTRS         USB_CONFIG_ATTR_RESERVED
#define USB_CONFIG_HEADER_MAX_POWER     USB_CONFIG_POWER_MA(500)

#define USB_INTERFACE_TYPE              DTYPE_Interface
#define USB_INTERFACE_CLASS             HID_CSCP_HIDClass

#define USB_HID_DESCRIPTOR_TYPE         HID_DTYPE_HID
#define USB_HID_DESCRIPTOR_REPORT_TYPE  HID_DTYPE_Report

#define USB_ENDPOINT_TYPE               DTYPE_Endpoint
#define USB_ENDPOINT_SIZE               8

#define USB_ENDPOINT_ADDR_IN            HID_EPADDR_IN
#define USB_ENDPOINT_ATTRS_IN           EP_TYPE_INTERRUPT

#define USB_ENDPOINT_ADDR_OUT           HID_EPADDR_OUT
#define USB_ENDPOINT_ATTRS_OUT          EP_TYPE_INTERRUPT

#define USB_STRING_TYPE                 DTYPE_String
#define USB_STRING_QUALIFIER            u""