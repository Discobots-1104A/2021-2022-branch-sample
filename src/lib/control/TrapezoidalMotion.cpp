//* bad library
//* control
//* TrapezoidalMotion - trapezoidal motion profile

//* headers
#include "lib/control/TrapezoidalMotion.h"

namespace Lib1104A {
namespace Control {
TrapezoidalMotion::TrapezoidalMotion(TrapezoidalLimits limits)
    : m_limits{limits}, m_elapsedTime{0.0}, m_target{0.0} {
  // do nothing
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
  m_limits = limits;
  return *this;
}

double TrapezoidalMotion::getNextTarget(double dt) {
  m_elapsedTime += dt;
  if (m_elapsedTime < (1.0 / 3.0) * m_totalTime) {
    double calculatedVelocity = (m_acceleration * m_elapsedTime);
    calculatedVelocity = std::clamp(calculatedVelocity, -m_limits.maxVelocity,
                                    m_limits.maxVelocity);
    calculatedVelocity = calculatedVelocity / m_limits.maxVelocity;
    return calculatedVelocity;
  } else if (m_elapsedTime < (2.0 / 3.0) * m_totalTime) {
    double calculatedVelocity = 1.0;
    return calculatedVelocity;
  } else {
    double calculatedVelocity =
        (m_acceleration * (m_totalTime - m_elapsedTime));
    calculatedVelocity = std::clamp(calculatedVelocity, -m_limits.maxVelocity,
                                    m_limits.maxVelocity);
    calculatedVelocity = (calculatedVelocity / m_limits.maxVelocity);
    return calculatedVelocity;
  }
}

TrapezoidalMotion &TrapezoidalMotion::reset() {
  m_elapsedTime = 0.0;
  return *this;
}

double TrapezoidalMotion::calculateEstTotalTime() {
  double calculatedTotalTime = (4.5 * m_target) / (m_limits.maxVelocity);
  calculatedTotalTime = std::fabs(calculatedTotalTime);
  return Misc::operator""_ms(calculatedTotalTime);
}

double TrapezoidalMotion::calculateEstAcceleration() {
  double calculatedAcceleration =
      (4.5 * m_target) / (m_totalTime * m_totalTime);
  return std::clamp(calculatedAcceleration, -m_limits.maxAcceleration,
                    m_limits.maxAcceleration);
}
} // namespace Control
} // namespace Lib1104A