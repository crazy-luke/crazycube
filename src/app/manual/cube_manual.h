/**
 * @file cube_manual.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 立方豆操作手册 Manual for CrazyCube
 * @version 1.0
 * @date 2022-09-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <vector>

#include "app/app_contract.h"

class CubeManual : public APP
{
private:
  const char* kTag = "CubeManual";
  int8_t actived_pannel_idx_;
  std::vector<lv_obj_t*> manual_pannels_ = {};
  
private:
  void SwitchPannel(uint8_t idx);
  void UpdateHint(uint8_t idx);
  uint8_t GetThresholdIndex(uint8_t idx);

public:
  void OnLaunch() override;
  void OnExitApp() override;
  void OnAction(AppAction action) override;
  void OnRoutine() override;
};

