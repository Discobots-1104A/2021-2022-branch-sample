//* operator control code

//* headers
#include "hardware/Arms.h"
#include "hardware/Globals.h"
#include "lib/control/PID.h"
#include "lib/control/filter/AbstractFilter.h"
#include "lib/control/filter/EMAFilter.h"
#include "lib/control/filter/PassthroughFilter.h"
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
  pros::Task armsFunction{armsPID};
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
    if (obj_controlMaster.get_digital_new_press(
            pros::E_CONTROLLER_DIGITAL_L1)) {
      obj_liftMutex.take(TIMEOUT_MAX);
      std::cout << "[armPID] took mutex and incrementing position" << std::endl;
      int foo = static_cast<int>(liftPosition);
      foo = (foo < 2) ? foo + 1 : 2;
      liftPosition = static_cast<Hardware::e_armPositions>(foo);
      obj_liftMutex.give();
    } else if (obj_controlMaster.get_digital_new_press(
                   pros::E_CONTROLLER_DIGITAL_L2)) {
      obj_liftMutex.take(TIMEOUT_MAX);
      std::cout << "[armPID] took mutex and decrementing position" << std::endl;
      int foo = static_cast<int>(liftPosition);
      foo = (foo > 0) ? foo - 1 : 0;
      liftPosition = static_cast<Hardware::e_armPositions>(foo);
      obj_liftMutex.give();
    }

    // if (obj_controlMaster.get_digital_new_press(
    //         pros::E_CONTROLLER_DIGITAL_UP)) {
    //   obj_holderMutex.take(TIMEOUT_MAX);
    //   int foo = static_cast<int>(holderPosition);
    //   foo = (foo < 1) ? foo + 1 : 1;
    //   holderPosition = static_cast<Hardware::e_armPositions>(foo);
    //   obj_holderMutex.give();
    // } else if (obj_controlMaster.get_digital_new_press(
    //                pros::E_CONTROLLER_DIGITAL_DOWN)) {
    //   obj_holderMutex.take(TIMEOUT_MAX);
    //   int foo = static_cast<int>(holderPosition);
    //   foo = (foo > 0) ? foo - 1 : 0;
    //   holderPosition = static_cast<Hardware::e_armPositions>(foo);
    //   obj_holderMutex.give();
    // }

    pros::delay(10);
  }
}

//* lift PID
void liftPID(void) {
  double oldVoltage{0.0};
  Lib1104A::Control::PIDGains liftGains{3.0, 0.01, 0.5};
  Lib1104A::Control::AbstractFilter *liftFilter =
      new Lib1104A::Control::PassthroughFilter();
  Lib1104A::Control::PID liftPID{liftGains, liftFilter};
  const int deadzoneZero{20};

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
    obj_liftMutex.give();

    liftPID.setTarget(target);

    rt_t travel = obj_arms.getPosition('l');
    double voltage = 12'000 * liftPID.calculate(travel, 10);

    voltage = std::clamp(voltage, oldVoltage - voltageRateArms,
                         oldVoltage + voltageRateArms);

    //* if our target is zero then we must handle this differently
    if (target == ARM_RESET_POSITION && deadzone(travel, deadzoneZero)) {
      voltage = -5'000;
    } else if (target == ARM_RESET_POSITION && !deadzone(travel, deadzoneZero)) {
      voltage = 0;
    }

    obj_arms.setVoltage('l', voltage);

    oldVoltage = voltage;

    pros::delay(10);
  }
}

//* holder PID
void holderPID(void) {
  while (!(pros::competition::is_autonomous() ||
           pros::competition::is_disabled())) {
    //TODO: this is temporary until we add more sensors to the holder
    if (obj_controlMaster.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
      obj_arms.setVelocity('h', 100);
    else if (obj_controlMaster.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
      obj_arms.setVelocity('h', -100);
    else
      obj_arms.setVelocity('h', 0);

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
