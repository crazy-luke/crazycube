/**
 * @file tts.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief TTS url
 * @version 1.0
 * @date 2022-09-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <WString.h>

#include "framework/context/speaker_context.h"

class TTS: public SpeakerContext<TTS> {
 private:
  const char* kTag = "TTS";
  String tts_voice_ = "";
  String token_;

 public: 
  TTS(String token);
  String GetTTSURL(String text);  
  //retry_times: TTS 播放失败重试次数，defalut: 0
   bool PlayTTS(String text, uint8_t retry_times = 0);
};