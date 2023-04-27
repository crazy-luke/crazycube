/**
 * @file kc_device.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief  Device data persistence
 * @version 1.0
 * @date 2022-08-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "kc_.h"

struct DeviceInfo {
  // String name;
  uint8_t color_r;
  uint8_t color_g;
  uint8_t color_b;
  bool lock_gesutre;
};

class DeviceKeyChain {
 public:
  void save(DeviceInfo info) {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    // pref.putString("name", info.name);
    pref.putUShort("color_r", info.color_r);
    pref.putUShort("color_g", info.color_g);
    pref.putUShort("color_b", info.color_b);
    pref.putBool("lock_gesutre", info.lock_gesutre);
    pref.end();
  }

  DeviceInfo Read() {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    DeviceInfo info = {
        // .name = pref.getString("name", ""),
        .color_r = pref.getUShort("color_r", 0),
        .color_g = pref.getUShort("color_g", 255),
        .color_b = pref.getUShort("color_b", 0),
        .lock_gesutre = pref.getBool("lock_gesutre", false),
    };
    pref.end();
    return info;
  };
};
