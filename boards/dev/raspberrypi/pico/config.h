#pragma once
// The Raspberry Pi Pico is a general development board.
// The following describes the available capabilities of the Pico development board in a way that makes it easy to use in controller configurations.

// Development boards receive a special marker to separate them from "production" boards.
// This is done since development boards have overlap across nearly every device.
// For example, channel "0" for any device (buttons, encoders, etc.) is pin 0.
// This overlap makes it harder for dev boards to work with layouts versus production boards.
#define BOARD_DEVELOPMENT

#define ONBOARD_LED 25

// This description is set up in a way to align Pico "GP" numbers with channels numbers.
// Certain channels will not be available because of this alignment. These will be marked with "PIN_NC"
#define BUTTON_DRIVER direct
#define BUTTONS_AVAILABLE 29
#define BUTTON_PINS \
   0,  1,  2,  3,  4,  5,  6,  7, \
   8,  9, 10, 11, 12, 13, 14, 15, \
  16, 17, 18, 19, 20, 21, 22, \
  PIN_NC, PIN_NC, PIN_NC, \
  26, 27, 28

// The channel number of the encoder indicates the Pico pin number + the pin after
// e.g. Encoder channel 5 uses Pico pins 5 and 6
// Channels 22-25 and 28 are not valid since they contain a non-valid pin number.
#define ENCODER_DRIVER direct
#define ENCODERS_AVAILABLE 29
#define ENCODER_PINS \
  [ 0] = {0,1}, \
  [ 1] = {1,2}, \
  [ 2] = {2,3}, \
  [ 3] = {3,4}, \
  [ 4] = {4,5}, \
  [ 5] = {5,6}, \
  [ 6] = {6,7}, \
  [ 7] = {7,8}, \
  [ 8] = {8,9}, \
  [ 9] = {9,10}, \
  [10] = {10,11}, \
  [11] = {11,12}, \
  [12] = {12,13}, \
  [13] = {13,14}, \
  [14] = {14,15}, \
  [15] = {15,16}, \
  [16] = {16,17}, \
  [17] = {17,18}, \
  [18] = {18,19}, \
  [19] = {19,20}, \
  [20] = {20,21}, \
  [21] = {21,22}, \
  [22] = {PIN_NC,PIN_NC}, \
  [23] = {PIN_NC,PIN_NC}, \
  [24] = {PIN_NC,PIN_NC}, \
  [25] = {PIN_NC,PIN_NC}, \
  [26] = {26,27}, \
  [27] = {27,28}, \
  [28] = {PIN_NC,PIN_NC}

// The Pico only has 3 analog pins: 26, 27, and 28.
// While "29" channels are available, to keep the pin mapping true, only 26-28 are usable.
#define ANALOG_DRIVER direct
#define ANALOG_CHANNELS_AVAILABLE 29
#define ANALOG_PINS \
  PIN_NC, PIN_NC, PIN_NC, PIN_NC, PIN_NC, PIN_NC, PIN_NC, PIN_NC, \
  PIN_NC, PIN_NC, PIN_NC, PIN_NC, PIN_NC, PIN_NC, PIN_NC, PIN_NC, \
  PIN_NC, PIN_NC, PIN_NC, PIN_NC, PIN_NC, PIN_NC, PIN_NC, PIN_NC, \
  PIN_NC, PIN_NC, 26, 27, 28

#define LIGHT_DRIVER direct
#define LIGHTS_AVAILABLE 29
#define LIGHT_PINS \
   0,  1,  2,  3,  4,  5,  6,  7, \
   8,  9, 10, 11, 12, 13, 14, 15, \
  16, 17, 18, 19, 20, 21, 22, \
  PIN_NC, PIN_NC, PIN_NC, \
  26, 27, 28

// The PIO RGB driver is enabled by default.
// This will be enabled on one of the two PIOs available, pio0.
// Up to four RGB channels are available on any four pins.
#define RGB_DRIVER pio
#define RGB_CHANNELS_AVAILABLE 29
#define RGB_PIO pio0
#define RGB_PINS \
   0,  1,  2,  3,  4,  5,  6,  7, \
   8,  9, 10, 11, 12, 13, 14, 15, \
  16, 17, 18, 19, 20, 21, 22, \
  PIN_NC, PIN_NC, PIN_NC, \
  26, 27, 28

// The PIO PSX driver is opt-in, and requires PSX_ACTIVE to be defined to enable it.
// This uses the remaining PIO, pio1.
#define PSX_DRIVER pio
#define PSX_PIO pio1
// The PIO driver requires no additional parts and has a couple caveats:
// * Three of the pins, DAT (MISO), ATT (SS), and ACK, can be any pin.
// * CMD will be the pin specified on PSX_CMD_CLK_PINBASE.
// * CLK will be the next pin after CLK (PSX_CMD_CLK_PINBASE + 1).
// If you wish to enable PSX support, copy and uncomment the following:
// #define PSX_ACTIVE
// #define PSX_CMD_CLK_PINBASE  4 // for CMD, pin 5 will be CLK
// #define PSX_ATT_PIN          3
// #define PSX_DAT_PIN          2
// #define PSX_ACK_PIN          1

/*** Chain Inclusion ***/
// This is what tells the compiler to include the controller configuration.
#include_next "config.h"