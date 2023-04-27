#include "syspad.h"

#include <algorithm>

#include "tools/crazy_log.h"
#include "framework/system/sys.h"
#include "gui/gui.h"
#include "keychain/kc_state.h"
#include "keychain/kc_wifi.h"
#include "lv/lv_helper.h"
#include "tools/mutex_helper.h"
#include "tools/timer_helper.h"

void SyspadTask(void* param) {
  Syspad* syspad = static_cast<Syspad*>(param);
  vTaskDelay(1000);
  syspad->Heart();
}

void Syspad::Heart()
{
  auto info = WifiInfoKeyChain().Read();
  bool wifi = context()->frame().network().IsConnected();
  UpdateWifiState(wifi);
  vTaskDelay(300);
  bool sync_time_successed_ = false;
  
  while (true) {
    CrazyLog::i(kTag, "tik~");
    MillisMonitor();

    { //WifiMonitor
      bool wifi_now = context()->frame().network().IsConnected();

      if (wifi_now != wifi) {  // update UI
        UpdateWifiState(wifi_now);
      }
      if (!wifi_now) {  // connect wifi
        CrazyLog::d(kTag, "Wifi OffLine");
           wifi_now = context()->frame().network().Connect(info.ssid, info.password, 5000);
        if (wifi_now) {  // update UI
          UpdateWifiState(wifi_now);
        }
      }
      if (wifi_now && !sync_time_successed_) {
        sync_time_successed_ = TimerHelper::SyncTime();
        CrazyLog::d(kTag, "sync time result: %d", sync_time_successed_);
      }
      wifi = wifi_now;
    }

    CrazyLog::i(kTag, "tok~");
    delay(WIFI_MONITOR_PERIOD);
  }
}


void Syspad::MillisMonitor (){
  CrazyLog::v(kTag, "MillisMonitor");
  auto ts = millis();
  if(ts - last_millis_ < 0){
    CrazyLog::e(kTag, "millis dead!");
    context()->frame().RestartOS();
    return;
  }
  last_millis_ = ts;
}


Syspad::Syspad() { 
  is_locked_ = false; 
  keyboard_allowed_ = false;
}

Syspad::~Syspad() { StopNetworkMonitor(); }

void Syspad::Init() {
  keyboard_allowed_ = StateKeyChain().Read().keyboard;
  mini_syspad_ = ui_init_mini_syspad();
  ui_show_lock(is_locked_);
}

void Syspad::StartNetworkMonitor() {
  if (task_handle_ != nullptr) {
    CrazyLog::w(kTag, "WifiMonitor already started");
    return;
  }
  ui_show_wifi(true);

  CrazyLog::d(kTag, "StartNetworkMonitor");
  xTaskCreatePinnedToCore(SyspadTask, "SyspadTask", 1024 * 4, this,
                          TASK_PRIORITY_WIFI, &task_handle_, CORE_0);
}

void Syspad::StopNetworkMonitor() {
  CrazyLog::w(kTag, "StopNetworkMonitor");
  ui_show_wifi(false);
  if (task_handle_) {
    vTaskDelete(task_handle_);
    task_handle_ = nullptr;
  }
}

bool Syspad::is_locked() { return is_locked_; }

bool Syspad::keyboard_allowed(){ return keyboard_allowed_;}

void Syspad::LockScreen(bool lock) {
  if (lock == is_locked_) return;
  is_locked_ = lock;
  context()->frame().speaker().PlayFile(AUDIO_RES_LOCK, true);
  ui_show_lock(is_locked_);
  ui_set_lock_keyboard_mode(keyboard_allowed_);
}

void Syspad::LockHint() {
  context()->frame().speaker().PlayFile(AUDIO_RES_MISS, true);
  ui_shake_lock();
}

void Syspad::KeyboardHint() {
  context()->frame().speaker().PlayFile(AUDIO_RES_KEYBOARD, true);
  ui_shake_lock();
}

bool Syspad::full_syspad() { return full_syspad_ != NULL; }

void Syspad::OnExitFullSyspad() {
  CrazyLog::d(kTag, "OnExitFullSyspad");
  if (full_syspad_ != NULL) {
    lv_obj_del(full_syspad_);
    full_syspad_pannels_.clear();
    full_syspad_ = NULL;
  }
}

void Syspad::OnLaunchFullSyspad() {
  CrazyLog::d(kTag, "OnLaunchFullSyspad");
  if (full_syspad_ == NULL) {
    full_syspad_ = ui_init_full_syspad();
    full_syspad_pannels_ = pannels_full_syspad();
    actived_pannel_idx_ = 0;
    auto state = StateKeyChain().Read();
    CrazyLog::d(kTag,"StateInfo volume:%d, brightness:%d, ledlight:%d, keyboard:%d",
      state.volume,state.brightness,state.ledlight,state.keyboard);
    ui_set_volume(state.volume, false);
    ui_set_brightness(state.brightness, false);
    ui_set_ledlight(state.ledlight, false);
    ui_set_keyboard_state(state.keyboard);
    keyboard_allowed_ = state.keyboard;
    SwitchPannel(kSyspadManualPanelIndex, false);
    SetManual("", "");
    UpdateDebugHint();
  }
}

void Syspad::UpdateDebugHint(){
  if(CrazyLog::level() == LogLevel::DEBUG)
    ui_set_hint_debug("debug");
  else if(CrazyLog::level() == LogLevel::VERBOSE)
    ui_set_hint_debug("verbose");
  else 
    ui_set_hint_debug("");
}

void Syspad::OnAction(SysbarAction action) {
  CrazyLog::d(kTag, "OnAction");
  if (full_syspad_ == NULL) {
    CrazyLog::e(kTag, "full_syspad is null");
    return;
  }

  if (action == SysbarAction::LEFT) {
    SwitchPannel(actived_pannel_idx_ - 1, true);
  } else if (action == SysbarAction::RIGHT) {
    SwitchPannel(actived_pannel_idx_ + 1, true);
  } else if (action == SysbarAction::CLOCKWISE) {
    if (actived_pannel_idx_ == kSyspadAboutPanelIndex)
      context()->frame().RestartOS();
    else if(actived_pannel_idx_ == kSyspadKeyboardPanelIndex)
      SwitchKeyboardState();
    else
      TurnValue(true);
  } else if (action == SysbarAction::ANTICLOCKWISE) {
    TurnValue(false);
  } else if (action == SysbarAction::DOWN) {
    if (actived_pannel_idx_ == kSyspadLEDPanelIndex) {
      auto state = context()->frame().SwitchLedStateWithStore();
    }
  }
}

void Syspad::SwitchKeyboardState(){
  auto checked = !ui_keyboard_is_checked();
  CrazyLog::d(kTag, "SwitchKeyboard to %d", checked);
  ui_set_keyboard_state(checked);
  StateKeyChain().UpdateKeyboard(checked);
  keyboard_allowed_ = checked;
}

void Syspad::TurnValue(bool up) {
  CrazyLog::d(kTag, "TurnValue %d", up);
  if (full_syspad_pannels_.size() <= actived_pannel_idx_) return;

  if (actived_pannel_idx_ == kSyspadVolumePanelIndex) {  
    // set volume
    uint8_t new_value = context()->frame().TurnVolumeWithStore(up);
    ui_set_volume(new_value, true);
  } else if (actived_pannel_idx_ ==  kSyspadBrightnessPanelIndex) {  
    // set display  brightness
    uint8_t new_value = context()->frame().TurnDisplayBrightnessWithStore(up);
    ui_set_brightness(new_value, true);
  } else if (actived_pannel_idx_ == kSyspadLEDPanelIndex) {  
    // set led brightness
     uint8_t new_value = context()->frame().TurnLedBrightnessWithStore(up);
     ui_set_ledlight(new_value, true);
  } else if( actived_pannel_idx_ == kSyspadAboutPanelIndex) {
     if(CrazyLog::level() == LogLevel::DEBUG) CrazyLog::set_level(LogLevel::INFO);
     else if(CrazyLog::level() == LogLevel::INFO) CrazyLog::set_level(LogLevel::DEBUG);
     UpdateDebugHint();
  }else {
    CrazyLog::ram(kTag);
  }
}

void Syspad::SwitchPannel(uint8_t idx, bool anim) {
  if (full_syspad_pannels_.size() <= idx) return;
  if (idx < 0) return;
  lv_obj_t* out_pannel = full_syspad_pannels_[actived_pannel_idx_];
  lv_obj_t* in_pannel = full_syspad_pannels_[idx];

  if (idx == 0)
    ShowHintPanel(false, true);
  else if (idx == full_syspad_pannels_.size() - 1)
    ShowHintPanel(true, false);
  else
    ShowHintPanel(true, true);

  ui_show_hit_lr_text(idx == kSyspadManualPanelIndex);

  lv_obj_clear_flag(in_pannel, LV_OBJ_FLAG_HIDDEN);
  bool forward = idx < actived_pannel_idx_;
  if (anim)
    lv_anim_move_in_out(in_pannel, out_pannel, full_syspad_,
                 forward ? RIGHT_TO_LEFT : LEFT_TO_RIGNT,
                 DISPLAY_MIRROR, 300);
  else
    lv_obj_add_flag(out_pannel, LV_OBJ_FLAG_HIDDEN);

  actived_pannel_idx_ = idx;
}

void Syspad::ShowHintPanel(bool left, bool right) {
  ui_show_hit_left(left);
  ui_show_hit_right(right);
}

void Syspad::UpdateWifiState(bool wifi_on) {
  CrazyLog::d(kTag, "UpdateWifiState %d", wifi_on);
  MutexUI::instance().Lock();
  ui_set_wifi_on(wifi_on);
  MutexUI::instance().Unlock();
  context()->OnNetworkStateChanged(wifi_on);
}

void Syspad::SetManual(const char* title, const char* content) {
  ui_set_manual(title, content);
}

void Syspad::ShowAssistant(bool flag){
  ui_show_assistant(flag);
}
