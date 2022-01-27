#pragma once

#include "guiGlobals.h"
#include "main.h"

// gui resources
namespace GUI {
    void drawSelector(void);
    extern lv_obj_t *autonomousSelectedLabel;
    extern lv_obj_t *trollImage;
    extern std::string autonomousSelectedText;
    extern std::string autonomousSelectedTextBuffer;
    extern const lv_img_dsc_t trollge;
}