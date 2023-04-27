/**
 * @file gui.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 适配 SquareLine_Studio 工程 CrazyCube_CrazyFM, Export UI Files
 * 修改如下
 *  1. ui.h
 *      注释或删除函数 ui_init
 *      增加函数声明 ui_CrazyFMScreen_screen_init
 *  2. ui.c
 *      注释或删除函数 ui_init
 *      修改Spinner 动画参数, lv_spinner_create(ui_CrazyFMScreenEffectPanel,2000,90)
 *      注释 lv_img_set_src(ui_CrazyFMCoverImage, &ui_img_crazyfm_cover_png);
 * @version 1.0
 * @date 2022-08-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "ui.h"
#include "framework/system/sys.h"

#define CRAZYFM_COVER_FILEPATH FILEPATH_SPIFF_LVGL("/image/crazyfm_cover.png")

// 设置封面
void ui_setCover_CrazyFM(const void* src) {
  lv_img_set_src(ui_CrazyFMCoverImage, src);
}

// 设置标题
void ui_setTitle_CrazyFM(const char* title) {
  lv_label_set_text(ui_CrazyFMTitleLabel, title);
}

//设置状态
void ui_setState_crazyFM(const char* state) {
  lv_label_set_text(ui_CrazyFMStateLabel, state);
}

// 创建封面
lv_obj_t* ui_create_img_obj(lv_obj_t* parent, const void* src) {
  CrazyLog::d("gui", "ui_create_img_obj");
  lv_obj_t* img = lv_img_create(parent);
  lv_img_set_src(img, src);
  lv_img_set_antialias(img, false);
  lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
  return img;
}

void _img_set_zoom_anim_cb(void* obj, int32_t zoom) {
  lv_img_set_zoom((lv_obj_t*)obj, (uint16_t)zoom);
}

void _obj_set_x_anim_cb(void* obj, int32_t x) {
  lv_obj_set_x((lv_obj_t*)obj, (lv_coord_t)x);
}


lv_obj_t* _ui_switch_album(lv_obj_t* parent, lv_obj_t* img_obj_old, const void* src, bool anim_next){

  lv_obj_t* img_obj_new = ui_create_img_obj(parent, src);

  //move out old image
  lv_obj_fade_out(img_obj_old, 500, 0);
  lv_anim_t a;
  lv_anim_init(&a);
  lv_anim_set_var(&a, img_obj_old);
  lv_anim_set_time(&a, 500);
  lv_anim_set_path_cb(&a, lv_anim_path_ease_out);

  if (anim_next) {
    lv_anim_set_values(&a, 0, LV_HOR_RES / 2);
  } else {
    lv_anim_set_values(&a, 0, -LV_HOR_RES / 2);
  }
  lv_anim_set_exec_cb(&a, _obj_set_x_anim_cb);
  lv_anim_set_ready_cb(&a, lv_obj_del_anim_ready_cb);
  lv_anim_start(&a);

  lv_anim_set_path_cb(&a, lv_anim_path_linear);
  lv_anim_set_var(&a, img_obj_old);
  lv_anim_set_time(&a, 500);
  lv_anim_set_values(&a, LV_IMG_ZOOM_NONE, LV_IMG_ZOOM_NONE / 2);
  lv_anim_set_exec_cb(&a, _img_set_zoom_anim_cb);
  lv_anim_set_ready_cb(&a, NULL);
  lv_anim_start(&a);

  //move in new image

  lv_obj_fade_in(img_obj_new, 500, 100);
  lv_anim_set_path_cb(&a, lv_anim_path_overshoot);
  lv_anim_set_var(&a, img_obj_new);
  lv_anim_set_time(&a, 500);
  lv_anim_set_delay(&a, 100);
  lv_anim_set_values(&a, LV_IMG_ZOOM_NONE / 4, LV_IMG_ZOOM_NONE);
  lv_anim_set_exec_cb(&a, _img_set_zoom_anim_cb);
  lv_anim_set_ready_cb(&a, NULL);
  lv_anim_start(&a);
  return img_obj_new;
}

// 加载封面
void ui_switch_album(const void* src, bool next) {
  CrazyLog::d("gui.h", "switch_album");
  lv_obj_t* parent = ui_CrazyFMScreen;
  ui_CrazyFMCoverImage =  _ui_switch_album(parent, ui_CrazyFMCoverImage,src, next);
}


// // 音量
// void ui_setVolume_crazyFM(byte volume) {
//   lv_label_set_text(ui_CrazyFMVolumeLabel, String(volume).c_str());
//   lv_slider_set_value(ui_CrazyFMScreenVolumeSlider, volume, LV_ANIM_OFF);
// }

// //删除 volume 动画
// void ui_clear_volume_anim_crazyFM(){
//   lv_anim_del(ui_CrazyFMScreenVolumePanel, NULL);
// }

void _ui_recreate_spinner_CrazyFM() {
  if(ui_CrazyFMScreenSpinner) lv_obj_del(ui_CrazyFMScreenSpinner);
  ui_CrazyFMScreenSpinner = lv_spinner_create(ui_CrazyFMScreenEffectPanel,2000,90);
  lv_obj_set_width( ui_CrazyFMScreenSpinner, 150);
  lv_obj_set_height( ui_CrazyFMScreenSpinner, 150);
  lv_obj_set_align( ui_CrazyFMScreenSpinner, LV_ALIGN_CENTER );
  lv_obj_clear_flag( ui_CrazyFMScreenSpinner, LV_OBJ_FLAG_CLICKABLE );    /// Flags
  lv_obj_set_style_arc_width(ui_CrazyFMScreenSpinner, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

  lv_obj_set_style_arc_color(ui_CrazyFMScreenSpinner, lv_color_hex(0x000000), LV_PART_INDICATOR | LV_STATE_DEFAULT );
  lv_obj_set_style_arc_opa(ui_CrazyFMScreenSpinner, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);
  lv_obj_set_style_arc_width(ui_CrazyFMScreenSpinner, 8, LV_PART_INDICATOR| LV_STATE_DEFAULT);
}

void ui_showEffect_crazyFM(bool flag) {
  if (flag){
    lv_obj_clear_flag(ui_CrazyFMScreenEffectPanel, LV_OBJ_FLAG_HIDDEN);
    _ui_recreate_spinner_CrazyFM();
  }else
    
    lv_obj_add_flag(ui_CrazyFMScreenEffectPanel, LV_OBJ_FLAG_HIDDEN);
}

//显示音量
// void ui_showVolume_crazyFM(bool flag) {
//   if (flag){
//     ui_clear_volume_anim_crazyFM();
//     lv_obj_clear_flag(ui_CrazyFMScreenVolumePanel, LV_OBJ_FLAG_HIDDEN);
//   }else
//     lv_obj_add_flag(ui_CrazyFMScreenVolumePanel, LV_OBJ_FLAG_HIDDEN);
// }


// void _ui_hideVolume_end_cb(lv_anim_t* a) {
//   lv_obj_add_flag(ui_CrazyFMScreenVolumePanel, LV_OBJ_FLAG_HIDDEN);
// }

void _ui_anim_callback_set_opacity(lv_anim_t* a, int32_t v)
{
   lv_obj_set_style_opa((lv_obj_t *)a->user_data, v, 0);
}

int32_t _ui_anim_callback_get_opacity(lv_anim_t* a)
{
   return lv_obj_get_style_opa((lv_obj_t *)a->user_data, 0);
}

//延迟隐藏音量
// void ui_hideVolume_crazyFM(uint32_t duration, uint32_t delay){
//   ui_clear_volume_anim_crazyFM();

//   lv_obj_t *TargetObject = ui_CrazyFMScreenVolumePanel;

//   lv_anim_t PropertyAnimation_0;
//   lv_anim_init(&PropertyAnimation_0);
//   lv_anim_set_time(&PropertyAnimation_0, duration);
//   lv_anim_set_user_data(&PropertyAnimation_0,TargetObject);
//   lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity );
//   lv_anim_set_values(&PropertyAnimation_0, 255, 0 );
//   lv_anim_set_path_cb( &PropertyAnimation_0, lv_anim_path_linear);
//   lv_anim_set_delay( &PropertyAnimation_0, delay + 0 );
//   lv_anim_set_playback_time(&PropertyAnimation_0, 0);
//   lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
//   lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
//   lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
//   lv_anim_set_early_apply( &PropertyAnimation_0, false );
//   lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_opacity );

//   lv_anim_set_ready_cb(&PropertyAnimation_0, _ui_hideVolume_end_cb);
//   lv_anim_start(&PropertyAnimation_0);
// }


// 适配初始化 ui_init
lv_obj_t* ui_init_CrazyFM(void) {
  ui_CrazyFMScreen_screen_init();
  ui_setState_crazyFM("");
  //ui_setCover_CrazyFM(FILEPATH_SPIFF_LVGL("/image/crazyfm_cover.png"));
  ui_setCover_CrazyFM(CRAZYFM_COVER_FILEPATH);  

  // lv_obj_add_flag(ui_CrazyFMVolumeLabel,LV_OBJ_FLAG_OVERFLOW_VISIBLE);
  ui_showEffect_crazyFM(false);
  return ui_CrazyFMScreen;
}