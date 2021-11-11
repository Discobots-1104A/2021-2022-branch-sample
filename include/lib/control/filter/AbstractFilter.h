//* bad library
//* control
//* AbstractFilter - base class for all filters

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers

//* stl

namespace Lib1104A {
namespace Control {
class AbstractFilter {
public:
  //? ctor & dtor
  AbstractFilter();
  virtual ~AbstractFilter();

  //? setters

  //? getters

  //? methods

  // reset filter
  virtual void reset() = 0;

  // filter a value
  virtual double filter(double value) = 0;

private:
  //? members

  //? private methods
};
} // namespace Control
} // namespace Lib1104A