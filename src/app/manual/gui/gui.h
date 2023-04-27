/**
 * @file gui.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 适配 SquareLine_Studio 工程 CrazyCube_CubeManual, Export UI Files 修改如下
 *  1. ui.h 
 *      注释或删除函数 ui_init
 *      增加函数声明 ui_CubeManualScreen_screen_init  
 *  2. ui.c
 *      注释或删除函数 ui_init
 * @version 1.0
 * @date 2022-09-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "ui.h"
#include <vector>

void ui_show_manual_sysbar(bool flag) {
  if (flag)
    lv_obj_clear_flag(ui_CubeManualSysbarPanel, LV_OBJ_FLAG_HIDDEN);
  else
    lv_obj_add_flag(ui_CubeManualSysbarPanel, LV_OBJ_FLAG_HIDDEN);
}

void ui_show_manual_gesture(bool flag) {
  if (flag)
    lv_obj_clear_flag(ui_CubeManualGesturePanel, LV_OBJ_FLAG_HIDDEN);
  else
    lv_obj_add_flag(ui_CubeManualGesturePanel, LV_OBJ_FLAG_HIDDEN);
}

void ui_show_manual_rssi(bool flag) {
  if (flag)
    lv_obj_clear_flag(ui_CubeManualRSSIPanel, LV_OBJ_FLAG_HIDDEN);
  else
    lv_obj_add_flag(ui_CubeManualRSSIPanel, LV_OBJ_FLAG_HIDDEN);
}


uint8_t kCubeManualSysbarPanelIndex =0;
uint8_t kCubeManualGesturePanelIndex = 1;
uint8_t kCubeManualRSSIPanelIndex = 2;

std::vector<lv_obj_t*> pannels_cube_manual() {
  return {ui_CubeManualSysbarPanel, ui_CubeManualGesturePanel, ui_CubeManualRSSIPanel};
}

lv_obj_t * ui_screen_manual(){
  return ui_CubeManualScreen;
}

void ui_set_cube_manual_title(const char* title){
  lv_label_set_text(ui_CubeManualTitleLabel, title);
}

void ui_set_cube_manual_seq(const char* content){
  lv_label_set_text(ui_CubeManualHintLabel, content);
}

void ui_show_CubeManualHintPanel(bool flag){
  if (flag)
    lv_obj_clear_flag(ui_CubeManualHintPanel, LV_OBJ_FLAG_HIDDEN);
  else
    lv_obj_add_flag(ui_CubeManualHintPanel, LV_OBJ_FLAG_HIDDEN);
}

//显示 wifi 信号强度
void ui_show_CubeManualWifiRSSI(int8_t rssi){
  lv_bar_set_value(ui_CubeManualRSSIBar, rssi, LV_ANIM_ON);
  lv_label_set_text(ui_CubeManualRSSILabel, String(rssi).c_str());
}

// 适配初始化 ui_init
lv_obj_t * ui_init_manual(void){
    ui_CubeManualScreen_screen_init();
    ui_show_manual_sysbar(false);
    ui_show_manual_gesture(false);
    ui_show_manual_rssi(false);
    ui_show_CubeManualWifiRSSI(0);
    return ui_CubeManualScreen;
}