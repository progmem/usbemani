# USBemani

⚠️ **Work-In-Progress!** This project is in a recent state of flux as development has led to a complete rearchitecture. The contents and documentation of this repository will be changing as items are finalized for release. Until then, please treat this as a sneak peek of what's to come. :)

USBemani is an opinionated, multi-architecture microcontroller firmware aimed at providing the best possible gameplay experience for a number of rhythm game controllers. The name stems from Konami's "Bemani" line of rhythm games, including **beatmania** and **beatmania IIDX**, **Dance Dance Revolution** (DDR), **Sound Voltex** (SDVX), **GuitarFreaks** and **DrumMania** (GitaDora), and **pop'n music**. However, USBemani aims at providing the best possible gameplay experience for all rhythm games, even if they don't fall within the Bemani family.

USBemani's design allows it to support multiple microcontroller platforms, with a flexible build system that allows for a given architecture's suggested build system to be leveraged in order to build the firmware. Support for a given architecture is handled via the implementation of "drivers", each handling a different input, output, or system component (such as buttons, encoders, analog/ADC reads, USB communication, etc.). This allows for easy exapandability and flexibility in implementing new microcontrollers and supporting components.

USBemani takes a "configuration first" principle, taking some inspiration from the QMK project by breaking down a given firmware build into the following three core components:

* A `board` determines the availability of capabilities based on the design of the board, such as which microcontroller is used and what pins are made available to users.
* A `controller` determines what capabilities should be used.
* A `config` provides an additional layer of user customization, allowing for overrides and implementation of custom code.

Documentation on how to create new `boards`, `controllers`, and `configs` is in progress. Until then, it's suggested to review the following examples:

* For general-purpose development boards:

  * `boards/dev/arduino/pro-micro` contains an example implementation of the Pro Micro development board.

  * `controllers/examples/arduino/pro-micro/iidx` contains an example implementation of a IIDX controller using the Pro Micro.
  * `configs/examples/arduino/pro-micro/iidx` contains three configuration examples for this IIDX controller.

* For purpose-built boards:

  * `boards/lain/dcfish/rev1` contains the definitions for a custom rhythm game PCB.
  * `controllers/examples/lain/dcfish/rev1/iidx` contains an example implementation of a IIDX controller using this custom PCB.
  * `configs/examples/lain/dcfish/rev1/iidx` contains multiple configurations for building the firmware depending on the encoder disk in use.

### Building USBemani

USBemani requires the setup and installation of a given architecture's toolchain. Documentation on how to do this is in progress. Until then, in general:

* For `avr8` platforms, you will need `avr-gcc` and `make`.
* For the Raspberry Pi `pico`, you will need `arm-none-eabi-gcc` and `cmake`.

To get started:

* Clone this repository, making sure to `--recurse-submodules`. If you've already cloned the repository, you will need to do a `submodule init` and `submodule update`.
* Run `make <controller>:<config>`, substituting `<controller>` and `<config>` .

Using one of the examples above, running `make examples/arduino/pro-micro/iidx:with-psx-support` will build the Arduino Pro Micro example implementation of a IIDX controller, using a config that enables support for the Playstation and Playstation 2.

### What if I have an issue?

Once documentation has been completed, feel free to submit a Github Issue. Standards on issue submission will be defined at that point and will populate this block once this has been completed. Until then, those who are helping test this repository and codebase can reach out to me directly via the various forums and group chats that I'm in.

### What happened to the old USBemani code?

The old codebase is still available [here](https://github.com/progmem/usbemani-legacy) for archival purposes.
