
#pragma once
#include "../app_contract.h"
#include "cube_manual.h"

LV_IMG_DECLARE(crazy_cube);

class CubeManualShell : public AppShell {
 public:
  APP* CreateApp() { return new CubeManual(); }
  const String app_id() { return "_manual"; }
  const char* app_name() { return "立方豆-手册"; }
  const void* app_img() { return &crazy_cube; }

  const String app_manul() {
    String content = "";
    content += "左右:切换页面\n";
    return content;
  }
};