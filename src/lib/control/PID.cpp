//* bad library
//* control
//* PID - proportional, integral, derivative controller

//* headers
#include "lib/control/PID.h"

namespace Lib1104A {
namespace Control {
PID::PID(PIDGains gains)
    : m_gains{gains}, m_filter{NULL}, m_timer{Utility::Timer()} {
  reset();
}

PID::PID(PIDGains gains, AbstractFilter *filter)
    : m_gains{gains}, m_filter{filter}, m_timer{Utility::Timer()} {
  reset();
}

PID::~PID() { m_filter = NULL; }

PID &PID::reset() {
  m_target = 0;
  m_error = 0;
  m_integral = 0;
  m_derivative = 0;
  m_lastError = 0;
  return *this;
}

double PID::calculate(double input) {
  double Dt = m_timer.getDtFromLast();

  m_error = std::copysign(1.0, m_target) - (input / m_target);
  m_derivative = (Dt) ? (m_lastError - m_error) / Dt : 0.0;
  m_derivative = m_filter ? m_filter->filter(m_derivative) : m_derivative;

  if (m_maxError == std::numeric_limits<double>::max() ||
      std::fabs(m_error) <= m_maxError) {
    m_integral += m_error * Dt;
  }
  if (m_integralReset &&
      std::copysign(1.0, m_error) != std::copysign(1.0, m_lastError)) {
    m_integral = 0.0;
  }

  m_integral = std::clamp(m_integral, m_integralMin, m_integralMax);

  m_lastError = m_error;

  return m_gains.m_Kp * m_error + m_gains.m_Ki * m_integral +
         m_gains.m_Kd * m_derivative + std::copysign(m_gains.m_Kbias, m_error);
}

PID &PID::setGains(PIDGains gains) {
  m_gains = gains;
  return *this;
}

PID &PID::setTarget(double target) {
  m_target = target;
  return *this;
}

PID &PID::setIntegralLimits(double min, double max) {
  m_integralMin = min;
  m_integralMax = max;
  return *this;
}

PID &PID::setIntegralReset(bool reset) {
  m_integralReset = reset;
  return *this;
}

PID &PID::setMaxError(double maxError) {
  m_maxError = maxError;
  return *this;
}

PID &PID::setDerivativeFilter(AbstractFilter *filter) {
  m_filter = filter;
  return *this;
}
} // namespace Control
} // namespace Lib1104A