//* bad hardware
//* chassis

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers
#include "lib/device/MotorGroup.h"

//* stl
#include <tuple>

//* bs
using Lib1104A::Device::MotorGroup;

namespace Hardware {
enum class kDriveMode { kMove, kMoveAbs, kMoveRel, kMoveVel, kMoveVoltage };

class Chassis {
public:
  //? ctor & dtor
  explicit Chassis(MotorGroup &left, MotorGroup &right);
  ~Chassis();

  //? setters

  //? getters

  //? methods
  template <typename... Args> void drive(kDriveMode mode, Args... args);

  //? public members
  //! i'm making the motorgroups public simply because i don't want to make a
  //! wrapper method for calling the stupid get_position functions aight
  MotorGroup &m_left, &m_right;

private:
  //? members

  //? private methods
};

} // namespace Hardware