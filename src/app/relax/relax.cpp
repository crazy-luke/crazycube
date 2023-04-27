#include "relax.h"

#include "tools/crazy_log.h"
#include "gui/gui.h"
#include "relax_game/relax_game.h"
#include "relax_game/snake/snake.h"
#include "relax_game/space_shoot/space_shoot.h"

void Relax::OnLaunch() {
  CrazyLog::d(kTag, "onLaunch");
  // context()->frame().imu().InitBackground(400);
  context()->frame().InitIMUWithNotice();
  lv_obj_t* ui_screen = ui_init_Relax();
  book_ = RelaxBook::SNAKE;
  ShowTitle(book_);
  lv_scr_load_anim(ui_screen, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 300, 0, false);
}

void Relax::OnExitApp() {
  CrazyLog::d(kTag, "onExitApp");
  if (game_) {
    game_->free();
    delete (game_);
    game_ = nullptr;
  }
  lv_scr_load_anim(context()->home_screen(), LV_SCR_LOAD_ANIM_MOVE_TOP, 300, 10,
                   true);
}

void Relax::OnRoutine() {
  if (game_) {
    if(game_->playing()){
      ControlGame();
    }
    game_->Loop();
  } else {
    TestDirection();
  }
}

void Relax::ControlGame() {
  auto direction = ParseDirection();
  switch (direction) {
    case RelaxDirection::RIGHT:
      game_->Right();
      break;
    case RelaxDirection::LEFT:
      game_->Left();
      break;
    case RelaxDirection::DOWN:
      game_->Down();
      break;
    case RelaxDirection::UP:
      game_->Up();
      break;
  }
  
}

void Relax::TestDirection() {
  auto direction = ParseDirection();
  switch (direction) {
    case RelaxDirection::RIGHT:
      ui_relax_update_direction("右 >>");
      break;
    case RelaxDirection::LEFT:
      ui_relax_update_direction("左 <<");
      break;
    case RelaxDirection::DOWN:
      ui_relax_update_direction("下 vv");
      break;
    case RelaxDirection::UP:
      ui_relax_update_direction("上 ^^");
      break;
    case RelaxDirection::CENTER:
      ui_relax_update_direction("中 ~~");
      break;
  }
}

RelaxDirection Relax::ParseDirection() {
  if (context()->frame().imu().Update(100, &angle_)) {
    if (angle_.roll > IMU_DEFALUT_VALUE_RIGHT) {
      return RelaxDirection::RIGHT;
    } else if (angle_.roll < IMU_DEFALUT_VALUE_LEFT) {
      return RelaxDirection::LEFT;
    }
    if (angle_.pitch >= IMU_DEFALUT_VALUE_DOWN) {
      return RelaxDirection::DOWN;
    } else if (angle_.pitch <= IMU_DEFALUT_VALUE_UP) {
      return RelaxDirection::UP;
    }else{
      return RelaxDirection::CENTER;
    }
  }
  return RelaxDirection::UNKNOW;
}

void Relax::OnAction(AppAction action) {
  switch (action) {
    case AppAction::ACT:
      if (game_ == nullptr) {
        if (book_ == RelaxBook::SNAKE)
          game_ = new Snake(context()->frame().display().tft());
        else
          game_ = new SpaceShoot(context()->frame().display().tft());
        game_->Init();
      }
      game_->Start();
      break;

    case AppAction::LEFT:
      if (game_ == nullptr) {
        if (book_ == RelaxBook::SNAKE)
          book_ = RelaxBook::SPACESHOOT;
        else
          book_ = RelaxBook::SNAKE;
        ShowTitle(book_);
      }
      break;
      // case AppAction::LEFT:
      //     game_->Down();
      //     break;
      // case AppAction::DOWN:
      //   game_->Down();
      //   break;
      // case AppAction::UP:
      //   game_->Up();
      //   break;
      // case AppAction::RIGHT:
      //   game_->Right();
      //   break;
  };
}

void Relax::ShowTitle(RelaxBook book) {
  if (book == RelaxBook::SNAKE) {
    ui_relax_update_game("贪食蛇");
  } else {
    ui_relax_update_game("小蜜蜂");
  }
}