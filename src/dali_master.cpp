/* dali_master library by Steve Parker
 */

#include "dali_master.h"

/**
 * Constructor.
 */
Dali_master::Dali_master()
{
  // be sure not to call anything that requires hardware be initialized here, put those in begin()
}

/**
 * Example method.
 */
void Dali_master::begin()
{
    // initialize hardware
    Serial.println("called begin");
}

/**
 * Example method.
 */
void Dali_master::process()
{
    // do something useful
    Serial.println("called process");
    doit();
}

/**
* Example private method
*/
void Dali_master::doit()
{
    Serial.println("called doit");
}
