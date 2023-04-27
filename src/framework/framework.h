/**
 * @file framework.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief
 * @version 1.0
 * @date 2022-08-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "./system/button.h"
#include "./system/display.h"
#include "./system/gesture_senor.h"
#include "./system/imu.h"
#include "./system/led.h"
#include "./system/mic/mic.h"
#include "./system/network.h"
#include "./system/speaker.h"
#include "./system/sys.h"

class Framework {
 private:
  Display display_;
  Network network_;
  Led led_;
  Speaker speaker_;
  GRS gesture_;
  IMU imu_;
  Mic mic_;
  Button btn_;

 public:
  Display& display();
  Network& network();
  Led& led();
  Speaker& speaker();
  GRS& gesture();
  IMU& imu();
  Mic& mic();
  Button& btn();
};

class Frame : public Framework {
 public:
  Frame(Frame const&) = delete;
  Frame& operator=(Frame const&) = delete;
  static Frame& instance() {
    static Frame instance_;
    return instance_;
  }

 private:
  Frame() { CrazyLog::d(kTag, "constructor!"); }
  const char* kTag = "Frame";

 public:
  // 调节音量并保存
  // turn_up : true up, false down
  // step: 调节幅度
  uint8_t TurnVolumeWithStore(bool turn_up, uint8_t step = 2);
  // 调节屏幕亮度并保存
  // turn_up : true up, false down
  uint8_t TurnDisplayBrightnessWithStore(bool turn_up);
  // 调节 Led 灯珠亮度并保存
  // turn_up : true up, false down
  uint8_t TurnLedBrightnessWithStore(bool turn_up);
  // 切换 Led 灯珠状态并保存
  LedState SwitchLedStateWithStore();
  // 恢复 Led 灯珠状态
  LedState ResotreLedStateWithStore();
  //初始化 MPU
  bool InitIMUWithNotice();
  
  // 重启OS
  void RestartOS();
};