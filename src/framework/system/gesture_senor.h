/**
 * @file gesture_senor.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 手势传感器   Gesture Recognition Sensor (PAJ7620)
 * @version 1.0
 * @date 2022-07-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <Arduino.h>

#define GRS_I2C_SDA 32
#define GRS_I2C_SCL 33


// #define GRS_INVERSION   //手势模块颠倒

enum class GestureAction {
  NONE = 0,      /**< No gesture */
  UP,            /**< Upwards gesture */
  DOWN,          /**< Downward gesture */
  LEFT,          /**< Leftward gesture */
  RIGHT,         /**< Rightward gesture */
  FORWARD,       /**< Forward gesture */
  BACKWARD,      /**< Backward gesture */
  CLOCKWISE,     /**< Clockwise circular gesture */
  ANTICLOCKWISE, /**< Anticlockwise circular gesture */
  WAVE           /**< Wave gesture */
};

class GRS {
 private:
  const char* kTag = "GRS";
  unsigned long last_update_time_ = 0;
  uint16_t data_interval_ = 500;  // 默认数据间隔

 public:
  bool Init(uint16_t data_interval);
  GestureAction GetAction();
  bool IsDataReady();
  void set_data_interval(uint16_t interval);  // 数据间隔
};
