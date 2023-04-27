/**
 * @file kc_state.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief  State data persistence
 * @version 1.0
 * @date 2022-08-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "kc_.h"

struct StateInfo {
  uint8_t volume;
  uint8_t brightness;
  uint8_t ledlight;
  uint8_t ledstate;
  bool keyboard;
};

class StateKeyChain {
 public:
  void UpdateVolume(uint8_t volume) {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    pref.putShort("volume", volume);
    pref.end();
  };

  void UpdateBrightness(uint8_t brightness) {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    pref.putShort("brightness", brightness);
    pref.end();
  };

  void UpdateLedLight(uint8_t light) {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    pref.putShort("ledlight", light);
    pref.end();
  };

  void UpdateLedState(uint8_t state) {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    pref.putShort("ledstate", state);
    pref.end();
  }

  void UpdateKeyboard(bool allowed) {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    pref.putBool("keyboard", allowed);
    pref.end();
  };


  StateInfo Read() {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    StateInfo info = {
        .volume = (uint8_t)pref.getShort("volume", 12),          // 0 ~ 22
        .brightness = (uint8_t)pref.getShort("brightness", 100),  // 0 ~ 100
        .ledlight = (uint8_t)pref.getShort("ledlight", 100), // 0~255
        .ledstate = (uint8_t)pref.getShort("ledstate", 0), 
        .keyboard = pref.getBool("keyboard", false),
    };
    pref.end();
    return info;
  };
};