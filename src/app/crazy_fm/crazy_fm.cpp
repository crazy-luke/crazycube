#include "crazy_fm.h"

#include "./gui/gui.h"
#include "framework/framework.h"
#include "keychain/kc_crazyfm.h"
#include "tools/crazy_log.h"

CrazyFM::CrazyFM() {
  fm_idx_ = 0;
  auto info = CrazyFMInfoKeyChain().Read();
  if (info.channel1.url.length() > 0) {
    channels_.push_back(info.channel1);
  }
  if (info.channel2.url.length() > 0) {
    channels_.push_back(info.channel2);
  }
  if (info.channel3.url.length() > 0) {
    channels_.push_back(info.channel3);
  }
}

void CrazyFM::OnLaunch() {
  CrazyLog::d(kTag, "onLaunch");
  lv_obj_t* new_scr = ui_init_CrazyFM();
  ShowChannel(0);
  // ReflashVolumeUI();
  lv_scr_load_anim(new_scr, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 300, 0, false);
}

void CrazyFM::ShowChannel(int8_t idx) {
  if (channels_.size() == 0) {
    ui_setTitle_CrazyFM("No URL!");
    return;
  }

  int8_t channel_count = channels_.size();
  if (idx >= channel_count) {
    idx = 0;
  } else if (idx < 0) {
    idx = channel_count - 1;
  }
  CrazyLog::d(kTag, "ShowChannel %d/%d", idx, channel_count);
  ui_setTitle_CrazyFM(channels_[idx].title.c_str());
  fm_idx_ = idx;
}

void CrazyFM::SwitchChannel(bool next) {
  CrazyLog::d(kTag, "SwitchChannel");
  ui_switch_album(CRAZYFM_COVER_FILEPATH,next);
  int8_t idx = next ? fm_idx_ + 1 : fm_idx_ - 1;
  ShowChannel(idx);
}

void CrazyFM::OnAction(AppAction action) {
  CrazyLog::d(kTag, "onAction %d", action);

  switch (action) {
    case AppAction::LEFT: {
      if (!is_playing_) SwitchChannel(false);
      break;
    }
    case AppAction::RIGHT: {
      if (!is_playing_) SwitchChannel(true);
      break;
    }
    case AppAction::ACT:
      is_playing_ ? Stop() : Play();
      break;
  }
}

void CrazyFM::Play() {
  if (is_playing_) return;
  if (channels_.size() == 0 || channels_.size() <= fm_idx_) {
    CrazyLog::w(kTag, "no data");
    return;
  }
  CrazyLog::d(kTag, "start play");
  ui_setState_crazyFM("连接中...");
  lv_timer_handler();  // relfash ui immediately
  delay(10);

  bool success = context()->frame().speaker().PlayStream(channels_[fm_idx_].url.c_str(), 1);
  if (success) {
    SetPlayingEffect(true);
    SpeakerListenerContainer::instance().PutListener(this); //监听播放状态, 连接成功也可能播放丢失。
  } else {
    ui_setState_crazyFM("播放失败，请重试!");
    CrazyLog::w(kTag, "PlayStream failed!");
  }
}

void CrazyFM::Stop() {
  if (!is_playing_) return;
  CrazyLog::i(kTag, "stop play");
  context()->frame().speaker().Stop();
  SetPlayingEffect(false);
  SpeakerListenerContainer::instance().Clear();
}

void CrazyFM::OnExitApp() {
  CrazyLog::d(kTag, "onExitApp");
  // ui_clear_volume_anim_crazyFM();
  Stop();
  lv_anim_del_all();
  lv_scr_load_anim(context()->home_screen(), LV_SCR_LOAD_ANIM_MOVE_TOP, 300, 0, true);
}

 void CrazyFM::OnAssistantState(bool on) {
    if(on) Stop();
 }

void CrazyFM::SetPlayingEffect(bool flag) {
  CrazyLog::d(kTag, "SetPlayingEffect");
  is_playing_ = flag;
  if (flag) {
    ui_setState_crazyFM("");
    context()->frame().led().SetState(LedState::EFFECT);
  } else {
    ui_setState_crazyFM("已停止");
    context()->frame().ResotreLedStateWithStore();
  }
  ui_showEffect_crazyFM(flag);

}

void CrazyFM::OnAudioFinish() {
  CrazyLog::d(kTag, "OnAudioFinish");
  if(is_playing_) SetPlayingEffect(false);  //关闭播放效果
}