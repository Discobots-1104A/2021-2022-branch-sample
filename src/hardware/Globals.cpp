//* bad hardware shit
//* globals

//* le header
#include "hardware/Globals.h"
#include "lib/libApi.h"

//* motor groups
Lib1104A::Device::MotorGroup obj_leftMotors{{16, 19}};
Lib1104A::Device::MotorGroup obj_rightMotors{{-7, -8}};
Lib1104A::Device::MotorGroup obj_liftMotors{{-9, 20}, pros::E_MOTOR_BRAKE_HOLD};
Lib1104A::Device::MotorGroup obj_holderMotors{{17}, pros::E_MOTOR_BRAKE_HOLD};
Lib1104A::Device::MotorGroup obj_intakeMotors{{6}, pros::E_MOTOR_BRAKE_HOLD};

//* pros hardware
pros::Controller obj_controlMaster{pros::E_CONTROLLER_MASTER};

//* my classes
Hardware::Chassis obj_chassis{obj_leftMotors, obj_rightMotors};
Hardware::Arms obj_arms{obj_liftMotors, obj_holderMotors};
Hardware::Conveyor obj_conveyor{obj_intakeMotors};
