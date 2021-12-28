//* bad hardware
//* arms and conveyor

//* headers
#include "hardware/ArmsConveyor.h"

namespace Hardware {

//TODO: i might wanna implement PID into the arm and holders to keep them in their positions
//TODO: it might be harder because we only have encoders on the motors but i think i can make do

ArmsConveyor::ArmsConveyor(MotorGroup &lift, MotorGroup &holder,
                           MotorGroup &conveyor, int lift_speed,
                           int holder_speed, int holder_max, int conveyor_speed)
    : m_lift(lift), m_holder(holder), m_conveyor(conveyor),
      m_lift_speed(lift_speed), m_holder_speed(holder_speed),
      m_holder_max(holder_max), m_conveyor_speed(conveyor_speed),
      holder_toggle(false), conveyor_toggle(false) {
  // do nothing
}

ArmsConveyor::~ArmsConveyor() {
  // do nothing
}

void ArmsConveyor::move_lift(int position) {
  m_lift.move_abs(position, m_lift_speed);
}

void ArmsConveyor::toggle_holder() {
  if (holder_toggle) {
    m_holder.move_abs(0, m_holder_speed);
  } else {
    m_holder.move_abs(m_holder_max, m_holder_speed);
  }
  holder_toggle = !holder_toggle;
}

void ArmsConveyor::toggle_conveyor() {
  if (conveyor_toggle) {
    m_conveyor.move_vel(m_conveyor_speed);
  } else {
    m_conveyor.move_vel(0);
  }
  conveyor_toggle = !conveyor_toggle;
}

} // namespace Hardware