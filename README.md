# stc89-blingheart
Open firmware for STC89C52RC based Commonly available Heart Shaped LED PCB kit 

## Description
  STC89C52RC in one of the best and faithful implementation of the classic intel 80C51 micro
  controller. This chip comes with the very basic peripherals like the original. The key 
  features are 4 ttl-level 8-bit ports, ADC, UART, WDT and the killer feature is the easy 
  programmability using very minimal ttl-level serial port.
  
 ## Wiring for Flashing the Chip
  If you have a board with any STC 8-bit controller like this 89C52 or any of the 12x or 15x
  series the only thing you need to program is a $2 USB-Serial converter and connect the 4
  wires as below:
  
    STC Micro ---   USB Serial converter
    VCC       ---   VCC
    GND       ---   GND
    RX(P3.0)  ---   TX
    TX(P3.1)  ---   RX
  
  This is a bare basic code which aim the replicate the effects that these PCB kit's comes 
  pre-programmed with.

## Development tools (Fully Open Source)  - Prefer Linux.
  This code can be easily developed using the fully opensource VSCodium IDE
  with PlatformIO extension which inturn uses the fully open source excellent sdcc toolchain along
  with the open source python based stcgal programmer.
