//* auto code

//* headers
#include "autos/autonomous.h"
#include "gui/guiGlobals.h"
#include "main.h"

namespace Autonomous {
e_autonomousSelection autonomousSelection;
int autonomousSelectionConfirmation = 0;
} // namespace Autonomous

//* auto callback
void autonomous() {
  GUI::autonomousSelectedTextBuffer =
      "Running auto: " + GUI::autonomousSelectedText;
  lv_label_set_text(GUI::autonomousSelectedLabel,
                    GUI::autonomousSelectedTextBuffer.c_str());
  lv_obj_align(GUI::autonomousSelectedLabel, NULL, LV_ALIGN_IN_TOP_MID, 0, 200);

  switch (Autonomous::autonomousSelection) {
  case Autonomous::e_autonomousSelection::E_LIVE:
    Autonomous::liveAuto();
    break;
  case Autonomous::e_autonomousSelection::E_SKILLS:
    Autonomous::skillsAuto();
    break;
  case Autonomous::e_autonomousSelection::E_TEST:
    Autonomous::testAuto();
    break;
  }
}