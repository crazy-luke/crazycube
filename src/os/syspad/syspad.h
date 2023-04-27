#pragma once

#include <Arduino.h>
#include <lvgl.h>
#include <vector>

#include "framework/framework.h"
#include "syspad_context.h"

#define AUDIO_RES_LOCK "/audio/lock.mp3"
#define AUDIO_RES_KEYBOARD "/audio/keyboard.mp3"
#define AUDIO_RES_MISS "/audio/miss.mp3"
#define WIFI_MONITOR_PERIOD 10 * 1000
#define TIMER_CHECK_INTERVAL 5 * 60 * 1000  // 5分钟校准一次时间

enum class SysbarAction { LEFT, RIGHT, UP, DOWN, CLOCKWISE, ANTICLOCKWISE };

class Syspad: public ContextSyspadSafeHolder {
 private:
  const char* kTag = "Syspad";
  TaskHandle_t task_handle_ = NULL;
  bool is_locked_;
  bool keyboard_allowed_;  // 是否允许启用蓝牙
  lv_obj_t* mini_syspad_;
  lv_obj_t* full_syspad_;
  uint8_t actived_pannel_idx_ = 0;
  unsigned long last_millis_ = 0;  // 记录最后一次 millis， 监控 millis 生命周期

  std::vector<lv_obj_t*> full_syspad_pannels_ = {};
  void ShowHintPanel(bool left, bool right);
  void SwitchPannel(uint8_t idx, bool anim);
  void TurnValue(bool up);
  void SwitchKeyboardState();
  friend void SyspadTask(void* param);
  void UpdateWifiState(bool wifi_on);
  void MillisMonitor();
  void Heart();
  void UpdateDebugHint();

 public:
  Syspad();
  ~Syspad();
  void Init();
  void LockScreen(bool lock);
  bool is_locked();
  bool keyboard_allowed();
  void LockHint();
  void KeyboardHint();
  bool full_syspad();
  void OnExitFullSyspad();
  void OnLaunchFullSyspad();
  void OnAction(SysbarAction action);
  void StartNetworkMonitor();
  void StopNetworkMonitor();
  void SetManual(const char* title, const char* content);
  void ShowAssistant(bool flag);
};