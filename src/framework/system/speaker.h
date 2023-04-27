/**
 * @file speaker.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief My awsome speaker
 * @version 1.0
 * @date 2022-08-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "Audio.h"
#include "speaker_listener.h"
// CrazyCube-MainBoard v0.3 :  separate Mic_Speaker SCK&LRC

#define SPEAKER_I2S_LRC GPIO_NUM_15
#define SPEAKER_I2S_SCK GPIO_NUM_14
#define SPEAKER_I2S_DATA GPIO_NUM_13

// CrazyCube-MainBoard v0.2
//  #define SPEAKER_I2S_LRC GPIO_NUM_14
//  #define SPEAKER_I2S_SCK GPIO_NUM_27
//  #define SPEAKER_I2S_DATA GPIO_NUM_26

#define MAX_VOLUME 21

#define SPEAKER_RETRY_TIME_MAX_LIMIT 3

class Speaker {
 private:
  const char * kTag = "Speaker";
  Audio audio_ = Audio(false, I2S_DAC_CHANNEL_BOTH_EN, I2S_NUM_1);
  TaskHandle_t task_handle_ = NULL;
  int8_t volume_;
  int8_t volume_boost_;

 private:
  void StartAudioTask(uint32_t delay);
  void FinishAudioTask();
  void ResumeVolume();  //恢复音量
  friend void AudioTask(void *param);

 public:
  Speaker(/* args */);
  ~Speaker();

  void PlayStream();
  /**
   * @brief playfile
   * 
   * @param path filepath
   * @param weak_influence  ture : won`t play file if another audio session is playing
   */
  void PlayFile(const char *path, bool weak_influence);
  void PlayFile(const char *path);
  bool PlayStream(const char *url, uint8_t retry_times = 0);
  void Stop();
  Speaker &SetVolume(uint8_t volume);  // vol 22 steps, 0...21
  uint8_t GetCurrentVolume();

  void CleanListener();
  
  //临时增加 Stream 音量,在Play后调用
  void BoostVolume(uint8_t volume); 
};


#define DEBUG_SPEAKER 0  //开启音频日志 

#if DEBUG_SPEAKER
// optional
void audio_info(const char *info) {
  Serial.print("info        ");
  Serial.println(info);
}
void audio_id3data(const char *info) {  // id3 metadata
  Serial.print("id3data     ");
  Serial.println(info);
}
void audio_eof_mp3(const char *info) {  // end of file
  Serial.print("eof_mp3     ");
  Serial.println(info);
}
void audio_showstation(const char *info) {
  Serial.print("station     ");
  Serial.println(info);
}
void audio_showstreamtitle(const char *info) {
  Serial.print("streamtitle ");
  Serial.println(info);
}
void audio_bitrate(const char *info) {
  Serial.print("bitrate     ");
  Serial.println(info);
}
void audio_commercial(const char *info) {  // duration in sec
  Serial.print("commercial  ");
  Serial.println(info);
}
void audio_icyurl(const char *info) {  // homepage
  Serial.print("icyurl      ");
  Serial.println(info);
}
void audio_lasthost(const char *info) {  // stream URL played
  Serial.print("lasthost    ");
  Serial.println(info);
}
void audio_eof_speech(const char *info) {
  Serial.print("eof_speech  ");
  Serial.println(info);
}
#endif