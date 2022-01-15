//* init code

//* headers
#include "hardware/Globals.h"
#include "lib/libApi.h"
#include "main.h"

//* init callback
void initialize() {
    obj_arms.tarePosition();
    obj_chassis.tarePosition();
}

//* comp init callback
void competition_initialize() {}

//* disabled callback
void disabled() {}
