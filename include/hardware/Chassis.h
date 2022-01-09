//* bad hardware shit
//* chassis

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers
#include "lib/libApi.h"

//* stl
#include <cmath>

//* other shid
using Lib1104A::Device::MotorGroup;
using Lib1104A::Misc::deg_t;
using Lib1104A::Misc::mV_t;
using Lib1104A::Misc::rpm_t;
using Lib1104A::Misc::rt_t;

namespace Hardware {

class Chassis {
public:
  //? ctor & dtor
  explicit Chassis(MotorGroup &leftMotors, MotorGroup &rightMotors);
  explicit Chassis(MotorGroup &leftMotors, MotorGroup &rightMotors,
                   pros::ADIEncoder leftEncoder,
                   pros::ADIEncoder rightEncoder, pros::Imu imu);
  virtual ~Chassis();

  //? setters
  Chassis &setBrakeMode(pros::motor_brake_mode_e_t mode);
  Chassis &tarePosition(void);

  //? getters
  rt_t getPosition(char side) const;
  deg_t getHeading(void) const; //! only works if using an imu

  //? methods
  void driveJoystick(int joystickLeft, int joystickRight);
  void driveVelocity(rpm_t leftVelocity, rpm_t rightVelocity);
  void driveVoltage(mV_t leftVoltage, mV_t rightVoltage);

private:
  //? members
  MotorGroup &m_leftMotors, &m_rightMotors;
  pros::ADIEncoder m_leftEncoder, m_rightEncoder;
  pros::Imu m_imu;
  bool m_advancedTracking;

  //? private methods
  void configureTracking(void);
};
} // namespace Hardware