//* bad library
//* device
//* MotorGroup - control da motor

//? i am wasting my time not using okapilib MotorGroup lmao!!!!!

//* headers
#include "lib/device/MotorGroup.h"

namespace Lib1104A {
namespace Device {

//? ctor & dtor
MotorGroup::MotorGroup(std::initializer_list<int> motor_ports,
                       pros::motor_brake_mode_e_t brake_mode,
                       pros::motor_gearset_e_t gearset,
                       pros::motor_encoder_units_e_t encoder_units)
    : m_brake_mode(brake_mode), m_gearset(gearset),
      m_encoder_units(encoder_units) {
  for (int port : motor_ports) {
    m_motor_ports.push_back(
        std::make_tuple<int, bool>(std::abs(port), port < 0));
  }
  set_brake_mode(brake_mode);
  set_gearset(gearset);
  set_encoder_units(encoder_units);
  set_reverse(motor_ports);
  tare_position();
}

//? private methods
void MotorGroup::set_gearset(pros::motor_gearset_e_t gearset) {
  for (auto motor_port : m_motor_ports) {
    pros::c::motor_set_gearing(std::get<0>(motor_port), gearset);
  }
  m_gearset = gearset;
}

void MotorGroup::set_encoder_units(
    pros::motor_encoder_units_e_t encoder_units) {
  for (auto motor_port : m_motor_ports) {
    pros::c::motor_set_encoder_units(std::get<0>(motor_port), encoder_units);
  }
  m_encoder_units = encoder_units;
}

//? setters
MotorGroup &MotorGroup::set_brake_mode(pros::motor_brake_mode_e_t mode) {
  for (auto motor_port : m_motor_ports) {
    pros::c::motor_set_brake_mode(std::get<0>(motor_port), mode);
  }
  m_brake_mode = mode;
  return *this;
}

MotorGroup &MotorGroup::set_reverse(void) {
  m_reverse_state_total = !m_reverse_state_total;
  for (auto motor_port : m_motor_ports) {
    pros::c::motor_set_reversed(
        std::get<0>(motor_port),
        (std::get<1>(motor_port) == m_reverse_state_total));
  }
  return *this;
}


//* This is catastropically bad, don't do this. Someone needs to fix this.
MotorGroup &
MotorGroup::set_reverse(std::initializer_list<int> motor_rev_states) {
  m_reverse_state_total = false;
  for (auto motor_port : m_motor_ports) {
    auto iterator = std::find_if(
        motor_rev_states.begin(), motor_rev_states.end(),
        [&](int x) { return std::abs(x) == std::get<0>(motor_port); });

    if (iterator != motor_rev_states.end()) {
      std::get<1>(motor_port) = (*iterator < 0);
      pros::c::motor_set_reversed(std::get<0>(motor_port),
                                  (std::get<1>(motor_port)));
    }
  }

  return *this;
}

MotorGroup &MotorGroup::tare_position(void) {
  for (auto motor_port : m_motor_ports) {
    pros::c::motor_tare_position(std::get<0>(motor_port));
  }
  return *this;
}

} // namespace Device
} // namespace Lib1104A
