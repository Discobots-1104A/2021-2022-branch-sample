//* init code

//* headers
#include "hardware/Globals.h"
#include "lib/libApi.h"
#include "main.h"
#include "pros/llemu.hpp"
#include "lvgl_test.h"

//* function declarations
void armPositionReset(void);

//* init callback
void initialize() {
    setup_display();
    armPositionReset();
    obj_arms.tarePosition();
    obj_chassis.tarePosition();
}

//* comp init callback
void competition_initialize() {
    armPositionReset();
    obj_arms.tarePosition();
    obj_chassis.tarePosition();
}

//* disabled callback
void disabled() {}

//* arm position reset
void armPositionReset(void) {
    //* so we want to move the arms all the way back but we don't
    //* have a limit switch so
    //TODO: bug someone to get us a limit switch
    //TODO: make this work
}
