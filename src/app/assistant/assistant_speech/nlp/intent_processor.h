/**
 * @file intent_processor.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 语言分支处理
 * @version 1.0
 * @date 2022-09-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "../audio_asr_tts/audio_processor/tts.h"
#include "api/api.h"
#include "framework/context/led_context.h"
#include "framework/context/network_context.h"
#include "intent_session.h"

class IntentProcessor : public NetworkContext<IntentProcessor>,
                        public LedContext<IntentProcessor> {
 private:
  const char* kTag = "IntentProcessor";
  String openai_key_;
  int16_t asst_nlp_;

 private:
  //VO: 此版本保留 获取 Bilibili 粉丝数和和本地时间，方便开发者套用
  SessionIntent ParseIntent_V0(String& text);
  SessionResult ProcessFans();
  SessionResult ProcessTime();

 public:
  IntentProcessor();
  IntentProcessor(String openai_key, int16_t asst_nlp);
  SessionResult processIntent(String text, SessionResult last_session);
};
