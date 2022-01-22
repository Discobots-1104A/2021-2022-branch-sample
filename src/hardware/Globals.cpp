//* bad hardware shit
//* globals

//* le header
#include "hardware/Globals.h"
#include "Arms.h"
#include "lib/libApi.h"
#include "okapi/api.hpp"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"

//* motors and motor groups
okapi::Motor obj_driveLeftFront{16, false, okapi::AbstractMotor::gearset::green,
                                okapi::AbstractMotor::encoderUnits::counts};
okapi::Motor obj_driveLeftBack{19, false, okapi::AbstractMotor::gearset::green,
                               okapi::AbstractMotor::encoderUnits::counts};
okapi::Motor obj_driveRightFront{7, true, okapi::AbstractMotor::gearset::green,
                                 okapi::AbstractMotor::encoderUnits::counts};
okapi::Motor obj_driveRightBack{8, true, okapi::AbstractMotor::gearset::green,
                                okapi::AbstractMotor::encoderUnits::counts};
okapi::Motor obj_liftMotorOne{9, true, okapi::AbstractMotor::gearset::green,
                              okapi::AbstractMotor::encoderUnits::counts};
okapi::Motor obj_liftMotorTwo{20, false, okapi::AbstractMotor::gearset::green,
                              okapi::AbstractMotor::encoderUnits::counts};
okapi::Motor obj_holderMotor{17, false, okapi::AbstractMotor::gearset::green,
                             okapi::AbstractMotor::encoderUnits::counts};
okapi::Motor obj_conveyorMotor{6, false, okapi::AbstractMotor::gearset::green,
                               okapi::AbstractMotor::encoderUnits::counts};

okapi::MotorGroup obj_driveLeftMotors{obj_driveLeftFront, obj_driveLeftBack};
okapi::MotorGroup obj_driveRightMotors{obj_driveRightFront, obj_driveRightBack};
okapi::MotorGroup obj_liftMotors{obj_liftMotorOne, obj_liftMotorTwo};
okapi::MotorGroup obj_holderMotors{obj_holderMotor};
okapi::MotorGroup obj_conveyorMotors{obj_conveyorMotor};

//* pros hardware
pros::Controller obj_controlMaster{pros::E_CONTROLLER_MASTER};

//* my classes
Hardware::Chassis obj_chassis{obj_driveLeftMotors, obj_driveRightMotors};
Hardware::Arms obj_arms{obj_liftMotors, obj_holderMotors};
Hardware::Conveyor obj_conveyor{obj_conveyorMotors};