//* bad library
//* control
//* TrapezoidalMotion - trapezoidal motion profile

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers

//* stl
#include <algorithm>
#include <cmath>

namespace Lib1104A {
namespace Control {
class TrapezoidalMotion {
public:
  //? ctor & dtor
  TrapezoidalMotion(double max_velocity, double max_acceleration,
                    double max_jerk);
  ~TrapezoidalMotion();

  //? setters

  //? getters

  //? methods

private:
  //? members

  //? private methods
};
} // namespace Control
} // namespace Lib1104A