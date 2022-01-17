//* operator control code

//* headers
#include "hardware/Arms.h"
#include "hardware/Globals.h"
#include "lib/control/PID.h"
#include "lib/control/filter/EMAFilter.h"
#include "lib/libApi.h"
#include "lib/misc/RobotConst.h"
#include "lib/util/Timer.h"
#include "main.h"
#include <algorithm>

//* function declarations
int deadzone(int value, int comp);
void driving(void);
void armsNaive(void);
void armsPID(void);
void liftPID(void);
void holderPID(void);
void conveyor(void);

//* mutexes
pros::Mutex obj_liftMutex;
pros::Mutex obj_holderMutex;

//* local variables
Hardware::e_armPositions liftPosition{Hardware::e_armPositions::E_STOW};
Hardware::e_armPositions holderPosition{Hardware::e_armPositions::E_STOW};
const double voltageRateArms{450.0};

//* opcontrol callback
void opcontrol() {
  pros::Task drivingFunction{driving};
  pros::Task armsFunction{/*armsNaive*/ armsPID};
  pros::Task liftFunction{liftPID};
  pros::Task holderFunction{holderPID};
  pros::Task conveyorFunction{conveyor};
  pros::Task armsFunctionPId{armsPID};
}

//? the other stuff

//* driving
void driving(void) {
  const int joystickDeadzone{10};

  while (!(pros::competition::is_autonomous() ||
           pros::competition::is_disabled())) {
    int power{deadzone(
        obj_controlMaster.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y),
        joystickDeadzone)},
        turn{deadzone(
            obj_controlMaster.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X),
            joystickDeadzone)};
    obj_chassis.driveJoystick(power + turn, power - turn);
    pros::delay(10);
  }
}

//* arms
void armsNaive(void) {
  using Hardware::e_armPositions;

  while (!(pros::competition::is_autonomous() ||
           pros::competition::is_disabled())) {

    if (obj_controlMaster.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
      obj_arms.setVelocity('l', 100);
    else if (obj_controlMaster.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
      obj_arms.setVelocity('l', -100);
    else
      obj_arms.setVelocity('l', 0);

    if (obj_controlMaster.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
      obj_arms.setVelocity('h', 100);
    else if (obj_controlMaster.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
      obj_arms.setVelocity('h', -100);
    else
      obj_arms.setVelocity('h', 0);

    pros::delay(10);
  }
}

//* lift
void armsPID(void) {
  while (!(pros::competition::is_autonomous() ||
           pros::competition::is_disabled())) {
    if (obj_controlMaster.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      obj_liftMutex.take(TIMEOUT_MAX);
      int foo = static_cast<int>(liftPosition);
      foo = (foo < 2) ? foo + 1 : 2;
      liftPosition = static_cast<Hardware::e_armPositions>(foo);
      obj_liftMutex.give();
    } else if (obj_controlMaster.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      obj_liftMutex.take(TIMEOUT_MAX);
      int foo = static_cast<int>(liftPosition);
      foo = (foo > 0) ? foo - 1 : 0;
      liftPosition = static_cast<Hardware::e_armPositions>(foo);
      obj_liftMutex.give();
    }

    if (obj_controlMaster.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
      obj_holderMutex.take(TIMEOUT_MAX);
      int foo = static_cast<int>(holderPosition);
      foo = (foo < 1) ? foo + 1 : 1;
      holderPosition = static_cast<Hardware::e_armPositions>(foo);
      obj_holderMutex.give();
    } else if (obj_controlMaster.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
      obj_holderMutex.take(TIMEOUT_MAX);
      int foo = static_cast<int>(holderPosition);
      foo = (foo > 0) ? foo - 1 : 0;
      holderPosition = static_cast<Hardware::e_armPositions>(foo);
      obj_holderMutex.give();
    }

    pros::delay(10);
  }
}

//* lift PID
void liftPID(void) {
  double old_voltage{0.0};
  Lib1104A::Control::PIDGains liftGains{0.1, 0.1, 0.1};
  Lib1104A::Control::EMAFilter *liftFilter =
      new Lib1104A::Control::EMAFilter(0.5);
  Lib1104A::Control::PID liftPID{liftGains, liftFilter};
  Lib1104A::Utility::Timer liftTimer{};

  obj_arms.tarePosition();
  liftPID.reset();

  while (!(pros::competition::is_autonomous() ||
           pros::competition::is_disabled())) {
    obj_liftMutex.take(TIMEOUT_MAX);
    int target = []() {
      if (liftPosition == Hardware::e_armPositions::E_STOW)
        return ARM_RESET_POSITION;
      else if (liftPosition == Hardware::e_armPositions::E_LOW)
        return LIFT_LOW_POSITION;
      else if (liftPosition == Hardware::e_armPositions::E_HIGH)
        return LIFT_HIGH_POSITION;

      return ARM_RESET_POSITION;
    }();
    liftPID.setTarget(target);
    obj_liftMutex.give();

    int travel = obj_arms.getPosition('l');
    double voltage =
        12'000.0 * liftPID.calculate(travel, liftTimer.getDtFromLast());
    voltage = std::clamp(voltage, old_voltage - voltageRateArms,
                         old_voltage + voltageRateArms);

    obj_arms.setVoltage('l', voltage);

    old_voltage = voltage;

    pros::delay(10);
  }
}

//* holder PID
void holderPID(void) {
  double old_voltage{0.0};
  Lib1104A::Control::PIDGains holderGains{0.1, 0.1, 0.1};
  Lib1104A::Control::EMAFilter *holderFilter =
      new Lib1104A::Control::EMAFilter(0.5);
  Lib1104A::Control::PID holderPID{holderGains, holderFilter};
  Lib1104A::Utility::Timer holderTimer{};

  obj_arms.tarePosition();
  holderPID.reset();

  while (!(pros::competition::is_autonomous() ||
           pros::competition::is_disabled())) {
    obj_holderMutex.take(TIMEOUT_MAX);
    int target = []() {
      if (holderPosition == Hardware::e_armPositions::E_STOW)
        return ARM_RESET_POSITION;
      else if (holderPosition == Hardware::e_armPositions::E_HIGH)
        return HOLDER_HIGH_POSITION;

      return ARM_RESET_POSITION;
    }();
    holderPID.setTarget(target);
    obj_holderMutex.give();

    int travel = obj_arms.getPosition('h');
    double voltage =
        12'000.0 * holderPID.calculate(travel, holderTimer.getDtFromLast());
    voltage = std::clamp(voltage, old_voltage - voltageRateArms,
                         old_voltage + voltageRateArms);

    obj_arms.setVoltage('h', voltage);

    old_voltage = voltage;

    pros::delay(10);
  }
}

//* conveyor
void conveyor(void) {
  while (!(pros::competition::is_autonomous() ||
           pros::competition::is_disabled())) {
    if (obj_controlMaster.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      obj_conveyor.setVelocity(CONVEYOR_MAX_VELOCITY);
    } else if (obj_controlMaster.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      obj_conveyor.setVelocity(-CONVEYOR_MAX_VELOCITY);
    } else {
      obj_conveyor.setVelocity(0);
    }
    pros::delay(10);
  }
}

//* deadzone func
int deadzone(int value, int comp) { return std::abs(value) < comp ? 0 : value; }
