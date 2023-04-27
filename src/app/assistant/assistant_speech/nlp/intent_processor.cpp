#include "intent_processor.h"

#include "keychain/kc_assistant.h"
#include "keychain/kc_device.h"
#include "tools/crazy_log.h"
#include "tools/timer_helper.h"

IntentProcessor::IntentProcessor() {
  auto asst = AssistantChain().Read();
  openai_key_ = asst.asst_openai_key;
  asst_nlp_ = asst.asst_nlp;
}

IntentProcessor::IntentProcessor(String openai_key, int16_t asst_nlp) {
  openai_key_ =  openai_key;
  asst_nlp_ = asst_nlp;
}

SessionResult IntentProcessor::processIntent(String text,
                                             SessionResult last_session) {
  CrazyLog::d(kTag, "processIntent");

#if CRAZY_LOG_YELL  // save memory
  CrazyLog::d(kTag,
              "processIntent, text:%s, last_session: success=%d "
              "session_type=%d, session_series= %s",
              text, last_session.success, last_session.session_type,
              last_session.session_series);
#endif
  SessionIntent cmd = SessionIntent::UNKNOWN;
  
  cmd = ParseIntent_V0(text);
    
  if (cmd == SessionIntent::CLOCK) {
    return ProcessTime();
  } else if (cmd == SessionIntent::FANS_BL) {
    return ProcessFans();
  } 
  return SessionResult{.success = false,
                       .tts = "",
                       .session_type = SessionType::UNKNOWN,
                       .session_series = ""};
}

SessionIntent IntentProcessor::ParseIntent_V0(String& text) {
  CrazyLog::i(kTag, "ParseIntent_V0");

  if (text.indexOf("现在几点") >= 0 || text.indexOf("几点了") >= 0 ||
      text.indexOf("时间") >= 0)
    return SessionIntent::CLOCK;
  if (text.indexOf("粉丝") >= 0) return SessionIntent::FANS_BL;

  return SessionIntent::UNKNOWN;
}

SessionResult IntentProcessor::ProcessTime() {
  CrazyLog::d(kTag, "ProcessTime");
  auto pTM = TimerHelper::GetLocalTime();
  String msg = "现在是北京时间" + String(pTM->tm_hour) + "点" + String(pTM->tm_min) + "分";
  return SessionResult{.success = true,
                       .tts = msg,
                       .session_type = SessionType::MESSAGE,
                       .session_series = "",
                       .session_times = 0};
}


SessionResult IntentProcessor::ProcessFans() {
  CrazyLog::d(kTag, "ProcessFans");
  auto pTM = TimerHelper::GetLocalTime();
  String testId = "1640130126";
  int fans = BilibiliApiN().SetNetwork(network()).GetFansData(testId);
  if (fans > 0) {
    String msg = "现在 UP主 在 Bilibili 的粉丝数是：" + String(fans) + "。";
    return SessionResult{.success = true,
                         .tts = msg,
                         .session_type = SessionType::MESSAGE,
                         .session_series = "",
                         .session_times = 0};
  } else {
    return SessionResult{.success = false,
                         .tts = "",
                         .session_type = SessionType::MESSAGE,
                         .session_series = "",
                         .session_times = 0};
  }
}
