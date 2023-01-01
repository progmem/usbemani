# USBemani

⚠️ **Work-In-Progress!** This project is in a recent state of flux as development has led to a complete rearchitecture. The contents and documentation of this repository will be changing as items are finalized for release. Until then, please treat this as a sneak peek of what's to come. :)

USBemani is an opinionated, multi-architecture microcontroller firmware aimed at providing the best possible gameplay experience for a number of rhythm game controllers. The name stems from Konami's "Bemani" line of rhythm games, including **beatmania** and **beatmania IIDX**, **Dance Dance Revolution** (DDR), **Sound Voltex** (SDVX), **GuitarFreaks** and **DrumMania** (GitaDora), and **pop'n music**. However, USBemani aims at providing the best possible gameplay experience for all rhythm games, even if they don't fall within the Bemani family.

USBemani's design allows it to support multiple microcontroller platforms, with a flexible build system that allows for a given architecture's suggested build system to be leveraged in order to build the firmware. Support for a given architecture is handled via the implementation of "drivers", each handling a different input, output, or system component (such as buttons, encoders, analog/ADC reads, USB communication, etc.). This allows for easy exapandability and flexibility in implementing new microcontrollers and supporting components.

USBemani takes a "configuration first" principle, taking some inspiration from the QMK project by breaking down a given firmware build into the following three core components:

* A `board` determines the availability of capabilities based on the design of the board, such as which microcontroller is used and what pins are made available to users.
* A `controller` determines what capabilities and components are in use. This defines certain attributes about these components, such as the number of installed RGB LEDs and the PPR of the encoders.
* A `layout` determines which board and controller are in use, and defines how controller components should be connected to the board. This also provides a home for user customizations, including custom code.

Documentation on how to create new `boards`, `controllers`, and `layouts` is in progress. Until then, it's suggested to review the following examples:

  * `boards/dev` contains two development board examples: one for the Pro Micro and one for the Raspberry Pi Pico.
  * `controllers/examples/iidx` contains two example IIDX controllers that match Konami's eAmusement Cloud controllers: one for a 'basic model' and another for a 'premium model'
  * `layouts/examples/iidx` contains two examples on how to wire these controllers up to a given development board.

### Building USBemani

USBemani requires the setup and installation of a given architecture's toolchain. Documentation on how to do this is in progress. Until then, in general:

* For `avr8` platforms, you will need `avr-gcc` and `make`.
* For the Raspberry Pi `pico`, you will need `arm-none-eabi-gcc` and `cmake`.

#### macOS

With `homebrew`, install the following:

```
# For all
brew install make git
# For avr8
brew tap osx-cross/avr
brew install avr-gcc
# For pico
brew tap ArmMbed/homebrew-formulae
brew install cmake arm-none-eabi-gcc
# Clone this repository
git clone https://github.com/progmem/usbemani --recurse-submodules
cd ./usbemani
# Build a controller!
make examples/arduino/pro-micro/iidx:default
make lain/mini-4:default
```

#### Linux

```
# Use your package manager to install git, make, and cmake, e.g. for Debian
sudo apt install git make cmake
# For avr8
curl --location 'https://github.com/modm-io/avr-gcc/releases/download/v11.2.0/modm-avr-gcc.tar.bz2' --output gcc-avr-toolchain.tar
sudo mkdir /opt/gcc-avr
sudo tar -C /opt/gcc-avr/ -xf gcc-avr-toolchain.tar --strip-components 1
echo 'export PATH=$PATH:/opt/gcc-avr/bin' >> ~/.profile
# For pico, install the 10.3-2021.10 version of the ARM toolchain
curl --location 'https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2' --output gcc-arm-none-eabi-toolchain.tar
sudo mkdir /opt/gcc-arm-none-eabi
sudo tar -C /opt/gcc-arm-none-eabi/ -xf gcc-arm-none-eabi-toolchain.tar --strip-components 1
echo 'export PATH=$PATH:/opt/gcc-arm-none-eabi/bin' >> ~/.profile
# Clone this repository
git clone https://github.com/progmem/usbemani --recurse-submodules
cd ./usbemani
# Build a controller!
make examples/arduino/pro-micro/iidx:default
make lain/mini-4:default
```

### What if I have an issue?

Once documentation has been completed, feel free to submit a Github Issue. Standards on issue submission will be defined at that point and will populate this block once this has been completed. Until then, those who are helping test this repository and codebase can reach out to me directly via the various forums and group chats that I'm in.

### What happened to the old USBemani code?

The old codebase is still available [here](https://github.com/progmem/usbemani-legacy) for archival purposes.
