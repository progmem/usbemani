#pragma once
#include <stdint.h>

#include "config.h"
#include "usb/descriptors/usbemani.h"
#if defined(KONAMI_CLOUD_ENABLED)
#include "usb/descriptors/konamicloud.h"
#endif
#include "usb/descriptors/output.h"
#include "psx/defs.h"

#define WEAK __attribute__((weak))

/*** System-Level ***/
// When all hardware is initialized and ready for use
WEAK void CALLBACK_OnHardwareReady(void);
// When user tasks are able to be performed
WEAK void CALLBACK_UserTask(void);


/*** USB ***/
/* Input */
// When a standard USBemani input packet is requested
WEAK void CALLBACK_OnUSBemaniInputRequest(USB_InputReport_USBemani_t *input);
// When a Konami Cloud input packet is requested
WEAK void CALLBACK_OnKonamiCloudInputRequest(USB_InputReport_KonamiCloud_t *input);
// When a USB output packet is ready for processing
WEAK void CALLBACK_OnUSBOutputAvailable(USB_OutputReport_t *output);

/*** Lighting ***/
// When USB lighting is active, run this code to perform draws.
WEAK void CALLBACK_OnLightingDrawUSB(USB_OutputReport_t *output);
// When fallback lighting is active, run this code to perform draws.
WEAK void CALLBACK_OnLightingDrawFallback(void);

/*** RGB ***/
// When variables should be updated for the next RGB frame
WEAK void CALLBACK_RGBCalculateNextFrame(void);
// When USB lighting is active, run this code to perform draws.
WEAK void CALLBACK_OnRGBDrawUSB(USB_OutputReport_t *output);
// When fallback lighting is active, run this code to perform draws.
WEAK void CALLBACK_OnRGBDrawFallback(void);

void CALLBACK_OnPlaystationInputRequest(PSX_Input_t *input);

/*** Timer ***/
// When our timer task can be run
void CALLBACK_OnTimer(void);
