#pragma once

#include "kc_.h"

#define ASST_NLP_NORMAL 0
#define ASST_NLP_OPENAI 1

struct AssistantInfo {
  String asst_id;
  String asst_secret;
  int16_t asst_tts_voice;
  int16_t asst_nlp;
  String asst_openai_key;
};

class AssistantChain {
 public:
  void Save(AssistantInfo info) {
    Preferences pref;
    pref.begin(KC_NAMESPACE_APP);
    pref.putString("asst_id", info.asst_id);
    pref.putString("asst_secret", info.asst_secret);
    pref.putShort("asst_tts_voice", info.asst_tts_voice);
    pref.putShort("asst_nlp", info.asst_nlp);
    pref.putString("asst_openai_key",info.asst_openai_key);
    pref.end();
  };

  AssistantInfo Read() {
    Preferences pref;
    pref.begin(KC_NAMESPACE_APP);
    AssistantInfo info = {
        .asst_id = pref.getString("asst_id", ""),
        .asst_secret = pref.getString("asst_secret", ""),

         //建议中文用 度小美=0，度逍遥（基础）=3
         //英文用 度逍遥（精品）=5003，度小鹿=5118 
        .asst_tts_voice = pref.getShort("asst_tts_voice", 3),
        .asst_nlp = pref.getShort("asst_nlp", ASST_NLP_NORMAL),
        .asst_openai_key = pref.getString("asst_openai_key",  ""),
    };
    pref.end();
    return info;
  };
};


