# dali_master

A Particle library for dali_master. Turns your Particle Photon into a DALI Master with the LED Warrior 14 modules available here:

- http://shop.codemercs.com/en/led-warrior14-01-module (Powered via 5v) 
- http://shop.codemercs.com/en/led-warrior14-02-module (Powered from DALI bus)

## About DALI

DALI (Digital Addressable Lighting Interface) is a method of controlling lighting fixtures via a 2 wire bus. The DALI interface communicates via Manchester encoding.

Up to 64 individual devices can be communicated with. Scenes and groups can be defined to group together multiple fixtures. More complicated builds use light and PIR sensors to turn lights on and off.

References: 
- https://en.wikipedia.org/wiki/Digital_Addressable_Lighting_Interface

## This project

The code here is based largely around this original library: https://create.arduino.cc/projecthub/NabiyevTR/simple-dali-controller-506e44 which uses custom circuitry to interface with the DALI bus. I had no interest in designing my own circuit so I purchased a ready-made solution which uses I2C and galvanicly isolates the MCU from the DALI bus.

I've managed to reliably address 2 light features on the bus using the RANDOMISE command which was my main goal.

While the DALI reference is available as a paid for PDF, I used various resources online to understand the commissioning process.

References:
- https://create.arduino.cc/projecthub/NabiyevTR/simple-dali-controller-506e44
- http://www.rayzig.com/manual/rayzig.html?DALIaddresssettingexplained.html
- https://elmicro.com/files/manuals/drm004.pdf

## Usage

Connect the LED Warrior to your Photon.

D0 -> SDA
D1 -> SCL
GND -> GND
VIN -> 5V (for 14-01 only)

You'll need pullup resistors for each I2C line (SDA & SCL).

Add the dali_master library to your project and follow this simple example:

```
#include "dali_master.h"
Dali_master dali;

void setup() {
  dali.begin(0x28); // I2C address of LED Warrior
}

void loop() {
  // Turn all connected devices on and off (no short address required)
  dali.transmitCommand(BROADCAST_C, ON_C);
  delay(1000);
  dali.transmitCommand(BROADCAST_C, OFF_C);
  delay(1000);
}
```

See the [examples](examples) folder for more details.

## LICENSE
Copyright 2017 Steve Parker

Licensed under the Apache License Version 2.0 license
