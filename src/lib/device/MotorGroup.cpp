//* bad library
//* device
//* MotorGroup - control da motor

//? i am wasting my time not using okapilib MotorGroup lmao!!!!!

//* headers
#include "lib/device/MotorGroup.h"

namespace Lib1104A {
namespace Device {

//? ctor & dtor
MotorGroup::MotorGroup(std::initializer_list<int> motorPorts,
                       pros::motor_brake_mode_e_t brakeMode,
                       pros::motor_gearset_e_t gearset,
                       pros::motor_encoder_units_e_t encoderUnits)
    : m_brakeMode(brakeMode), m_gearset(gearset),
      m_encoderUnits(encoderUnits) {
  for (int port : motorPorts) {
    m_motorPorts.push_back(
        std::make_tuple<int, bool>(std::abs(port), port < 0));
  }
  setBrakeMode(brakeMode);
  setGearset(gearset);
  setEncoderUnits(encoderUnits);
  setReverse(motorPorts);
  tarePosition();
}

MotorGroup::~MotorGroup() {
  // do nothing
}

//? private methods
void MotorGroup::setGearset(pros::motor_gearset_e_t gearset) {
  for (auto motor_port : m_motorPorts) {
    pros::c::motor_set_gearing(std::get<0>(motor_port), gearset);
  }
  m_gearset = gearset;
}

void MotorGroup::setEncoderUnits(
    pros::motor_encoder_units_e_t encoderUnits) {
  for (auto motor_port : m_motorPorts) {
    pros::c::motor_set_encoder_units(std::get<0>(motor_port), encoderUnits);
  }
  m_encoderUnits = encoderUnits;
}

//? setters
MotorGroup &MotorGroup::setBrakeMode(pros::motor_brake_mode_e_t mode) {
  for (auto motorPort : m_motorPorts) {
    pros::c::motor_set_brake_mode(std::get<0>(motorPort), mode);
  }
  m_brakeMode = mode;
  return *this;
}

MotorGroup &MotorGroup::setReverse(void) {
  m_reverseStateTotal = !m_reverseStateTotal;
  for (auto motorPort : m_motorPorts) {
    pros::c::motor_set_reversed(
        std::get<0>(motorPort),
        (std::get<1>(motorPort) == m_reverseStateTotal));
  }
  return *this;
}

//* This is catastropically bad, don't do this. Someone needs to fix this.
MotorGroup &
MotorGroup::setReverse(std::initializer_list<int> motorRevStates) {
  m_reverseStateTotal = false;
  for (auto motorPort : m_motorPorts) {
    auto iterator = std::find_if(
        motorRevStates.begin(), motorRevStates.end(),
        [&](int x) { return std::abs(x) == std::get<0>(motorPort); });

    if (iterator != motorRevStates.end()) {
      std::get<1>(motorPort) = (*iterator < 0);
      pros::c::motor_set_reversed(std::get<0>(motorPort),
                                  (std::get<1>(motorPort)));
    }
  }

  return *this;
}

MotorGroup &MotorGroup::tarePosition(void) {
  for (auto motorPort : m_motorPorts) {
    pros::c::motor_tare_position(std::get<0>(motorPort));
  }
  return *this;
}

//? getters
Misc::rpm_t MotorGroup::getVelocity(int index) const {
  return pros::c::motor_get_actual_velocity(std::get<0>(m_motorPorts[index]));
}

Misc::rpm_t MotorGroup::getVelocity(std::initializer_list<int> indices) const {
  Misc::rpm_t velocity = 0;
  for (auto index : indices) {
    velocity += getVelocity(index);
  }
  velocity /= indices.size();
  return velocity;
}

Misc::mA_t MotorGroup::getCurrent(int index) const {
  return pros::c::motor_get_current_draw(std::get<0>(m_motorPorts[index]));
}

Misc::mA_t MotorGroup::getCurrent(std::initializer_list<int> indices) const {
  Misc::mA_t current = 0;
  for (auto index : indices) {
    current += getCurrent(index);
  }
  current /= indices.size();
  return current;
}

Misc::mV_t MotorGroup::getVoltage(int index) const {
  return pros::c::motor_get_voltage(std::get<0>(m_motorPorts[index]));
}

Misc::mV_t MotorGroup::getVoltage(std::initializer_list<int> indices) const {
  Misc::mV_t voltage = 0;
  for (auto index : indices) {
    voltage += getVoltage(index);
  }
  voltage /= indices.size();
  return voltage;
}

bool MotorGroup::getReversed(void) const { return m_reverseStateTotal; }

int32_t MotorGroup::getDirection(int index) const {
  return pros::c::motor_get_direction(std::get<0>(m_motorPorts[index]));
}

Misc::rt_t MotorGroup::getPosition(int index) const {
  return pros::c::motor_get_position(std::get<0>(m_motorPorts[index]));
}

Misc::rt_t MotorGroup::getPosition(std::initializer_list<int> indices) const {
  Misc::rt_t position = 0;
  for (auto index : indices) {
    position += getPosition(index);
  }
  position /= indices.size();
  return position;
}

Misc::rt_t MotorGroup::getPosition(void) const {
  Misc::rt_t position = 0;
  for (auto motorPort : m_motorPorts) {
    position += getPosition(std::get<0>(motorPort));
  }
  position /= m_motorPorts.size();
  return position;
}

Misc::W_t MotorGroup::getPower(int index) const {
  return pros::c::motor_get_power(std::get<0>(m_motorPorts[index]));
}

Misc::W_t MotorGroup::getPower(std::initializer_list<int> indices) const {
  Misc::W_t power = 0;
  for (auto index : indices) {
    power += getPower(index);
  }
  power /= indices.size();
  return power;
}

Misc::C_t MotorGroup::getTemperature(int index) const {
  return pros::c::motor_get_temperature(std::get<0>(m_motorPorts[index]));
}

Misc::C_t
MotorGroup::getTemperature(std::initializer_list<int> indices) const {
  Misc::C_t temperature = 0;
  for (auto index : indices) {
    temperature += getTemperature(index);
  }
  temperature /= indices.size();
  return temperature;
}

Misc::Nm_t MotorGroup::getTorque(int index) const {
  return pros::c::motor_get_torque(std::get<0>(m_motorPorts[index]));
}

Misc::Nm_t MotorGroup::getTorque(std::initializer_list<int> indices) const {
  Misc::Nm_t torque = 0;
  for (auto index : indices) {
    torque += getTorque(index);
  }
  torque /= indices.size();
  return torque;
}

Misc::Nm_t MotorGroup::getTorque(void) const {
  Misc::Nm_t torque = 0;
  for (auto motorPort : m_motorPorts) {
    torque += getTorque(std::get<0>(motorPort));
  }
  torque /= m_motorPorts.size();
  return torque;
}

//? methods
void MotorGroup::move(int joystickVal) const {
  for (auto motorPort : m_motorPorts) {
    pros::c::motor_move(std::get<0>(motorPort), joystickVal);
  }
}

void MotorGroup::moveAbsolute(Misc::rt_t position,
                               Misc::rpm_t velocity) const {
  for (auto motorPort : m_motorPorts) {
    pros::c::motor_move_absolute(std::get<0>(motorPort), position, velocity);
  }
}

void MotorGroup::moveRelative(Misc::rt_t position,
                               Misc::rpm_t velocity) const {
  for (auto motorPort : m_motorPorts) {
    pros::c::motor_move_relative(std::get<0>(motorPort), position, velocity);
  }
}

void MotorGroup::moveVelocity(Misc::rpm_t velocity) const {
  for (auto motorPort : m_motorPorts) {
    pros::c::motor_move_velocity(std::get<0>(motorPort), velocity);
  }
}

void MotorGroup::moveVelocity(
    std::initializer_list<Misc::rpm_t> velocities) const {
  std::vector<Misc::rpm_t> velocities__{velocities};
  for (int i = 0; i < m_motorPorts.size(); i++) {
    pros::c::motor_move_velocity(std::get<0>(m_motorPorts[i]),
                                 velocities__[i]);
  }
}

void MotorGroup::moveVoltage(Misc::mV_t voltage) const {
  for (auto motorPort : m_motorPorts) {
    pros::c::motor_move_voltage(std::get<0>(motorPort), voltage);
  }
}

void MotorGroup::moveVoltage(
    std::initializer_list<Misc::mV_t> voltages) const {
  std::vector<Misc::mV_t> voltages__{voltages};
  for (int i = 0; i < m_motorPorts.size(); i++) {
    pros::c::motor_move_voltage(std::get<0>(m_motorPorts[i]), voltages__[i]);
  }
}

} // namespace Device
} // namespace Lib1104A
