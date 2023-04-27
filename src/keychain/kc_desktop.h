/**
 * @file kc_desktop.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief  Desktop APP keychain
 * @version 1.0
 * @date 2022-08-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "kc_.h"

struct DesktopInfo {
  String sign;
  bool auto_screensaver;
};

class DesktopKeyChain {
 public:
  void Save(DesktopInfo info) {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    pref.putString("desk_sign", info.sign);
    pref.putBool("auto_screensaver", info.auto_screensaver);
    pref.end();
  }

  DesktopInfo Read() {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    DesktopInfo info = {
        .sign = pref.getString("desk_sign", ""),
        .auto_screensaver = pref.getBool("desk_screensaver", true),
    };
    pref.end();
    return info;
  };
};
