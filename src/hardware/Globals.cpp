//* bad hardware shit
//* globals

//* le header
#include "hardware/Globals.h"
#include "lib/libApi.h"

//* pid gains
Lib1104A::Control::PIDGains obj_PIDGainsLift = {0.5, 0.001, 0.5, 0.0};
Lib1104A::Control::PIDGains obj_PIDGainsHolder = {0.5, 0.001, 0.5, 0.0};

//* motor groups
Lib1104A::Device::MotorGroup obj_leftMotors{{16, 19}};
Lib1104A::Device::MotorGroup obj_rightMotors{{-7, -8}};
Lib1104A::Device::MotorGroup obj_liftMotors{{-9, 20}};
Lib1104A::Device::MotorGroup obj_holderMotors{{17}};
Lib1104A::Device::MotorGroup obj_intakeMotors{{9}};

//* pros hardware
pros::Controller obj_controlMaster{pros::E_CONTROLLER_MASTER};

//* my classes
Hardware::Chassis obj_chassis{obj_leftMotors, obj_rightMotors};
Hardware::Arms obj_arms{obj_liftMotors, obj_holderMotors, obj_PIDGainsLift,
                        obj_PIDGainsHolder, 450, 450};
Hardware::Conveyor obj_conveyor{obj_intakeMotors};
