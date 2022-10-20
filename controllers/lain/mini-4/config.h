#pragma once

/*** Controller Type ***/
#define CONTROLLER_TYPE iidx

/*** Buttons ***/
// The number of active button connectors in use.
#define BUTTONS_ACTIVE    11
// The channels in use, numbered based on the board.
#define BUTTON_CHANNELS   0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

/*** Encoders ***/
// If needed, the direction of all encoders can be reversed.
#define ENCODER_CHANNELS_REVERSED
// The number of active encoder connections in use.
#define ENCODERS_ACTIVE   1
// The channels in use, numbered based on the board.
#define ENCODER_CHANNELS  0
// The PPR of the encoders in use. For optical tooth wheels, this should be the number of teeth.
#define ENCODER_PPR       36
// The polling frequency for encoders, in hertz. Higher number means more frequent polling.
// Slower boards will update encoders in a round-robin fashion (frequency / encoders = polling rate)
#define ENCODER_FREQUENCY 16000
// The number of polling samples before an encoder input is considered valid.
// A higher number (up to 255) will result in some input lag in exchange for data validity.
#define ENCODER_SAMPLES_UNTIL_VALID 255
// The number of quarter steps before triggering a directional input.
#define ENCODER_DIRECTION_THRESHOLD 2
// How long a direction should hold, in milliseconds, before timing out.
#define ENCODER_DIRECTION_HOLD_TIMEOUT 200

/*** RGB ***/
// USER DEFINED: TT size
#define RGB_LEDS_TURNTABLE 12
#define RGB_LEDS_PER_KEY 4
// How many RGB channels are active
#define RGB_CHANNELS_ACTIVE   1
#define RGB_CHANNELS          0
// Which RGB LEDs are in use
#define RGB_LED_TYPE          WS2812
// How many RGB LEDs per channel, comma-separated
// Keys, E1-E4, Turntable
#define RGB_LEDS_PER_CHANNEL  (7 * RGB_LEDS_PER_KEY) + (4 * 1) + (RGB_LEDS_TURNTABLE)
// Framerate to target
#define RGB_FRAMERATE_TARGET  120

/*** USB ***/
// The number of buttons to expose (11 buttons + 2 virtual for LR2)
#define USB_BUTTONS_ACTIVE      13
// The number of axes to expose for encodes. USBemani will handle axis maximums automatically.
#define USB_ENCODER_AXES_ACTIVE 1
// Which USB axes to expose
#define USB_ENCODER_AXES        USB_Axis_X
// The number of axes to expose for general purpose
#define USB_GENERAL_AXES_ACTIVE 1
// Which USB axes to expose
#define USB_GENERAL_AXES        USB_Axis_Y

// The number of RGB channels to expose (7 keys + 4 buttons + TT)
#define USB_RGB_ACTIVE          12


/*** Button Combinations ***/
// The buttons that must be held to reset to the bootloader.
#define BUTTON_COMBO_ARCH_RESET   0, 1
// The buttons that must be held to boot with Konami Cloud descriptors
#define BUTTON_COMBO_KONAMI_CLOUD 7, 8

// Hold key 2 to enable "LR2 mode"
#define QUIRK_IIDX_LR2_BUTTON_COMBO 1


/*** Additional Includes ***/
// USB Labels
#include "labels.h"

/*** Chain Inclusion ***/
#include_next "config.h"