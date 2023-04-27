/**
 * @file app_contract.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief App Contract
 * @version 1.0
 * @date 2022-09-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <WString.h>
#include <lvgl.h>

#include "app_context.h"
#include "framework/system/button.h"

#define NOTIFY_ID_EXIT_TASK 999

enum class AppAction { LEFT, RIGHT, UP, DOWN, ACT };
// enum class AppButton {L1, R1};

class APP : public ContextAPPSafeHolder {
 public:
  virtual ~APP();

 public:  // optinal method
  // Loop 任务
  virtual void OnRoutine();
  // 手势操作
  virtual void OnAction(AppAction action);
  // AI 助手被唤醒通知
  virtual void OnAssistantState(bool on);  
  // 状态栏被唤醒通知, false:此刻不允许开启 syspad，默认为 ture。
  virtual bool OnSyspadState(bool on);    

  /**
   * @brief  
   *   Button Action
   * @param id  
   * @param state 
   * @return true
   *     do default action by os , defalut is true
   * @return false
   *    cancle default action
   */
  virtual bool OnButton(ButtonID id, ButtonState state);

 public:  // require method
  // 退出 APP
  virtual void OnExitApp() = 0;
  // 启动 APP
  virtual void OnLaunch() = 0;
};

// APP 配置
class AppShell {
 public:  // optinal method
   // APP 说明菜单， defalut is empty
  virtual const String app_manul(); 
   // APP 禁止AI 助手， defalut is false
  virtual const bool asst_supress();  

 public:  // require method
  virtual APP* CreateApp() = 0;
  virtual const String app_id() = 0;
  virtual const char* app_name() = 0;
  virtual const void* app_img() = 0;
};