#include "usbemani.h"

TimerTick_t _timer;
HSV_Color_t _effect_global;

USB_LightingHelper_t USB_LightingHelper = {
  .active = 0,
};

int main(void) {
  // Initialize hardware
  Arch_Init();
  Analog_Init();
  Button_Init();
  Encoder_Init();
  Light_Init();
  PSX_Init();
  RGB_Init();
  Timer_Init();

  // Wait a brief moment for initialized components to stabilize before initializing anything else
  Arch_Stabilize();
  // Initialize quirks
  Quirks_Init();

  // Check if bootloader entry is requested
  Arch_BootloaderCheck();
  // Check if Konami Cloud descriptors are requested
  HID_KonamiCloudCheck();

  // Call user hook when hardware is ready
  if (CALLBACK_OnHardwareReady)
    CALLBACK_OnHardwareReady();

  // Initialize HID/USB stack
  HID_Init();

  for(;;) {
    HID_Task();
    PSX_Task();
    Analog_Task();

    // If an RGB frame tick has passed, call user hook to update values
    if (RGB_ReadyToCalculate()) {
      if (CALLBACK_RGBCalculateNextFrame) {
        CALLBACK_RGBCalculateNextFrame();
      }
    }

    // If the framebuffer is free to draw, call user hooks to perform draws
    if (RGB_ReadyToDraw()) {
      if (CALLBACK_OnRGBDrawUSB && USB_LightingHelper.last_output) {
        CALLBACK_OnRGBDrawUSB(USB_LightingHelper.last_output);
      } else if (CALLBACK_OnRGBDrawFallback) {
        CALLBACK_OnRGBDrawFallback();
      }
      RGB_Render();
    }

    // If it's time to update lights, call user hooks to perform draws
    if (Light_ReadyToDraw()) {
      if (CALLBACK_OnLightingDrawUSB && USB_LightingHelper.last_output) {
        CALLBACK_OnLightingDrawUSB(USB_LightingHelper.last_output);
      } else if (CALLBACK_OnLightingDrawFallback) {
        CALLBACK_OnLightingDrawFallback();
      }
      Light_Render();
    }

    // Call user-defined tasks at the end
    if (CALLBACK_UserTask) {
      CALLBACK_UserTask();
    }
  }
}

// 8kHz timer
void CALLBACK_OnTimer() {
  // Increment the tick timer
  Timer_Tick();
  // Update the current status of RGB frame draws
  RGB_UpdateStatus();
  // Update the current status of traditional lighting frame draws
  Light_UpdateStatus();

  // Tick down our enumerated lighting timer.
  if (USB_LightingHelper.active) {
    USB_LightingHelper.active--;
  } else if (USB_LightingHelper.last_output) {
    USB_LightingHelper.last_output = NULL;
  }
}
