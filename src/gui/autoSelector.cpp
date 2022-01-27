//* autonomous selector

#include "autos/autonomous.h"
#include "display/lv_core/lv_obj.h"
#include "display/lv_core/lv_style.h"
#include "display/lv_hal/lv_hal_disp.h"
#include "display/lv_misc/lv_color.h"
#include "display/lv_objx/lv_btn.h"
#include "display/lv_objx/lv_label.h"
#include "gui/guiGlobals.h"
#include "pros/rtos.hpp"
#include <cstdio>

namespace GUI {
// objects
lv_obj_t *liveAutoButton;
lv_obj_t *skillsAutoButton;
lv_obj_t *testAutoButton;
lv_obj_t *autoSelectButton;
lv_obj_t *liveAutoButtonLabel;
lv_obj_t *skillsAutoButtonLabel;
lv_obj_t *testAutoButtonLabel;
lv_obj_t *autoSelectButtonLabel;
lv_obj_t *autonomousSelectedLabel;
lv_obj_t *trollImage;

lv_style_t *autonomousButtonStyle;
lv_style_t *autonomousConfirmButtonStyle;

std::string autonomousSelectedText = "NONE";
std::string autonomousSelectedTextBuffer = {};
std::string autoSelectButtonLabelBuffer = {};

// function declarations
lv_style_t *createButtonStyle(lv_style_t *copy, lv_color_t rel, lv_color_t pr,
                              lv_color_t textColor, lv_color_t borderColor,
                              lv_coord_t borderWidth);
lv_res_t selectAutonomous(lv_obj_t *btn);
lv_res_t confirmAutonomousSelection(lv_obj_t *btn);

// gui drawing
void drawSelector(void) {
  autonomousButtonStyle = createButtonStyle(
      &lv_style_plain, LV_COLOR_MAKE(128, 128, 128),
      LV_COLOR_MAKE(192, 192, 192), LV_COLOR_MAKE(255, 255, 255),
      LV_COLOR_MAKE(0, 0, 0), 2);
  autonomousConfirmButtonStyle = createButtonStyle(
      &lv_style_plain, LV_COLOR_MAKE(255, 70, 70), LV_COLOR_MAKE(255, 102, 102),
      LV_COLOR_MAKE(255, 255, 255), LV_COLOR_MAKE(0, 0, 0), 2);

  liveAutoButton = lv_btn_create(lv_scr_act(), NULL);
  skillsAutoButton = lv_btn_create(lv_scr_act(), NULL);
  testAutoButton = lv_btn_create(lv_scr_act(), NULL);
  autoSelectButton = lv_btn_create(lv_scr_act(), NULL);

  lv_obj_set_free_num(liveAutoButton, 0);
  lv_obj_set_free_num(skillsAutoButton, 1);
  lv_obj_set_free_num(testAutoButton, 2);
  lv_obj_set_free_num(autoSelectButton, 3);

  lv_btn_set_action(liveAutoButton, LV_BTN_ACTION_CLICK, selectAutonomous);
  lv_btn_set_action(skillsAutoButton, LV_BTN_ACTION_CLICK, selectAutonomous);
  lv_btn_set_action(testAutoButton, LV_BTN_ACTION_CLICK, selectAutonomous);
  lv_btn_set_action(autoSelectButton, LV_BTN_ACTION_CLICK,
                    confirmAutonomousSelection);

  lv_btn_set_style(liveAutoButton, LV_BTN_STYLE_REL, &autonomousButtonStyle[0]);
  lv_btn_set_style(skillsAutoButton, LV_BTN_STYLE_REL,
                   &autonomousButtonStyle[0]);
  lv_btn_set_style(testAutoButton, LV_BTN_STYLE_REL, &autonomousButtonStyle[0]);
  lv_btn_set_style(liveAutoButton, LV_BTN_STYLE_PR, &autonomousButtonStyle[1]);
  lv_btn_set_style(skillsAutoButton, LV_BTN_STYLE_PR,
                   &autonomousButtonStyle[1]);
  lv_btn_set_style(testAutoButton, LV_BTN_STYLE_PR, &autonomousButtonStyle[1]);
  lv_btn_set_style(autoSelectButton, LV_BTN_STYLE_REL,
                   &autonomousConfirmButtonStyle[0]);
  lv_btn_set_style(autoSelectButton, LV_BTN_STYLE_PR,
                   &autonomousConfirmButtonStyle[1]);

  lv_obj_set_size(liveAutoButton, 160, 50);
  lv_obj_set_size(skillsAutoButton, 160, 50);
  lv_obj_set_size(testAutoButton, 160, 50);
  lv_obj_set_size(autoSelectButton, 480, 50);

  lv_obj_align(liveAutoButton, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  lv_obj_align(skillsAutoButton, NULL, LV_ALIGN_IN_TOP_LEFT, 160, 0);
  lv_obj_align(testAutoButton, NULL, LV_ALIGN_IN_TOP_LEFT, 320, 0);
  lv_obj_align(autoSelectButton, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 50);

  liveAutoButtonLabel = lv_label_create(liveAutoButton, NULL);
  skillsAutoButtonLabel = lv_label_create(skillsAutoButton, NULL);
  testAutoButtonLabel = lv_label_create(testAutoButton, NULL);
  autoSelectButtonLabel = lv_label_create(autoSelectButton, NULL);
  lv_label_set_text(liveAutoButtonLabel, "Live");
  lv_label_set_text(skillsAutoButtonLabel, "Skills");
  lv_label_set_text(testAutoButtonLabel, "Test");
  lv_label_set_text(autoSelectButtonLabel, "Confirm Selection");

  autonomousSelectedLabel = lv_label_create(lv_scr_act(), NULL);
  autonomousSelectedTextBuffer =
      "Autonomous selected: " + autonomousSelectedText;
  lv_label_set_text(autonomousSelectedLabel,
                    autonomousSelectedTextBuffer.c_str());
  lv_obj_align(autonomousSelectedLabel, NULL, LV_ALIGN_CENTER, 0, 45);
}

// function definitions
lv_style_t *createButtonStyle(lv_style_t *copy, lv_color_t rel, lv_color_t pr,
                              lv_color_t textColor, lv_color_t borderColor,
                              lv_coord_t borderWidth) {
  lv_style_t *buttonStyle = (lv_style_t *)malloc(sizeof(lv_style_t) * 2);
  for (int i = 0; i < 2; ++i) {
    lv_style_copy(&buttonStyle[i], copy);
  }

  buttonStyle[0].body.main_color = rel;
  buttonStyle[0].body.grad_color = rel;
  buttonStyle[0].body.border.color = borderColor;
  buttonStyle[0].body.border.width = borderWidth;
  buttonStyle[0].text.color = textColor;

  buttonStyle[1].body.main_color = pr;
  buttonStyle[1].body.grad_color = pr;
  buttonStyle[1].body.border.color = borderColor;
  buttonStyle[1].body.border.width = borderWidth;
  buttonStyle[1].text.color = textColor;

  return buttonStyle;
}

lv_res_t selectAutonomous(lv_obj_t *btn) {
  uint8_t id = lv_obj_get_free_num(btn);
  switch (id) {
  case 0:
    Autonomous::autonomousSelection = Autonomous::e_autonomousSelection::E_LIVE;
    autonomousSelectedText = "LIVE";
    autonomousSelectedTextBuffer =
        "Autonomous selected: " + autonomousSelectedText;
    lv_label_set_text(autonomousSelectedLabel,
                      autonomousSelectedTextBuffer.c_str());
    lv_obj_align(autonomousSelectedLabel, NULL, LV_ALIGN_CENTER, 0, 45);
    break;
  case 1:
    Autonomous::autonomousSelection =
        Autonomous::e_autonomousSelection::E_SKILLS;
    autonomousSelectedText = "SKILLS";
    autonomousSelectedTextBuffer =
        "Autonomous selected: " + autonomousSelectedText;
    lv_label_set_text(autonomousSelectedLabel,
                      autonomousSelectedTextBuffer.c_str());
    lv_obj_align(autonomousSelectedLabel, NULL, LV_ALIGN_CENTER, 0, 45);
    break;
  case 2:
    Autonomous::autonomousSelection = Autonomous::e_autonomousSelection::E_TEST;
    autonomousSelectedText = "TEST";
    autonomousSelectedTextBuffer =
        "Autonomous selected: " + autonomousSelectedText;
    lv_label_set_text(autonomousSelectedLabel,
                      autonomousSelectedTextBuffer.c_str());
    lv_obj_align(autonomousSelectedLabel, NULL, LV_ALIGN_CENTER, 0, 45);
    break;
  }

  return LV_RES_OK;
}

lv_res_t confirmAutonomousSelection(lv_obj_t *btn) {
  if (Autonomous::autonomousSelection == Autonomous::e_autonomousSelection::E_NONE) {
    autoSelectButtonLabelBuffer = "No autonomous selected.";
    lv_label_set_text(autoSelectButtonLabel,
                      autoSelectButtonLabelBuffer.c_str());
    return LV_RES_OK;
  }

  if (Autonomous::autonomousSelectionConfirmation == 0) {
    ++Autonomous::autonomousSelectionConfirmation;
    autoSelectButtonLabelBuffer = "Confirm selected? " + autonomousSelectedText;
    lv_label_set_text(autoSelectButtonLabel,
                      autoSelectButtonLabelBuffer.c_str());
  } else if (Autonomous::autonomousSelectionConfirmation == 1) {
    Autonomous::autonomousSelectionConfirmation = 2;
  }

  return LV_RES_OK;
}

} // namespace GUI
