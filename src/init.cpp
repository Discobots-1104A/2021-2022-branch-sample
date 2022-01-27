//* init code

//* headers
#include "autos/autonomous.h"
#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_label.h"
#include "gui/guiGlobals.h"
#include "hardware/Globals.h"
#include "lib/libApi.h"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"

//* function declarations
void armPositionReset(void);
void waitForSelection(void);

//* init callback
void initialize() {
  armPositionReset();
  obj_arms.tarePosition();
  obj_chassis.tarePosition();
  GUI::drawSelector();
  waitForSelection();
}

//* comp init callback
void competition_initialize() {
  armPositionReset();
  obj_arms.tarePosition();
  obj_chassis.tarePosition();
}

//* disabled callback
void disabled() {
  lv_label_set_text(GUI::autonomousSelectedLabel, "Disabled.");
  lv_obj_align(GUI::autonomousSelectedLabel, NULL, LV_ALIGN_IN_TOP_MID, 0, 200);
}

//* arm position reset
void armPositionReset(void) {
  //* so we want to move the arms all the way back but we don't
  //* have a limit switch so
  // TODO: bug someone to get us a limit switch
  // TODO: make this work
}

//* wait for selection
void waitForSelection(void) {
  while (1) {
    if (Autonomous::autonomousSelectionConfirmation == 2) {
      lv_obj_clean(lv_scr_act());
      GUI::trollImage = lv_img_create(lv_scr_act(), NULL);
      lv_img_set_src(GUI::trollImage, &GUI::trollge);
      lv_obj_set_size(GUI::trollImage, 400, 175);
      lv_obj_align(GUI::trollImage, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
      GUI::autonomousSelectedLabel = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(GUI::autonomousSelectedLabel, " ");
      lv_obj_align(GUI::autonomousSelectedLabel, NULL, LV_ALIGN_IN_TOP_MID, 0,
                   200);
      break;
    }
    pros::delay(10);
  }
}
