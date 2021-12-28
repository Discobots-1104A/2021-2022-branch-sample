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
                        MotorGroup &conveyor, int lift_speed, int holder_speed,
                        int holder_max, int conveyor_speed);
  virtual ~ArmsConveyor();

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
  int m_lift_speed, m_holder_speed, m_holder_max, m_conveyor_speed;
  bool holder_toggle, conveyor_toggle;

  //? private methods
};
} // namespace Hardware