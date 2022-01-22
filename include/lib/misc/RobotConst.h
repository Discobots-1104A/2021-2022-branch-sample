//* bad library
//* utility
//* robot constants - for math calculations

//* header guard
#pragma once

//* definitions

// constants
#define M_PI 3.14159265358979323846 // pi

// distance to robot ticks constant
#define DIST_IN_TO_TICKS_CONSTANT 900.0 / (4.0 * M_PI)
#define DIST_M_TO_TICKS_CONSTANT 900.0 / ((4.0 / 39.37) * M_PI)

// null constants for constructing shit i dont need in other constructors
#define NULL_ADI_PORT 8
#define NULL_SMART_PORT 21

// arm positions in ticks
#define LIFT_RESET_POSITION 100.0
#define LIFT_HIGH_POSITION 2070.0
#define LIFT_LOW_POSITION 1350.0
#define LIFT_ZERO_TORQUE 0.5
#define HOLDER_RESET_POSITION 10.0
#define HOLDER_HIGH_POSITION 1020.0

// max velocities for subsystems
#define LIFT_MAX_VELOCITY 200
#define HOLDER_MAX_VELOCITY 200
#define CONVEYOR_MAX_VELOCITY 200

// drive shit
#define DRIVE_MAX_VELOCITY 200
