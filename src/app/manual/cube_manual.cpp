#include "cube_manual.h"

#include "tools/crazy_log.h"
#include "gui/gui.h"

#include "lv/lv_helper.h"
#include "framework/system/display.h"
#include "framework/framework.h"

void CubeManual::OnLaunch() {
  CrazyLog::d(kTag, "onLaunch");

  lv_obj_t* ui_screen = ui_init_manual();
  manual_pannels_ = pannels_cube_manual();
  actived_pannel_idx_ = 0;
  ui_show_manual_sysbar(true);
  ui_show_CubeManualHintPanel(true);
  UpdateHint(kCubeManualSysbarPanelIndex);
  lv_scr_load_anim(ui_screen, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 300, 0, false);
}

void CubeManual::OnExitApp() {
  CrazyLog::d(kTag, "OnExitApp");
  manual_pannels_.clear();
  lv_scr_load_anim(context()->home_screen(), LV_SCR_LOAD_ANIM_MOVE_TOP, 300, 0,
                   true);
}

void CubeManual::OnAction(AppAction action) {
  if (action == AppAction::LEFT) {
    CrazyLog::d(kTag, "LEFT");
    SwitchPannel(GetThresholdIndex(actived_pannel_idx_ + 1));
  } else if (action == AppAction::RIGHT) {
    CrazyLog::d(kTag, "RIGHT");
    SwitchPannel(GetThresholdIndex(actived_pannel_idx_ - 1));
  }
}

uint8_t CubeManual::GetThresholdIndex(uint8_t idx){
  uint8_t t_idx = idx;
  if (idx >= manual_pannels_.size()) t_idx = 0;
  if (idx < 0) t_idx = manual_pannels_.size() - 1;
  return t_idx;
}

void CubeManual::SwitchPannel(uint8_t idx) {
  CrazyLog::d(kTag, "SwitchPannel");

  lv_obj_t* out_pannel = manual_pannels_[actived_pannel_idx_];
  lv_obj_t* in_pannel = manual_pannels_[idx];

  lv_obj_clear_flag(in_pannel, LV_OBJ_FLAG_HIDDEN);
   AnimMoveDirection direction = idx > actived_pannel_idx_ ? RIGHT_TO_LEFT : LEFT_TO_RIGNT;
  lv_anim_move_in_out(in_pannel, out_pannel, ui_screen_manual(),
                direction,DISPLAY_MIRROR, 300);

  actived_pannel_idx_ = idx;
  UpdateHint(idx);
}

void CubeManual::UpdateHint(uint8_t idx){
  CrazyLog::d(kTag, "UpdateHint");
  if(idx!=0) ui_show_CubeManualHintPanel(false);
  
  String sql =  String(idx+1)+ "/" + String(manual_pannels_.size());
  ui_set_cube_manual_seq(sql.c_str());

  if(idx == kCubeManualSysbarPanelIndex){
    ui_set_cube_manual_title("状态栏图标");
  }else if(idx == kCubeManualGesturePanelIndex){
    ui_set_cube_manual_title("手势控制说明");
  }else if(idx == kCubeManualRSSIPanelIndex) {
    ui_set_cube_manual_title("Wifi 信号");
  }else {
    ui_set_cube_manual_title("");
  }
}

void CubeManual::OnRoutine(){
  //当前是 wifi 信号栏
  if(actived_pannel_idx_ == kCubeManualRSSIPanelIndex){
    auto rssi = context()->frame().network().SignalStrength();
    rssi = map(rssi, -100, 0, 0, 100);
    ui_show_CubeManualWifiRSSI(rssi);
  }
}
