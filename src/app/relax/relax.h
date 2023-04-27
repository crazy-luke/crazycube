/**
 * @file relax.cpp
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief take a break , have fun~
 * @version 1.0
 * @date 2022-09-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "../app_contract.h"
#include "relax_game/relax_game.h"
#include "framework/framework.h"

class Relax : public APP {
 private:
  const char* kTag = "RelaxAPP";
  RelaxGame * game_;
  EularAngle angle_;
  RelaxBook book_ = RelaxBook::SNAKE;

private:
  void ShowTitle(RelaxBook book);
  RelaxDirection ParseDirection();
  void ControlGame();
  void TestDirection();

public:
  void OnLaunch() override;
  void OnExitApp() override;
  void OnRoutine() override;
  void OnAction(AppAction action) override;
};
