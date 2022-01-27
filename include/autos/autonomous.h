#pragma once

// for autonomous stuff
namespace Autonomous {
enum class e_autonomousSelection {
  E_LIVE,
  E_SKILLS,
  E_TEST,
};

extern e_autonomousSelection autonomousSelection;
extern int autonomousSelectionConfirmation;

// autonomous callbacks
void liveAuto(void);
void skillsAuto(void);
void testAuto(void);

} // namespace Autonomous
