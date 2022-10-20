#pragma once
// The Arduino Pro Micro is a general development board.
// The following provides a sample user configuration for the Pro Micro dev board in a IIDX controller.
// This example enables PSX support, which requires additional configuration.

/*** PSX ***/
/* PLEASE READ THE FOLLOWING:
  While PSX is technically supported on our board, our example won't use it as it requires the removal of the RXLED resistor (the one on the left).
  With that being said, the following is provided for informational purposes on how to enable PSX support.
  Note that this requires the use of the specific pins defined by the hardware included on the Pro Micro's chip (the ATmega32u4), and cannot be changed:
  * Pin 16 is our MOSI pin. This is the PSX "CMD" pin.
  * Pin 14 is our MISO pin. This is the PSX "DAT" pin.
  * Pin 15 is our SCLK pin. This is the PSX "CLK" pin.
  * The RXLED resistor pad closest to the bottom edge of the board is our CS pin. This is the PSX "ATT" pin.

  Additionally, a user-customizable pin must be provided. This is the PSX "ACK" pin, which we'll customize below.

  Note that while PSX_ACTIVE is usually defined in the controller, any other parameters such as PSX_ACK_PIN would usually be defined by the board.
  However, since our board is a generic dev board, we'll define it here so it's only included in this specific configuration.
*/
// PSX support is opt-in, so we need to enable it.
#define PSX_ACTIVE
// Our customizable pin, the PSX "ACK" pin, will be on our last remaining pin, Arduino pin 0.
#define PSX_ACK_PIN  PRO_MICRO_PIN_0


/*** Additional Includes ***/
// We'll include some friendly USB labels in a separate file.
// We'll pull the one from the "default" folder since the'll be the same.
#include "../default/labels.h"
