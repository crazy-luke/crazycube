/**
 * @file gui.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 适配 SquareLine_Studio 工程 CrazyCube_Assistant, Export UI Files
 * 修改如下
 * @version 1.0
 *   1. ui.h
 *      注释或删除函数 ui_init
 *      增加函数声明 ui_AssistantScreen_screen_init
 *      注释或删除 字体
 *   2. ui.c
 *      注释或删除函数 ui_init
 *      修改屏幕父类 ui_AssistantScreen = lv_obj_create(lv_layer_sys());
 * @date 2022-09-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "ui.h"

void ui_show_mictime_panel_assistant(bool flag) {
  if (flag) {
    lv_obj_clear_flag(ui_AssistantMicTimePanel, LV_OBJ_FLAG_HIDDEN);
  } else {
    lv_anim_del(ui_AssistantMicTimePanel, NULL);
    lv_obj_add_flag(ui_AssistantMicTimePanel, LV_OBJ_FLAG_HIDDEN);
  }
}

void _ui_start_mictimebar_init() {
  lv_bar_set_range(ui_AssistantMicTimeBar, 0,100);
  lv_bar_set_start_value(ui_AssistantMicTimeBar,100,LV_ANIM_OFF);
  lv_bar_set_value(ui_AssistantMicTimeBar, 100,LV_ANIM_OFF);
}

void ui_start_mictimebar_countdown(int32_t time) {
  lv_bar_set_value(ui_AssistantMicTimeBar, 100,LV_ANIM_OFF);
  lv_obj_set_style_anim_time(ui_AssistantMicTimeBar, time, LV_PART_MAIN| LV_STATE_DEFAULT);
  lv_bar_set_value(ui_AssistantMicTimeBar,0,LV_ANIM_ON);
}

void ui_show_mic_assistant(bool flag, bool recording = false) {
  if (flag) {
    lv_obj_clear_flag(ui_AssistantMicSpinner, LV_OBJ_FLAG_HIDDEN);
    if(recording){
      lv_obj_clear_flag(ui_AssistantMicImage, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_AssistantMicLabel, LV_OBJ_FLAG_HIDDEN);
      
      lv_obj_set_style_arc_color(ui_AssistantMicSpinner, lv_palette_main(LV_PALETTE_LIGHT_BLUE), 
      LV_PART_INDICATOR); 

      ui_show_mictime_panel_assistant(true);  //show mictime
    }else{
      lv_obj_clear_flag(ui_AssistantMicLabel, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_AssistantMicImage, LV_OBJ_FLAG_HIDDEN);
      lv_obj_set_style_arc_color(ui_AssistantMicSpinner, lv_palette_main(LV_PALETTE_GREY), LV_PART_INDICATOR); 
      // lv_obj_set_style_arc_color(ui_AssistantMicSpinner, lv_color_hex(0x28D072), LV_PART_INDICATOR); 

      ui_show_mictime_panel_assistant(false);  // close mictime
    }
  } else {
    lv_obj_add_flag(ui_AssistantMicSpinner, LV_OBJ_FLAG_HIDDEN);

    ui_show_mictime_panel_assistant(false);  // close mictime
  }
  
}

void ui_show_wave_assistant(bool flag) {
  if (flag) {
    lv_obj_clear_flag(ui_AssistantWavePanel, LV_OBJ_FLAG_HIDDEN);
    assistant_wave_Animation(ui_AssistantWaveImage, 0);
  } else {
    lv_anim_del(ui_AssistantWaveImage, NULL);
    lv_obj_add_flag(ui_AssistantWavePanel, LV_OBJ_FLAG_HIDDEN);
  }
}

// 适配初始化 ui_init
lv_obj_t* ui_init_assistant(void) {
  ui_AssistantScreen_screen_init();
  lv_obj_set_size(ui_AssistantScreen, LV_PCT(100), LV_PCT(100));

  lv_obj_set_style_pad_all(ui_AssistantScreen, 0,
                           LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_AssistantScreen, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);

  
  lv_obj_set_style_text_color(ui_AssistantMicLabel, lv_palette_main(LV_PALETTE_GREY), LV_PART_MAIN | LV_STATE_DEFAULT );
  lv_obj_clear_flag(ui_AssistantAudioPanel, LV_OBJ_FLAG_HIDDEN);
  ui_show_mic_assistant(true,false);
  ui_show_wave_assistant(false);
  ui_show_mictime_panel_assistant(false);
  _ui_start_mictimebar_init();

  return ui_AssistantScreen;
}