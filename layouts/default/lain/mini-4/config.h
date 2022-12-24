#pragma once

/*** Buttons ***/
#define BUTTON_CHANNELS 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

/*** Encoders ***/
#define ENCODER_CHANNELS_REVERSED
#define ENCODER_CHANNELS                0
#define ENCODER_FREQUENCY               16000
#define ENCODER_SAMPLES_UNTIL_VALID     255
#define ENCODER_DIRECTION_THRESHOLD     2
#define ENCODER_DIRECTION_HOLD_TIMEOUT  200

/*** RGB ***/
#define RGB_CHANNELS          0
#define RGB_FRAMERATE_TARGET  120

/*** USB ***/
#define USB_BUTTONS_ACTIVE      13
#define USB_ENCODER_AXES_ACTIVE 1
#define USB_ENCODER_AXES        USB_Axis_X
#define USB_GENERAL_AXES_ACTIVE 1
#define USB_GENERAL_AXES        USB_Axis_Y
#define USB_RGB_ACTIVE          12

/*** Button Combinations ***/
#define BUTTON_COMBO_ARCH_RESET     0, 1
#define BUTTON_COMBO_KONAMI_CLOUD   7, 8

/*** Quirks ***/
#define QUIRK_IIDX_LR2_BUTTON_COMBO 1

/*** Additional Includes ***/
#include "usb_labels.h"
