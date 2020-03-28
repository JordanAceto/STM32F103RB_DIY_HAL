## This is a Hardware Abstraction Layer for the STM32F103RB.

### It does not use any of the supplied STM HAL files.

### This is just for goofing around and to learn a little about stm32 microcontrollers and embedded development.
### It is in the very early stages now, more to come.

#### Some acronyms used:
- PSP: Processor Support Package
- BSP: Board Support Package

#### To build and flash an example application:
- look in the examples directory and choose an example application to demo.
- $ make [name of the example application without the extension]
- $ make write

#### For instance, to build the 'simple_blink.c' example:
- $ make simple_blink

#### To clean the bin directory:
- $ make clean

#### Efforts have been made to keep the formatting of the files consistent. Once you get the hang of how things are organized it should be pretty easy to guess what each file will contain. For the peripherals, the header files map pretty closely to the information in the manual.

#### For each peripheral in the manuals (as I get to them), a structure is made for the registers contained in that peripheral, and enumerations are used for the flags and masks in each register. Typically a publicly accesible pointer to the peripheral structure is defined.
