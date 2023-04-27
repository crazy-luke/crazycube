/**
 * @file assistant_speech.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief  Audio AssistantSpeech
 * @version 1.0
 * @date 2022-09-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <lvgl.h>

#include <memory>
#include <mutex>

#include "assistant_context.h"
#include "audio_asr_tts/audio_processor/token_store.h"
#include "audio_asr_tts/speech_recognise.h"
#include "framework/system/speaker.h"
#include "nlp/intent_processor.h"

#define AUDIO_RES_READY "/audio/ready.mp3"
#define AUDIO_RES_MESSAGE "/audio/message.mp3"

enum class AsstLaunchResult { SUCCESS, STOPPED, TOKEN_EXPIRED };

class AssistantSpeech : public SpeakerListener,
                        public ContextAssistantSafeHolder {
 private:
  const char *kTag = "AssistantSpeech";
  lv_obj_t *screen_ = nullptr;
  SessionResult last_session_;
  TaskHandle_t task_handle_speech_ = nullptr;
  TaskHandle_t task_handle_token_ = nullptr;
  bool allow_record_;  // 是否允许录音

  TokenStore token_store_;
  SpeechLanguage speech_language_;
  uint16_t speech_max_time_;

 public:
  AssistantSpeech();
  ~AssistantSpeech();

  void Start();
  void Stop();

  // 唤起 Assistant
  AsstLaunchResult OnLaunch(SpeechLanguage speech_language,
                            uint16_t speech_max_time,
                            SessionType session_type = SessionType::UNKNOWN);  
  void OnExit(bool play_notice = false);                // 关闭 Assistant
  bool IsForegroundWorking();                           // 前台运行中
  bool IsReady();  // 任务启动中 可以唤醒
  void DoSpeechResultByAction();  //手动触发SpeechResult;

 private:
  void OnSpeechResult(String text);
  void OnAudioFinish();

  bool StartRecordingState();
  void PauseRecordingState();
  void StopRecordingState();
  void ClearLastSession();

 private:
  // token task
  std::mutex lock_task_token_;
  friend void AssistantTokenTask(void *param);
  bool DoAssistantTokenTaskWithLock();
  void StartTokenTask();
  void StopTokenTask();

  // speech task
  std::mutex lock_task_speech_;
  friend void AssistantSpeechTask(void *param);
  void DoAssistantSpeechTaskWithLock();
  void SpeechProcess();
  void StartSpeechTask();
  void StopSpeechTask();
};