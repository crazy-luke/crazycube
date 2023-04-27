/**
 * @file kc_os_mode.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief  RunMode data persistence
 * @version 1.0
 * @date 2022-08-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "kc_.h"

#define OS_MODE_APPOS 1      // OS 模式
#define OS_MODE_SIMULATOR 2  // SIMULATOR 模式
#define OS_MODE_CODELAB 3    // CodeLab 模式

class OSModeKeyChain {
 public:
  // 运行模式
  byte os_mode() {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    byte mode = pref.getShort("os_mode", OS_MODE_APPOS);
    pref.end();
    return mode;
  };

  // 更新运行模式
  void UpdateRunMode(byte os_mode) {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    pref.putShort("os_mode", os_mode);
    pref.end();
  }

  // 最后一次使用的APP
  String app_id() {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    String app_id = pref.getString("app_id", "");
    pref.end();
    return app_id;
  };

  // 最后一次使用的APP
  void UpdateAppId(String app_id) {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    pref.putString("app_id", app_id);
    pref.end();
  }
};