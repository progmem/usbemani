#pragma once
// The Raspberry Pi Pico is a general development board.
// The following provides a sample controller configuration for the Pico dev board in a IIDX controller.

/*** Controller Type ***/
// Our example is a IIDX controller. Including this line tells USBemani how to setup certain properties to best support IIDX.
#define CONTROLLER_TYPE iidx

/*** Buttons ***/
// The number of active buttons to use.
// For our example (a IIDX controller), we'll use 11 buttons.
#define BUTTONS_ACTIVE 11
// The channels in use.
// For our example, we'll use pins 0-6 as our keys, and pins 7-10 for our E1-E4 buttons.
// USBemani will automatically map these in the order provided, so pin 0 becomes our USB "Button 1", and pin 10 becomes "Button 11".
#define BUTTON_CHANNELS 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

/*** Encoders ***/
// If needed, the direction of all encoders can be reversed. We won't do this for our example, but it can be enabled with the following:
// #define ENCODER_CHANNELS_REVERSED
// The number of active encoders in use.
#define ENCODERS_ACTIVE         1
// The encoder channel we wish to use. Encoders use two pins per encoder.
// Our board provides encoder channels using a "base pin" number for the first channel, with the next pin after for the second channel.
// For our example, we'll use pin 14 as the base pin, which will use pins 14 and 15
#define ENCODER_CHANNELS        14
// The PPR of the encoders in use.
// For optical tooth wheels, count the number of teeth on the wheel.
// For pre-packaged encoders, use the PPR as stated on the encoder or in the datasheet.
// USBemani will use this information to automatically scale the encoder to meet what the game expects for a full rotation of the encoder.
// Our example will use a generic 360PPR encoder.
#define ENCODER_PPR             360
// The polling frequency for encoders, in hertz. A higher number means more frequent polling.
// Our example uses what is considered a "high PPR" encoder. These encoders require more frequent polling to avoid error.
// For our example controller, we'll poll our encoder at 32kHz.
#define ENCODER_FREQUENCY       32000
// The number of polling samples before an encoder input is considered valid.
// A higher number (up to 255) can better correct for error, at the expense of a little bit of input lag.
// A lower number is more responsive, but can be prone to error depending on the encoder in use.
// For our example, we'll use the highest value, 255.
// This will result in 255/32000 seconds of input lag at the latest (~8ms).
#define ENCODER_SAMPLES_UNTIL_VALID     255
// The number of "steps' before triggering a directional input.
// For use on the PSX, PS2, or software like LR2, this defines how "far" the encoder has to rotate before triggering a direction.
// This number is expressed in "quarter steps", which is our encoder PPR * 4 (in our example, we have 1440 quarter steps per rotation).
// For our example, we'll trigger a directional input after 20 successive quarter steps in either direction. This means a 1/72 rotation will trigger a directional pulse.
#define ENCODER_DIRECTION_THRESHOLD     20
// How long a direction should hold, in milliseconds, before timing out.
#define ENCODER_DIRECTION_HOLD_TIMEOUT  200

/*** RGB ***/
// How many RGB channels are active
#define RGB_CHANNELS_ACTIVE     1
// Which RGB channel to use
#define RGB_CHANNELS            16
// Which RGB LEDs are in use
// For this example, we'll use WS2812 LEDs (e.g. NeoPixels)
#define RGB_LED_TYPE            WS2812
// How fast we should draw our RGB LEDs (our target framerate)
// USBemani provides two parts to an RGB LED draw:
// * An "effect update", which updates at our target framerate
// * A "draw", which attempts to occur at our target framerate
// Note that while a draw may can miss its window depending on the number of LEDs, the effect update will still occur at the framerate.
// For our example, we'll target 120FPS
#define RGB_FRAMERATE_TARGET    120
// How many RGB LEDs per channel
// Since our board only has one channel, we only need to provide one number
// For our example, we'll say we have a single RGB LED per key/button, and a ring of 24 LEDs for the turntable
// Custom user definitions can be added here for use in our code.
#define RGB_LEDS_PER_TURNTABLE  24
#define RGB_LEDS_PER_KEY        1
// We can use these numbers to calculate our final number of RGB LEDs per channel
// For our example, our buttons will be wired up first, in order, followed by our turntable:
// Button 1 -> 2 -> 3 -> ... -> 9 -> 10 -> 11 -> Turntable
#define RGB_LEDS_PER_CHANNEL    (BUTTONS_ACTIVE * RGB_LEDS_PER_KEY) + (RGB_LEDS_PER_TURNTABLE)

/*** PSX ***/
// Because the Pi Pico has enough pins available, our example will include PSX support.
#define PSX_ACTIVE
// As noted in the board's config files, there are a couple caveats:
// * Three of the pins, DAT (MISO), ATT (SS), and ACK, can be any pin.
// * CMD will be the pin specified on PSX_CMD_CLK_PINBASE.
// * CLK will be the next pin after CLK (PSX_CMD_CLK_PINBASE + 1).
// We'll use the following pins:
#define PSX_CMD_CLK_PINBASE  18 // for CMD, pin 19 will be CLK
#define PSX_ATT_PIN          20
#define PSX_DAT_PIN          21
#define PSX_ACK_PIN          22

/*** USB ***/
// The number of buttons to expose (11 buttons, plus 2 virtual for LR2)
#define USB_BUTTONS_ACTIVE      13
// The number of axes to expose for encoders
#define USB_ENCODER_AXES_ACTIVE 1
// Which USB axes to expose for encoders
#define USB_ENCODERS_AXES       USB_Axis_X
// The number of axes to expose for general purpose
// IIDX doesn't use this, but it's provided to correct issues with certain test utilities
#define USB_GENERAL_AXES_ACTIVE 1
#define USB_GENERAL_AXES        USB_Axis_Y
// The number of traditional light channels to expose
// This example doesn't use traditional lights, but they can be enabled with the following:
// #define USB_LIGHTS_ACTIVE    12
// The number of RGB channels to expose
// For this example, we'll expose 7 keys, 4 buttons, and the turntable, for a total of 12.
#define USB_RGB_ACTIVE          12

/*** Chain Inclusion ***/
// This is what tells the compiler to include the user configuration.
#include_next "config.h"