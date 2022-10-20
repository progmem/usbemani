#pragma once

/* Non-USB Related Configuration Tokens: */
//		#define DISABLE_TERMINAL_CODES

/* USB Class Driver Related Tokens: */
//		#define HID_HOST_BOOT_PROTOCOL_ONLY
//		#define HID_STATETABLE_STACK_DEPTH       {Insert Value Here}
//		#define HID_USAGE_STACK_DEPTH            {Insert Value Here}
//		#define HID_MAX_COLLECTIONS              {Insert Value Here}
//		#define HID_MAX_REPORTITEMS              {Insert Value Here}
//		#define HID_MAX_REPORT_IDS               {Insert Value Here}
//		#define NO_CLASS_DRIVER_AUTOFLUSH

/* General USB Driver Related Tokens: */
//		#define ORDERED_EP_CONFIG
#define USE_STATIC_OPTIONS (USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)
#define USB_DEVICE_ONLY
//		#define USB_HOST_ONLY
//		#define USB_STREAM_TIMEOUT_MS            {Insert Value Here}
//		#define NO_LIMITED_CONTROLLER_CONNECT
//		#define NO_SOF_EVENTS

/* USB Device Mode Driver Related Tokens: */
//		#define USE_RAM_DESCRIPTORS
#define USE_FLASH_DESCRIPTORS
//		#define USE_EEPROM_DESCRIPTORS
//		#define NO_INTERNAL_SERIAL
#define FIXED_CONTROL_ENDPOINT_SIZE      8
//		#define DEVICE_STATE_AS_GPIOR            {Insert Value Here}
#define FIXED_NUM_CONFIGURATIONS         1
//		#define CONTROL_ONLY_DEVICE
//		#define INTERRUPT_CONTROL_ENDPOINT
//		#define NO_DEVICE_REMOTE_WAKEUP
//		#define NO_DEVICE_SELF_POWER
