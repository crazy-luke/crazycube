/**
 * @file kc_wifi.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief Save Wifi SSID ...
 * @version 1.0
 * @date 2022-08-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "kc_.h"

struct WifiInfo {
  String ssid;
  String password;
};

class WifiInfoKeyChain {
 public:
  void Save(WifiInfo info) {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    pref.putString("wifi-ssid", info.ssid);
    if(info.password.compareTo(KC_SECRET_HINT) != 0)
      pref.putString("wifi-password", info.password);
    pref.end();
  };

  WifiInfo Read() {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    WifiInfo info = {.ssid = pref.getString("wifi-ssid", ""),
                     .password = pref.getString("wifi-password", "")};
    pref.end();
    return info;
  };


  WifiInfo ReadSecurity() {
    auto info =  Read();
    if(!info.password.isEmpty()) info.password = KC_SECRET_HINT;
    return info;
  };

};