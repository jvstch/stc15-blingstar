# stc15-blingstar
Open firmware for STC15F204EA based Commonly available Star Shaped LED PCB kit 
### Details in the below youtube video:
  https://youtu.be/giRV_Y_Iqjg

## Description
  STC15F204EA in one of the fast implementation(1 instruction per clock) of the classic intel 80C51 micro
  controller. This chip comes with many classic peripherals like ADC's UART, Timers, Interrupts etc but don't
  include any modern purpose built ports like I2C,SPI,PWM etc. The key 
  features are 4 ttl-level ports(P0-2bits, P1-8bits, P2-8bits and P3-8bits), and the killer feature is the easy programmability using very minimal ttl-level serial port.
  
 ## Wiring for Flashing the Chip
  If you have a board with any STC 8-bit controller like this STC15F204EA or any of the 89x, stc8, 12x or 15x
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
  with the open source python based stcgal programmer or the C based stc8prog.
### Programmer links:
  https://github.com/grigorig/stcgal
  https://github.com/IOsetting/stc8prog/releases
