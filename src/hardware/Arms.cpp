//* bad hardware shit
//* arms

//* headers
#include "hardware/Arms.h"

namespace Hardware {

//? ctor & dtor
Arms::Arms(MotorGroup &liftMotors, MotorGroup &holderMotors)
    : m_liftMotors(liftMotors), m_holderMotors(holderMotors),
      m_holderPotentiometer(NULL_ADI_PORT) {
  m_advancedMode = false;
  // m_liftMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  // m_holderMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  tarePosition();
}

Arms::Arms(MotorGroup &liftMotors, MotorGroup &holderMotors,
           int holderRotationPort)
    : m_liftMotors(liftMotors), m_holderMotors(holderMotors),
      m_holderPotentiometer(holderRotationPort) {
  m_advancedMode = true;
  tarePosition();
}

Arms::~Arms(void) {
  // do nothing
}

//? setters
Arms &Arms::tarePosition(void) {
  m_liftMotors.tarePosition();
  m_holderMotors.tarePosition();
  return *this;
}

void Arms::setVelocity(char arm, rpm_t velocity) {
  if (arm == 'l') {
    m_liftMotors.moveVelocity(velocity);
  } else if (arm == 'h') {
    m_holderMotors.moveVelocity(velocity);
  }
}

void Arms::setVoltage(char arm, mV_t voltage) {
  if (arm == 'l') {
    m_liftMotors.moveVoltage(voltage);
  } else if (arm == 'h') {
    m_holderMotors.moveVoltage(voltage);
  }
}

void Arms::setPositionAbsolute(char arm, rpm_t velocity, rt_t position) {
  if (arm == 'l') {
    while (m_liftMotors.moveAbsolute(velocity, position) != 1) {
      pros::delay(10);
    };
  } else if (arm == 'h') {
    m_holderMotors.moveAbsolute(velocity, position);
  }
}

//? getters
rt_t Arms::getPosition(char arms) {
  if (arms == 'l') {
    return m_liftMotors.getPosition();
  } else if (arms == 'h') {
    return (m_advancedMode) ? m_holderPotentiometer.get_value()
                            : m_holderMotors.getPosition();
  }
  return 0;
}

//? methods

//? private methods

} // namespace Hardware