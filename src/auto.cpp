//* auto code

//* headers
#include "autos/autonomous.h"
#include "main.h"


namespace Autonomous {
e_autonomousSelection autonomousSelection;
}

//* auto callback
void autonomous() {
  switch (Autonomous::autonomousSelection) {
  case Autonomous::e_autonomousSelection::E_RED:
    Autonomous::redAuto();
    break;
  case Autonomous::e_autonomousSelection::E_BLUE:
    Autonomous::blueAuto();
    break;
  case Autonomous::e_autonomousSelection::E_SKILLS:
    Autonomous::skillsAuto();
    break;
  case Autonomous::e_autonomousSelection::E_TEST:
    Autonomous::testAuto();
    break;
  }
}