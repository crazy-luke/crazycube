/**
 * @file DemoApp.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief
 * @version 1.0
 * @date 2022-08-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "../app_contract.h"

class DemoApp : public APP {
 private:
  const char* kTag = "DemoApp";

public:
  void OnLaunch() override;
  void OnExitApp() override;
};
