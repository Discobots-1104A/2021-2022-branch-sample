//* bad library
//* device
//* MotorGroup - controls a bunch of motors together because pee

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers
#include "lib/misc/Units.h"

//* stl
#include <initializer_list>
#include <vector>
#include <tuple>


namespace Lib1104A {
namespace Device {

class MotorGroup {
public:
  //? ctor & dtor
  explicit MotorGroup(std::initializer_list<int> motorPorts,
                      pros::motor_brake_mode_e_t brakeMode = pros::E_MOTOR_BRAKE_COAST,
                      pros::motor_gearset_e_t gearset = pros::E_MOTOR_GEARSET_18,
                      pros::motor_encoder_units_e_t encoderUnits = pros::E_MOTOR_ENCODER_COUNTS);
  virtual ~MotorGroup();

  //? setters
  MotorGroup &setBrakeMode(pros::motor_brake_mode_e_t mode);
  MotorGroup &setReverse(void);
  MotorGroup &setReverse(std::initializer_list<int> motorRevStates);
  MotorGroup &tarePosition(void);

  //? getters
  Misc::rpm_t getVelocity(int index) const;
  Misc::rpm_t getVelocity(std::initializer_list<int> indices) const;
  Misc::mA_t getCurrent(int index) const;
  Misc::mA_t getCurrent(std::initializer_list<int> indices) const;
  Misc::mV_t getVoltage(int index) const;
  Misc::mV_t getVoltage(std::initializer_list<int> indices) const;
  bool getReversed(void) const;
  int32_t getDirection(int index) const;
  Misc::rt_t getPosition(int index) const;
  Misc::rt_t getPosition(std::initializer_list<int> indices) const;
  Misc::rt_t getPosition(void) const; // all of them
  Misc::W_t getPower(int index) const;
  Misc::W_t getPower(std::initializer_list<int> indices) const;
  Misc::C_t getTemperature(int index) const;
  Misc::C_t getTemperature(std::initializer_list<int> indices) const;
  Misc::Nm_t getTorque(int index) const;
  Misc::Nm_t getTorque(std::initializer_list<int> indices) const;
  Misc::Nm_t getTorque(void) const; // all of them

  //? methods
  void move(int joystickVal) const;
  void moveAbsolute(Misc::rt_t position, Misc::rpm_t velocity) const;
  void moveRelative(Misc::rt_t position, Misc::rpm_t velocity) const;
  void moveVelocity(Misc::rpm_t velocity) const;
  void moveVelocity(std::initializer_list<Misc::rpm_t> velocities) const;
  void moveVoltage(Misc::mV_t voltage) const;
  void moveVoltage(std::initializer_list<Misc::mV_t> voltages) const;

private:
  //? members
  std::vector<std::tuple<int, bool>> m_motorPorts;
  bool m_reverseStateTotal;
  pros::motor_brake_mode_e_t m_brakeMode;
  pros::motor_gearset_e_t m_gearset;
  pros::motor_encoder_units_e_t m_encoderUnits;

  //? private methods
  void setGearset(pros::motor_gearset_e_t gearset);
  void setEncoderUnits(pros::motor_encoder_units_e_t encoderUnits);
};
} // namespace Device
} // namespace Lib1104A
