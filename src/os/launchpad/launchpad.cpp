#include "launchpad.h"

#include "./gui/ui.h"
#include "tools/crazy_log.h"
#include "lv/lv_helper.h"

void Launchpad::Init() {
  ui_init();

  actived_panel_ = ui_AppPanel1;
  // lv_img_set_src(ui_LogoImage1, &crazy_cube);
  lv_label_set_text(ui_NameLabel1, "C");
  // lv_img_set_src(ui_LogoImage2, &crazy_cube);
  lv_label_set_text(ui_NameLabel2, "");
  lv_disp_t *d = lv_obj_get_disp(ui_AppScreen);
  lv_obj_set_x(ui_AppPanel2, -lv_disp_get_hor_res(d));
}

void Launchpad::ReloadActiveAPP(const void *icon, const char *name) {
  CrazyLog::d(kTag, "reloadActiveAPP");

  if (actived_panel_ == ui_AppPanel1) {
    lv_img_set_src(ui_LogoImage1, icon);
    lv_label_set_text(ui_NameLabel1, name);
  } else {
    lv_img_set_src(ui_LogoImage2, icon);
    lv_label_set_text(ui_NameLabel2, name);
  }
}

void Launchpad::SwitchAPP(bool forward, const void *icon, const char *name) {
  CrazyLog::d(kTag, "switchAPP forward: %d", forward);

  lv_obj_t *ui_AppPanel_out = actived_panel_;
  lv_obj_t *ui_Image_Out;
  lv_obj_t *ui_Label_Out;

  lv_obj_t *ui_AppPanel_in;  
  lv_obj_t *ui_Image_In;
  lv_obj_t *ui_Label_In;

  if (actived_panel_ == ui_AppPanel1) {
    ui_AppPanel_in = ui_AppPanel2;
    ui_Image_In = ui_LogoImage2;
    ui_Label_In = ui_NameLabel2;
    ui_Image_Out = ui_LogoImage1;
    ui_Label_Out = ui_NameLabel1;
  } else {
    ui_AppPanel_in = ui_AppPanel1;
    ui_Image_In = ui_LogoImage1;
    ui_Label_In = ui_NameLabel1;
    ui_Image_Out = ui_LogoImage2;
    ui_Label_Out = ui_NameLabel2;
  }
  lv_img_set_src(ui_Image_In, icon);
  lv_label_set_text(ui_Label_In, name);

  actived_panel_ = ui_AppPanel_in;

  uint32_t duration = 300U;
  lv_anim_move_in_out(ui_AppPanel_in, ui_AppPanel_out, ui_AppScreen,
            forward ? RIGHT_TO_LEFT : LEFT_TO_RIGNT,
            DISPLAY_MIRROR, duration);

#if LV_COLOR_SCREEN_TRANSP
  lv_obj_set_style_opa(ui_Image_In,LV_OPA_100,0);
  lv_obj_set_style_opa(ui_Image_Out,LV_OPA_100,0);
  lv_obj_set_style_opa(ui_Label_In,LV_OPA_100,0);
  lv_obj_set_style_opa(ui_Label_Out,LV_OPA_100,0);
  if(duration > 0){
    fade_animation(ui_Image_In,80,255,duration,0, ANIM_PATH_EASE_IN);
    fade_animation(ui_Label_In,80,255,duration,0, ANIM_PATH_EASE_IN);
    fade_animation(ui_Image_Out,255,80,duration,0,ANIM_PATH_EASE_OUT);
    fade_animation(ui_Label_Out,255,80,duration,0,ANIM_PATH_EASE_OUT);
  }
#endif
}

lv_obj_t *Launchpad::launchpad_screen() { return ui_AppScreen; }


void Launchpad::ShowBackHint(bool flag){
 if (flag){
    lv_obj_clear_flag(ui_AppHintPanel, LV_OBJ_FLAG_HIDDEN);
  }else
    lv_obj_add_flag(ui_AppHintPanel, LV_OBJ_FLAG_HIDDEN);
}

void Launchpad::SetSubMode(bool flag) {
  ShowBackHint(flag);
  is_sub_mode_ = flag;
}