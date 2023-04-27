#pragma once

#include <memory>

#include "framework/framework.h"

// 提供给 Assistant 的 Context
class ContextAssistant {
 public:
  // AI 助手被唤醒通知
  // 1: EnterState,  0: ExitState
  virtual void OnAssistantState(bool on) = 0;
  // AI 助手 Ready 通知
  virtual void OnAssistantReady(bool ready) = 0;
  // Framework
  virtual Frame& frame() = 0;
};

class ContextAssistantSafeHolder {
 private:
  std::weak_ptr<ContextAssistant> context_;  // should be weak

 protected:
  // best way: if(auto ctx = context())  ctx->xxx
  std::shared_ptr<ContextAssistant> context() { return context_.lock(); }

 public:
  void set_context(std::shared_ptr<ContextAssistant> context) {
    context_ = context;
  }
};
