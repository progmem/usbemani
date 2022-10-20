#pragma once

#define ONBOARD_LED PIN_E6

#define BUTTON_DRIVER direct
#define BUTTONS_AVAILABLE 11
#define BUTTON_PINS \
  PIN_D0, PIN_D1, PIN_D2, PIN_D3, \
  PIN_D4, PIN_D5, PIN_D6, PIN_D7, \
  PIN_B4, PIN_B5, PIN_B6

#define ENCODER_DRIVER direct
#define ENCODERS_AVAILABLE 2
#define ENCODER_PINS [0] = {PIN_F0, PIN_F1}, [1] = {PIN_F4, PIN_F5}

// PS2: B0-B3 for SPI bus
// PS2: F6 for ACK
#define PSX_DRIVER spi
#define PSX_DAT_PIN PIN_SPI_MISO
#define PSX_CMD_PIN PIN_SPI_MOSI
#define PSX_CLK_PIN PIN_SPI_SCLK
#define PSX_ATT_PIN PIN_SPI_SS
#define PSX_ACK_PIN PIN_F6

/*** Chain Inclusion ***/
#include_next "config.h"