#pragma once

#include "../app_contract.h"
#include "assistant.h"

LV_IMG_DECLARE(app_asst);

class AssistantShell : public AppShell {
 public:
  APP* CreateApp() { return new Assistant(); }
  const String app_id() { return "_assistant"; }
  const char* app_name() { return "AI 助手"; }
  const void* app_img() { return &app_asst; }
};