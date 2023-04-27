/**
 * @file kc_crazyfm.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief  播客持久化数据 crazyfm data persistence
 * @version 1.0
 * @date 2022-08-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "kc_.h"

struct CrazyFMChannel {
  String title;
  String url;
};

struct CrazyFMInfo {
  CrazyFMChannel channel1;
  CrazyFMChannel channel2;
  CrazyFMChannel channel3;
};

class CrazyFMInfoKeyChain {
 public:
  void Save(CrazyFMInfo info) {
    Preferences pref;
    pref.begin(KC_NAMESPACE_APP);
    pref.putString("fm_title_1", info.channel1.title);
    pref.putString("fm_url_1", info.channel1.url);
    pref.putString("fm_title_2", info.channel2.title);
    pref.putString("fm_url_2", info.channel2.url);
    pref.putString("fm_title_3", info.channel3.title);
    pref.putString("fm_url_3", info.channel3.url);
    pref.end();
  };

  CrazyFMInfo Read() {
    Preferences pref;
    pref.begin(KC_NAMESPACE_APP);
    CrazyFMInfo info = {.channel1 = {.title = pref.getString("fm_title_1", ""),
                                     .url = pref.getString("fm_url_1", "")},
                        .channel2 = {.title = pref.getString("fm_title_2", ""),
                                     .url = pref.getString("fm_url_2", "")},
                        .channel3 = {.title = pref.getString("fm_title_3", ""),
                                     .url = pref.getString("fm_url_3", "")}};
    pref.end();
    return info;
  };
};
