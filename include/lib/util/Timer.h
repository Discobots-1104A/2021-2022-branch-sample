//* bad library
//* utility
//* timer - for timing things

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers
#include "lib/misc/Units.h"

//* stl

namespace Lib1104A {
namespace Utility {

class Timer {
public:
  //? ctor & dtor
  Timer();
  ~Timer();

  //? setters

  // set timer mark
  void set() const;
  // clear timer mark
  void clear() const;

  //? getters

  // get current time
  Misc::ms_t getTime() const;
  // get Dt from last called
  Misc::ms_t getDtFromLast() const;
  // get Dt from mark
  Misc::ms_t getDtFromMark() const;

  //? methods

private:
  //? members

  // timer start
  const Misc::ms_t m_start;
  // timer mark
  mutable Misc::ms_t m_mark;
  // last called
  mutable Misc::ms_t m_last;

  //? private methods
};

} // namespace Utility
} // namespace Lib1104A