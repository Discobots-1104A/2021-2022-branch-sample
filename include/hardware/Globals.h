//* bad hardware shit
//* globals

//* header guard
#pragma once

//* pros api
#include "api.h"

//* other headers
#include "hardware/Arms.h"
#include "hardware/Chassis.h"
#include "hardware/Conveyor.h"

//* hardware stuffs
extern pros::Controller obj_controlMaster;
extern Hardware::Chassis obj_chassis;
extern Hardware::Arms obj_arms;
extern Hardware::Conveyor obj_conveyor;
