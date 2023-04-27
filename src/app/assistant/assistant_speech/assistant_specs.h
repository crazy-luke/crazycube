/**
 * @file assistant_specs.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief Assistant Specs
 * @version 0.1
 * @date 2023-01-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "audio_asr_tts/speech_specs.h"
#include "nlp/intent_session.h"


class AssistantSpecs {
  public:
    virtual bool OnAssistantSpecs(SpeechLanguage& language, uint16_t& speech_max_time, SessionType& type) = 0;
};
