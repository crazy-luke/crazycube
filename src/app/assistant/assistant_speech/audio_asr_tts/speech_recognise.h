/**
 * @file SpeechRecognise.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 语音信号送往 AI 服务器 识别指令。 当前使用: 百度语音识别服务。
 * @version 1.0
 * @date 2022-09-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <WString.h>
#include "speech_specs.h"

class I2SSampler;
class ChunkedUploader;
class RingBufferAccessor;

class SpeechRecognise {
 private:
  const char *kTag = "SpeechRecognise";
  I2SSampler *sample_provider_;
  unsigned long start_time_;
  unsigned long elapsed_time_;
  
  int last_audio_position_;
  ChunkedUploader *m_speech_recogniser = nullptr;
  // crazyadam: make sure free memory, task may delete
  RingBufferAccessor *reader_temp_ = nullptr;  
  uint16_t speech_max_time_;  //最大收音时长

 private:
  void LoadServerToken();

 public:
  SpeechRecognise(I2SSampler *sample_provider);
  ~SpeechRecognise();

  bool Enter(String token, SpeechLanguage language, uint16_t speech_max_time);
  /**
   * @param msg recognise msg
   * @param force_result just finish  and get result
   * @return true  finish
   */
  bool Run(String &msg, bool force_result);
  void Exit();
};
