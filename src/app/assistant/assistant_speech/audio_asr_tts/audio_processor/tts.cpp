#include "tts.h"

#include "tools/crazy_log.h"
#include "tools/urlencode.h"
#include "token_store.h"
#include "keychain/kc_assistant.h"

// see https://ai.baidu.com/ai-doc/SPEECH/Qk38y8lrl

TTS::TTS(String token): token_(token) {
  tts_voice_ = AssistantChain().Read().asst_tts_voice;
}

String TTS::GetTTSURL(String text) {
  String url = "http://tsn.baidu.com/text2audio?";

  String cuid = WiFi.macAddress();
  String param = "lan=zh&vol=14&aue=3&ctp=1";
  param += "&per="+tts_voice_;
  param += "&cuid=" + cuid + "&tok=" + token_;
  // param += "&lan=zh&spd=5&vol=5&per=1&aue=3";
 // String body = "tex=" + UrlEncode().Encode(text);
  String body = "tex=" + text;
  String fullURL = url + param + "&" + body;


// #if CRAZY_LOG_YELL  // save memory
  CrazyLog::d(kTag, "fullURL: %s", fullURL.c_str());
// #endif

  return fullURL;
}

bool TTS::PlayTTS(String text, uint8_t retry_times){
  const char *  kTag = "TTS";

  if(token_.isEmpty()){
     CrazyLog::w(kTag, "token empty");
    return false;
  }

   String ttsURL = GetTTSURL(text);
#if CRAZY_LOG_YELL 
   CrazyLog::d(kTag, "PlayTTS:%s", ttsURL.c_str());
#endif
   bool success = speaker().PlayStream(ttsURL.c_str(), retry_times);
  //  if(success && speaker().GetCurrentVolume()>=9) {
  //   //非安静模式下 临时增加音量
  //   speaker().BoostVolume(5);
  //  }
   return success;
}