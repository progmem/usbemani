#pragma once
// The Arduino Pro Micro is a general development board.
// The following converts the Pro Micro Arduino pins to the AVR pins expected by USBemani.

// Left edge, from top to bottom:
#define PRO_MICRO_PIN_1     PIN_D3
#define PRO_MICRO_PIN_0     PIN_D2
// GND
// GND
#define PRO_MICRO_PIN_2     PIN_D1
#define PRO_MICRO_PIN_3     PIN_D0
#define PRO_MICRO_PIN_4     PIN_D4
#define PRO_MICRO_PIN_5     PIN_C6
#define PRO_MICRO_PIN_6     PIN_D7
#define PRO_MICRO_PIN_7     PIN_E6
#define PRO_MICRO_PIN_8     PIN_B4
#define PRO_MICRO_PIN_9     PIN_B5

// Right edge, from top to bottom:
// RAW
// GND
// RST
// VCC
#define PRO_MICRO_PIN_21    PIN_F4
#define PRO_MICRO_PIN_20    PIN_F5
#define PRO_MICRO_PIN_19    PIN_F6
#define PRO_MICRO_PIN_18    PIN_F7
#define PRO_MICRO_PIN_15    PIN_B1  // Also known as PIN_SPI_SCLK
#define PRO_MICRO_PIN_14    PIN_B3  // Also known as PIN_SPI_MISO
#define PRO_MICRO_PIN_16    PIN_B2  // Also known as PIN_SPI_MOSI
#define PRO_MICRO_PIN_10    PIN_B6

// Analog pins, which require the use of special "APIN" definitions
// These should _only_ be used for the analog driver!
#define PRO_MICRO_PIN_A0    APIN_F7
#define PRO_MICRO_PIN_A1    APIN_F6
#define PRO_MICRO_PIN_A2    APIN_F5
#define PRO_MICRO_PIN_A3    APIN_F4
#define PRO_MICRO_PIN_A6    APIN_D4
#define PRO_MICRO_PIN_A7    APIN_D7
#define PRO_MICRO_PIN_A8    APIN_B4
#define PRO_MICRO_PIN_A9    APIN_B5
#define PRO_MICRO_PIN_A10   APIN_B6

// The two LEDs, from left to right:
#define PRO_MICRO_PIN_RXLED PIN_B0
#define PRO_MICRO_PIN_TXLED PIN_D5

// Additional aliases:
#define PRO_MICRO_PIN_TXO   PRO_MICRO_PIN_1
#define PRO_MICRO_PIN_RXI   PRO_MICRO_PIN_0

