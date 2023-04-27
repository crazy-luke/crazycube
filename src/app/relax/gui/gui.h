/**
 * @file gui.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 适配 SquareLine_Studio 工程 CrazyCube_Relax, Export UI Files
 * 修改如下
 *  1. ui.h
 *      修改函数名称  ui_init -> ui_RelaxScreen_screen_init
 *      注释或删除 字体
 *  2. ui.c
 *      注释或删除函数 ui_init
 * @version 1.0
 * @date 2022-09-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "ui.h"

// 初始化界面
lv_obj_t* ui_init_Relax(void) {
  ui_RelaxScreen_screen_init();
  return ui_RelaxScreen;
}

void ui_relax_update_game(const char * title){
  lv_label_set_text(ui_GameTitleLabel, title);
}

void ui_relax_update_direction(const char * direction){
  lv_label_set_text(ui_RelaxDirectionLabel, direction);

}