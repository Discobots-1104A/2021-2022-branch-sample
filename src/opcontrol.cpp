//* operator control code

//* headers
#include "hardware/Globals.h"
#include "lib/libApi.h"
#include "main.h"

//* function declarations
int deadzone(int value, int comp);
void driving(void);
void armsNaive(void);
void armsPID(void);
void conveyor(void);

//* opcontrol callback
void opcontrol() {
  pros::Task drivingFunction{driving};
  pros::Task armsFunction{armsNaive};
  pros::Task conveyorFunction{conveyor};
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

//* arms PID
void armsPID(void) {
  
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
