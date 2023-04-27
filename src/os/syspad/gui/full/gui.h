
/**
 * @file gui.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 适配 SquareLine_Studio 工程 CrazyCube_Syspad_Full, Export UI Files
 * 修改如下
 *  1. ui.h
 *      注释或删除函数 ui_init
 *      注释或删除 字体
 *      添加函数声明 ui_SyspadFullScreen_screen_init
 *
 *  2. ui.c
 *      注释或删除函数 ui_init
 *      修改屏幕父类 ui_SyspadFullScreen = lv_obj_create(lv_layer_sys());
 * @version 1.0
 * @date 2022-09-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <vector>

#include "framework/system/display.h"
#include "framework/system/led.h"
#include "framework/system/speaker.h"
#include "framework/system/sys.h"
#include "ui.h"

void ui_show_hit_left(bool flag) {
  if (flag)
    lv_obj_clear_flag(ui_SyspadHintLeftImage, LV_OBJ_FLAG_HIDDEN);
  else
    lv_obj_add_flag(ui_SyspadHintLeftImage, LV_OBJ_FLAG_HIDDEN);
}

void ui_show_hit_right(bool flag) {
  if (flag)
    lv_obj_clear_flag(ui_SyspadHintRightImage, LV_OBJ_FLAG_HIDDEN);
  else
    lv_obj_add_flag(ui_SyspadHintRightImage, LV_OBJ_FLAG_HIDDEN);
}

void ui_show_hit_lr_text(bool flag) {
  if (flag)
    lv_obj_clear_flag(ui_SyspadPanelHint2, LV_OBJ_FLAG_HIDDEN);
  else
    lv_obj_add_flag(ui_SyspadPanelHint2, LV_OBJ_FLAG_HIDDEN);
}

void ui_set_hint_debug(const char * text) {
  lv_label_set_text(ui_SyspadAboutDebugLabel,text);
}

lv_obj_t* ui_init_full_syspad() {
  ui_SyspadFullScreen_screen_init();
  lv_bar_set_value(ui_SyspadVolumeBar, 0, LV_ANIM_OFF);
  lv_bar_set_range(ui_SyspadVolumeBar, 0, MAX_VOLUME);
  lv_bar_set_range(ui_SyspadBrightnessBar, 0, MAX_BRIGHTNESS);
  lv_bar_set_range(ui_SyspadLEDBar, 0, MAX_LED_LIGHT);

  lv_obj_set_size(ui_SyspadFullScreen, LV_PCT(100), LV_PCT(100));
  lv_obj_set_style_pad_all(ui_SyspadFullScreen, 0,
                           LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_SyspadFullScreen, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_clear_flag(ui_SyspadHintPanel, LV_OBJ_FLAG_HIDDEN);

  lv_obj_add_flag(ui_SyspadVolumePanel, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_SyspadBrightnessPanel, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_SyspadManualPanel, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_SyspadLEDPanel, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_SyspadAboutPanel, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_SyspadKeyboardPanel, LV_OBJ_FLAG_HIDDEN);

  String v = "超级立方豆\nv:"+ FIRMWARE_VERSION_NAME +"\n作者:疯狂豆®";
  lv_label_set_text(ui_SyspadAboutLabel,v.c_str());

  return ui_SyspadFullScreen;
}

void ui_set_volume(int volume, bool anim = true) {
  lv_anim_enable_t lv_anim = anim ? LV_ANIM_ON : LV_ANIM_OFF;
  lv_bar_set_value(ui_SyspadVolumeBar, volume, lv_anim);
}

void ui_set_brightness(int brightness, bool anim = true) {
  lv_anim_enable_t lv_anim = anim ? LV_ANIM_ON : LV_ANIM_OFF;
  lv_bar_set_value(ui_SyspadBrightnessBar, brightness, lv_anim);
}

void ui_set_ledlight(int light, bool anim = true) {
  lv_anim_enable_t lv_anim = anim ? LV_ANIM_ON : LV_ANIM_OFF;
  lv_bar_set_value(ui_SyspadLEDBar, light, lv_anim);
}

void ui_set_manual(const char* title, const char* content) {
  lv_label_set_text(ui_SyspadManualTitleLabel, title);
  lv_label_set_text(ui_SyspadManualContentLabel, content);
}

void ui_set_keyboard_state(bool checked) {
  if (checked) {
    lv_obj_add_state(ui_SyspadKeyboardSwitch, LV_STATE_CHECKED);
    lv_label_set_text(ui_SyspadKeyboardHitTitleLabel1, "状态: 锁屏时启用");
  } else {
    lv_obj_clear_state(ui_SyspadKeyboardSwitch, LV_STATE_CHECKED);
    lv_label_set_text(ui_SyspadKeyboardHitTitleLabel1, "状态: 未启用");
  }
}

bool ui_keyboard_is_checked(){
  return lv_obj_has_state(ui_SyspadKeyboardSwitch, LV_STATE_CHECKED);
}

uint8_t kSyspadAboutPanelIndex = 0;
uint8_t kSyspadKeyboardPanelIndex = 1;
uint8_t kSyspadManualPanelIndex = 2;
uint8_t kSyspadVolumePanelIndex = 3;
uint8_t kSyspadLEDPanelIndex = 4;
uint8_t kSyspadBrightnessPanelIndex = 5;

std::vector<lv_obj_t*> pannels_full_syspad() {
  return {ui_SyspadAboutPanel,  ui_SyspadKeyboardPanel,
          ui_SyspadManualPanel, ui_SyspadVolumePanel,
          ui_SyspadLEDPanel,    ui_SyspadBrightnessPanel};
}