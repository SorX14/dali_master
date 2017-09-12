# dali_master

A Particle library for dali_master. Turns your Particle Photon into a DALI Master with the LED Warrior 14 modules available here:

- http://shop.codemercs.com/en/led-warrior14-01-module (Powered via 5v) 
- http://shop.codemercs.com/en/led-warrior14-02-module (Powered from DALI bus)

## About DALI

DALI (Digital Addressable Lighting Interface) is a method of controlling lighting fixtures via a 2 wire bus. The DALI interface communicates via Manchester encoding.

Up to 64 individual devices can be communicated with one master. Scenes and groups can be defined to group together multiple fixtures. More complicated builds use light and PIR sensors to turn lights on and off.

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

## Welcome to your library!

To get started, modify the sources in [src](src). Rename the example folder inside [examples](examples) to a more meaningful name and add additional examples in separate folders.

To compile your example you can use `particle compile examples/usage` command in [Particle CLI](https://docs.particle.io/guide/tools-and-features/cli#update-your-device-remotely) or use our [Desktop IDE](https://docs.particle.io/guide/tools-and-features/dev/#compiling-code).

Libraries can also depend on other libraries. To add a dependency use [`particle library add`](https://docs.particle.io/guide/tools-and-features/cli#adding-a-library) or [library management](https://docs.particle.io/guide/tools-and-features/dev/#managing-libraries) in Desktop IDE.

After the library is done you can upload it with `particle library upload` or `Upload` command in the IDE. This will create a private (only visible by you) library that you can use in other projects. If you wish to make your library public, use `particle library publish` or `Publish` command.

_TODO: update this README_

## Usage

Connect XYZ hardware, add the dali_master library to your project and follow this simple example:

```
#include "dali_master.h"
Dali_master dali_master;

void setup() {
  dali_master.begin();
}

void loop() {
  dali_master.process();
}
```

See the [examples](examples) folder for more details.

## Documentation

TODO: Describe `Dali_master`

## Contributing

Here's how you can make changes to this library and eventually contribute those changes back.

To get started, [clone the library from GitHub to your local machine](https://help.github.com/articles/cloning-a-repository/).

Change the name of the library in `library.properties` to something different. You can add your name at then end.

Modify the sources in <src> and <examples> with the new behavior.

To compile an example, use `particle compile examples/usage` command in [Particle CLI](https://docs.particle.io/guide/tools-and-features/cli#update-your-device-remotely) or use our [Desktop IDE](https://docs.particle.io/guide/tools-and-features/dev/#compiling-code).

After your changes are done you can upload them with `particle library upload` or `Upload` command in the IDE. This will create a private (only visible by you) library that you can use in other projects. Do `particle library add dali_master_myname` to add the library to a project on your machine or add the dali_master_myname library to a project on the Web IDE or Desktop IDE.

At this point, you can create a [GitHub pull request](https://help.github.com/articles/about-pull-requests/) with your changes to the original library. 

If you wish to make your library public, use `particle library publish` or `Publish` command.

## LICENSE
Copyright 2017 Steve Parker

Licensed under the <insert your choice of license here> license
