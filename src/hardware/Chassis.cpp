//* bad hardware
//* chassis

//* headers
#include "hardware/Chassis.h"

namespace Hardware {

Chassis::Chassis(MotorGroup &left, MotorGroup &right)
    : m_left(left), m_right(right) {
  // do nothing
}

template <typename... Args> void Chassis::drive(kDriveMode mode, Args... args) {
  auto argsTuple = std::make_tuple(args...);
  switch (mode) {
  case kDriveMode::kMove:
    m_left.move(std::get<0>(argsTuple));
    break;

  case kDriveMode::kMoveAbs:
    m_left.move_abs(std::get<0>(argsTuple), std::get<1>(argsTuple));
    m_right.move_abs(std::get<0>(argsTuple), std::get<1>(argsTuple));
    break;

  case kDriveMode::kMoveRel:
    m_left.move_rel(std::get<0>(argsTuple), std::get<1>(argsTuple));
    m_right.move_rel(std::get<0>(argsTuple), std::get<1>(argsTuple));
    break;

  case kDriveMode::kMoveVel:
    m_left.move_vel(std::get<0>(argsTuple));
    m_right.move_vel(std::get<0>(argsTuple));
    break;

  case kDriveMode::kMoveVoltage:
    m_left.move_vol(std::get<0>(argsTuple));
    m_right.move_vol(std::get<0>(argsTuple));
    break;
  }
}

} // namespace Hardware
