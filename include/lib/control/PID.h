//* bad library
//* control
//* PID - proportional, integral, derivative controller

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers
#include "lib/control/filter/Filter.h"

//* stl
#include <algorithm>
#include <cmath>
#include <limits>

namespace Lib1104A {
namespace Control {

struct PIDGains {
  double m_Kp;
  double m_Ki;
  double m_Kd;
  double m_Kbias;
};

class PID {
public:
  //? ctor & dtor
  explicit PID(PIDGains gains);
  explicit PID(PIDGains gains, AbstractFilter *filter);
  virtual ~PID();

  //? setters

  // set gains
  // 
  // please don't set values unrealistically high, i.e. kP = 200.0
  // try keeping them around the 1.0 range and even less for kI
  PID &setGains(PIDGains gains);

  // set target
  PID &setTarget(double target);

  // set integral limits
  PID &setIntegralLimits(double min, double max);

  // toggle integral reset
  PID &setIntegralReset(bool reset);

  // set max error to integrate
  PID &setMaxError(double maxError);

  // set derivative filter
  PID &setDerivativeFilter(AbstractFilter *filter);

  //? getters
  double &getError(void);

  //? methods

  // reset
  PID &reset();

  // calculate
  double calculate(double input, double dt);

private:
  //? members
  PIDGains m_gains;
  AbstractFilter *m_filter;

  double m_target{0.0};
  double m_error{0.0};
  double m_output{0.0};
  double m_integral{0.0};
  double m_derivative{0.0};

  double m_lastError{0.0};
  double m_integralMin{-1.0};
  double m_integralMax{1.0};
  double m_maxError{std::numeric_limits<double>::max()};
  bool m_integralReset{true};

  //? private methods
};

} // namespace Control
} // namespace Lib1104A