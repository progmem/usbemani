#pragma once

/*** Controller Type ***/
#define CONTROLLER_TYPE sdvx

/*** Buttons ***/
// The number of active button connectors in use.
#define BUTTONS_ACTIVE    8
// The channels in use, numbered based on the board.
#define BUTTON_CHANNELS   0, 1, 2, 3, 4, 5, 6, 7

/*** Encoders ***/
#define ENCODER_QUARTER_STEPPING
#define ENCODER_CHANNELS_REVERSED
// The number of active encoder connections in use.
#define ENCODERS_ACTIVE   2
// The channels in use, numbered based on the board.
#define ENCODER_CHANNELS  0, 1
// The PPR of the encoders in use. For optical tooth wheels, this should be the number of teeth.
#define ENCODER_PPR       24
// The polling frequency for encoders, in hertz. Higher number means more frequent polling.
// Slower boards will update encoders in a round-robin fashion (frequency / encoders = polling rate)
#define ENCODER_FREQUENCY 16000
// How long a direction should hold, in milliseconds, before timing out.
#define ENCODER_DIRECTION_HOLD_TIMEOUT 1000

/*** RGB ***/
// How many RGB channels are active
#define RGB_CHANNELS_ACTIVE   1
#define RGB_CHANNELS          0
// Which RGB LEDs are in use
#define RGB_LED_TYPE          WS2812
// How many RGB LEDs per channel, comma-separated
// Buttons/Labels, Bottom-Right, VOL-R, Top-Right, Top-Left, VOL-L, Bottom-Left, Logo
#define RGB_LEDS_PER_CHANNEL  (14 + 4 + 1 + 3 + 3 + 1 + 4 + 2)
// Framerate to target
#define RGB_FRAMERATE_TARGET  120

/*** USB ***/
// The number of buttons to expose
#define USB_BUTTONS_ACTIVE      8
// The number of axes to expose for encodes. USBemani will handle axis maximums automatically.
#define USB_ENCODER_AXES_ACTIVE 2
// Which USB axes to expose
#define USB_ENCODER_AXES        USB_Axis_X, USB_Axis_Y
// The number of traditional lighting channels to expose
#define USB_LIGHTS_ACTIVE       7
// The number of RGB channels to expose
#define USB_RGB_ACTIVE          1

/*** Button Combinations ***/
// The buttons that must be held to reset to the bootloader.
#define BUTTON_COMBO_ARCH_RESET   0, 1  // BT-A, BT-B
#define BUTTON_COMBO_KONAMI_CLOUD 6     // Start

/*** Chain Inclusion ***/
#include_next "config.h"