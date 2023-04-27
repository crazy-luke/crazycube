#include "framework.h"

#include "keychain/kc_state.h"

Display& Framework::display() { return display_; }
Network& Framework::network() { return network_; }
Led& Framework::led() { return led_; }
Speaker& Framework::speaker() { return speaker_; }
GRS& Framework::gesture() { return gesture_; }
IMU& Framework::imu() { return imu_; }
Mic& Framework::mic() { return mic_; }
Button& Framework::btn() { return btn_; }

uint8_t Frame::TurnVolumeWithStore(bool turn_up, uint8_t step) {
  CrazyLog::d(kTag, "TurnVolumeWithStore");
  StateKeyChain kc;
  uint8_t pre_value = kc.Read().volume;
  uint8_t new_value = 0;
  if (turn_up) {  // 提高音量
    new_value = std::min(pre_value + step, MAX_VOLUME);
  } else {  // 降低音量
    new_value = std::max(pre_value - step, 0);
  }
  CrazyLog::d(kTag, "TurnValue volume form %d to %d", pre_value, new_value);
  speaker().SetVolume(new_value);
  kc.UpdateVolume(new_value);
  return new_value;
}

uint8_t Frame::TurnDisplayBrightnessWithStore(bool turn_up) {
  CrazyLog::d(kTag, "TurnDisplayBrightnessWithStore");
  StateKeyChain kc;
  int pre_value = kc.Read().brightness;
  int new_value = 0;
  if (turn_up) {
    new_value = std::min(pre_value + 10, MAX_BRIGHTNESS);
  } else {
    new_value = std::max(pre_value - 10, 10);  // Do not set to zero
  }
  CrazyLog::d(kTag, "TurnValue brightness form %d to %d", pre_value, new_value);
  display().SetBrightness(new_value);
  kc.UpdateBrightness(new_value);
  return new_value;
}

uint8_t Frame::TurnLedBrightnessWithStore(bool turn_up) {
  CrazyLog::d(kTag, "TurnLedBrightnessWithStore");
  // set light brightness
  StateKeyChain kc;
  int pre_value = kc.Read().ledlight;
  int new_value = 0;
  if (turn_up) {
    new_value = std::min(pre_value + 25, MAX_LED_LIGHT);
  } else {
    new_value = std::max(pre_value - 25, 25);  // Do not set to zero
  }
  CrazyLog::d(kTag, "TurnValue led_light form %d to %d", pre_value, new_value);
  led().SetBrightness(new_value);
  kc.UpdateLedLight(new_value);
  return new_value;
}

LedState Frame::SwitchLedStateWithStore(){
  CrazyLog::d(kTag, "SwitchLedStateWithStore");
  auto state = led().SwitchState();
  StateKeyChain().UpdateLedState((uint8_t)state);
  return state;
}

LedState Frame::ResotreLedStateWithStore(){
  auto state = static_cast<LedState>(StateKeyChain().Read().ledstate);
  led().SetState(state);
  return state;
}

void Frame::RestartOS() {
  CrazyLog::w(kTag, "RestartOS");
  display().CleanTips();
  display().ShowSubTipsDisplay("立方豆重启中...");
  ESP.restart();
}

bool Frame::InitIMUWithNotice() {
  CrazyLog::d(kTag, "InitIMUWithNotice");
  if(!imu().ready()){
    display().ShowSubTipsDisplay("初始化陀螺仪\n请稍等...");
    imu().Init();
    display().CleanTips();
  }

  return imu().ready();
}