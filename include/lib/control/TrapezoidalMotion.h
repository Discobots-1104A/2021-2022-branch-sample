//* bad library
//* control
//* TrapezoidalMotion - trapezoidal motion profile

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers
#include "lib/misc/RobotConst.h"
#include "lib/misc/Units.h"

//* stl
#include <algorithm>
#include <cmath>

namespace Lib1104A {
namespace Control {

struct TrapezoidalLimits {
  double maxVelocity;
  double maxAcceleration;
};

struct FeedforwardLimits {
  double maxVoltage;
  double minVoltageBackEmf;
};

class TrapezoidalMotion {
public:
  //? ctor & dtor
  explicit TrapezoidalMotion(TrapezoidalLimits mLimits, FeedforwardLimits ffLimits);
  ~TrapezoidalMotion();

  //? setters

  // set target
  TrapezoidalMotion &setTarget(double target);

  // set limits
  TrapezoidalMotion &setLimits(TrapezoidalLimits limits);

  //? getters

  // get next target
  double getNextTarget(double dt);

  //? methods

  // reset
  TrapezoidalMotion &reset();

private:
  //? members
  TrapezoidalLimits m_mLimits;
  double m_kVoltsPerMS;
  double m_kVoltsPerMS2;
  const FeedforwardLimits m_ffLimits;

  Misc::ms_t m_totalTime;
  Misc::ms_t m_elapsedTime;
  double m_target;
  double m_acceleration;
  double m_velocityTarget;
  double m_voltageTarget;

  //? private methods
  double calculateEstTotalTime();
  double calculateEstAcceleration();
  double calculateVelocityTarget(double dt);
};
} // namespace Control
} // namespace Lib1104A