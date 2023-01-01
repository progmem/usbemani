#pragma once
// Mickey's DJDao FPS differs in a couple of ways:
// A) Only 8 lights are active (Select isn't in use)
// B) RGB has been added

/*** Buttons ***/
#define BUTTON_CHANNELS 0, 1, 2, 3, 4, 5, 6, 7, 8

/*** Lights ***/
// Override the number of available lights
#undef  LIGHTS_ACTIVE
#define LIGHTS_ACTIVE   8
#define LIGHT_CHANNELS  0, 1, 2, 3, 4, 5, 6, 7

/*** Encoders ***/
#define ENCODER_CHANNELS_REVERSED
#define ENCODER_CHANNELS                16 // +17
#define ENCODER_SAMPLES_UNTIL_VALID     64
#define ENCODER_DIRECTION_HOLD_TIMEOUT  80

/*** RGB ***/
// Enable RGB
#define RGB_CHANNELS_ACTIVE   1
#define RGB_CHANNELS          0
#define RGB_LED_TYPE          WS2812
#define RGB_LEDS_PER_CHANNEL  32
#define RGB_FRAMERATE_TARGET  60

/*** USB ***/
#define USB_BUTTONS_ACTIVE      11
#define USB_ENCODER_AXES_ACTIVE 1
#define USB_ENCODER_AXES        USB_Axis_X
#define USB_GENERAL_AXES_ACTIVE 1
#define USB_GENERAL_AXES        USB_Axis_Y
#define USB_LIGHTS_ACTIVE       8
#define USB_RGB_ACTIVE          1

/*** Button Combinations ***/
#define BUTTON_COMBO_ARCH_RESET     0, 1
#define BUTTON_COMBO_KONAMI_CLOUD   7, 8

/*** Quirks ***/
#define QUIRK_IIDX_LR2_BUTTON_COMBO 1
