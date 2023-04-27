/**
 * @file speaker_context.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief SpeakerContext
 * @version 0.1
 * @date 2023-02-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include "../system/speaker.h"
#include "tools/crazy_log.h"

template <class T>
class SpeakerContext {
 private:
  Speaker* speaker_ = nullptr;

 protected:
  Speaker& speaker() { return *speaker_; }

  bool ContainSpeaker() {
    if (speaker_ == nullptr) {
      CrazyLog::e("SpeakerContext", "is null!");
      return false;
    }
    return true;
  }

 public:
  T& SetSpeaker(Speaker& speaker) {
    speaker_ = &speaker;
    return (T&)(*this);
  }
};