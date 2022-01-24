//testing how lvgl works and shit

#include "lvgl_test.h"
#include "trollge.h"

void setup_display() {
    lv_obj_t *trollge_img = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(trollge_img, &trollge);
    lv_obj_set_size(trollge_img, 300, 200);
    lv_obj_align(trollge_img, NULL, LV_ALIGN_CENTER, 0, 0);
}
