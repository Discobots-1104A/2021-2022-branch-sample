//* bad library
//* control
//* TrapezoidalMotion - trapezoidal motion profile

//* headers
#include "lib/control/TrapezoidalMotion.h"

namespace Lib1104A {
namespace Control {
TrapezoidalMotion::TrapezoidalMotion(TrapezoidalLimits mLimits,
                                     FeedforwardLimits ffLimits)
    : m_mLimits{mLimits}, m_ffLimits{ffLimits}, m_elapsedTime{0}, m_target{
                                                                        0.0} {
  m_kVoltsPerMS = m_ffLimits.maxVoltage / m_mLimits.maxVelocity;
  m_kVoltsPerMS2 = m_ffLimits.maxVoltage / m_mLimits.maxAcceleration;
}

TrapezoidalMotion::~TrapezoidalMotion() {
  // do nothing
}

TrapezoidalMotion &TrapezoidalMotion::setTarget(double target) {
  m_target = target;
  m_totalTime = calculateEstTotalTime();
  m_acceleration = calculateEstAcceleration();
  return *this;
}

TrapezoidalMotion &TrapezoidalMotion::setLimits(TrapezoidalLimits limits) {
  m_mLimits = limits;
  m_kVoltsPerMS = m_ffLimits.maxVoltage / m_mLimits.maxVelocity;
  m_kVoltsPerMS2 = m_ffLimits.maxVoltage / m_mLimits.maxAcceleration;
  return *this;
}

double TrapezoidalMotion::getNextTarget(double dt) {
  m_velocityTarget = calculateVelocityTarget(dt);
  m_voltageTarget = m_kVoltsPerMS * m_velocityTarget +
                    m_kVoltsPerMS2 * m_acceleration +
                    m_ffLimits.minVoltageBackEmf;
  m_voltageTarget /= m_ffLimits.maxVoltage;

  return m_voltageTarget;
}

TrapezoidalMotion &TrapezoidalMotion::reset() {
  m_elapsedTime = 0.0;
  return *this;
}

double TrapezoidalMotion::calculateEstTotalTime() {
  double calculatedTotalTime = (4.5 * m_target) / (m_mLimits.maxVelocity);
  calculatedTotalTime = std::fabs(calculatedTotalTime);
  return Misc::operator""_ms(calculatedTotalTime);
}

double TrapezoidalMotion::calculateEstAcceleration() {
  double calculatedAcceleration =
      (4.5 * m_target) / (m_totalTime * m_totalTime);
  return std::clamp(calculatedAcceleration, -m_mLimits.maxAcceleration,
                    m_mLimits.maxAcceleration);
}

double TrapezoidalMotion::calculateVelocityTarget(double dt) {
  m_elapsedTime += dt;

  double velocity;

  if (m_elapsedTime < (1.0 / 3.0) * m_totalTime) {
    velocity = m_acceleration * m_elapsedTime;
  } else if (m_elapsedTime < (2.0 / 3.0) * m_totalTime) {
    velocity = 1.0;
  } else {
    velocity = m_acceleration * (m_totalTime - m_elapsedTime);
  }

  velocity =
      std::clamp(velocity, -m_mLimits.maxVelocity, m_mLimits.maxVelocity);

  return velocity;
}

} // namespace Control
} // namespace Lib1104A

// quick test comment to check ssh