#include "gesture_helper.h"
#include "tools/crazy_log.h"

#define GESTURE_GARD_TIME_LEFT_RIGHT 1000

//左<->右, 手势间隔需要大于 GESTURE_GARD_TIME
bool GestureHelper::ActionFilter(GestureAction action) {
  bool approve = true;
  long cur_gesture_time = millis();
 
  if (action == GestureAction::RIGHT &&
      last_gesture_action_ == GestureAction::LEFT &&
      cur_gesture_time - last_gesture_time_ < GESTURE_GARD_TIME_LEFT_RIGHT) {
    approve = false;
  } else if (action == GestureAction::LEFT &&
             last_gesture_action_ == GestureAction::RIGHT &&
             cur_gesture_time - last_gesture_time_ < GESTURE_GARD_TIME_LEFT_RIGHT) {
    approve = false;
  } 
  
  if (approve) {
    last_gesture_time_ = cur_gesture_time;
    last_gesture_action_ = action;
  } else {
    CrazyLog::d(kTag, "Ooops,  Gesture misjudgement!");
  }

  return approve;
};

SysbarActionConvertResult GestureHelper::ConvertSysbarAction(GestureAction action) {
  SysbarActionConvertResult result;
  switch (action) {
    case GestureAction::UP:
      result.success = true;
      result.action = SysbarAction::UP;
      break;
    case GestureAction::DOWN:
      result.success = true;
      result.action = SysbarAction::DOWN;
      break;
    case GestureAction::LEFT:
      result.success = true;
      result.action = SysbarAction::LEFT;
      break;
    case GestureAction::RIGHT:
      result.success = true;
      result.action = SysbarAction::RIGHT;
      break;
    case GestureAction::CLOCKWISE:
      result.success = true;
      result.action = SysbarAction::CLOCKWISE;
      break;
    case GestureAction::ANTICLOCKWISE:
      result.success = true;
      result.action = SysbarAction::ANTICLOCKWISE;
      break;
    default:
      result.success = false;
  }

  return result;
}

AppActionConvertResult GestureHelper::ConvertAppAction(GestureAction action) {
  AppActionConvertResult result;
  switch (action) {
    case GestureAction::LEFT:
      result.success = true;
      result.action = AppAction::LEFT;
      break;
    case GestureAction::RIGHT:
      result.success = true;
      result.action = AppAction::RIGHT;
      break;
    case GestureAction::UP:
      result.success = true;
      result.action = AppAction::UP;
      break;
    case GestureAction::DOWN:
      result.success = true;
      result.action = AppAction::DOWN;
      break;
    case GestureAction::CLOCKWISE:
      result.success = true;
      result.action = AppAction::ACT;
      break;
    default:
      result.success = false;
  }

  return result;
}
