/**
 * @file crazy_fm.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief  Boardcasting
 * @version 1.0
 * @date 2022-08-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <WString.h>

#include <vector>

#include "../app_contract.h"
#include "framework/system/speaker_listener.h"
#include "keychain/kc_crazyfm.h"

class CrazyFM : public APP, public SpeakerListener {
 private:
  const char* kTag = "CrazyFM";
  bool is_playing_ = false;
  std::vector<CrazyFMChannel> channels_;
  int8_t fm_idx_;

 private:
  void ShowChannel(int8_t idx);
  void SwitchChannel(bool next);
  void Play();
  void Stop();
  // void ReflashVolumeUI();
  void SetPlayingEffect(bool flag);

 public:
  CrazyFM();

 public:
  // APP
  void OnLaunch() override;
  void OnExitApp() override;
  void OnAction(AppAction action) override;
  void OnAssistantState(bool on) override;

  // SpeakerListener
  void OnAudioFinish() override;
};

// english

// 获取音源方法https://www.qingting.fm/
//  https://files.51voa.cn/202208/endangered-south-african-penguins-driven-away-by-shipping-noise.mp3
//  清晨音乐台 https://lhttp.qtfm.cn/live/4915/64k.mp3
