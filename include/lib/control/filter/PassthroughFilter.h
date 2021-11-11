//* bad library
//* control
//* Passthrough - a filter that passes all data through

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers
#include "lib/control/filter/AbstractFilter.h"

//* stl

namespace Lib1104A {
namespace Control {
class PassthroughFilter : public AbstractFilter {
public:
  //? ctor & dtor
  PassthroughFilter();
  ~PassthroughFilter();

  //? setters

  //? getters

  //? methods

  // reset filter
  void reset() override;

  // filter a value
  double filter(double value) override;

private:
  //? members

  //? private methods
};
} // namespace Control
} // namespace Lib1104A