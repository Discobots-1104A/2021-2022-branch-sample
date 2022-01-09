//* bad hardware shit
//* chassis

//* headers
#include "hardware/Chassis.h"

namespace Hardware {

//? ctor & dtor
Chassis::Chassis(MotorGroup &leftMotors, MotorGroup &rightMotors)
    : m_leftMotors(leftMotors), m_rightMotors(rightMotors),
      m_leftEncoder(NULL_ADI_PORT, NULL_ADI_PORT),
      m_rightEncoder(NULL_ADI_PORT, NULL_ADI_PORT), m_imu(NULL_SMART_PORT),
      m_advancedTracking(false) {}

Chassis::Chassis(MotorGroup &leftMotors, MotorGroup &rightMotors,
                 pros::ADIEncoder leftEncoder, pros::ADIEncoder rightEncoder,
                 pros::Imu imu)
    : m_leftMotors(leftMotors), m_rightMotors(rightMotors),
      m_leftEncoder(leftEncoder), m_rightEncoder(rightEncoder), m_imu(imu),
      m_advancedTracking(true) {
  configureTracking();
}

Chassis::~Chassis() {
  // do nothing
}

//? setters
Chassis &Chassis::setBrakeMode(pros::motor_brake_mode_e_t mode) {
  m_leftMotors.setBrakeMode(mode);
  m_rightMotors.setBrakeMode(mode);
  return *this;
}

Chassis &Chassis::tarePosition(void) {
  if (m_advancedTracking) {
    m_leftEncoder.reset();
    m_rightEncoder.reset();
  } else {
    m_leftMotors.tarePosition();
    m_rightMotors.tarePosition();
  }
  return *this;
}

//? getters
rt_t Chassis::getPosition(char side) const {
  if (m_advancedTracking) {
    if (side == 'l') {
      return m_leftEncoder.get_value();
    } else if (side == 'r') {
      return m_rightEncoder.get_value();
    } else {
      return 0;
    }
  } else {
    if (side == 'l') {
      return m_leftMotors.getPosition();
    } else if (side == 'r') {
      return m_rightMotors.getPosition();
    } else {
      return 0;
    }
  }
}

deg_t Chassis::getHeading(void) const {
  if (m_advancedTracking) {
    return m_imu.get_heading();
  } else {
    return 0;
  }
}

//? methods
void Chassis::driveJoystick(int joystickLeft, int joystickRight) {
  m_leftMotors.move(joystickLeft);
  m_rightMotors.move(joystickRight);
}

void Chassis::driveVelocity(rpm_t leftVelocity, rpm_t rightVelocity) {
  m_leftMotors.moveVelocity(leftVelocity);
  m_rightMotors.moveVelocity(rightVelocity);
}

void Chassis::driveVoltage(mV_t leftVoltage, mV_t rightVoltage) {
  m_leftMotors.moveVoltage(leftVoltage);
  m_rightMotors.moveVoltage(rightVoltage);
}

//? private methods
void Chassis::configureTracking(void) {
    m_imu.reset();
    m_leftEncoder.reset();
    m_rightEncoder.reset();
    while (m_imu.is_calibrating()) {
        pros::delay(10);
    }
}

} // namespace Hardware