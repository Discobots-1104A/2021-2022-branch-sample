//* bad library
//* device
//* MotorGroup - control da motor

//? i am wasting my time not using okapilib MotorGroup lmao!!!!!

//* headers
#include "lib/device/MotorGroup.h"

namespace Lib1104A {
namespace Device {

//? ctor & dtor
MotorGroup::MotorGroup(std::initializer_list<pros::Motor *> motors)
    : m_motors(motors) {
  // do nothing
}

MotorGroup::~MotorGroup() {
  for (auto motor : m_motors) {
    motor = nullptr;
  }
}

//? setters
MotorGroup &MotorGroup::set_brake_mode(pros::motor_brake_mode_e_t mode) {
  for (auto motor : m_motors) {
    motor->set_brake_mode(mode);
  }
  return *this;
}

MotorGroup &MotorGroup::set_reverse(bool reversed) {
  for (auto motor : m_motors) {
    motor->set_reversed(reversed);
  }
  return *this;
}

MotorGroup &MotorGroup::tare_position() {
  for (auto motor : m_motors) {
    motor->tare_position();
  }
  return *this;
}

//? getters
Misc::rpm_t MotorGroup::get_vel(int index) const {
  return m_motors[index]->get_actual_velocity();
}

Misc::rpm_t MotorGroup::get_vel(std::initializer_list<int> indices) const {
  Misc::rpm_t vel = 0;
  for (auto index : indices) {
    vel += m_motors[index]->get_actual_velocity();
  }
  vel /= indices.size();
  return vel;
}

Misc::mA_t MotorGroup::get_current(int index) const {
  return m_motors[index]->get_current_draw();
}

Misc::mA_t MotorGroup::get_current(std::initializer_list<int> indices) const {
  Misc::mA_t current = 0;
  for (auto index : indices) {
    current += m_motors[index]->get_current_draw();
  }
  current /= indices.size();
  return current;
}

Misc::mV_t MotorGroup::get_voltage(int index) const {
  return m_motors[index]->get_voltage();
}

Misc::mV_t MotorGroup::get_voltage(std::initializer_list<int> indices) const {
  Misc::mV_t voltage = 0;
  for (auto index : indices) {
    voltage += m_motors[index]->get_voltage();
  }
  voltage /= indices.size();
  return voltage;
}

int32_t MotorGroup::get_direction(int index) const {
  return m_motors[index]->get_direction();
}

uint64_t MotorGroup::get_position(int index) const {
  return m_motors[index]->get_position();
}

uint64_t MotorGroup::get_position(std::initializer_list<int> indices) const {
  double position = 0.0;
  for (auto index : indices) {
    position += m_motors[index]->get_position();
  }
  position /= indices.size();
  return (uint64_t)std::round(position);
}

Misc::W_t MotorGroup::get_power(int index) const {
  return m_motors[index]->get_power();
}

Misc::W_t MotorGroup::get_power(std::initializer_list<int> indices) const {
  Misc::W_t power = 0.0;
  for (auto index : indices) {
    power += m_motors[index]->get_power();
  }
  power /= indices.size();
  return power;
}

Misc::C_t MotorGroup::get_torque(int index) const {
  return m_motors[index]->get_torque();
}

Misc::C_t MotorGroup::get_torque(std::initializer_list<int> indices) const {
  Misc::C_t torque = 0.0;
  for (auto index : indices) {
    torque += m_motors[index]->get_torque();
  }
  torque /= indices.size();
  return torque;
}

//? methods
void MotorGroup::move(int voltage) {
  for (auto motor : m_motors) {
    motor->move(voltage);
  }
}

void MotorGroup::move_abs(double position, int velocity) {
  for (auto motor : m_motors) {
    motor->move_absolute(position, velocity);
  }
}

void MotorGroup::move_rel(double position, int velocity) {
  for (auto motor : m_motors) {
    motor->move_relative(position, velocity);
  }
}

void MotorGroup::move_vel(int velocity) {
  for (auto motor : m_motors) {
    motor->move_velocity(velocity);
  }
}

void MotorGroup::move_vol(int voltage) {
  for (auto motor : m_motors) {
    motor->move_voltage(voltage);
  }
}

} // namespace Device
} // namespace Lib1104A
