/**
 * @file lab.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 试验区代码, CodeLab
 * @version 0.1
 * @date 2022-09-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <memory.h>
#include "framework/framework.h"
#include "code_test.h"

class Lab {
 private:
  const char* kTag = "Lab";
  void OnButtonListener(ButtonID id, ButtonState state);
  friend void LabOnButtonListener(ButtonID id, ButtonState state, void* param);
  std::unique_ptr<CodeTest> test_;

  bool ConnectWifi();

 public:
  void Init();
  void Routine();

private:
  Frame& frame();

};
