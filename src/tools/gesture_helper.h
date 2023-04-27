/**
 * @file gesture_guard.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 手势误判， Gesture misjudgement
 * @version 1.0
 * @date 2022-09-09
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "app/app_contract.h"
#include "framework/system/gesture_senor.h"
#include "os/syspad/syspad.h"

struct SysbarActionConvertResult {
  bool success = false;
  SysbarAction action;
};

struct AppActionConvertResult {
  bool success = false;
  AppAction action;
};

class GestureHelper {
 private:
  const char* kTag = "GestureHelper";
  long last_gesture_time_ = 0;
  GestureAction last_gesture_action_ = GestureAction::NONE;

 public:
  bool ActionFilter(GestureAction action);
  SysbarActionConvertResult ConvertSysbarAction(GestureAction action);
  AppActionConvertResult ConvertAppAction(GestureAction action);
};