/**
 * @file gui.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 适配 SquareLine_Studio 工程 CrazyCube_Syspad_Mini, Export UI Files 修改如下
 *  1. ui.h
 *      注释或删除函数 ui_init
 *      注释或删除 字体
 *      添加函数声明 ui_SyspadMiniScreen_screen_init
 *
 *  2. ui.c
 *      注释或删除函数 ui_init
 *      修改屏幕父类 ui_SyspadMiniScreen = lv_obj_create(lv_layer_sys());
 * @version 1.0
 * @date 2022-09-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "ui.h"
#include "full/gui.h"

LV_IMG_DECLARE(ui_img_wifi_off_png);
LV_IMG_DECLARE(ui_img_wifi_on_png);
LV_IMG_DECLARE(ui_img_keyboard_png);

void ui_show_lock(bool flag) {
  if (flag)
    lv_obj_clear_flag(ui_SyspadMiniLockImage, LV_OBJ_FLAG_HIDDEN);
  else
    lv_obj_add_flag(ui_SyspadMiniLockImage, LV_OBJ_FLAG_HIDDEN);
}

void ui_set_lock_keyboard_mode(bool is_keyboard) {
  if (is_keyboard)
    lv_img_set_src(ui_SyspadMiniLockImage, &ui_img_keyboard_png);
  else
    lv_img_set_src(ui_SyspadMiniLockImage, &ui_img_lock_png);
}

void ui_show_wifi(bool flag) {
  if (flag)
    lv_obj_clear_flag(ui_SyspadMiniWifiImage, LV_OBJ_FLAG_HIDDEN);
  else
    lv_obj_add_flag(ui_SyspadMiniWifiImage, LV_OBJ_FLAG_HIDDEN);
}

void ui_show_assistant(bool flag) {
  if (flag)
    lv_obj_clear_flag(ui_SyspadMiniAssistantImage, LV_OBJ_FLAG_HIDDEN);
  else
    lv_obj_add_flag(ui_SyspadMiniAssistantImage, LV_OBJ_FLAG_HIDDEN);
}

void ui_show_mic_assistant(bool flag) {
  if (flag)
    lv_obj_clear_flag(ui_SyspadMiniMicImage, LV_OBJ_FLAG_HIDDEN);
  else
    lv_obj_add_flag(ui_SyspadMiniMicImage, LV_OBJ_FLAG_HIDDEN);
}


void ui_set_wifi_on(bool on) {
  if (on)
    lv_img_set_src(ui_SyspadMiniWifiImage, &ui_img_wifi_on_png);
  else
    lv_img_set_src(ui_SyspadMiniWifiImage, &ui_img_wifi_off_png);
}

void ui_shake_lock() { 
  lv_obj_set_x(ui_SyspadMiniLockImage, 20 );
  syspad_lock_shake_Animation(ui_SyspadMiniLockImage, 5);
}

// 初始化 sysbar 界面
lv_obj_t* ui_init_mini_syspad(void) {
  ui_SyspadMiniScreen_screen_init();
  lv_obj_set_size(ui_SyspadMiniScreen, LV_PCT(100), 30);
  lv_obj_set_y(ui_SyspadMiniPanel, -10);
  lv_obj_set_style_bg_opa(ui_SyspadMiniScreen, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  ui_show_wifi(false);
  ui_show_assistant(false);
  ui_show_mic_assistant(false);
  return ui_SyspadMiniScreen;
}

