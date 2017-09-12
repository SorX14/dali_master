#pragma once

/* dali_master library by Steve Parker
 */

// This will load the definition for common Particle variable types
#include "Particle.h"

// This is your main class that users will import into their application
class Dali_master
{
public:
  /**
   * Constructor
   */
  Dali_master();

  /**
   * Example method
   */
  void begin();

  /**
   * Example method
   */
  void process();

private:
  /**
   * Example private method
   */
  void doit();
};
