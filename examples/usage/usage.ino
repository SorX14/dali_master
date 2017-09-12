// Example usage for dali_master library by Steve Parker.

#include "dali_master.h"

// Initialize objects from the lib
Dali_master dali_master;

void setup() {
    // Call functions on initialized library objects that require hardware
    dali_master.begin();
}

void loop() {
    // Use the library's initialized objects and functions
    dali_master.process();
}
