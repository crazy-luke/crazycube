#include "assistant_speech.h"

#include <SPIFFS.h>
#include <WString.h>
#include <driver/i2s.h>

#include "audio_asr_tts/audio_processor/token_store.h"
#include "audio_asr_tts/audio_processor/tts.h"
#include "framework/framework.h"
#include "framework/system/sys.h"
#include "gui/gui.h"
#include "tools/crazy_log.h"
#include "tools/mutex_helper.h"

#define NOTIFY_ID_ASST_START 12
#define NOTIFY_ID_ASST_PAUSE 13
#define NOTIFY_ID_ASST_EXIT 14
#define NOTIFY_ID_ASST_FORCE_RESULT  15 

#define ASSISTANT_SESSION_MAX_TIME 10

void AssistantTokenTask(void* param) {
  AssistantSpeech* assistant = static_cast<AssistantSpeech*>(param);
  bool success = assistant->DoAssistantTokenTaskWithLock();
  // if token ready start speech
  if (success) assistant->StartSpeechTask();
  assistant->task_handle_token_ = NULL;
  vTaskDelete(NULL);
}

void AssistantSpeechTask(void* param) {
  AssistantSpeech* assistant = static_cast<AssistantSpeech*>(param);
  assistant->context()->OnAssistantReady(true);  // 语音识别任务启动时通知
                                                 // Lock Task before exit
  assistant->DoAssistantSpeechTaskWithLock();
  assistant->context()->OnAssistantReady(false);  // 语音识别任务结束时通知
  assistant->task_handle_speech_ = NULL;
  vTaskDelete(NULL);
}

AssistantSpeech::AssistantSpeech() {}

AssistantSpeech::~AssistantSpeech() {
  Stop();
  CrazyLog::d(kTag, "~released");
}

void AssistantSpeech::Start() {
  token_store_.SetNetwork(context()->frame().network());
  if (token_store_.CheckExpired())
    StartTokenTask();
  else
    StartSpeechTask();
}

void AssistantSpeech::Stop() {
  CrazyLog::d(kTag, "Stop");
  StopRecordingState();
  StopTokenTask();
  StopSpeechTask();
}

AsstLaunchResult AssistantSpeech::OnLaunch(SpeechLanguage speech_language,
                                           uint16_t speech_max_time,
                                           SessionType session_type) {
  CrazyLog::d(kTag, "OnLaunch");
  speech_language_ = speech_language;
  speech_max_time_ = speech_max_time;

  ClearLastSession();
  last_session_.session_type = session_type;

  if (IsForegroundWorking()) {
    CrazyLog::i(kTag, "Already OnLaunch!");
    return AsstLaunchResult::SUCCESS;
  }

  if (token_store_.CheckExpired()) {
    CrazyLog::w(kTag, "token expired");
    return AsstLaunchResult::TOKEN_EXPIRED;
  }

  if (task_handle_speech_ == nullptr) {
    CrazyLog::w(kTag, "speech task is not running");
    return AsstLaunchResult::STOPPED;
  }

  // launch
  context()->OnAssistantState(true);  // 通知 OS ，AI 助手将要开启

  context()->frame().speaker().PlayFile(AUDIO_RES_READY);
  MutexUI::instance().Lock();
  screen_ = ui_init_assistant();
  MutexUI::instance().Unlock();
  allow_record_ = true;  // UI 界面初始化后 允许使用 Mic
  xTaskNotify(task_handle_speech_, NOTIFY_ID_ASST_START, eSetBits);
  return AsstLaunchResult::SUCCESS;
}

void AssistantSpeech::OnExit(bool play_notice) {
  CrazyLog::d(kTag, "OnExit");

  if (!IsForegroundWorking()) {
    StopRecordingState();
    context()->frame().speaker().Stop();
    CrazyLog::d(kTag, "already_exit");
    return;
  }

  StopRecordingState();
  context()->frame().speaker().CleanListener();
  if (play_notice)
    context()->frame().speaker().PlayFile(AUDIO_RES_MESSAGE);
  else
    context()->frame().speaker().Stop();
  context()->OnAssistantState(false);  // 通知AI 助手已经关闭
}

void AssistantSpeech::OnSpeechResult(String text) {
  CrazyLog::d(kTag, "OnSpeechResult");

  if (!text.isEmpty()) CrazyLog::d(kTag, "Speech text_in=%s", text.c_str());

  PauseRecordingState();
  if (text.isEmpty() || !IsForegroundWorking()) {
    CrazyLog::d(kTag,
                text.isEmpty() ? "text is empty " : "not foregroundWorking");
    OnExit();
    return;
  }

  auto session = IntentProcessor()
                     .SetLed(context()->frame().led())
                     .SetNetwork(context()->frame().network())
                     .processIntent(text, last_session_);

  if (!session.tts.isEmpty())
    CrazyLog::d(kTag, "Speech text_out=%s", session.tts.c_str());

  if (!session.success) {  // 没有成功匹配
    OnExit();
  } else if (!session.tts.isEmpty()) {  // 播放 TTS
    bool success = TTS(token_store_.baidu_token())
                       .SetSpeaker(context()->frame().speaker())
                       .PlayTTS(session.tts, 1);
    if (!success || !IsForegroundWorking()) {
      if (!success) CrazyLog::e(kTag, "PlayTTS failed!");
      OnExit();
      return;
    }
    SpeakerListenerContainer::instance().PutListener(this);
    // show wave ui
    if (IsForegroundWorking()) {
      MutexUI::instance().Lock();
      ui_show_mic_assistant(false);
      ui_show_wave_assistant(true);
      MutexUI::instance().Unlock();
    }
  } else if (session.session_type == SessionType::MESSAGE &&
             session.tts.isEmpty()) {  // 静默命令
    OnExit(true);
  } else {
    OnExit();
  }
  last_session_ = session;
}

void AssistantSpeech::OnAudioFinish() {
  CrazyLog::i(kTag, "OnAudioFinish");

  // 一、 持续对话条件
  // 1. 对话屏幕还在
  // 2. 上次会话成功
  // 3. SERISE_XXXX
  // 4. 最大次数
  if (IsForegroundWorking() && last_session_.success &&
      last_session_.session_type == SessionType::SERISE_OPENAI &&
      last_session_.session_times < ASSISTANT_SESSION_MAX_TIME) {
        
    xTaskNotify(task_handle_speech_, NOTIFY_ID_ASST_START, eSetBits);
    // show mic
    if (IsForegroundWorking()) {
      MutexUI::instance().Lock();
      ui_show_mic_assistant(true, false);
      ui_show_wave_assistant(false);
      MutexUI::instance().Unlock();
    }

  } else {
    OnExit(true);
  }
}

bool AssistantSpeech::IsForegroundWorking() { return screen_ != nullptr; }

bool AssistantSpeech::IsReady() { return task_handle_speech_ != NULL; }

void AssistantSpeech::DoSpeechResultByAction(){
  CrazyLog::d(kTag, "DoSpeechResultByAction");
  xTaskNotify(task_handle_speech_, NOTIFY_ID_ASST_FORCE_RESULT, eSetBits);
}
//-------------------------------- SUPPORT -------------------------------

bool AssistantSpeech::StartRecordingState() {
  if (!allow_record_) {
    CrazyLog::d(kTag, "do not allow StartRecordingState");
    return false;
  }
  // 开始录音
  context()->frame().mic().Start(task_handle_speech_);
  if (IsForegroundWorking()) {
    MutexUI::instance().Lock();
    ui_show_mic_assistant(true, true);
    lv_timer_handler();
    MutexUI::instance().Unlock();
  }
  return true;
}

void AssistantSpeech::PauseRecordingState() {
  context()->frame().mic().Suspend(task_handle_speech_);
  if (IsForegroundWorking()) {
    MutexUI::instance().Lock();
    ui_show_mic_assistant(true, false);
    lv_timer_handler();
    MutexUI::instance().Unlock();
  }
}

void AssistantSpeech::StopRecordingState() {
  // 停止当前 speech 任务的 Mic
  context()->frame().mic().Stop(task_handle_speech_);
  if (IsForegroundWorking()) {
    MutexUI::instance().Lock();
    lv_anim_del_all();
    lv_obj_del(screen_);
    MutexUI::instance().Unlock();
    screen_ = nullptr;
    // 退出界面后不允许开启 Mic
    allow_record_ = false;
    xTaskNotify(task_handle_speech_, NOTIFY_ID_ASST_PAUSE, eSetBits);
  }
  // clear session series
  ClearLastSession();
}

void AssistantSpeech::ClearLastSession() {
  last_session_.session_series = "";
  last_session_.session_times = 0;
  last_session_.session_type = SessionType::UNKNOWN;
  last_session_.tts = "";
  last_session_.success = false;
}

//-------------------------------- TASK -------------------------------
// token task work on core 0

bool AssistantSpeech::DoAssistantTokenTaskWithLock() {
  CrazyLog::d(kTag, "DoAssistantTokenTask Start");
  std::lock_guard<std::mutex> l(lock_task_token_);

  bool success = false;
  uint8_t retry_times = 0;
  const TickType_t xMaxBlockTime = pdMS_TO_TICKS(1000 * 10);
  bool token_expired = token_store_.CheckExpired();

  while (token_expired) {
    if (retry_times++ > 4) {
        CrazyLog::d(kTag, "relfash baidu token failed: too many retry time");
        break;
    }
    CrazyLog::d(kTag, "Start to reflash baidu token");
    if (context()->frame().network().IsConnected()) {
      token_store_.ReflashBaiduToken();
      token_expired = token_store_.CheckExpired();
      if (!token_expired) {
        success = true;  // success
        CrazyLog::d(kTag, "baidu ok");
        break;
      }
    }
    CrazyLog::d(kTag, "waiting for reflash baidu token...");
    uint32_t ulNotificationValue = ulTaskNotifyTake(pdTRUE, xMaxBlockTime);
    if (NOTIFY_ID_ASST_EXIT == ulNotificationValue) {
      CrazyLog::d(kTag, "AssistantTokenTask receive exit signal");
      break;
    }
  }
  CrazyLog::d(kTag, "DoAssistantTokenTask exit");
  return success;
}

void AssistantSpeech::StartTokenTask() {
  CrazyLog::d(kTag, "StartTokenTask");
  if (task_handle_token_ != nullptr) {
    CrazyLog::d(kTag, "AssistantTokenTask already started");
    return;
  }
  xTaskCreatePinnedToCore(AssistantTokenTask, "AssistantTokenTask", 1024 * 4,
                          this, TASK_PRIORITY_ASSISTANT, &task_handle_token_,
                          CORE_0);
}

void AssistantSpeech::StopTokenTask() {
  CrazyLog::d(kTag, "StopTokenTask");

  // stop AssistantTokenTask: need lock
  if (task_handle_token_ != nullptr) {
    xTaskNotify(task_handle_token_, NOTIFY_ID_ASST_EXIT, eSetBits);
    CrazyLog::d(kTag, "Waiting for AssistantTokenTask exit");
    { std::lock_guard<std::mutex> l(lock_task_token_); }
    delay(10);
    CrazyLog::d(kTag, "AssistantTokenTask stopped");
  }
}

void AssistantSpeech::DoAssistantSpeechTaskWithLock() {
  CrazyLog::d(kTag, "DoAssistantSpeechTask Start");
  std::lock_guard<std::mutex> l(lock_task_speech_);
  SpeechProcess();
  CrazyLog::d(kTag, "DoAssistantSpeechTask Finish");
}

void AssistantSpeech::SpeechProcess() {
  CrazyLog::d(kTag, "SpeechProcess");

  uint32_t ulNotificationValue;
  while (true) {
    CrazyLog::d(kTag, "SpeechProcess1: waiting for start signal");
    ulNotificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    // 1. exit signal
    if (ulNotificationValue == NOTIFY_ID_ASST_EXIT) {
      CrazyLog::d(kTag, "SpeechProcess1:  receive NOTIFY_ID_ASST_TASK");
      return;
    }
    // 2. ignore other signal except start
    if (ulNotificationValue != NOTIFY_ID_ASST_START) {
      CrazyLog::d(kTag, "SpeechProcess1: ignore signal %d",
                  ulNotificationValue);
      continue;
    }

    CrazyLog::d(kTag, "SpeechProcess1:  do Speech Process");
    auto speech = SpeechRecognise(context()->frame().mic().sampler());

    if (!speech.Enter(token_store_.baidu_token(), speech_language_,
                      speech_max_time_)) {
      speech.Exit();
      OnSpeechResult("");
      continue;
    }

    // start recording
    if (!StartRecordingState()) {
      speech.Exit();
      continue;
    }

    String msg;
    bool force_result = false;
    ui_start_mictimebar_countdown(speech_max_time_);
    
    while (true) {
      // 1. waiting audio sampler signal
      ulNotificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

      // 2. receive not sampler signal
      if (ulNotificationValue != NOTIFY_ID_STATE_I2S_SAMPLER) {
        if (ulNotificationValue == NOTIFY_ID_ASST_EXIT) {
          CrazyLog::d(kTag, "SpeechProcess2: receive NOTIFY_ID_ASST_EXIT");
          return;  // exit
        } else if (ulNotificationValue == NOTIFY_ID_ASST_PAUSE) {
          CrazyLog::d(kTag, "SpeechProcess2: receive NOTIFY_ID_ASST_PAUSE");
          break;  // pause
        } else if(ulNotificationValue == NOTIFY_ID_ASST_FORCE_RESULT) {
          CrazyLog::d(kTag, "SpeechProcess2: receive NOTIFY_ID_ASST_FORCE_RESULT");
          force_result = true;
        }else {
          CrazyLog::d(kTag, "SpeechProcess2: ignore signal %d",
                      ulNotificationValue);
          continue;
        }

      }

      // 3. receive sampler signal
      if (speech.Run(msg, force_result)) {
        // do result if finished
        speech.Exit();
        OnSpeechResult(msg);
        break;
      }
      vTaskDelay(2);  //breath
    }
  }
}

// speech task work on core 1
void AssistantSpeech::StartSpeechTask() {
  CrazyLog::d(kTag, "StartSpeechTask");
  if (task_handle_speech_ != nullptr) {
    CrazyLog::d(kTag, "AssistantSpeechTask already started");
    return;
  }
  xTaskCreatePinnedToCore(AssistantSpeechTask, "AssistantSpeechTask", 1024 * 6,
                          this, TASK_PRIORITY_ASSISTANT, &task_handle_speech_,
                          CORE_1);
}

void AssistantSpeech::StopSpeechTask() {
  CrazyLog::d(kTag, "StopSpeechTask");

  // stop AssistantSpeechTask
  if (task_handle_speech_ != nullptr) {
    xTaskNotify(task_handle_speech_, NOTIFY_ID_ASST_EXIT, eSetBits);
    CrazyLog::d(kTag, "Waiting for AssistantSpeechTask exit");
    { std::lock_guard<std::mutex> l(lock_task_speech_); }
    delay(10);
    CrazyLog::d(kTag, "AssistantSpeechTask stopped");
  }
}