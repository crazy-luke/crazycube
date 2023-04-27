#pragma once

#include "lv/lv_helper.h"
#include "ui.h"

lv_obj_t* ui_init_Photo(void) {
  ui_PhotoScreen_screen_init();
  return ui_PhotoScreen;
}
void ui_set_Photo(String filepath) {
  lv_img_set_src(ui_PhotoImge, FILEPATH_SPIFF_LVGL(filepath));
}