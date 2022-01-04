//* bad library
//* device
//* MotorGroup - controls a bunch of motors together because pee

//* header guard

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
  explicit MotorGroup(std::initializer_list<int> motor_ports,
                      pros::motor_brake_mode_e_t brake_mode = pros::E_MOTOR_BRAKE_COAST,
                      pros::motor_gearset_e_t gearset = pros::E_MOTOR_GEARSET_18,
                      pros::motor_encoder_units_e_t encoder_units = pros::E_MOTOR_ENCODER_COUNTS);
  virtual ~MotorGroup();

  //? setters
  MotorGroup &set_brake_mode(pros::motor_brake_mode_e_t mode);
  MotorGroup &set_reverse(void);
  MotorGroup &set_reverse(std::initializer_list<int> motor_rev_states);
  MotorGroup &tare_position(void);

  //? getters
  Misc::rpm_t get_velocity(int index) const;
  Misc::rpm_t get_velocity(std::initializer_list<int> indices) const;
  Misc::mA_t get_current(int index) const;
  Misc::mA_t get_current(std::initializer_list<int> indices) const;
  Misc::mV_t get_voltage(int index) const;
  Misc::mV_t get_voltage(std::initializer_list<int> indices) const;
  bool get_reversed(void) const;
  int32_t get_direction(int index) const;
  uint64_t get_position(int index) const;
  uint64_t get_position(std::initializer_list<int> indices) const;
  Misc::W_t get_power(int index) const;
  Misc::W_t get_power(std::initializer_list<int> indices) const;
  Misc::C_t get_temperature(int index) const;
  Misc::C_t get_temperature(std::initializer_list<int> indices) const;
  Misc::Nm_t get_torque(int index) const;
  Misc::Nm_t get_torque(std::initializer_list<int> indices) const;

  //? methods
  void move(int joystick_val) const;
  void move_absolute(int32_t position, Misc::rpm_t velocity) const;
  void move_relative(int32_t position, Misc::rpm_t velocity) const;
  void move_velocity(Misc::rpm_t velocity) const;
  void move_velocity(std::initializer_list<Misc::rpm_t> velocities) const;
  void move_voltage(Misc::mV_t voltage) const;
  void move_voltage(std::initializer_list<Misc::mV_t> voltages) const;

private:
  //? members
  std::vector<std::tuple<int, bool>> m_motor_ports;
  bool m_reverse_state_total;
  pros::motor_brake_mode_e_t m_brake_mode;
  pros::motor_gearset_e_t m_gearset;
  pros::motor_encoder_units_e_t m_encoder_units;

  //? private methods
  void set_gearset(pros::motor_gearset_e_t gearset);
  void set_encoder_units(pros::motor_encoder_units_e_t encoder_units);
};
} // namespace Device
} // namespace Lib1104A
