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

#include "framework/framework.h"

// 提供给 Syspad 的 Context
class ContextSyspad {
 public:
  virtual void OnNetworkStateChanged(bool on) = 0;
  virtual Frame& frame() = 0;
};

// ContextSyspad Safe holder
class ContextSyspadSafeHolder{
 private:
  std::weak_ptr<ContextSyspad> context_;  // should be weak
 protected:

 std::shared_ptr<ContextSyspad> context() {
    return context_.lock(); 
 }
  
 protected:
  friend class AppOS;
  void set_context(std::shared_ptr<ContextSyspad> context) { context_ = context; }
};