/**
 * @file speaker_listener.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 喇叭监听
 * @version 1.0
 * @date 2022-07-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

class SpeakerListener
{
  public:
     virtual void OnAudioFinish() = 0;
};

class SpeakerListenerContainer {
 private:
  SpeakerListenerContainer(void) {}

 public:
  static SpeakerListenerContainer& instance() {
    static SpeakerListenerContainer instance_;
    return instance_;
  }

 private:
  const char* kTag = "SpeakerListenerContainer";
  SpeakerListener * listener_;  //TODO: use vector

 public:
    void PutListener(SpeakerListener* listener);
    void Clear();
    void OnAudioFinishLintener();
};
