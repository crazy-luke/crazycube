#include "speaker.h"

#include <algorithm> 

#include "tools/crazy_log.h"
#include "sys.h"
#include "keychain/kc_state.h"

Speaker::Speaker(/* args */) {
  audio_.setPinout(SPEAKER_I2S_SCK, SPEAKER_I2S_LRC, SPEAKER_I2S_DATA);
  audio_.setConnectionTimeout(8000, 8000);
  audio_.setBufsize(0, SPEAKER_PSRAM_BUF);  // 300K psram
  volume_ = audio_.getVolume();
  volume_boost_ = volume_;
}

Speaker::~Speaker() {
  CrazyLog::d(kTag, "~release");
  FinishAudioTask();
}

bool Speaker::PlayStream(const char* url, uint8_t retry_times) {
  CrazyLog::d(kTag, "PlayStream");
  CrazyLog::d(kTag, "retry_times %d",retry_times);
  Stop();
  ResumeVolume();

  if(retry_times > SPEAKER_RETRY_TIME_MAX_LIMIT) {
    CrazyLog::w(kTag, "oops~ max retry time is %d", SPEAKER_RETRY_TIME_MAX_LIMIT);
    retry_times = SPEAKER_RETRY_TIME_MAX_LIMIT;
  }   
  uint8_t try_time = 0;
  bool success = false;
  while(try_time ++ <= (retry_times+1) && !success){
    CrazyLog::ram("before PlayStream");
    CrazyLog::w(kTag, "try time: %d", try_time);
    success = audio_.connecttohost(url);
  }
  if(success) StartAudioTask(10);
  return success;
}

void Speaker::FinishAudioTask() {
  if (task_handle_ != NULL) {
    CrazyLog::d(kTag, "FinishAudioTask");
    vTaskDelete(task_handle_);
    task_handle_ = NULL;
  }
}

void AudioTask(void* param) {
  const char* kTag = "Speaker";
  CrazyLog::d(kTag, "AudioTask");
  Audio* audio = (Audio*)param;
  const TickType_t kMaxBlockTime = pdMS_TO_TICKS(5000);
  uint32_t ulNotificationValue = 0;
  while (true) {
    CrazyLog::d(kTag, "do play");
    while (audio->isRunning()) {
      audio->loop();
      vTaskDelay(1);
    }
    CrazyLog::d(kTag, "waiting");
    SpeakerListenerContainer::instance().OnAudioFinishLintener();
    SpeakerListenerContainer::instance().Clear();
    ulNotificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    if(ulNotificationValue > 0){
      CrazyLog::d(kTag, "receive ulNotificationValue:%d",ulNotificationValue);
      vTaskDelay(ulNotificationValue);
    }
  }
}

void Speaker::StartAudioTask(uint32_t delay) {
  CrazyLog::d(kTag, "StartAudioTask");
  if (task_handle_ != nullptr) {
    xTaskNotify(task_handle_, delay, eSetBits);
    CrazyLog::d(kTag, "notify audio task");
    return;
  }
  xTaskCreatePinnedToCore(AudioTask, "AudioTask", 1024*4, &audio_,
                          TASK_PRIORITY_SPEAKER, &task_handle_,
                          CORE_0);
}

void Speaker::PlayFile(const char* path){
  PlayFile(path,false);
}

void Speaker::PlayFile(const char* path, bool weak_influence) {
  CrazyLog::d(kTag, "playFile");
  if(weak_influence && audio_.isRunning())
    return;
  ResumeVolume();
  Stop();
  audio_.connecttoFS(SPIFFS, path);
  StartAudioTask(10);
}

void Speaker::Stop() {
  if (audio_.isRunning()) {
    CrazyLog::d(kTag, "Stop");
    audio_.stopSong();
    vTaskDelay(50);  // buffer time
  }
}

Speaker& Speaker::SetVolume(uint8_t volume) {
  CrazyLog::d(kTag, "setVolume %d", volume);
  volume_ = std::min((int)volume,MAX_VOLUME);
  audio_.setVolume(volume_);
  return *this;
}

uint8_t Speaker::GetCurrentVolume() {
  // return audio_.getVolume();
  return volume_;
}

void Speaker::CleanListener(){
  SpeakerListenerContainer::instance().Clear();
}

void Speaker::ResumeVolume(){
  if(volume_ != volume_boost_) {
    CrazyLog::d(kTag, "ResumeVolume");
    volume_boost_ = volume_;
    SetVolume(volume_);
  }
}

void Speaker::BoostVolume(uint8_t volume){
  CrazyLog::d(kTag, "BoostVolume");
  volume_boost_ = volume_ + volume; 
  audio_.setVolume(volume_boost_);
}