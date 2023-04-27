/**
 * @file display.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief
 * @version 1.0
 * @date 2022-08-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <TFT_eSPI.h>
#include <lvgl.h>

#include "lv/ui_font.h"

#define MAX_BRIGHTNESS 100
#define LCD_BL_PIN 5
#define LCD_BL_PWM_CHANNEL 0
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240

#define DISPLAY_MIRROR 1  // 镜像

class Display {
 private:
  const char* kTag = "Display";
  lv_obj_t* tip_label_;
  lv_obj_t* tip_sub_label_;
  lv_obj_t* tips_pannel_;

 private:
  void CreateTipsPannel();
  void InitLvgl();

 public:
  void Init(uint8_t brightness, uint8_t rotation = DISPLAY_MIRROR ? 4 : 0, bool lvgl = true);
  void Routine();
  void SetBrightness(uint8_t brightness);
  void ShowTipsDisplay(String text, const lv_font_t* font = &ui_font_SourceHanCrazyCube26);
  void ShowSubTipsDisplay(String text, const lv_font_t* font = &ui_font_SourceHanCrazyCube26);
  void CleanTips();
  TFT_eSPI* tft();
  
  void set_lv_ui_enable(bool flag); //是否允许 LVGL 刷新UI
  bool lv_ui_enable();
};
