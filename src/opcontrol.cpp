//* operator control code

//* headers
#include "hardware/Globals.h"
#include "lib/libApi.h"
#include "main.h"

//* local globals for funnies
int joystickDeadzone{10};
int liftPosition{0};
int holderPosition{0};

//* function declarations
int deadzone(int value);
void driving(void);
void arms(void);

//* opcontrol callback
void opcontrol() {
  pros::Task drivingFunction{driving};
  pros::Task armsFunction{arms};
}

//? the other stuff

//* driving
void driving(void) {
  while (!(pros::competition::is_autonomous() ||
           pros::competition::is_disabled())) {
    int power{deadzone(
        obj_controlMaster.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y))},
        turn{deadzone(
            obj_controlMaster.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X))};
    obj_chassis.driveJoystick(power + turn, power - turn);
    pros::delay(10);
  }
}

//* arms
void arms(void) {
  using Hardware::e_armPositions;

  while (!(pros::competition::is_autonomous() ||
           pros::competition::is_disabled())) {
    if (obj_controlMaster.get_digital_new_press(
            pros::E_CONTROLLER_DIGITAL_L1) &&
        liftPosition < 2) {
      ++liftPosition;
    } else if (obj_controlMaster.get_digital_new_press(
                   pros::E_CONTROLLER_DIGITAL_L2) &&
               liftPosition > 0) {
      --liftPosition;
    } else if (obj_controlMaster.get_digital_new_press(
                   pros::E_CONTROLLER_DIGITAL_UP) &&
               holderPosition < 1) {
      ++holderPosition;
    } else if (obj_controlMaster.get_digital_new_press(
                   pros::E_CONTROLLER_DIGITAL_DOWN) &&
               holderPosition > 0) {
      --holderPosition;
    }

    if (liftPosition == 0) {
      obj_arms.setPosition('l', e_armPositions::E_STOW);
    } else if (liftPosition == 1) {
      obj_arms.setPosition('l', e_armPositions::E_LOW);
    } else if (liftPosition == 2) {
      obj_arms.setPosition('l', e_armPositions::E_HIGH);
    }

    if (holderPosition == 0) {
      obj_arms.setPosition('h', e_armPositions::E_STOW);
    } else if (holderPosition == 1) {
      obj_arms.setPosition('h', e_armPositions::E_HIGH);
    }

    pros::delay(10);
  }
}

//* deadzone func
int deadzone(int value) {
  return std::abs(value) < joystickDeadzone ? 0 : value;
}
