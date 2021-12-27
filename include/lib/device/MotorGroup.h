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


namespace Lib1104A {
namespace Device {

class MotorGroup {
public:
  //? ctor & dtor
  explicit MotorGroup(std::initializer_list<pros::Motor *> motors);
  ~MotorGroup();

  //? setters
  MotorGroup &set_brake_mode(pros::motor_brake_mode_e_t mode);
  MotorGroup &set_reverse(bool reverse);
  MotorGroup &tare_position();

  //? getters
  Misc::rpm_t get_vel(int index) const;
  Misc::rpm_t get_vel(std::initializer_list<int> indices) const;
  Misc::mA_t get_current(int index) const;
  Misc::mA_t get_current(std::initializer_list<int> indices) const;
  Misc::mV_t get_voltage(int index) const;
  Misc::mV_t get_voltage(std::initializer_list<int> indices) const;
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
  void move(int voltage);
  void move_abs(double position, int velocity);
  void move_rel(double position, int velocity);
  void move_vel(int velocity);
  void move_vol(int voltage);

private:
  //? members
  std::vector<pros::Motor *> m_motors;

  //? private methods
};
} // namespace Device
} // namespace Lib1104A
