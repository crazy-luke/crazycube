/**
 * @file led_context.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief LedContext
 * @version 0.1
 * @date 2023-02-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include "../system/led.h"
#include "tools/crazy_log.h"

template <class T>
class LedContext {
 private:
  Led* led_ = nullptr;

 protected:
  Led& led() {
    ContainLed();
    return *led_;
  }

  bool ContainLed() {
    if (led_ == nullptr) {
      CrazyLog::e("LedContext", "is null!");
      return false;
    }
    return true;
  }

 public:
  T& SetLed(Led& led) {
    led_ = &led;
    return (T&)(*this);
  }
};