
/**
 * @file controller_ex.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief
 * @version 0.1
 * @date 2023-02-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "os/os.h"
#include "tools/crazy_log.h"
#include "framework/system/button.h"
#include "framework/system/gesture_senor.h"


#define CONTROLLER_EX_DEBUG 0

// 提供给 ControllerEx 的 Context
class ContextControllerEx {
 public:
  virtual void OnActionEx(GestureAction action) = 0;
  virtual void OnButtonListenerEx(ButtonID id, ButtonState state) = 0;
};

// ContextControllerEx Safe holder
class ContextControllerExSafeHolder{
 private:
  std::weak_ptr<ContextControllerEx> context_;  // should be weak
 protected:

 std::shared_ptr<ContextControllerEx> context() {
    return context_.lock(); 
 }
  
 protected:
  friend class AppOS;
  void set_context(std::shared_ptr<ContextControllerEx> context) { context_ = context; }
};


//外部控制器
class ControllerEx: public ContextControllerExSafeHolder
{
private:
    const char * kTag = "Plugin";

public:
    ControllerEx(/* args */);
    ~ControllerEx();

public:
  void Routine();
};