//* bad library
//* control
//* DEMAFilter - double exponential moving average filter

//* headers
#include "lib/control/filter/DEMAFilter.h"

namespace Lib1104A {
namespace Control {
DEMAFilter::DEMAFilter(double alpha)
    : m_alpha{alpha}, m_prevValue{0.0}, m_prevValue2{0.0} {
  // do nothing
}

DEMAFilter::~DEMAFilter() {
  // do nothing
}

DEMAFilter &DEMAFilter::setAlpha(double alpha) {
  m_alpha = alpha;
  return *this;
}

void DEMAFilter::reset() {
  m_prevValue = 0.0;
  m_prevValue2 = 0.0;
}

double DEMAFilter::filter(double value) {
  m_prevValue = ema(value, m_prevValue);
  m_prevValue2 = ema(m_prevValue, m_prevValue2);
  return 2.0 * m_prevValue - m_prevValue2;
}

double DEMAFilter::ema(double value, double prev) {
  return m_alpha * value + (1.0 - m_alpha) * prev;
}
} // namespace Control
} // namespace Lib1104A
