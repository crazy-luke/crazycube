/**
 * @file app_os.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief OS Manager All apps and resources
 * @version 1.0
 * @date 2022-08-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <memory>
#include <vector>

#include "app/app_list.h"
#include "app/assistant/assistant_speech/assistant_speech.h"
#include "framework/framework.h"
#include "framework/system/keyboard.h"
#include "launchpad/launchpad.h"
#include "os.h"
#include "syspad/syspad.h"
#include "tools/gesture_helper.h"
#include "outlander/plugin/controller_ex.h"

class AppOS : public OS,
              public ContextAPP,
              public ContextSyspad,
              public ContextAssistant,
              public ContextControllerEx,
              public std::enable_shared_from_this<AppOS> {
 private:
  const char* kTag = "AppOS";
  std::vector<AppShell*> app_sheels_;
  Launchpad launchpad_;
  Syspad syspad_;
  std::shared_ptr<APP> running_app_ptr_;  // 当前正在运行的APP
  uint8_t active_app_idx_;

  AssistantSpeech asst_speech_;
  GestureHelper gesture_helper_;
  SemaphoreHandle_t g_xGuiSemaphore = xSemaphoreCreateMutex();
  std::shared_ptr<Keyboard> keyboard_ptr_;
  TaskHandle_t task_handle_ = NULL;
  ButtonListener* button_listener_ = NULL;
  bool allow_lock_gesture_;
  ControllerEx * controller_ex_ptr_ = NULL;

#ifdef AUTO_SCROLL
  long show_ts_;
#endif

 private:
  void ReloadAppList(std::vector<AppShell*> apps, String position_app_id,
                     bool is_group_app);
  void LaunchAPP(uint8_t idx);
  uint8_t FindAppIndex(std::vector<AppShell*>& apps, String app_id);
  void SwitchAPP(bool forward);
  void OnAction(GestureAction action);
  void OpenFullSyspad();
  void CloseFullSyspad();
  void CloseAPP();
  bool LockScreen();
  bool UnLockScreen();

  // Button Action
 private:
  void InitButton();
  void OnButtonListener(ButtonID id, ButtonState state);
  void OnButtonSyspad(ButtonID& id, ButtonState& state);
  void OnButtonDefault(ButtonID& id, ButtonState& state);
  friend void AppOSOnButtonListener(ButtonID id, ButtonState state,
                                    void* param);

 public:
  // OS
  void Init() override;
  void Routine() override;
  // ContextAPP
  lv_obj_t* home_screen() override;
  void NetworkMonitor(bool enable) override;
  bool CallAssistant() override;
  Frame& frame() override;
  void OnGroup(String group_id) override;
  // ContextSyspad
  void OnNetworkStateChanged(bool on) override;
  // ContextAssistant
  void OnAssistantState(bool on) override;
  void OnAssistantReady(bool ready) override;

  // ContextControllerEx
  void OnActionEx(GestureAction action)  override;
  void OnButtonListenerEx(ButtonID id, ButtonState state)  override;

 private:
  void UpdateUIAssistantState();
};