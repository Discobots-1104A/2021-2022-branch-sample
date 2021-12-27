//* bad hardware
//* arms and conveyor

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers
#include "lib/device/MotorGroup.h"

//* stl

//* bs
using Lib1104A::Device::MotorGroup;

namespace Hardware {
class ArmsConveyor {
public:
  //? ctor & dtor
  explicit ArmsConveyor(MotorGroup &lift, MotorGroup &holder,
                        MotorGroup &conveyor);
  ~ArmsConveyor();

  //? setters

  //? getters

  //? methods
  void move_lift(int position);
  void toggle_holder();
  void toggle_conveyor();

  //? public members
  //! same reason as the chassis
  MotorGroup &m_lift, &m_holder, &m_conveyor;

private:
  //? members

  //? private methods
};
} // namespace Hardware