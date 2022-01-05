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

//? getters
Misc::rpm_t MotorGroup::get_velocity(int index) const {
  return pros::c::motor_get_actual_velocity(std::get<0>(m_motor_ports[index]));
}

Misc::rpm_t MotorGroup::get_velocity(std::initializer_list<int> indices) const {
  Misc::rpm_t velocity = 0;
  for (auto index : indices) {
    velocity += get_velocity(index);
  }
  velocity /= indices.size();
  return velocity;
}

Misc::mA_t MotorGroup::get_current(int index) const {
  return pros::c::motor_get_current_draw(std::get<0>(m_motor_ports[index]));
}

Misc::mA_t MotorGroup::get_current(std::initializer_list<int> indices) const {
  Misc::mA_t current = 0;
  for (auto index : indices) {
    current += get_current(index);
  }
  current /= indices.size();
  return current;
}

Misc::mV_t MotorGroup::get_voltage(int index) const {
  return pros::c::motor_get_voltage(std::get<0>(m_motor_ports[index]));
}

Misc::mV_t MotorGroup::get_voltage(std::initializer_list<int> indices) const {
  Misc::mV_t voltage = 0;
  for (auto index : indices) {
    voltage += get_voltage(index);
  }
  voltage /= indices.size();
  return voltage;
}

bool MotorGroup::get_reversed(void) const { return m_reverse_state_total; }

int32_t MotorGroup::get_direction(int index) const {
  return pros::c::motor_get_direction(std::get<0>(m_motor_ports[index]));
}

uint64_t MotorGroup::get_position(int index) const {
  return pros::c::motor_get_position(std::get<0>(m_motor_ports[index]));
}

uint64_t MotorGroup::get_position(std::initializer_list<int> indices) const {
  uint64_t position = 0;
  for (auto index : indices) {
    position += get_position(index);
  }
  position /= indices.size();
  return position;
}

Misc::W_t MotorGroup::get_power(int index) const {
  return pros::c::motor_get_power(std::get<0>(m_motor_ports[index]));
}

Misc::W_t MotorGroup::get_power(std::initializer_list<int> indices) const {
  Misc::W_t power = 0;
  for (auto index : indices) {
    power += get_power(index);
  }
  power /= indices.size();
  return power;
}

Misc::C_t MotorGroup::get_temperature(int index) const {
  return pros::c::motor_get_temperature(std::get<0>(m_motor_ports[index]));
}

Misc::C_t
MotorGroup::get_temperature(std::initializer_list<int> indices) const {
  Misc::C_t temperature = 0;
  for (auto index : indices) {
    temperature += get_temperature(index);
  }
  temperature /= indices.size();
  return temperature;
}

Misc::Nm_t MotorGroup::get_torque(int index) const {
  return pros::c::motor_get_torque(std::get<0>(m_motor_ports[index]));
}

Misc::Nm_t MotorGroup::get_torque(std::initializer_list<int> indices) const {
  Misc::Nm_t torque = 0;
  for (auto index : indices) {
    torque += get_torque(index);
  }
  torque /= indices.size();
  return torque;
}

//? methods
void MotorGroup::move(int joystick_val) const {
  for (auto motor_port : m_motor_ports) {
    pros::c::motor_move(std::get<0>(motor_port), joystick_val);
  }
}

void MotorGroup::move_absolute(Misc::rt_t position,
                               Misc::rpm_t velocity) const {
  for (auto motor_port : m_motor_ports) {
    pros::c::motor_move_absolute(std::get<0>(motor_port), position, velocity);
  }
}

void MotorGroup::move_relative(Misc::rt_t position,
                               Misc::rpm_t velocity) const {
  for (auto motor_port : m_motor_ports) {
    pros::c::motor_move_relative(std::get<0>(motor_port), position, velocity);
  }
}

void MotorGroup::move_velocity(Misc::rpm_t velocity) const {
  for (auto motor_port : m_motor_ports) {
    pros::c::motor_move_velocity(std::get<0>(motor_port), velocity);
  }
}

void MotorGroup::move_velocity(
    std::initializer_list<Misc::rpm_t> velocities) const {
  std::vector<Misc::rpm_t> velocities__{velocities};
  for (int i = 0; i < m_motor_ports.size(); i++) {
    pros::c::motor_move_velocity(std::get<0>(m_motor_ports[i]),
                                 velocities__[i]);
  }
}

void MotorGroup::move_voltage(Misc::mV_t voltage) const {
  for (auto motor_port : m_motor_ports) {
    pros::c::motor_move_voltage(std::get<0>(motor_port), voltage);
  }
}

void MotorGroup::move_voltage(
    std::initializer_list<Misc::mV_t> voltages) const {
  std::vector<Misc::mV_t> voltages__{voltages};
  for (int i = 0; i < m_motor_ports.size(); i++) {
    pros::c::motor_move_voltage(std::get<0>(m_motor_ports[i]), voltages__[i]);
  }
}

} // namespace Device
} // namespace Lib1104A
