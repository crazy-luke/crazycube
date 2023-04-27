/**
 * @file app_context.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief Provide APP OS Content Holder
 * @version 1.0
 * @date 2022-09-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <lvgl.h>
#include <memory>
#include <any>

#include "framework/framework.h"

// 提供给 APP 的 Context
class ContextAPP {
 public:
  virtual lv_obj_t* home_screen() = 0;
  virtual void NetworkMonitor(bool enable) = 0; 
  virtual bool CallAssistant() = 0;
  virtual Frame& frame() = 0;
  virtual void OnGroup(String group_id) = 0;
};

// ContextAPP Safe holder
class ContextAPPSafeHolder{
 private:
  std::weak_ptr<ContextAPP> context_;  // should be weak
 protected:

 //best way: if(auto ctx = context())  ctx->xxx
 //but infact APP can`t run without context
 std::shared_ptr<ContextAPP> context() {
    return context_.lock(); 
 }
  
 protected:
  friend class AppOS;
  void set_context(std::shared_ptr<ContextAPP> context) { context_ = context; }
};