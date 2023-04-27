
#include "gesture_senor.h"

#include <I2Cdev.h>
#include <paj7620.h>
#include <stdint.h>

#include "tools/crazy_log.h"

bool GRS::Init(uint16_t data_interval) {
  CrazyLog::d(kTag, "init");
  set_data_interval(data_interval);
  Wire.begin(GRS_I2C_SDA, GRS_I2C_SCL);
  Wire.setClock(400000);
  int retry = 0;
  uint8_t error = 0;
  do {
    retry++;
    error = paj7620Init();
    if (retry > 3) break;
  } while (error);

  if (error) {
    CrazyLog::e(kTag, "init error code: %d", error);
    return false;
  }

  CrazyLog::d(kTag, "Gesture start...");
  return true;
}

#ifdef GRS_INVERSION

GestureAction GRS::GetAction() {
  GestureAction action = GestureAction::NONE;
  // if (!g_data_ready) {
  //   return action;
  // }
  uint8_t data = 0, data1 = 0, error;
  error = paj7620ReadReg(0x43, 1, &data);
  if (!error) {
    switch (data) {
      case GES_RIGHT_FLAG:
        CrazyLog::d(kTag, "DOWN");
        action = GestureAction::DOWN;
        break;
      case GES_LEFT_FLAG:
        CrazyLog::d(kTag, "UP");
        action = GestureAction::UP;
        break;
      case GES_UP_FLAG:
        CrazyLog::d(kTag, "RIGHT");
        action = GestureAction::RIGHT;
        break;
      case GES_DOWN_FLAG:
        CrazyLog::d(kTag, "LEFT");
        action = GestureAction::LEFT;
        break;
      case GES_FORWARD_FLAG:
        CrazyLog::d(kTag, "FORWARD");
        action = GestureAction::FORWARD;
        break;
      case GES_BACKWARD_FLAG:
        CrazyLog::d(kTag, "Backward");
        action = GestureAction::BACKWARD;
        break;
      case GES_CLOCKWISE_FLAG:
        CrazyLog::d(kTag, "Clockwise");
        action = GestureAction::CLOCKWISE;
        break;
      case GES_COUNT_CLOCKWISE_FLAG:
        CrazyLog::d(kTag, "anti-clockwise");
        action = GestureAction::ANTICLOCKWISE;
        break;
      default:
        paj7620ReadReg(0x44, 1, &data1);
        if (data1 == GES_WAVE_FLAG) {
          CrazyLog::d(kTag, "wave");
          action = GestureAction::WAVE;
        }
    }
  }
  // g_data_ready = false;
  last_update_time_ = millis();
  return action;
}

#else

GestureAction GRS::GetAction() {
  GestureAction action = GestureAction::NONE;
  // if (!g_data_ready) {
  //   return action;
  // }
  uint8_t data = 0, data1 = 0, error;
  error = paj7620ReadReg(0x43, 1, &data);
  if (!error) {
    switch (data) {
      case GES_RIGHT_FLAG:
        CrazyLog::d(kTag, "UP");
        action = GestureAction::UP;
        break;
      case GES_LEFT_FLAG:
        CrazyLog::d(kTag, "DOWN");
        action = GestureAction::DOWN;
        break;
      case GES_UP_FLAG:
        CrazyLog::d(kTag, "LEFT");
        action = GestureAction::LEFT;
        break;
      case GES_DOWN_FLAG:
        CrazyLog::d(kTag, "RIGHT");
        action = GestureAction::RIGHT;
        break;
      case GES_FORWARD_FLAG:
        CrazyLog::d(kTag, "FORWARD");
        action = GestureAction::FORWARD;
        break;
      case GES_BACKWARD_FLAG:
        CrazyLog::d(kTag, "Backward");
        action = GestureAction::BACKWARD;
        break;
      case GES_CLOCKWISE_FLAG:
        CrazyLog::d(kTag, "Clockwise");
        action = GestureAction::CLOCKWISE;
        break;
      case GES_COUNT_CLOCKWISE_FLAG:
        CrazyLog::d(kTag, "anti-clockwise");
        action = GestureAction::ANTICLOCKWISE;
        break;
      default:
        paj7620ReadReg(0x44, 1, &data1);
        if (data1 == GES_WAVE_FLAG) {
          CrazyLog::d(kTag, "wave");
          action = GestureAction::WAVE;
        }
    }
  }
  // g_data_ready = false;
  last_update_time_ = millis();
  return action;
}
#endif

bool GRS::IsDataReady(){
  return (millis() - last_update_time_ >= data_interval_);  //millis 溢出暂不处理
}


void GRS::set_data_interval(uint16_t data_interval){
  data_interval_ = data_interval;
}