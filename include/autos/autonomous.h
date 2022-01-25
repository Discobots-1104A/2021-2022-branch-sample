#pragma once

// for autonomous stuff
namespace Autonomous {
enum class e_autonomousSelection {
  E_RED,
  E_BLUE,
  E_SKILLS,
  E_TEST,
};

extern e_autonomousSelection autonomousSelection;

// autonomous callbacks
void redAuto(void);
void blueAuto(void);
void skillsAuto(void);
void testAuto(void);

} // namespace Autonomous
