#pragma once
// The following provides a sample user layout for building a IIDX "premium model" controller with a Raspberry Pi Pico.
// Layouts act as a combination of a "wiring guide" and a user configuration area.

// This example uses a development board. Development boards have overlap across pins between multiple devices.
// Because of this, layouts designed for development boards and layouts designed for "production" boards are not immediately interchangeable.
// For example, on a development board, channel "0" for any device is pin 0.
// However, on a production board, channel "0" is often on a different pin depending on the device.
// To note that our layout is intended for development board use, we'll flag the layout as a development board layout.
#define LAYOUT_DEVELOPMENT

// For reference, our default controller target (examples/iidx/premium-model) assumes the following:
// * 11 buttons
// * 11 lights
// * 1 encoder, at 360 PPR

/*** Buttons ***/
// The channels in use.
// For our example, we'll use pins 0-6 for our keys, and pins 7-10 for our E1-E4 buttons.
// USBemani will automatically map these in the order provided, so pin 0 becomes our USB "Button 1", and pin 10 becomes "Button 11".
#define BUTTON_CHANNELS 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

/*** Lights ***/
// The channels in use.
// For our example, we'll use pins 11-17 as our keys, and pins 17-21 for our E1-E4 buttons.
// USBemani will automatically map these in the order provided, so pin 11 becomes our USB "Light 1", and pin 21 becomes "Light 11".
#define LIGHT_CHANNELS 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21

/*** Encoders ***/
// If needed, the direction of all encoders can be reversed.
// This may be needed depending on how the encoders are wired to the board.
// We won't do this for our example, but it can be enabled with the following:
// #define ENCODER_CHANNELS_REVERSED
// The encoder channel we wish to use. Encoders use two pins per encoder.
// Our board provides encoder channels using a "base pin" number for the first channel, with the next pin after for the second channel.
// For our example, we'll use pin 26 as the base pin, which will use pins 26 and 27
#define ENCODER_CHANNELS  26
// The polling frequency for encoders, in hertz. A higher number means more frequent polling.
// Our example uses what is considered a "high PPR" encoder. These encoders require more frequent polling to avoid error.
// For our example, we'll poll our encoder at 32kHz.
#define ENCODER_FREQUENCY 32000
// The number of polling samples before an encoder input is considered valid.
// A higher number (up to 255) can better correct for error, at the expense of a little bit of input lag.
// A lower number is more responsive, but can be prone to error depending on the encoder in use.
// For our example, we'll use the highest value, 255.
// This will result in 255/32000 seconds of input lag at the worst-case (~8ms).
#define ENCODER_SAMPLES_UNTIL_VALID     255
// The number of "steps' before triggering a directional input.
// For use on the PSX, PS2, or software like LR2, this defines how "far" the encoder has to rotate before triggering a direction.
// This number is expressed in "quarter steps", which is our encoder PPR * 4 (in our example, we have 1440 quarter steps per rotation).
// For our example, we'll trigger a directional input after 20 successive quarter steps in either direction. This means a 1/72 rotation will trigger a directional pulse.
#define ENCODER_DIRECTION_THRESHOLD     20
// How long a direction should hold, in milliseconds, before timing out.
#define ENCODER_DIRECTION_HOLD_TIMEOUT  200

/*** USB ***/
// The number of buttons to expose.
// We have 11 buttons, and we'll add 2 additional "virtual" buttons for software like LR2.
#define USB_BUTTONS_ACTIVE      13
// The number of axes to expose for encoders.
// We only have one encoder, so we only need one axis.
#define USB_ENCODER_AXES_ACTIVE 1
// Which USB axes to expose for encoders
// We'll use the X axis, which mimics the Konami eAmusement Cloud descriptors.
#define USB_ENCODER_AXES        USB_Axis_Y
// The number of axes to expose for general purpose
// IIDX doesn't use this, but it's provided to correct issues with certain test utilities.
#define USB_GENERAL_AXES_ACTIVE 1
// Which USB axes to expose for general purpose
// We'll use the Y axis to correct issues with certain test utilities.
#define USB_GENERAL_AXES        USB_Axis_X
// The number of traditional light channels to expose
// We have 11 buttons with lights, so we'll expose 11 lights.
#define USB_LIGHTS_ACTIVE       11
// USB allows us to define labels for our bottons, axes, and lights.
// We'll include these labels from another file, which is shared across multiple examples.
#include "../../usb_labels.h"
