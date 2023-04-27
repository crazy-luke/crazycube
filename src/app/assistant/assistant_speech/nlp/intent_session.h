#pragma once

#include <WString.h>

enum class SessionType {
  UNKNOWN = 0,
  MESSAGE,        // 消息:　单次会话
  SERISE_OPENAI,  // OPENAI 持续会话
  SERISE_WEATHER  // 天气持续对话 ,包含上下文 weather_nlp [[Deprecated("体验一般")]] 
};

struct SessionResult {
  bool success;              // 是否成功
  String tts;                // 等待播放的tts
  SessionType session_type;  // 会话类型
  String session_series;     // 持续对话
  uint8_t session_times;     // 持续会话次数
};

enum class SessionIntent {
  UNKNOWN,
  CLOCK,
  FANS_BL,
};
