//* bad hardware shit
//* arms

//* headers
#include "hardware/Arms.h"

namespace Hardware {

//? ctor & dtor
Arms::Arms(MotorGroup &liftMotors, MotorGroup &holderMotors,
           PIDGains liftPIDGains, PIDGains holderPIDGains, int liftVoltageDelta,
           int holderVoltageDelta)
    : m_liftMotors(liftMotors), m_holderMotors(holderMotors),
      m_liftRotation(NULL_SMART_PORT), m_holderRotation(NULL_SMART_PORT),
      m_liftTask(std::bind(&Arms::liftTaskFn, *this)),
      m_holderTask(std::bind(&Arms::holderTaskFn, *this)),
      m_liftPIDGains(liftPIDGains), m_holderPIDGains(holderPIDGains),
      m_liftPID(m_liftPIDGains), m_holderPID(m_holderPIDGains),
      m_liftVoltageDelta(liftVoltageDelta),
      m_holderVoltageDelta(holderVoltageDelta),
      m_liftTarget(e_armPositions::E_STOW),
      m_holderTarget(e_armPositions::E_STOW) {
  m_liftPID.setDerivativeFilter(m_liftEMA).setGains(m_liftPIDGains);
  m_holderPID.setDerivativeFilter(m_holderEMA).setGains(m_holderPIDGains);
  m_advancedMode = false;
  tarePosition();
}

Arms::Arms(MotorGroup &liftMotors, MotorGroup &holderMotors,
           PIDGains liftPIDGains, PIDGains holderPIDGains, int liftVoltageDelta,
           int holderVoltageDelta, pros::Rotation liftRotation,
           pros::Rotation holderRotation)
    : m_liftMotors(liftMotors), m_holderMotors(holderMotors),
      m_liftRotation(liftRotation), m_holderRotation(holderRotation),
      m_liftTask(std::bind(&Arms::liftTaskFn, *this)),
      m_holderTask(std::bind(&Arms::holderTaskFn, *this)),
      m_liftPIDGains(liftPIDGains), m_holderPIDGains(holderPIDGains),
      m_liftPID(m_liftPIDGains), m_holderPID(m_holderPIDGains),
      m_liftVoltageDelta(liftVoltageDelta),
      m_holderVoltageDelta(holderVoltageDelta),
      m_liftTarget(e_armPositions::E_STOW),
      m_holderTarget(e_armPositions::E_STOW) {
  m_liftPID.setDerivativeFilter(m_liftEMA).setGains(m_liftPIDGains);
  m_holderPID.setDerivativeFilter(m_holderEMA).setGains(m_holderPIDGains);
  m_advancedMode = true;
  tarePosition();
}

Arms::~Arms(void) {
  m_liftTask.remove();
  m_holderTask.remove();
  delete m_liftEMA;
  delete m_holderEMA;
}

//? setters
Arms &Arms::tarePosition(void) {
  if (m_advancedMode) {
    m_liftRotation.reset_position();
    m_holderRotation.reset_position();
  } else {
    m_liftMotors.tarePosition();
    m_holderMotors.tarePosition();
  }

  return *this;
}

//? getters
rt_t Arms::getPosition(char arms) {
  if (arms == 'l') {
    return (m_advancedMode) ? m_liftRotation.get_position()
                            : m_liftMotors.getPosition();
  } else if (arms == 'h') {
    return (m_advancedMode) ? m_holderRotation.get_position()
                            : m_holderMotors.getPosition();
  }
  return 0;
}

//? methods
void Arms::setPosition(char arms, e_armPositions position) {
  if (arms == 'l') {
    m_liftMutex.take(TIMEOUT_MAX);
    m_liftTarget = position;
    m_liftMutex.give();
  } else if (arms == 'r') {
    m_holderMutex.take(TIMEOUT_MAX);
    m_holderTarget = position;
    m_holderMutex.give();
  }
};

void Arms::setPositionNoPID(char arms, e_armPositions position) {
  if (arms == 'l') {
    if (position == e_armPositions::E_STOW) {
      m_liftMotors.moveVelocity(-LIFT_MAX_VELOCITY);
      while (m_liftMotors.getTorque() < LIFT_ZERO_TORQUE) {
        pros::delay(10);
      }
      m_liftMotors.tarePosition();
      m_liftMotors.moveVelocity(0);
    } else if (position == e_armPositions::E_LOW) {
      m_liftMotors.moveAbsolute(LIFT_LOW_POSITION, LIFT_MAX_VELOCITY);
    } else if (position == e_armPositions::E_HIGH) {
      m_liftMotors.moveAbsolute(LIFT_HIGH_POSITION, LIFT_MAX_VELOCITY);
    }
  }
}

//? private methods
void Arms::liftTaskFn(void) {
  Lib1104A::Utility::Timer timer;
  m_liftPID.reset();
  int voltageOld = 0;

  while (!(pros::competition::is_disabled())) {
    m_liftMutex.take(TIMEOUT_MAX);
    rt_t target = [&]() {
      if (m_liftTarget == e_armPositions::E_STOW) {
        return 0.0;
      } else if (m_liftTarget == e_armPositions::E_LOW) {
        return LIFT_LOW_POSITION;
      } else if (m_liftTarget == e_armPositions::E_HIGH) {
        return LIFT_HIGH_POSITION;
      }
      return 0.0;
    }();
    m_liftMutex.give();

    m_liftPID.setTarget(target);

    int travel = getPosition('l');
    int voltage = m_liftPID.calculate(travel, timer.getDtFromLast());
    voltage = std::clamp(voltage, -LIFT_MAX_VELOCITY, LIFT_MAX_VELOCITY);

    m_liftMotors.moveVoltage(voltage);

    voltageOld = voltage;

    pros::delay(10);
  }

  m_liftMotors.moveVoltage(0);
}

void Arms::holderTaskFn(void) {
  Lib1104A::Utility::Timer timer;
  m_holderPID.reset();
  int voltageOld = 0;

  while (!(pros::competition::is_disabled())) {
    m_holderMutex.take(TIMEOUT_MAX);
    rt_t target = [&]() {
      if (m_holderTarget == e_armPositions::E_STOW) {
        return 0.0;
      } else if (m_holderTarget == e_armPositions::E_HIGH) {
        return HOLDER_HIGH_POSITION;
      }
      return 0.0;
    }();
    m_holderMutex.give();

    m_holderPID.setTarget(target);

    int travel = getPosition('h');
    int voltage = m_holderPID.calculate(travel, timer.getDtFromLast());
    voltage = std::clamp(voltage, -HOLDER_MAX_VELOCITY, HOLDER_MAX_VELOCITY);

    m_holderMotors.moveVoltage(voltage);

    voltageOld = voltage;

    pros::delay(10);
  }
}

} // namespace Hardware