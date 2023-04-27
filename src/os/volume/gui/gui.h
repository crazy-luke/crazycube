
/**
 * @file gui.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 适配 SquareLine_Studio 工程 CrazyCube__Volume, Export UI Files
 * 修改如下
 *  1. ui.h
 *      注释或删除函数 ui_VolumeScreen
 *      注释或删除 字体
 *      添加函数声明 ui_VolumeScreen_screen_init
 *
 *  2. ui.c
 *      注释 ui_VolumeScreen
 *      修改屏幕父类 ui_VolumePanel = lv_obj_create(lv_layer_sys());
 *      volume_hide_Animation增加 参数lv_anim_ready_cb_t ready_cb
 *                  lv_anim_set_ready_cb(&PropertyAnimation_0, ready_cb);
 * @version 1.0
 * @date 2022-09-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "ui.h"

bool ui_volumebar_exist() {
    return ui_VolumePanel != nullptr;
}

lv_obj_t* ui_init_volumebar() {
    ui_VolumeScreen_screen_init();
    lv_bar_set_range(ui_VolumeBar, 0,100);
    return  ui_VolumePanel;
}

void delete_volumebar(int delay) {
    volume_hide_Animation(ui_VolumePanel, delay,[](lv_anim_t* a){
       lv_obj_del(ui_VolumePanel);
       ui_VolumePanel = nullptr;
    });
}

void update_volumebar(int volume) {
  lv_bar_set_value(ui_VolumeBar, volume, LV_ANIM_OFF);
}

void update_volumebar_labe(const char* text){
    lv_label_set_text(ui_VolumeLabel, text);
}
