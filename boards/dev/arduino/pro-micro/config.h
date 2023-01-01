#pragma once
// The Arduino Pro Micro is a general development board.
// The following describes the available capabilities of the Pro Micro development board in a way that makes it easy to use in controller configurations.

// Development boards receive a special marker to separate them from "production" boards.
// This is done since development boards have overlap across nearly every device.
// For example, channel "0" for any device (buttons, encoders, etc.) is pin 0.
// This overlap makes it harder for dev boards to work with layouts versus production boards.
#define BOARD_DEVELOPMENT

// This description is set up in a way to align Arduino pins numbers with the AVR pins.
// Certain channels will not be available because of this alignment. These will be marked with "PIN_NC"
// Our general development board example will use Arduino pin numbers.
// USBemani expects AVR pin numbers (the chip used on the Pro Micro), so an additional file has been included to map these pins.
#include "pin_mapping.h"

#define BUTTON_DRIVER direct
#define BUTTONS_AVAILABLE 22
// NOTE: RXI is Arduino pin 0, and TXO is pin 1
#define BUTTON_PINS \
  PRO_MICRO_PIN_RXI, \
  PRO_MICRO_PIN_TXO, \
  PRO_MICRO_PIN_2, \
  PRO_MICRO_PIN_3, \
  PRO_MICRO_PIN_4, \
  PRO_MICRO_PIN_5, \
  PRO_MICRO_PIN_6, \
  PRO_MICRO_PIN_7, \
  PRO_MICRO_PIN_8, \
  PRO_MICRO_PIN_9, \
  PRO_MICRO_PIN_10, \
  PIN_NC, \
  PIN_NC, \
  PIN_NC, \
  PRO_MICRO_PIN_14, \
  PRO_MICRO_PIN_15, \
  PRO_MICRO_PIN_16, \
  PIN_NC, \
  PRO_MICRO_PIN_18, \
  PRO_MICRO_PIN_19, \
  PRO_MICRO_PIN_20, \
  PRO_MICRO_PIN_21

// The channel number of the encoder indicates the Arduino pin number + the pin after
// e.g. Encoder channel 5 uses Arduino pins 5 and 6.
// Channels 10-13 and 16-17 are not valid since they contain a non-valid pin number.
#define ENCODER_DRIVER direct
#define ENCODERS_AVAILABLE 22
#define ENCODER_PINS \
  [ 0] = {PRO_MICRO_PIN_0,PRO_MICRO_PIN_1}, \
  [ 1] = {PRO_MICRO_PIN_1,PRO_MICRO_PIN_2}, \
  [ 2] = {PRO_MICRO_PIN_2,PRO_MICRO_PIN_3}, \
  [ 3] = {PRO_MICRO_PIN_3,PRO_MICRO_PIN_4}, \
  [ 4] = {PRO_MICRO_PIN_4,PRO_MICRO_PIN_5}, \
  [ 5] = {PRO_MICRO_PIN_5,PRO_MICRO_PIN_6}, \
  [ 6] = {PRO_MICRO_PIN_6,PRO_MICRO_PIN_7}, \
  [ 7] = {PRO_MICRO_PIN_7,PRO_MICRO_PIN_8}, \
  [ 8] = {PRO_MICRO_PIN_8,PRO_MICRO_PIN_9}, \
  [ 9] = {PRO_MICRO_PIN_9,PRO_MICRO_PIN_10}, \
  [10] = {PIN_NC,PIN_NC}, \
  [11] = {PIN_NC,PIN_NC}, \
  [12] = {PIN_NC,PIN_NC}, \
  [13] = {PIN_NC,PIN_NC}, \
  [14] = {PRO_MICRO_PIN_14,PRO_MICRO_PIN_15}, \
  [15] = {PRO_MICRO_PIN_15,PRO_MICRO_PIN_16}, \
  [16] = {PIN_NC,PIN_NC}, \
  [17] = {PIN_NC,PIN_NC}, \
  [18] = {PRO_MICRO_PIN_18,PRO_MICRO_PIN_19}, \
  [19] = {PRO_MICRO_PIN_19,PRO_MICRO_PIN_20}, \
  [20] = {PRO_MICRO_PIN_20,PRO_MICRO_PIN_21}, \
  [21] = {PIN_NC,PIN_NC}

#define LIGHT_DRIVER direct
#define LIGHTS_AVAILABLE 22
#define LIGHT_PINS \
  PRO_MICRO_PIN_RXI, \
  PRO_MICRO_PIN_TXO, \
  PRO_MICRO_PIN_2, \
  PRO_MICRO_PIN_3, \
  PRO_MICRO_PIN_4, \
  PRO_MICRO_PIN_5, \
  PRO_MICRO_PIN_6, \
  PRO_MICRO_PIN_7, \
  PRO_MICRO_PIN_8, \
  PRO_MICRO_PIN_9, \
  PRO_MICRO_PIN_10, \
  PIN_NC, \
  PIN_NC, \
  PIN_NC, \
  PRO_MICRO_PIN_14, \
  PRO_MICRO_PIN_15, \
  PRO_MICRO_PIN_16, \
  PIN_NC, \
  PRO_MICRO_PIN_18, \
  PRO_MICRO_PIN_19, \
  PRO_MICRO_PIN_20, \
  PRO_MICRO_PIN_21

// The MSPI RGB driver is enabled by default.
// This is supported on Arduino pin 1 (TXO on the Pro Micro, AVR pin D3), and requires two extra parts:
// * A current-limiting resistor (anything 300-1000 ohm should be fine)
// * An SN74HC14N or similar inverter to invert the signal.
// The driver also consumes pin D5 (TXLED) in the process.
#define RGB_DRIVER mspi
#define RGB_CHANNELS_AVAILABLE 1

// Analog channels are in order of their Arduino "A" number.
#define ANALOG_DRIVER direct
#define ANALOG_CHANNELS_AVAILABLE 11
#define ANALOG_PINS \
  PRO_MICRO_PIN_A0, \
  PRO_MICRO_PIN_A1, \
  PRO_MICRO_PIN_A2, \
  PRO_MICRO_PIN_A3, \
  PIN_NC, \
  PIN_NC, \
  PRO_MICRO_PIN_A6, \
  PRO_MICRO_PIN_A7, \
  PRO_MICRO_PIN_A8, \
  PRO_MICRO_PIN_A9, \
  PRO_MICRO_PIN_A10

// PSX is supported, but requires some care.
// This requires pins B0, B1, B2, and B3 (Arduino pins 14-16, plus the RXLED pin, which requires precision soldering and the removal of the resistor).
// This also requires a user-definable pin, PSX_ACK_PIN.
#define PSX_DRIVER spi
#define PSX_DAT_PIN PIN_SPI_MISO
#define PSX_CMD_PIN PIN_SPI_MOSI
#define PSX_CLK_PIN PIN_SPI_SCLK
#define PSX_ATT_PIN PIN_SPI_SS

/*** Chain Inclusion ***/
// This is what tells the compiler to include the controller configuration.
#include_next "config.h"