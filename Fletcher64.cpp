//
//    FILE: Fletcher64.cpp
//  AUTHOR: Rob Tillaart
// PURPOSE: Arduino class for Fletcher32
//     URL: https://github.com/RobTillaart/Fletcher


#include "Fletcher64.h"

#define FLETCHER_64                       4294967295ULL



Fletcher64::Fletcher64()
{
  begin();
}


void Fletcher64::begin(uint32_t s1, uint32_t s2)
{
  _s1    = s1;
  _s2    = s2;
  _count = 0;
}


void Fletcher64::add(uint32_t value)
{
  _count++;
  _s1 += value;
#ifdef ARDUINO_ARCH_SAMD
  _s1 = (_s1 & ((((uint64_t) 1)<<32)-1)) + (_s1 >> 32);
#else
  if (_s1 >= FLETCHER_64) _s1 -= FLETCHER_64;
#endif
  _s2 += _s1;
#ifdef ARDUINO_ARCH_SAMD
  _s2 = (_s2 & ((((uint64_t) 1)<<32)-1)) + (_s2 >> 32);
#else
  if (_s2 >= FLETCHER_64) _s2 -= FLETCHER_64;
#endif
}


void Fletcher64::add(const uint32_t * array, uint16_t length)
{
  while (length--)
  {
    add(*array++);
  }
}


// -- END OF FILE --

